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
#include "dma_packet_scheduler_v1_0.h"

/* ACQCONF Registers - General */
#define DMA_PKT_SCHED_REG_GCFG                  0x000
#define DMA_PKT_SCHED_REG_GCFG_BIT_ENA          BIT(0)
#define DMA_PKT_SCHED_REG_GCFG_BIT_IRQENA       BIT(8)
#define DMA_PKT_SCHED_REG_GSTAT                 0x004
#define DMA_PKT_SCHED_REG_IRQVEC                0x010
#define DMA_PKT_SCHED_REG_IRQENA                0x014
#define DMA_PKT_SCHED_REG_SLTENA                0x020
/* ACQCONF Registers - Per Stream */
#define DMA_PKT_SCHED_REG_LASTWIN(n)            (0x200+0x04*(n))
/* CTXMEM for Stream n */
#define DMA_PKT_SCHED_CTX_SCFG(n)               (0x1000+0x20*(n))
#define DMA_PKT_SCHED_CTX_SCFG_LSB_WINCNT       16
#define DMA_PKT_SCHED_CTX_SCFG_MSB_WINCNT       20
#define DMA_PKT_SCHED_CTX_SCFG_LSB_WINCUR       24
#define DMA_PKT_SCHED_CTX_SCFG_MSB_WINCUR       28
#define DMA_PKT_SCHED_CTX_BUFSTART(n)           (0x1004+0x20*(n))
#define DMA_PKT_SCHED_CTX_WINSIZE(n)            (0x1008+0x20*(n))
#define DMA_PKT_SCHED_CTX_PTR(n)                (0x100C+0x20*(n))
#define DMA_PKT_SCHED_CTX_WINEND(n)             (0x1010+0x20*(n))
/* WNDW Window w for Stream n */
#define DMA_PKT_SCHED_WIN_WINCNT(n, w, so)           (0x4000+(so)*(n)+0x08*(w))
#define DMA_PKT_SCHED_WIN_WINCNT_LSB_CNT              0
#define DMA_PKT_SCHED_WIN_WINCNT_MSB_CNT             30
#define DMA_PKT_SCHED_WIN_WINCNT_MASK                0x7FFFFFFF
#define DMA_PKT_SCHED_WIN_WINCNT_BIT_PKTCMPLT_MASK   0x80000000

#define WIN_STAT_EMPTY   0
#define WIN_STAT_FULL    1

static unsigned int windows = 2;
static unsigned int win_size = 0x0800;
static unsigned int stream_offset = 2*0x08;

static DECLARE_WAIT_QUEUE_HEAD(dma_pkt_sched_waitqueue);

module_param(windows,  int, 0444); /* write permission for user (root), read permissions for all */
MODULE_PARM_DESC(windows, "Integer number of buffer-windows per slot");
module_param(win_size, int, 0444); /* write permission for user (root), read permissions for all */
MODULE_PARM_DESC(win_size, "Buffer-window size in bytes");

static struct dma_pkt_sched_framework {
        struct class *class; /* class needed for /dev/ entry */
        unsigned int major;  /* major number for all dma_pkt_sched devices */
        void *drvdata[255];
} dma_pkt_sched;

#define DMA_PKT_SCHED_DATA(minor) dma_pkt_sched.drvdata[(minor)]
#define REGISTER_DMA_PKT_SCHED(minor, private) DMA_PKT_SCHED_DATA((minor)) = (private)

#define PKT_IS_COMPLETE(win_cnt)   (DMA_PKT_SCHED_WIN_WINCNT_BIT_PKTCMPLT_MASK & win_cnt)
#define PKT_LEN(win_cnt)           (DMA_PKT_SCHED_WIN_WINCNT_MASK & win_cnt)

