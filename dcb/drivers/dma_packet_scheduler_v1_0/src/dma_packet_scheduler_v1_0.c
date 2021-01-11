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

#include <linux/kernel.h>
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
#include <linux/net.h>
#include <linux/inet.h>

#include "dma_packet_scheduler_v1_0.h"

/* ACQCONF Registers - General */
#define DPS_REG_GCFG                  0x000
#define DPS_REG_GCFG_BIT_ENA          BIT(0)
#define DPS_REG_GCFG_BIT_IRQENA       BIT(8)
#define DPS_REG_GCFG_BIT_EVENTMODE    BIT(16)
#define DPS_REG_GCFG_BIT_RESET        BIT(31)
#define DPS_REG_GSTAT                 0x004
#define DPS_REG_IRQVEC                0x010
#define DPS_REG_IRQENA                0x014
#define DPS_REG_SLTENA                0x020
/* ACQCONF Registers - Per Stream */
#define DPS_REG_LASTWIN(n)            (0x200+0x10*(n))
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
#define DPS_WIN_WINCNT_MSB_CNT             29
#define DPS_WIN_WINCNT_MASK                0x3FFFFFFF
#define DPS_WIN_WINCNT_BIT_EOE_MASK        0x40000000
#define DPS_WIN_WINCNT_BIT_PKTCMPLT_MASK   0x80000000

#define MAP_FAILED   (-1)

#define DEFAULT_UDP_DST_PORT         5232
#define DEFAULT_UDP_DST_IP           ((unsigned long int)0x7F000001) /* localhost 127.0.0.1 */

static unsigned int windows = 2;
static unsigned int win_size = 0x1000;
static unsigned int stream_offset = 2*0x08;
//static char mode[] = "queue";

static DECLARE_WAIT_QUEUE_HEAD(dps_waitqueue);
static unsigned int read_wait_queue_length = 0;

module_param(windows,  int, 0444); /* write permission for user (root), read permissions for all */
MODULE_PARM_DESC(windows, "Integer number of buffer-windows per slot");
module_param(win_size, int, 0444); /* write permission for user (root), read permissions for all */
MODULE_PARM_DESC(win_size, "Buffer-window size in bytes");
//module_param(mode, charp, 0444); /* write permission for user (root), read permissions for all */
//MODULE_PARM_DESC(mode, "Operation mode: 'udp_direct' to directly send buffer, 'queue' to queue up buffer");

static struct dps_framework {
        struct class *class; /* class needed for /dev/ entry */
        unsigned int major;  /* major number for all dma_pkt_sched devices */
        void *drvdata[255];
} dma_pkt_sched;

#define DPS_DATA(minor) dma_pkt_sched.drvdata[(minor)]
#define REGISTER_DMA_PKT_SCHED(minor, private) DPS_DATA((minor)) = (private)

#define PKT_IS_COMPLETE(win_cnt)   (DPS_WIN_WINCNT_BIT_PKTCMPLT_MASK & win_cnt)
#define PKT_IS_EOE(win_cnt)        (DPS_WIN_WINCNT_BIT_EOE_MASK & win_cnt)
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
        struct socket *udp_socket;
        struct sockaddr_in udp_dst_addr;
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

/** reg_set - register bit set operation
 * @info:       pointer to local data struct of this driver containing the register base address
 * @reg_offs:   register offset in bytes
 * @mask:       mask of the bits to be set (1 = set bit)
 *
 * Sets the bits defined by mask in the register at reg_offs.
 */
void reg_set(struct dps_info *info, unsigned int reg_offs, u32 mask)
{
        u32 value;

        value = ioread32(info->base_addr + reg_offs);
        rmb();
        value |= mask;
        iowrite32(value, info->base_addr + reg_offs);
        wmb();
}

/** reg_clr - register bit clear operation
 * @info:       pointer to local data struct of this driver containing the register base address
 * @reg_offs:   register offset in bytes
 * @mask:       mask of the bits to be cleared (1 = clear bit)
 *
 * Clears the bits defined by mask in the register at reg_offs.
 */
void reg_clr(struct dps_info *info, unsigned int reg_offs, u32 mask)
{
        u32 value;

        value = ioread32(info->base_addr + reg_offs);
        rmb();
        value &= ~mask;
        iowrite32(value, info->base_addr+reg_offs);
        wmb();
}

