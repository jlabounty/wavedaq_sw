// SPDX-License-Identifier: GPL-2.0
/*
 * PSI WaveDAQ DMA Packet Scheduler Vivado IP.
 *
 * Driver for DMA Packet Scheduler Vivado IP. The IP writes WaveDAQ packages into memory
 * and updates corresponding descriptors.
 *
 * Vivado DMA Packet Scheduler IP and documentation available at
 * <https://bitbucket.org/twavedaq/wavedaq_fw_dcb/src/master/dcb_vivado_hw/ip_repo/dma_packet_scheduler_v1_0/>
 *
 * 2020 Elmar Schmid <elmar.schmid@psi.ch>
 */

#include <linux/slab.h>
#include <linux/module.h>
#include <linux/property.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/io.h>
#include <linux/dmapool.h>
#include <linux/dma-mapping.h>
#include <linux/log2.h>
#include <linux/list.h>
#include <linux/interrupt.h>
#include <linux/poll.h>
#include <asm/uaccess.h>
#include "dma_packet_scheduler_v1_0.h"

/* ACQCONF Registers - General */
#define DPS_REG_GCFG                  0x000
#define DPS_REG_GCFG_BIT_ENA          BIT(0)
#define DPS_REG_GCFG_BIT_IRQENA       BIT(8)
#define DPS_REG_GSTAT                 0x004
#define DPS_REG_IRQVEC                0x010
#define DPS_REG_IRQENA                0x014
#define DPS_REG_SLTENA                0x020
/* ACQCONF Registers - Per Stream */
#define DPS_REG_LASTWIN(n)            (0x200+0x04*(n))
/* CTXMEM for Stream n */
#define DPS_CTX_SCFG(n)               (0x1000+0x20*(n))
#define DPS_CTX_SCFG_LSB_WINCNT       16
#define DPS_CTX_SCFG_MSB_WINCNT       20
#define DPS_CTX_SCFG_LSB_WINCUR       24
#define DPS_CTX_SCFG_MSB_WINCUR       28
#define DPS_CTX_BUFSTART(n)           (0x1004+0x20*(n))
#define DPS_CTX_WINSIZE(n)            (0x1008+0x20*(n))
#define DPS_CTX_PTR(n)                (0x100C+0x20*(n))
#define DPS_CTX_WINEND(n)             (0x1010+0x20*(n))
/* WNDW Window w for Stream n */
#define DPS_WIN_WINCNT(n, w, so)           (0x4000+(so)*(n)+0x08*(w))
#define DPS_WIN_WINCNT_LSB_CNT              0
#define DPS_WIN_WINCNT_MSB_CNT             30
#define DPS_WIN_WINCNT_MASK                0x7FFFFFFF
#define DPS_WIN_WINCNT_BIT_PKTCMPLT_MASK   0x80000000

#define MAP_FAILED   (-1)

static unsigned int windows = 2;
static unsigned int win_size = 0x1000;
static unsigned int stream_offset = 2*0x08;

static DECLARE_WAIT_QUEUE_HEAD(dps_waitqueue);

module_param(windows,  int, 0444); /* write permission for user (root), read permissions for all */
MODULE_PARM_DESC(windows, "Integer number of buffer-windows per slot");
module_param(win_size, int, 0444); /* write permission for user (root), read permissions for all */
MODULE_PARM_DESC(win_size, "Buffer-window size in bytes");

static struct dps_framework {
        struct class *class; /* class needed for /dev/ entry */
        unsigned int major;  /* major number for all dma_pkt_sched devices */
        void *drvdata[255];
} dma_pkt_sched;

#define DPS_DATA(minor) dma_pkt_sched.drvdata[(minor)]
#define REGISTER_DMA_PKT_SCHED(minor, private) DPS_DATA((minor)) = (private)

#define PKT_IS_COMPLETE(win_cnt)   (DPS_WIN_WINCNT_BIT_PKTCMPLT_MASK & win_cnt)
#define PKT_LEN(win_cnt)           (DPS_WIN_WINCNT_MASK & win_cnt)