struct dma_pkt_sched_info {
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
/* list functions to use: */
/*
Add item @ head:
void list_add(struct list_head *new, struct list_head *head);
Add item @ end
void list_add_tail(struct list_head *new, struct list_head *head);
Delete item from list:
void list_del(struct list_head *entry);
Check if entry is last one of list:
int list_is_last(const struct list_head *list, const struct list_head *head);
Check if list is empty:
int list_empty(const struct list_head *head);
Check if only one item left in list:
int list_is_singular(const struct list_head *head);
Get struct of list item (like container_of()):
list_entry(ptr, type, member);
Get struct of first entry of list (list must not be empty):
list_first_entry(ptr, type, member);
Get struct of first entry of list (null if list is empty):
list_first_entry_or_null(ptr, type, member);
Loop to go through list (also safe versions available):
list_for_each(pos, head);
For more functions to go through lists etc. see linux/list.h
*/

struct slot_buf_info {
        dma_addr_t dma_handle;
        char *dma_vaddr;
        unsigned char last_proc_win;
        struct win_buf_info *win_buf;
};

struct win_buf_info {
        struct list_head lhead;
        unsigned char status;
        struct dma_buf buffer_info;
        char *dma_vaddr;
        unsigned char slot;
        unsigned char win;
};

void reg_set(struct dma_pkt_sched_info *info, unsigned int reg_offs, u32 mask)
{
        u32 value;

        value = ioread32(info->base_addr + reg_offs);
        rmb();
        value |= mask;
        iowrite32(value, info->base_addr + reg_offs);
        wmb();
}

void reg_clr(struct dma_pkt_sched_info *info, unsigned int reg_offs, u32 mask)
{
        u32 value;

        value = ioread32(info->base_addr + reg_offs);
        rmb();
        value &= ~mask;
        iowrite32(value, info->base_addr+reg_offs);
        wmb();
}

void reg_write(struct dma_pkt_sched_info *info, unsigned int reg_offs, u32 value)
{
        iowrite32(value, info->base_addr+reg_offs);
        wmb();
}

u32 reg_read(struct dma_pkt_sched_info *info, unsigned int reg_offs)
{
        u32 value;

        value = ioread32(info->base_addr + reg_offs);
        rmb();
        return value;
}

u32 get_irqvec(struct dma_pkt_sched_info *info)
{
        return reg_read(info, DMA_PKT_SCHED_REG_IRQVEC);
}

void clr_irqvec(struct dma_pkt_sched_info *info, u32 mask)
{
        reg_write(info, DMA_PKT_SCHED_REG_IRQVEC, mask);
}

static struct dma_pkt_sched_info * dma_packet_sched_get_pdata(struct platform_device *pdev)
{
        struct dma_pkt_sched_info *pdata;
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
        pdata = devm_kzalloc(&pdev->dev, sizeof(struct dma_pkt_sched_info), GFP_KERNEL);
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

        pdata->pool = dma_pool_create("dma_pkt_sched_pool", &pdev->dev, windows*win_size, 128, 0);
        if (!pdata->pool)
                return  ERR_PTR(-ENOMEM);

        /* initializations */
        for(slot=0; slot<pdata->slots; slot++)
        {
                dma_vaddr = dma_pool_alloc(pdata->pool, GFP_KERNEL, &dma_handle);
                if (!dma_vaddr)
                        return  ERR_PTR(-ENOMEM);
                reg_write(pdata, DMA_PKT_SCHED_CTX_BUFSTART(slot), (u32)dma_handle);
                reg_write(pdata, DMA_PKT_SCHED_CTX_SCFG(slot), (u32)((windows-1)<<DMA_PKT_SCHED_CTX_SCFG_LSB_WINCNT));
                reg_write(pdata, DMA_PKT_SCHED_CTX_WINSIZE(slot), win_size);
                /* initialize slot buffer information */
                pdata->slot_buf[slot].dma_vaddr  = dma_vaddr;
                pdata->slot_buf[slot].dma_handle = dma_handle;
                pdata->slot_buf[slot].last_proc_win = windows-1;
                pdata->slot_buf[slot].win_buf = devm_kmalloc_array(&pdev->dev, windows, sizeof(struct win_buf_info), GFP_KERNEL);
                if (!pdata->slot_buf[slot].win_buf)
                        return ERR_PTR(-ENOMEM);
                pr_info("SLOT: %d DMA physical addr 0x%08X   DMA virtual address 0x%08X\n", slot, (unsigned int)dma_handle, (unsigned int)dma_vaddr);
                for(win=0; win<windows; win++)
                {
                        /* initialize window buffer information */
                        pdata->slot_buf[slot].win_buf[win].status    = WIN_STAT_EMPTY;
                        pdata->slot_buf[slot].win_buf[win].buffer_info.data = dma_vaddr + win*win_size;
                        pdata->slot_buf[slot].win_buf[win].buffer_info.slot = slot;
                        pdata->slot_buf[slot].win_buf[win].buffer_info.win  = win;
                        pdata->slot_buf[slot].win_buf[win].buffer_info.len  = 0;
//                        pdata->slot_buf[slot].win_buf[win].dma_vaddr = dma_vaddr + win*win_size;
//                        pdata->slot_buf[slot].win_buf[win].slot      = slot;
//                        pdata->slot_buf[slot].win_buf[win].win       = win;
                        reg_write(pdata, DMA_PKT_SCHED_WIN_WINCNT(slot, win, stream_offset), 0x00000000);
                        pr_info("WIN %d: DMA virtual address 0x%08X\n", win, (unsigned int)(pdata->slot_buf[slot].win_buf[win].buffer_info.data));
                }
        }