/** reg_write - register write operation
 * @info:       pointer to local data struct of this driver containing the register base address
 * @reg_offs:   register offset in bytes
 * @value:      data to be written to the register
 */
void reg_write(struct dps_info *info, unsigned int reg_offs, u32 value)
{
        iowrite32(value, info->base_addr+reg_offs);
        wmb();
}

/** reg_read - register read operation
 * @info:       pointer to local data struct of this driver containing the register base address
 * @reg_offs:   register offset in bytes
 */
u32 reg_read(struct dps_info *info, unsigned int reg_offs)
{
        u32 value;

        value = ioread32(info->base_addr + reg_offs);
        rmb();
        return value;
}

/** get_irqvec - reads the interrupt vector register
 * @info:       pointer to local data struct of this driver containing the register base address
 */
u32 get_irqvec(struct dps_info *info)
{
        return reg_read(info, DPS_REG_IRQVEC);
}

/** clr_irqvec - bits in the interrupt vector register
 * @info:       pointer to local data struct of this driver containing the register base address
 * @mask:       mask of the bits to be cleared (1 = clear bit)
 */
void clr_irqvec(struct dps_info *info, u32 mask)
{
        reg_write(info, DPS_REG_IRQVEC, mask);
}

static int udp_socket_send(struct dps_info *info, unsigned char slot, unsigned char win)
{
        struct msghdr msg;
        struct iovec iov;
        mm_segment_t oldfs;
        unsigned int len;
        int size = 0;

        if (info->udp_socket->sk==NULL)
                return 0;

        mutex_lock(&info->dps_mutex);
        len = info->slot_buf[slot].win_buf[win].len;

        iov.iov_base = info->slot_buf[slot].win_buf[win].dma_vaddr;
        mutex_unlock(&info->dps_mutex);

        iov.iov_len = len;

        msg.msg_flags = 0;
        msg.msg_name = &info->udp_dst_addr;
        msg.msg_namelen  = sizeof(struct sockaddr_in);
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
        iov_iter_init(&msg.msg_iter, READ, &iov, 1, len);

        oldfs = get_fs();
        set_fs(KERNEL_DS);
        size = sock_sendmsg(info->udp_socket, &msg);
        set_fs(oldfs);

        /* clear IP wincnt register so IP knows that window is free */
        mutex_lock(&info->dps_mutex);
        reg_write(info, DPS_WIN_WINCNT(slot, win, stream_offset), 0);
        /* clear sidedata in driver */
        info->slot_buf[slot].win_buf[win].len = 0;
        mutex_unlock(&info->dps_mutex);

        return size;
}

static int udp_socket_init(struct dps_info *info)
{
        int retval;

        /* create a socket */
        retval = sock_create(AF_INET, SOCK_DGRAM, IPPROTO_UDP, &info->udp_socket);
        if(retval < 0)
                return -ENXIO;

        return 0;
}

static void udp_socket_free(struct dps_info *info)
{
        /* free allocated resources */
        if (info->udp_socket != NULL)
        {
                sock_release(info->udp_socket);
                info->udp_socket = NULL;
        }
}

/**
 * dps_rm_from_queue - remove number of entries from buffer queue
 * @info:      pointer to struct local data struct containing the queue head
 * @entries:   number of entries to remove from queue head (0 flushes the queue)
 *
 * Returns the number of list items that were removed.
 *
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

/**
 * dps_list_len - evaluat number of items in list
 * @pdev:   pointer to platform device struct
 *
 * Returns the number of items that are currently in the list.
 *
 * Goes throug the buffer queue and counts the number of items.
 */
static int dps_list_len(struct dps_info *info)
{
        struct list_head *pos;
        int items = 0;

        mutex_lock(&info->dps_mutex);
        list_for_each(pos, &info->queue_head) items++;
        mutex_unlock(&info->dps_mutex);

        return items;
}

/**
 * dma_packet_sched_get_pdata - read parameters and initialize
 * @pdev:   pointer to platform device struct
 *
 * Returns a pointer to a dps_info struct containing all information for the driver to work.
 *
 * Reads information from the device tree, allocates a dps_info structure that contains relevant
 * information to operate the driver. Further more the dma buffers and an array
 * for managing buffer information are allocated and initialized. The items of the array are used
 * for the processing queue of the buffers. All necessary register settings are initialized.
 */