struct dps_info {
        struct device *dev;
        int irq;
        unsigned int irq_vec;
        struct mutex dps_mutex;
        unsigned int minor;
        void __iomem *base_addr;
        unsigned int slots;
        struct dma_pool *pool;
        struct slot_buf_info *slot_buf;
        struct list_head queue_head;
};

struct slot_buf_info {
        dma_addr_t dma_handle;
        char *dma_vaddr;
        unsigned char last_proc_win;
        struct win_buf_info *win_buf;
};

struct win_buf_info {
        struct list_head lhead;
        dma_addr_t dma_paddr;
        char *dma_vaddr;
        unsigned char slot;
        unsigned char win;
        unsigned int  len;
};

void reg_set(struct dps_info *info, unsigned int reg_offs, u32 mask)
{
        u32 value;

        value = ioread32(info->base_addr + reg_offs);
        rmb();
        value |= mask;
        iowrite32(value, info->base_addr + reg_offs);
        wmb();
}

void reg_clr(struct dps_info *info, unsigned int reg_offs, u32 mask)
{
        u32 value;

        value = ioread32(info->base_addr + reg_offs);
        rmb();
        value &= ~mask;
        iowrite32(value, info->base_addr+reg_offs);
        wmb();
}

void reg_write(struct dps_info *info, unsigned int reg_offs, u32 value)
{
        iowrite32(value, info->base_addr+reg_offs);
        wmb();
}

u32 reg_read(struct dps_info *info, unsigned int reg_offs)
{
        u32 value;

        value = ioread32(info->base_addr + reg_offs);
        rmb();
        return value;
}

u32 get_irqvec(struct dps_info *info)
{
        return reg_read(info, DPS_REG_IRQVEC);
}

void clr_irqvec(struct dps_info *info, u32 mask)
{
        reg_write(info, DPS_REG_IRQVEC, mask);
}

/**
 * dps_rm_from_queue - remove number of entries from buffer queue
 * @info:      pointer to struct local data struct containing the queue head
 * @entries:   number of entries to remove from queue head (0 flushes the queue)
 *
 * Returns the number of list items that were removed.
 *
 * Descripton:
 * Removes items from the buffer queue head and clears the corresponding registers
 * in order to tell the IP device that the corresponding window buffer available again
 * for writing through DMA.
 */
static int dps_rm_from_queue(struct dps_info *info, int entries)
{
        struct win_buf_info *curr_wb_info;
        struct list_head *pos;
        int len;

        if(entries <= 0)
                return -EINVAL;

        /* mark buffers as cleared and remove them from the queue */
        mutex_lock(&info->dps_mutex);
        len = 0;
        pos = info->queue_head.next;
        while(pos != &(info->queue_head) && (entries == 0 || len != entries) )
        {
                curr_wb_info = list_entry(pos, struct win_buf_info, lhead);
//                pr_info("Releasing buffer %d: slot %d   win %d   virt_addr 0x%08X   size %d\n", len, curr_wb_info->slot, curr_wb_info->win, (unsigned int)(curr_wb_info->dma_vaddr), curr_wb_info->len);
                /* update list pointer to next (current will be removed from list) */
                pos = pos->next;
                /* delete list entry */
                list_del(&(curr_wb_info->lhead));
                /* clear IP wincnt register so IP knows that window is free */
                reg_write(info, DPS_WIN_WINCNT(curr_wb_info->slot, curr_wb_info->win, stream_offset), 0);
                /* clear sidedata in driver */
                curr_wb_info->len = 0;

                len++;
        }
        mutex_unlock(&info->dps_mutex);

        return len;
}

static struct dps_info * dma_packet_sched_get_pdata(struct platform_device *pdev)
{
        struct dps_info *pdata;
        struct resource *res;
        dma_addr_t dma_handle;
        char *dma_vaddr;
        int status;
        unsigned int dt_val;
        unsigned int slot, win;