        return pdata;
}

static int dma_pkt_sched_data_available(struct dma_pkt_sched_info *info)
{
        int empty;

        mutex_lock(&info->dps_mutex);
        empty =  list_empty(&info->queue_head);
        mutex_unlock(&info->dps_mutex);

        if(empty)
                return 0;

        return 1;
}

static long dma_pkt_sched_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
        struct dma_pkt_sched_info *pdata = file->private_data;

        switch(cmd)
        {
                case DMA_PSCHED_EN_IOCTL:
                        pr_debug("Enabling DMA packet scheduler\n");
                        reg_set(pdata, DMA_PKT_SCHED_REG_GCFG, DMA_PKT_SCHED_REG_GCFG_BIT_ENA);
                        break;
                case DMA_PSCHED_DIS_IOCTL:
                        pr_debug("Disabling DMA packet scheduler\n");
                        reg_clr(pdata, DMA_PKT_SCHED_REG_GCFG, DMA_PKT_SCHED_REG_GCFG_BIT_ENA);
                        break;
                case DMA_PSCHED_EN_SLOT_IOCTL:
                        pr_debug("Enabling DMA packet scheduler for slot 0x%08X\n", (u32)arg);
//                        iowrite32((u32)arg, pdata->base_addr+DMA_PKT_SCHED_REG_SLTENA);
                        reg_write(pdata, DMA_PKT_SCHED_REG_SLTENA, (u32)arg);
                        break;
                default:
                        return -EINVAL;
        }

        return 0;
}

static int dma_pkt_sched_open(struct inode *inode, struct file *file)
{
        int minor = iminor(inode);

        /* Identify this device, and associate the device data with the file */
        file->private_data = DMA_PKT_SCHED_DATA(minor);

        return generic_file_open(inode, file);
}

static ssize_t dma_pkt_sched_read(struct file *file, char __user *buf, size_t count, loff_t * ppos)
{
        struct dma_pkt_sched_info *info = file->private_data;
        int len;
        struct win_buf_info *curr_wb_info;
        struct dma_buf *dma_buf_arr;
        struct list_head *pos;
        int i, j;
        char *buffer;

        if(!dma_pkt_sched_data_available(info))
                return -EAGAIN;

        if(count == 0)
                return 0;

        dma_buf_arr = kmalloc_array(count, sizeof(struct dma_buf), GFP_KERNEL);/* allocate wb_info_ptr_arr */;

        /* fetch data from queue */
        mutex_lock(&info->dps_mutex);
        len = 0;
        for (pos = info->queue_head.next; pos != &(info->queue_head); pos = pos->next)
        {
                curr_wb_info = list_entry(pos, struct win_buf_info, lhead);
                memcpy(&dma_buf_arr[len], &(curr_wb_info->buffer_info), sizeof(struct dma_buf));
                len++;
                if(len == count) break;
        }
        mutex_unlock(&info->dps_mutex);

        /* data output to user */
        if(len>0)
        {
                if( copy_to_user(buf, dma_buf_arr, len*sizeof(struct dma_buf)) )
                        len = -EFAULT;
        }
//        for(i=0;i<len;i++)
//        {
//                pr_info("Buffer Information %d: slot %d   win %d   virt_addr 0x%08X   size %d\n", i, dma_buf_arr[i].slot, dma_buf_arr[i].win, (unsigned int)(dma_buf_arr[i].data), dma_buf_arr[i].len);
//        }
        for(i = 0; i<len; i++)
        {
                buffer = dma_buf_arr[i].data;
                for(j = 0; j<dma_buf_arr[i].len; j++)
                {
                        if( (j%16)==0 ) pr_info("\n");
                        pr_info(" %02X", buffer[j]);
                }
                pr_info("\n");
        }

        kfree(dma_buf_arr);

        return len;
}