static struct dps_info * dma_packet_sched_get_pdata(struct platform_device *pdev)
{
        struct dps_info *pdata;
        struct resource *res;
        dma_addr_t dma_handle;
        char *dma_vaddr;
        int status;
        unsigned int dt_val;
        unsigned int slot;
        unsigned int win;

        /* adjust window number and winsize */
        win_size = roundup_pow_of_two(win_size);
        pr_debug("Window size %d\n", win_size);
        if(windows>32)
        {
                windows = 32;
                pr_warn("Number of windows set to max. 32");
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
                pr_debug("SLOT %d: virt addr 0x%08X   phys addr 0x%08X\n", slot, (unsigned int)dma_vaddr, (unsigned int)dma_handle);
                for(win=0; win<windows; win++)
                {
                        /* initialize window buffer information */
                        pdata->slot_buf[slot].win_buf[win].dma_vaddr = dma_vaddr + win*win_size;
                        pdata->slot_buf[slot].win_buf[win].dma_paddr = dma_handle + win*win_size;
                        pdata->slot_buf[slot].win_buf[win].slot = slot;
                        pdata->slot_buf[slot].win_buf[win].win  = win;
                        pdata->slot_buf[slot].win_buf[win].len  = 0;
                        reg_write(pdata, DPS_WIN_WINCNT(slot, win, stream_offset), 0x00000000);
                        pr_debug("DMA WIN %d: virt addr 0x%08X   phys addr 0x%08X\n", win, (unsigned int)(pdata->slot_buf[slot].win_buf[win].dma_vaddr), (unsigned int)(pdata->slot_buf[slot].win_buf[win].dma_paddr));
                }
        }

        return pdata;
}

/**
 * dps_ioctl - ioctl() system call processing
 */
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

/**
 * dps_sysfs - sysfs control and configuration processing
 */
/** sysfs dps_config number of slots
 *
 * Description:
 * Reading "slots" returns the number of slots connected to the DMA buffer.
 */
static ssize_t slots_show(struct device *dev, struct device_attribute *attr, char *buffer)
{
        struct dps_info *info = dev_get_drvdata(dev);

        return sprintf(buffer, "%d\n", info->slots);
}
static DEVICE_ATTR_RO(slots);

/** sysfs dps_config number of windows
 *
 * Description:
 * Reading "windows" returns the number of window buffers available for each slot
 * of the DMA buffer.
 */
static ssize_t windows_show(struct device *dev, struct device_attribute *attr, char *buffer)
{
        return sprintf(buffer, "%d\n", windows);
}
static DEVICE_ATTR_RO(windows);

/** sysfs dps_config window size
 *
 * Description:
 * Reading "window_size" returns the window size (max. packet size) of a window buffer.
 */
static ssize_t win_size_show(struct device *dev, struct device_attribute *attr, char *buffer)
{
        return sprintf(buffer, "%d\n", win_size);
}
static DEVICE_ATTR_RO(win_size);

static struct attribute *dps_config_attrs[] = {
    &dev_attr_slots.attr,
    &dev_attr_windows.attr,
    &dev_attr_win_size.attr,
    NULL
};

static struct attribute_group dps_config_group = {
    .name = "dps_config",
    .attrs = dps_config_attrs,
};

/** sysfs dps_ctrl enable
 *
 * Description:
 * Writing "enable" enables (1) or disables (0) the global DMA buffer.
 * Reading returns the status of the global DMA buffer enable.
 */
static ssize_t enable_show(struct device *dev, struct device_attribute *attr, char *buffer)
{
        struct dps_info *info = dev_get_drvdata(dev);
        u32 reg_val;

        reg_val = reg_read(info, DPS_REG_GCFG);
        if(reg_val & DPS_REG_GCFG_BIT_ENA)
        {
                return sprintf(buffer, "%d\n", 1);
        }
        else
        {
                return sprintf(buffer, "%d\n", 0);
        }
}