        /* adjust window number and winsize */
        win_size = roundup_pow_of_two(win_size);
        pr_info("Window size %d\n", win_size);
        if(windows>32)
        {
                windows = 32;
                pr_warn("Nuumber of windows set to max. 32");
        }
        stream_offset = roundup_pow_of_two(windows)*0x08;

        /* allocate device info structure */
        pdata = devm_kzalloc(&pdev->dev, sizeof(struct dps_info), GFP_KERNEL);
        if (!pdata)
                return ERR_PTR(-ENOMEM);

        /* initialize queue */
        INIT_LIST_HEAD(&pdata->queue_head);

        /* read information from device tree */
        res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
        pdata->base_addr = devm_ioremap_resource(&pdev->dev, res);
        if (IS_ERR(pdata->base_addr))
                return pdata->base_addr;

        pdata->irq = platform_get_irq(pdev, 0);
        pr_info("Interrupt: %d \n", pdata->irq);
        if (pdata->irq<0)
                return ERR_PTR(-ENODEV);

        status = fwnode_property_read_u32(pdev->dev.fwnode, "xlnx,#slots", &dt_val);
        if (status)
                return ERR_PTR(status);
        pdata->slots = dt_val;

        pdata->slot_buf = devm_kmalloc_array(&pdev->dev, pdata->slots, sizeof(struct slot_buf_info), GFP_KERNEL);
        if (!pdata->slot_buf)
                return ERR_PTR(-ENOMEM);

        /* DMA mask on full address region the system supports */
        /* Adapt dma_mask if PL IP is not capable of covering the entire adress range */
        /* dma_mask = dma_get_required_mask(&pdev->dev); */
        status = dma_set_mask_and_coherent(&pdev->dev, 0xFFFFFFFF);
        if (status)
                return ERR_PTR(status);

        pdata->pool = dma_pool_create("dps_pool", &pdev->dev, windows*win_size, 128, 0);
        if (!pdata->pool)
                return  ERR_PTR(-ENOMEM);

        /* initializations */
        for(slot=0; slot<pdata->slots; slot++)
        {
                dma_vaddr = dma_pool_alloc(pdata->pool, GFP_KERNEL, &dma_handle);
                if (!dma_vaddr)
                        return  ERR_PTR(-ENOMEM);
                reg_write(pdata, DPS_CTX_BUFSTART(slot), (u32)dma_handle);
                reg_write(pdata, DPS_CTX_SCFG(slot), (u32)((windows-1)<<DPS_CTX_SCFG_LSB_WINCNT));
                reg_write(pdata, DPS_CTX_WINSIZE(slot), win_size);
                /* initialize slot buffer information */
                pdata->slot_buf[slot].dma_vaddr  = dma_vaddr;
                pdata->slot_buf[slot].dma_handle = dma_handle;
                pdata->slot_buf[slot].last_proc_win = windows-1;
                pdata->slot_buf[slot].win_buf = devm_kmalloc_array(&pdev->dev, windows, sizeof(struct win_buf_info), GFP_KERNEL);
                if (!pdata->slot_buf[slot].win_buf)
                        return ERR_PTR(-ENOMEM);
                pr_info("SLOT %d: virt addr 0x%08X   phys addr 0x%08X\n", slot, (unsigned int)dma_vaddr, (unsigned int)dma_handle);
                for(win=0; win<windows; win++)
                {
                        /* initialize window buffer information */
                        pdata->slot_buf[slot].win_buf[win].dma_vaddr = dma_vaddr + win*win_size;
                        pdata->slot_buf[slot].win_buf[win].dma_paddr = dma_handle + win*win_size;
                        pdata->slot_buf[slot].win_buf[win].slot = slot;
                        pdata->slot_buf[slot].win_buf[win].win  = win;
                        pdata->slot_buf[slot].win_buf[win].len  = 0;
                        reg_write(pdata, DPS_WIN_WINCNT(slot, win, stream_offset), 0x00000000);
                        pr_info("DMA WIN %d: virt addr 0x%08X   phys addr 0x%08X\n", win, (unsigned int)(pdata->slot_buf[slot].win_buf[win].dma_vaddr), (unsigned int)(pdata->slot_buf[slot].win_buf[win].dma_paddr));
                }
        }