static loff_t dma_pkt_sched_llseek(struct file *file, loff_t ppos, int origin)
{
        struct dma_pkt_sched_info *info = file->private_data;
        struct win_buf_info *curr_wb_info;
        struct list_head *pos;
        int len;

//        pr_info("Releasing %d window buffers (origin %d)\n", (int)ppos, origin);

        if(ppos <= 0)
                return -EINVAL;

        /* mark buffers as cleared and remove them from the queue */
        mutex_lock(&info->dps_mutex);
        len = 0;
        pos = info->queue_head.next;
        while(pos != &(info->queue_head) && len != ppos)
        {
                curr_wb_info = list_entry(pos, struct win_buf_info, lhead);
//                pr_info("Releasing buffer %d: slot %d   win %d   virt_addr 0x%08X   size %d\n", len, curr_wb_info->buffer_info.slot, curr_wb_info->buffer_info.win, (unsigned int)(curr_wb_info->buffer_info.data), curr_wb_info->buffer_info.len);
                /* update list pointer to next (current will be removed from list) */
                pos = pos->next;
                /* delete list entry */
                list_del(&(curr_wb_info->lhead));
                /* clear IP wincnt register so IP knows that window is free */
                reg_write(info, DMA_PKT_SCHED_WIN_WINCNT(curr_wb_info->buffer_info.slot, curr_wb_info->buffer_info.win, stream_offset), 0);
                /* clear sidedata in driver */
                curr_wb_info->buffer_info.len = 0;
                curr_wb_info->status = WIN_STAT_EMPTY;

                len++;
        }
        mutex_unlock(&info->dps_mutex);

        return (loff_t)len;
}

static __poll_t dma_pkt_sched_poll(struct file *file, poll_table *wait)
{
        struct dma_pkt_sched_info *info = file->private_data;
        __poll_t ret;

        poll_wait(file, &dma_pkt_sched_waitqueue, wait);

        ret = 0;
        if(!dma_pkt_sched_data_available(info))
                ret = EPOLLIN | EPOLLRDNORM;

        return ret;
}

static const struct file_operations dma_pkt_sched_fops = {
        .owner   = THIS_MODULE,  /* used for reference counting */
        .llseek  = dma_pkt_sched_llseek,
        .open    = dma_pkt_sched_open,
        .read    = dma_pkt_sched_read,
        .poll    = dma_pkt_sched_poll,
//        .release = dma_pkt_sched_release,
//        .flush   = dma_pkt_sched_flush,
//        .unlink  = dma_pkt_sched_unlink,
// see /include/linux/fs.h line 1727ff
        .unlocked_ioctl = dma_pkt_sched_ioctl,
#ifdef CONFIG_COMPAT
        .compat_ioctl   = dma_pkt_sched_ioctl,
#endif
};

static irqreturn_t dma_packet_sched_irq_handler(int irq, void *dev_id)
{
        struct dma_pkt_sched_info *info = (struct dma_pkt_sched_info*)dev_id;

        pr_info("DMA packet scheduler interrupt received (top half)\n");
        info->irq_vec = get_irqvec(info);
        clr_irqvec(info, 0xFFFFFFFF);

        return IRQ_WAKE_THREAD;
}

static irqreturn_t dma_packet_sched_irq_thread_handler(int irq, void *dev_id)
{
        struct dma_pkt_sched_info *info = (struct dma_pkt_sched_info*)dev_id;
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
                                last_win = reg_read(info, DMA_PKT_SCHED_REG_LASTWIN(slot));
                                win = (win+1)%windows;
                                wincnt = reg_read(info, DMA_PKT_SCHED_WIN_WINCNT(slot, win, stream_offset));
                                if( PKT_IS_COMPLETE(wincnt) == 0 || info->slot_buf[slot].win_buf[win].status == WIN_STAT_FULL)
                                {
                                        break;
                                }
                                mutex_lock(&info->dps_mutex);
                                pr_info("Adding slot %d win %d to list\n", slot, win);
                                info->slot_buf[slot].win_buf[win].status = WIN_STAT_FULL;
                                info->slot_buf[slot].win_buf[win].buffer_info.len = PKT_LEN(wincnt);
                                list_add_tail(&info->slot_buf[slot].win_buf[win].lhead, &info->queue_head);
                                info->slot_buf->last_proc_win = win;
                                mutex_unlock(&info->dps_mutex);
                        }
                        while (win != last_win);
                }
        }

        return IRQ_HANDLED;
}