static ssize_t enable_store(struct device *dev, struct device_attribute *attr, const char *buffer, size_t count)
{
        struct dps_info *info = dev_get_drvdata(dev);
        long enable;

        if( kstrtol(buffer, 0, &enable) )
                return -EINVAL;

        if(enable == 1)
        {
                reg_set(info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_ENA);
                return count;
        }
        else if (enable == 0)
        {
                reg_clr(info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_ENA);
                return count;
        }
        return -EINVAL;
}
static DEVICE_ATTR_RW(enable);

/** sysfs dps_ctrl event_mode
 *
 * Description:
 * Writing "event_mode" configures the way, events are synchronized in the core and in the driver.
 * With event_mode 0, packets are transceived with a round robin selection of the slots in the core.
 * With event_mode 1, a slot prcessing an end of event (EOE) flag in the packet header
 * will block further data packets.Once the EOE flag was received on all slots that are enabled,
 * the blocking is reset and all slots are enabled again for transmission.
 * Reading returns the status of the global DMA buffer enable.
 */
static ssize_t event_mode_show(struct device *dev, struct device_attribute *attr, char *buffer)
{
        struct dps_info *info = dev_get_drvdata(dev);
        u32 reg_val;

        reg_val = reg_read(info, DPS_REG_GCFG);
        if (reg_val & DPS_REG_GCFG_BIT_EVENTMODE)
        {
                return sprintf(buffer, "%d\n", 1);
        }
        else
        {
                return sprintf(buffer, "%d\n", 0);
        }
}

static ssize_t event_mode_store(struct device *dev, struct device_attribute *attr, const char *buffer, size_t count)
{
        struct dps_info *info = dev_get_drvdata(dev);
        long event_mode;

        if (kstrtol(buffer, 0, &event_mode))
                return -EINVAL;

        if (event_mode == 1)
        {
                reg_set(info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_EVENTMODE);
                return count;
        }
        else if (event_mode == 0)
        {
                reg_clr(info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_EVENTMODE);
                return count;
        }
        return -EINVAL;
}
static DEVICE_ATTR_RW(event_mode);

/** sysfs dps_ctrl reset
 *
 * Description:
 * Writing "reset" re-initializes the driver and applies a reset to the IP core.
 * Reading returns the status of the global DMA buffer enable.
 * Note that this is a write only value, i.e. it will always read 0.
 */
static ssize_t reset_show(struct device *dev, struct device_attribute *attr, char *buffer)
{
        struct dps_info *info = dev_get_drvdata(dev);
        u32 reg_val;

        reg_val = reg_read(info, DPS_REG_GCFG);
        if (reg_val & DPS_REG_GCFG_BIT_RESET)
        {
                return sprintf(buffer, "%d\n", 1);
        }
        else
        {
                return sprintf(buffer, "%d\n", 0);
        }
}

static ssize_t reset_store(struct device *dev, struct device_attribute *attr, const char *buffer, size_t count)
{
        struct dps_info *info = dev_get_drvdata(dev);
        unsigned int slot;
        unsigned int win;
        long reset;

        if (kstrtol(buffer, 0, &reset))
                return -EINVAL;

        if (reset == 1)
        {
                reg_set(info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_RESET);
                /* keep reset active to avoid packets arriving while structures are being cleared */

                /* flush queue (cleares WINCNT registers) */
                dps_rm_from_queue(info, info->slots*windows);

                /* buffer processing locations and buffer lengths */
                for (slot = 0; slot < info->slots; slot++)
                {
                        info->slot_buf[slot].last_proc_win = windows-1;
                        for(win = 0; win < windows; win++)
                        {
                                info->slot_buf[slot].win_buf[win].len  = 0;
                        }
                }

                /* clear interrupts*/
                clr_irqvec(info, 0xFFFFFFFF);

                /* everything is cleared, reset can be removed */
                reg_clr(info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_RESET);
                return count;
        }
        else if (reset == 0)
        {
                reg_clr(info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_RESET);
                return count;
        }
        return -EINVAL;
}
static DEVICE_ATTR_RW(reset);

/** sysfs dps_ctrl slot enable
 *
 * Description:
 * Writing "slot_enable" enables (1) or disables (0) the corresponding slot.
 * Each bit represents a slot. The LSB corresponds to slot 0.
 * Reading returns the current value of the DMA buffer slot_enable.
 */