        return pdata;
}

static long dps_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
        struct dps_info *info = file->private_data;
        struct win_buf_info *curr_wb_info;
        int err = 0;
        int retval = 0;

        if (_IOC_TYPE(cmd) != DPS_IOC_MAGIC) return -ENOTTY;
        if (_IOC_NR(cmd) > DPS_IOC_MAXNR) return -ENOTTY;

        if (_IOC_DIR(cmd) & _IOC_READ)
                err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
        else if (_IOC_DIR(cmd) & _IOC_WRITE)
                err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
        if (err) return -EFAULT;

        switch(cmd)
        {
                case DPS_IOCT_EN:
                        if((u32)arg == DPS_IP_DISABLE)
                        {
                                reg_clr(info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_ENA);
                        }
                        else
                        {
                                reg_set(info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_ENA);
                        }
                        break;
                case DPS_IOCT_SLOT_EN:
                        reg_write(info, DPS_REG_SLTENA, (u32)arg);
                        break;
                case DPS_IOCT_FREE_BUF:
                        if(!dps_rm_from_queue(info, 1))
                                return -EFAULT;
                        break;
                case DPS_IOCQ_WINSIZE:
                        return win_size;
                        break;
                case DPS_IOCQ_NOWINDOWS:
                        return windows;
                        break;
                case DPS_IOCQ_BUFSIZE:
                        mutex_lock(&info->dps_mutex);
                        curr_wb_info = list_first_entry_or_null(&(info->queue_head), struct win_buf_info, lhead);
                        if(curr_wb_info == NULL)
                                retval = -EFAULT;
                        else
                                retval = curr_wb_info->len;
                        mutex_unlock(&info->dps_mutex);
                        break;
                default:
                        return -ENOTTY;
        }

        return retval;
}

static int dps_open(struct inode *inode, struct file *file)
{
        int minor = iminor(inode);

        /* Identify this device, and associate the device data with the file */
        file->private_data = DPS_DATA(minor);

        return generic_file_open(inode, file);
}

static ssize_t dps_read(struct file *file, char __user *buf, size_t count, loff_t * ppos)
{
        struct dps_info *info = file->private_data;
        struct win_buf_info *curr_wb_info;
        char *buffer;
        int len;
        ssize_t retval = 0;

        if(count == 0)
                return 0;

        mutex_lock(&info->dps_mutex);
        curr_wb_info = list_first_entry_or_null(&(info->queue_head), struct win_buf_info, lhead);
        if( curr_wb_info != NULL )
        {
                len = curr_wb_info->len;
                if(*ppos<len)
                {
                        buffer = curr_wb_info->dma_vaddr;

                        /* data output to user */
                        if(len>0)
                        {
                                len = len-*ppos;
                                if(count<len) len = count;
                                if( copy_to_user(buf, (const char*)buffer, len) )
                                        len = -EFAULT;
                                *ppos += len;
                                retval = len;
                        }
                }
                else
                {
                        retval = 0;
                }

        }
        else
        {
                retval = -EAGAIN;
        }
        mutex_unlock(&info->dps_mutex);

        return retval;
}

static int dps_mmap(struct file *file, struct vm_area_struct *vma)
{
        struct dps_info *info = file->private_data;
        struct win_buf_info *curr_wb_info;
        int retval;

        /* fetch data from queue */
        mutex_lock(&info->dps_mutex);
        curr_wb_info = list_first_entry_or_null(&(info->queue_head), struct win_buf_info, lhead);
        if( curr_wb_info != NULL )
        {
                /* for better performance, this mapping could be done for all buffers*/
                /* when the dma buffers are allocated. */
                retval = dma_mmap_coherent(info->dev, vma,
                                        curr_wb_info->dma_vaddr, curr_wb_info->dma_paddr,
                                        vma->vm_end - vma->vm_start);
        }
        else
        {
                retval = MAP_FAILED;
        }
        mutex_unlock(&info->dps_mutex);

        return retval;
}