static int dma_pkt_sched_probe(struct platform_device *pdev)
{
        struct dma_pkt_sched_info *dma_pkt_sched_info;
        int major;
        int status;

//        pr_debug("xlnx,dma-pkt-sched-axi-1.0: probed\n");
        pr_info("xlnx,dma-pkt-sched-axi-1.0: probed\n");
        pr_info("Buffer size per slot: %d windows, %d bytes/window \n", windows, win_size);

        /* create and populate device info structure */
        dma_pkt_sched_info = dma_packet_sched_get_pdata(pdev);
        if(IS_ERR(dma_pkt_sched_info))
                return PTR_ERR(dma_pkt_sched_info);

        platform_set_drvdata(pdev, dma_pkt_sched_info);

        /* register interrupt handler */
        status = devm_request_threaded_irq(&pdev->dev,
                                           dma_pkt_sched_info->irq,
                                           dma_packet_sched_irq_handler,
                                           dma_packet_sched_irq_thread_handler,
                                           IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
                                           "dma_pkt_sched", dma_pkt_sched_info);
        if(status)
                return status;

        mutex_init(&dma_pkt_sched_info->dps_mutex);

        /* create /dev/ entry */
        dma_pkt_sched.class = class_create(THIS_MODULE, "dma_pkt_sched");
        if (IS_ERR(dma_pkt_sched.class))
                return PTR_ERR(dma_pkt_sched.class);

        major = register_chrdev(0, "dma_pkt_sched", &dma_pkt_sched_fops);
        if (major < 0)
                return major;
        dma_pkt_sched.major = major;
        dma_pkt_sched_info->minor = 0;

        dma_pkt_sched_info->dev = device_create(dma_pkt_sched.class, NULL,
                                                MKDEV(dma_pkt_sched.major, dma_pkt_sched_info->minor),
                                                dma_pkt_sched_info, "dma_pkt_sched%d", dma_pkt_sched_info->minor);
        if (IS_ERR(dma_pkt_sched_info->dev))
                return PTR_ERR(dma_pkt_sched_info->dev);

        REGISTER_DMA_PKT_SCHED(dma_pkt_sched_info->minor, dma_pkt_sched_info); /* register "minor" device instance */
        /* /dev/ creation done */

        /* enable interrupts */
        reg_set(dma_pkt_sched_info, DMA_PKT_SCHED_REG_IRQENA, 0xFFFFFFFF);
        reg_set(dma_pkt_sched_info, DMA_PKT_SCHED_REG_GCFG, DMA_PKT_SCHED_REG_GCFG_BIT_IRQENA);

        return 0;
}

static int dma_pkt_sched_remove(struct platform_device *pdev)
{
        struct dma_pkt_sched_info *dma_pkt_sched_info = platform_get_drvdata(pdev);
        int slot;

        /* TBD: disable everything !!! */

//        pr_debug("xlnx,dma-pkt-sched-axi-1.0: removed\n");
        pr_info("xlnx,dma-pkt-sched-axi-1.0: removed\n");

        devm_free_irq(&pdev->dev, dma_pkt_sched_info->irq, &pdev->dev);

        /* free allocated dma memory */
        for(slot = 0; slot<dma_pkt_sched_info->slots; slot++)
        {
                dma_pool_free(dma_pkt_sched_info->pool, dma_pkt_sched_info->slot_buf[slot].dma_vaddr, dma_pkt_sched_info->slot_buf[slot].dma_handle);
        }
        dma_pool_destroy(dma_pkt_sched_info->pool);

        /* remove device */
        device_del(dma_pkt_sched_info->dev);
        /* kfree(dma_pkt_sched_info); not needed, cleanup done in platform_device.c */

        /* Framework cleanup. */
        unregister_chrdev(dma_pkt_sched.major, "dma_pkt_sched");
        class_destroy(dma_pkt_sched.class);

        return 0;
}

static const struct of_device_id dma_pkt_sched_dt_match[] = {
        { .compatible = "xlnx,dma-pkt-sched-axi-1.0", },
        { }
};
MODULE_DEVICE_TABLE(of, dma_pkt_sched_dt_match);

static struct platform_driver dma_pkt_sched_driver = {
        .driver = {
                .owner = THIS_MODULE,
                .name = "dma-pkt-sched-axi-1.0",
                .of_match_table = dma_pkt_sched_dt_match,
        },
        .probe = dma_pkt_sched_probe,
        .remove = dma_pkt_sched_remove,
};

module_platform_driver(dma_pkt_sched_driver);

MODULE_DESCRIPTION("PSI WaveDAQ DMA Packet Scheduler Vivado IP driver");
MODULE_AUTHOR("Elmar Schmid <elmar.schmid@psi.ch>");
MODULE_LICENSE("GPL");