static ssize_t slot_enable_show(struct device *dev, struct device_attribute *attr, char *buffer)
{
        struct dps_info *info = dev_get_drvdata(dev);
        u32 reg_val;

        reg_val = reg_read(info, DPS_REG_SLTENA);
        return sprintf(buffer, "0x%08X\n", reg_val);
}

static ssize_t slot_enable_store(struct device *dev, struct device_attribute *attr, const char *buffer, size_t count)
{
        struct dps_info *info = dev_get_drvdata(dev);
        int retval;
        long slot_en;

        retval = kstrtol(buffer, 0, &slot_en);
        if(retval)
                return -EINVAL;

        reg_write(info, DPS_REG_SLTENA, slot_en);
        return count;
}
static DEVICE_ATTR_RW(slot_enable);

/** sysfs dps_ctrl next_buffer
 *
 * Description:
 * Reading "next_buffer" returns the number of window buffers that are currently in the queue for
 * readout.
 * Writing a value to "next_buffer" removes the corresponding number of window buffers from the
 * head of the read queue.
 */
static ssize_t next_buffer_show(struct device *dev, struct device_attribute *attr, char *buffer)
{
        struct dps_info *info = dev_get_drvdata(dev);

        return sprintf(buffer, "%d\n", dps_list_len(info));
}

static ssize_t next_buffer_store(struct device *dev, struct device_attribute *attr, const char *buffer, size_t count)
{
        struct dps_info *info = dev_get_drvdata(dev);
        int retval = 0;
        long target_items;
        int real_items;

        retval = kstrtol(buffer, 0, &target_items);
        if(retval)
                return -EINVAL;

        real_items = dps_rm_from_queue(info, target_items);
        if((long)real_items != target_items)
                pr_warn("Warning: removed %d of %d packets\n", real_items, (int)target_items);
        return count;
}
static DEVICE_ATTR_RW(next_buffer);

/** sysfs dps_ctrl data_bytes
 *
 * Description:
 * Reading "data_bytes" returns the number of bytes stored in the window buffer that is
 * currently available for readout (head of the reoudout queue).
 */
static ssize_t data_bytes_show(struct device *dev, struct device_attribute *attr, char *buffer)
{
        struct dps_info *info = dev_get_drvdata(dev);
        struct win_buf_info *curr_wb_info;
        int retval = 0;

        mutex_lock(&info->dps_mutex);
        curr_wb_info = list_first_entry_or_null(&(info->queue_head), struct win_buf_info, lhead);
        if(curr_wb_info == NULL)
                retval = sprintf(buffer, "%d\n", 0);
        else
                retval = sprintf(buffer, "%d\n", curr_wb_info->len);
        mutex_unlock(&info->dps_mutex);

        return retval;
}
static DEVICE_ATTR_RO(data_bytes);

/** sysfs dps_ctrl udp_dst_ip_addr
 *
 * Description:
 * Writing "udp_dst_ip_addr" with the format ip.ip.ip.ip configures the UDP socket to send
 * data to the destination ip specified.
 * Reading returns the configured destinattion IP address (IPv4).
 */
static ssize_t udp_dst_ip_addr_show(struct device *dev, struct device_attribute *attr, char *buffer)
{
        struct dps_info *info = dev_get_drvdata(dev);
        unsigned int ip_addr;

        ip_addr = ntohl(info->udp_dst_addr.sin_addr.s_addr);

        return sprintf(buffer, "%d.%d.%d.%d\n", 0xFF&(ip_addr>>24), 0xFF&(ip_addr>>16), 0xFF&(ip_addr>>8), 0xFF&ip_addr);
}

static ssize_t udp_dst_ip_addr_store(struct device *dev, struct device_attribute *attr, const char *buffer, size_t count)
{
        struct dps_info *info = dev_get_drvdata(dev);
        int ip_addr;

        ip_addr = in_aton(buffer);

        info->udp_dst_addr.sin_addr.s_addr = ip_addr;

        /* Re-initialize socket with new parameters */
        udp_socket_free(info);
        udp_socket_init(info);

        return count;
}
static DEVICE_ATTR_RW(udp_dst_ip_addr);