/*
static int dps_flush(struct file *file, fl_owner_t id)
{
        pr_info("flush captured (0x%08X, 0x%08X)", (int)id, (int)THIS_MODULE);
        return 0;
}
*/

/*
static ssize_t dps_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
        struct dps_info *info = file->private_data;

        pr_info("fsync captured (0x%08X, 0x%08X, 0x%08X)", (int)start, (int)end, datasync);
        return (loff_t)dps_rm_from_queue(info, 1);
        return 0;
}
*/

static loff_t dps_llseek(struct file *file, loff_t offset, int whence)
{
        struct dps_info *info = file->private_data;
        struct win_buf_info *curr_wb_info;
        int retval;

        /* fetch data from queue */
        mutex_lock(&info->dps_mutex);
        curr_wb_info = list_first_entry_or_null(&(info->queue_head), struct win_buf_info, lhead);
        if( curr_wb_info != NULL )
        {
                i_size_write(file->f_inode, (loff_t)(curr_wb_info->len));
                retval = default_llseek(file, offset, whence);
        }
        else
        {
                retval = -EINVAL;
        }
        mutex_unlock(&info->dps_mutex);

        return retval;
}

static __poll_t dps_poll(struct file *file, poll_table *wait)
{
        struct dps_info *info = file->private_data;
        __poll_t retval;

        poll_wait(file, &dps_waitqueue, wait);

        retval = 0;
        mutex_lock(&info->dps_mutex);
        if( list_empty(&info->queue_head) )
                retval = EPOLLIN | EPOLLRDNORM;
        mutex_unlock(&info->dps_mutex);

        return retval;
}

static const struct file_operations dps_fops = {
        .owner   = THIS_MODULE,  /* used for reference counting */
        .llseek  = dps_llseek,
        .open    = dps_open,
        .read    = dps_read,
        .poll    = dps_poll,
        .mmap    = dps_mmap,
//        .flush   = dps_flush,
//        .fsync   = dps_fsync,
//        .release = dps_release,
        .unlocked_ioctl = dps_ioctl,
#ifdef CONFIG_COMPAT
        .compat_ioctl   = dps_ioctl,
#endif
};

static irqreturn_t dma_packet_sched_irq_handler(int irq, void *dev_id)
{
        struct dps_info *info = (struct dps_info*)dev_id;

        pr_info("DMA packet scheduler interrupt received (top half)\n");
        info->irq_vec = get_irqvec(info);
        clr_irqvec(info, 0xFFFFFFFF);

        return IRQ_WAKE_THREAD;
}

static irqreturn_t dma_packet_sched_irq_thread_handler(int irq, void *dev_id)
{
        struct dps_info *info = (struct dps_info*)dev_id;
        unsigned int slot_mask;
        unsigned char win, last_win;
        unsigned char slot;
        u32 wincnt;

        pr_info("DMA packet scheduler interrupt received (bottom half)\n");
        /* Check slots for interrupts and fill queue */
        for(slot=0; slot<info->slots; slot++)
        {
                slot_mask = (1<<slot);
                if(info->irq_vec & slot_mask)
                {
                        win = info->slot_buf->last_proc_win;
                        do
                        {
                                clr_irqvec(info, slot_mask); /* maybe another packet arrived, we're reading all, so clear again */
                                last_win = reg_read(info, DPS_REG_LASTWIN(slot));
                                win = (win+1)%windows;
                                wincnt = reg_read(info, DPS_WIN_WINCNT(slot, win, stream_offset));
                                if( PKT_IS_COMPLETE(wincnt) == 0 || info->slot_buf[slot].win_buf[win].len != 0)
                                {
                                        break;
                                }
                                mutex_lock(&info->dps_mutex);
                                pr_info("Adding slot %d win %d to list\n", slot, win);
                                info->slot_buf[slot].win_buf[win].len = PKT_LEN(wincnt);
                                list_add_tail(&info->slot_buf[slot].win_buf[win].lhead, &info->queue_head);
                                info->slot_buf->last_proc_win = win;
                                mutex_unlock(&info->dps_mutex);
                        }
                        while (win != last_win);
                }
        }

        return IRQ_HANDLED;
}