/** sysfs dps_ctrl udp_dst_port
 *
 * Description:
 * Writing "udp_dst_port" by writing the corresponding value.
 * Reading returns the configured destination port.
 */
static ssize_t udp_dst_port_show(struct device *dev, struct device_attribute *attr, char *buffer)
{
        struct dps_info *info = dev_get_drvdata(dev);
        unsigned int port;

        port = ntohs(info->udp_dst_addr.sin_port);

        return sprintf(buffer, "%d\n", port);
}

static ssize_t udp_dst_port_store(struct device *dev, struct device_attribute *attr, const char *buffer, size_t count)
{
        struct dps_info *info = dev_get_drvdata(dev);
        long port;

        if( kstrtol(buffer, 0, &port) )
                return -EINVAL;

        info->udp_dst_addr.sin_port = htons((unsigned int)port);

        /* Re-initialize socket with new parameters */
        udp_socket_free(info);
        udp_socket_init(info);

        return count;
}
static DEVICE_ATTR_RW(udp_dst_port);

static struct attribute *dps_ctrl_attrs[] = {
    &dev_attr_enable.attr,
    &dev_attr_event_mode.attr,
    &dev_attr_reset.attr,
    &dev_attr_slot_enable.attr,
    &dev_attr_next_buffer.attr,
    &dev_attr_data_bytes.attr,
    &dev_attr_udp_dst_ip_addr.attr,
    &dev_attr_udp_dst_port.attr,
    NULL
};

static struct attribute_group dps_ctrl_group = {
    .name = "dps_ctrl",
    .attrs = dps_ctrl_attrs,
};

/* Only used when groups are assigned with
 * pdev->dev.groups = dps_groups;
 * in probe() function
 */
static const struct attribute_group *dps_groups[] = {
    &dps_config_group,
    &dps_ctrl_group,
    NULL
};


/**
 * dps_open - open() system call processing
 */
static int dps_open(struct inode *inode, struct file *file)
{
        int minor = iminor(inode);

        /* Identify this device, and associate the device data with the file */
        file->private_data = DPS_DATA(minor);

        return generic_file_open(inode, file);
}

/**
 * dps_read - read() system call processing
 */
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
                                if( copy_to_user(buf, (const char*)(&buffer[*ppos]), len) )
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

/**
 * dps_mmap - mmap() system call processing
 */
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

/**
 * dps_llseek - lseek() system call processing
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

/**
 * dps_poll - poll()/select() system call processing
 */
static __poll_t dps_poll(struct file *file, poll_table *wait)
{
        struct dps_info *info = file->private_data;
        __poll_t retval;

        poll_wait(file, &dps_waitqueue, wait);
        read_wait_queue_length++;

        retval = 0;
        mutex_lock(&info->dps_mutex);
        if( !list_empty(&info->queue_head) )
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
        .unlocked_ioctl = dps_ioctl,
#ifdef CONFIG_COMPAT
        .compat_ioctl   = dps_ioctl,
#endif
};

static irqreturn_t dma_packet_sched_irq_handler(int irq, void * dev_id)
{
        struct dps_info * info = (struct dps_info *)dev_id;

        /* Disable IP interrupts */
        reg_clr(info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_IRQENA);
        /* Save and clear interrupt vector */
        info->irq_vec = get_irqvec(info);
        clr_irqvec(info, info->irq_vec);

        /* proceed to threaded interrupt handler */
        return IRQ_WAKE_THREAD;
}