static int dps_probe(struct platform_device *pdev)
{
        struct dps_info *dps_info;
        int major;
        int status;

//        pr_debug("xlnx,dma-pkt-sched-axi-1.0: probed\n");
        pr_info("xlnx,dma-pkt-sched-axi-1.0: probed\n");
        pr_info("Buffer size per slot: %d windows, %d bytes/window \n", windows, win_size);

        /* create and populate device info structure */
        dps_info = dma_packet_sched_get_pdata(pdev);
        if(IS_ERR(dps_info))
                return PTR_ERR(dps_info);

        platform_set_drvdata(pdev, dps_info);

        /* register interrupt handler */
        status = devm_request_threaded_irq(&pdev->dev,
                                           dps_info->irq,
                                           dma_packet_sched_irq_handler,
                                           dma_packet_sched_irq_thread_handler,
                                           IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
                                           "dma_pkt_sched", dps_info);
        if(status)
                return status;

        mutex_init(&dps_info->dps_mutex);

        /* create /dev/ entry */
        dma_pkt_sched.class = class_create(THIS_MODULE, "dma_pkt_sched");
        if (IS_ERR(dma_pkt_sched.class))
                return PTR_ERR(dma_pkt_sched.class);

        major = register_chrdev(0, "dma_pkt_sched", &dps_fops);
        if (major < 0)
                return major;
        dma_pkt_sched.major = major;
        dps_info->minor = 0;

        dps_info->dev = device_create(dma_pkt_sched.class, NULL,
                                                MKDEV(dma_pkt_sched.major, dps_info->minor),
                                                dps_info, "dma_pkt_sched%d", dps_info->minor);
        if (IS_ERR(dps_info->dev))
                return PTR_ERR(dps_info->dev);

        REGISTER_DMA_PKT_SCHED(dps_info->minor, dps_info); /* register "minor" device instance */
        /* /dev/ creation done */

        /* enable interrupts */
        reg_set(dps_info, DPS_REG_IRQENA, 0xFFFFFFFF);
        reg_set(dps_info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_IRQENA);

        return 0;
}

static int dps_remove(struct platform_device *pdev)
{
        struct dps_info *dps_info = platform_get_drvdata(pdev);
        int slot;

        /* TBD: disable everything !!! */

//        pr_debug("xlnx,dma-pkt-sched-axi-1.0: removed\n");
        pr_info("xlnx,dma-pkt-sched-axi-1.0: removed\n");

        devm_free_irq(&pdev->dev, dps_info->irq, &pdev->dev);

        /* free allocated dma memory */
        for(slot = 0; slot<dps_info->slots; slot++)
        {
                dma_pool_free(dps_info->pool, dps_info->slot_buf[slot].dma_vaddr, dps_info->slot_buf[slot].dma_handle);
        }
        dma_pool_destroy(dps_info->pool);

        /* remove device */
        device_del(dps_info->dev);
        /* kfree(dps_info); not needed, cleanup done in platform_device.c */

        /* Framework cleanup. */
        unregister_chrdev(dma_pkt_sched.major, "dma_pkt_sched");
        class_destroy(dma_pkt_sched.class);

        return 0;
}

static const struct of_device_id dps_dt_match[] = {
        { .compatible = "xlnx,dma-pkt-sched-axi-1.0", },
        { }
};
MODULE_DEVICE_TABLE(of, dps_dt_match);

static struct platform_driver dps_driver = {
        .driver = {
                .owner = THIS_MODULE,
                .name = "dma-pkt-sched-axi-1.0",
                .of_match_table = dps_dt_match,
        },
        .probe = dps_probe,
        .remove = dps_remove,
};

module_platform_driver(dps_driver);

MODULE_DESCRIPTION("PSI WaveDAQ DMA Packet Scheduler Vivado IP driver");
MODULE_AUTHOR("Elmar Schmid <elmar.schmid@psi.ch>");
MODULE_LICENSE("GPL");