static irqreturn_t dma_packet_sched_irq_thread_handler(int irq, void *dev_id)
{
        struct dps_info * info = (struct dps_info *)dev_id;
        unsigned int slot_mask;
        unsigned char win;
        unsigned char last_win;
        unsigned char slot;
        u32 wincnt;

        /* Check slots for interrupts and fill queue */
        while (info->irq_vec > 0)
        {
                //pr_info("Entering IRQ slot loop: irq_vec = 0x%08X\n", info->irq_vec);
                for (slot = 0; slot < info->slots; slot++)
                {
                        slot_mask = (1 << slot);
                        if (info->irq_vec & slot_mask)
                        {
                                win = info->slot_buf[slot].last_proc_win;
                                do
                                {
                                        clr_irqvec(info, slot_mask); /* maybe another packet arrived, we're reading all, so clear again */
                                        last_win = reg_read(info, DPS_REG_LASTWIN(slot));
                                        win = (win + 1) % windows;
                                        wincnt = reg_read(info, DPS_WIN_WINCNT(slot, win, stream_offset));
                                        /* pr_info("Handling slot %d: last_win = %d, win = %d, wincnt = 0x%08X\n", slot, last_win, win, wincnt); */
                                        if ((PKT_IS_COMPLETE(wincnt) == 0) || (info->slot_buf[slot].win_buf[win].len != 0))
                                        {
                                                break;
                                        }
                                        mutex_lock(&info->dps_mutex);
                                        info->slot_buf[slot].win_buf[win].len = PKT_LEN(wincnt);
#if 0
                                        list_add_tail(&info->slot_buf[slot].win_buf[win].lhead, &info->queue_head);
#endif
                                        info->slot_buf[slot].last_proc_win = win;
                                        mutex_unlock(&info->dps_mutex);
#if 0
                                        if (read_wait_queue_length > 0)
                                        {
                                                wake_up(&dps_waitqueue);
                                                read_wait_queue_length = 0;
                                        }
#endif
                                        udp_socket_send(info, slot, win);
                                }
                                while ((win != last_win) && (PKT_IS_EOE(wincnt) == 0));

                                /* Do not reschedule processing slot if all windows are processed*/
                                if (win == last_win)
                                {
                                        info->irq_vec &= ~slot_mask;
                                }
                        }
                }
        }
        /* Re-enable Interrupts */
        reg_set(info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_IRQENA);

        return IRQ_HANDLED;
}

static int dps_probe(struct platform_device *pdev)
{
        struct dps_info *dps_info;
        int major;
        int status;

        pr_debug("xlnx,dma-pkt-sched-axi-1.0: probed\n");
        pr_debug("Buffer size per slot: %d windows, %d bytes/window \n", windows, win_size);

        /* create and populate device info structure */
        dps_info = dma_packet_sched_get_pdata(pdev);
        if(IS_ERR(dps_info))
                return PTR_ERR(dps_info);

        reg_set(dps_info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_RESET);
        reg_clr(dps_info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_RESET);

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

        /* initialize UDP socket */
        memset(&dps_info->udp_dst_addr, 0, sizeof(struct sockaddr));
        dps_info->udp_dst_addr.sin_family      = AF_INET;
        dps_info->udp_dst_addr.sin_addr.s_addr = htonl(DEFAULT_UDP_DST_IP);
        dps_info->udp_dst_addr.sin_port        = htons(DEFAULT_UDP_DST_PORT);
        udp_socket_init(dps_info);

        /* Create a sysfs file on the client device node */
        status = sysfs_create_groups(&pdev->dev.kobj, dps_groups);
        if (status)
        {
                pr_err("sysfs creation failed\n");
                return status;
        }
        /* recommended here instead of sysfs_create_group & sysfs_remove_group
         * to avoid race conditions but did not work:
         *pdev->dev.groups = dps_groups;
         */

        /* enable interrupts and IP (slots and overall)*/
        reg_write(dps_info, DPS_REG_IRQENA, 0xFFFFFFFF);
        reg_write(dps_info, DPS_REG_SLTENA, 0xFFFFFFFF);
        reg_set(dps_info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_ENA | DPS_REG_GCFG_BIT_IRQENA);

        return 0;
}

static int dps_remove(struct platform_device *pdev)
{
        struct dps_info *dps_info = platform_get_drvdata(pdev);
        int slot;

        /* disable IP and interrupts (slots and overall)*/
        reg_clr(dps_info, DPS_REG_GCFG, DPS_REG_GCFG_BIT_ENA | DPS_REG_GCFG_BIT_IRQENA);
        reg_write(dps_info, DPS_REG_IRQENA, 0x00000000);
        reg_write(dps_info, DPS_REG_SLTENA, 0x00000000);

        sysfs_remove_groups(&pdev->dev.kobj, dps_groups);

        /* Destroy UDP socket */
        udp_socket_free(dps_info);

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

        pr_debug("xlnx,dma-pkt-sched-axi-1.0: removed\n");

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
