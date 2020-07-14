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

#include <linux/module.h>
#include <linux/property.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/io.h>
#include <linux/dma-mapping.h>
#include <linux/dmapool.h>
#include "dma_packet_scheduler_v1_0.h"

/// @cond
//ACQCONF Registers - General
#define DMA_PKT_SCHED_REG_GCFG                  0x000
#define DMA_PKT_SCHED_REG_GCFG_BIT_ENA          BIT(0)
#define DMA_PKT_SCHED_REG_GCFG_BIT_IRQENA       BIT(8)
#define DMA_PKT_SCHED_REG_GSTAT                 0x004
#define DMA_PKT_SCHED_REG_IRQVEC                0x010
#define DMA_PKT_SCHED_REG_IRQENA                0x014
#define DMA_PKT_SCHED_REG_SLTENA                0x020
//ACQCONF Registers - Per Stream
#define DMA_PKT_SCHED_REG_LASTWIN(n)            (0x20C+0x04*(n))
//CTXMEM for Stream n
#define DMA_PKT_SCHED_CTX_SCFG(n)               (0x1000+0x20*(n))
#define DMA_PKT_SCHED_CTX_SCFG_LSB_WINCNT       16
#define DMA_PKT_SCHED_CTX_SCFG_MSB_WINCNT       20
#define DMA_PKT_SCHED_CTX_SCFG_LSB_WINCUR       24
#define DMA_PKT_SCHED_CTX_SCFG_MSB_WINCUR       28
#define DMA_PKT_SCHED_CTX_BUFSTART(n)           (0x1004+0x20*(n))
#define DMA_PKT_SCHED_CTX_WINSIZE(n)            (0x1008+0x20*(n))
#define DMA_PKT_SCHED_CTX_PTR(n)                (0x100C+0x20*(n))
#define DMA_PKT_SCHED_CTX_WINEND(n)             (0x1010+0x20*(n))
//WNDW Window w for Stream n
#define DMA_PKT_SCHED_WIN_WINCNT(n, w, so)      (0x4000+(so)*(n)+0x08*(w))
#define DMA_PKT_SCHED_WIN_WINCNT_LSB_CNT         0
#define DMA_PKT_SCHED_WIN_WINCNT_MSB_CNT        30
#define DMA_PKT_SCHED_WIN_WINCNT_BIT_PKTCMPLT   (1 << 31)
/// @endcond

static int windows = 2;
static int win_size = 0x0800;

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

struct dma_pkt_sched_info {
        struct device *dev;
        unsigned int minor;
        void __iomem *base_addr;
        unsigned int slots;
        dma_addr_t dma_handle;
        char *dma_vaddr;
        struct dma_pool *pool;
};

void reg_set(void __iomem *addr, u32 mask)
{
        u32 value;

        value =  ioread32(addr);
        rmb();
        value |= mask;
        iowrite32(value, addr);
        wmb();
}

void reg_clr(void __iomem *addr, u32 mask)
{
        u32 value;

        value =  ioread32(addr);
        rmb();
        value &= ~mask;
        iowrite32(value, addr);
        wmb();
}

static struct dma_pkt_sched_info * clk_meas_get_pdata(struct platform_device *pdev)
{
        struct dma_pkt_sched_info *pdata;
        struct resource *res;
        int status;
        unsigned int dt_val;

        /* allocate device info structure */
        pdata = devm_kzalloc(&pdev->dev, sizeof(struct dma_pkt_sched_info), GFP_KERNEL);
        if (!pdata)
                return ERR_PTR(-ENOMEM);

        /* read information from device tree */
        res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
        pdata->base_addr = devm_ioremap_resource(&pdev->dev, res);
        if (IS_ERR(pdata->base_addr))
                return pdata->base_addr;

        status = fwnode_property_read_u32(pdev->dev.fwnode, "xlnx,#slots", &dt_val);
        if (status)
                return ERR_PTR(status);
        pdata->slots = dt_val;

        /* DMA mask on full address region the system supports */
        /* Adapt dma_mask if PL IP is not capable of covering the entire adress range */
//        dma_mask = dma_get_required_mask(&pdev->dev);
        status = dma_set_mask_and_coherent(&pdev->dev, 0xFFFFFFFF);
        if (status)
                return ERR_PTR(status);

        pdata->pool = dma_pool_create("dma_pkt_sched_pool", &pdev->dev, (pdata->slots)*windows*win_size, 128, 0);
        if (!pdata->pool)
                return  ERR_PTR(-ENOMEM);
        pdata->dma_vaddr = dma_pool_alloc(pdata->pool, GFP_KERNEL, &pdata->dma_handle);
        if (!pdata->dma_vaddr)
                return  ERR_PTR(-ENOMEM);

        pr_info("DMA physical addr 0x%08X   virtual address 0x%08X\n", (unsigned int)(pdata->dma_handle), (unsigned int)(pdata->dma_vaddr));

        return pdata;
}

static long dma_pkt_sched_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
        struct dma_pkt_sched_info *pdata = file->private_data;

        switch(cmd)
        {
                case DMA_PSCHED_EN_IOCTL:
                        pr_debug("Enabling DMA packet scheduler\n");
                        reg_set(pdata->base_addr+DMA_PKT_SCHED_REG_GCFG, DMA_PKT_SCHED_REG_GCFG_BIT_ENA);
                        break;
                case DMA_PSCHED_DIS_IOCTL:
                        pr_debug("Disabling DMA packet scheduler\n");
                        reg_clr(pdata->base_addr+DMA_PKT_SCHED_REG_GCFG, DMA_PKT_SCHED_REG_GCFG_BIT_ENA);
                        break;
                case DMA_PSCHED_EN_SLOT_IOCTL:
                        pr_debug("Enabling DMA packet scheduler for slot 0x%08X\n", (u32)arg);
                        iowrite32((u32)arg, pdata->base_addr+DMA_PKT_SCHED_REG_SLTENA);
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

        /* nonseekable_open removes seek, and pread()/pwrite() permissions */
        return nonseekable_open(inode, file);
}

static const struct file_operations dma_pkt_sched_fops = {
        .owner   = THIS_MODULE,  /* used for reference counting */
        .open    = dma_pkt_sched_open,
//        .read    = dma_pkt_sched_read,
//        .release = dma_pkt_sched_release,
//        .llseek  = no_llseek,
        .unlocked_ioctl = dma_pkt_sched_ioctl,
#ifdef CONFIG_COMPAT
        .compat_ioctl   = dma_pkt_sched_ioctl,
#endif
};

static int dma_pkt_sched_probe(struct platform_device *pdev)
{
        struct dma_pkt_sched_info *dma_pkt_sched_info;
        int major;

//        pr_debug("xlnx,dma-pkt-sched-axi-1.0: probed\n");
        pr_info("xlnx,dma-pkt-sched-axi-1.0: probed\n");
        pr_info("Buffer size per slot: %d windows, %d bytes/window \n", windows, win_size);

        /* create and populate device info structure */
        dma_pkt_sched_info = clk_meas_get_pdata(pdev);
        if(IS_ERR(dma_pkt_sched_info))
                return PTR_ERR(dma_pkt_sched_info);

        platform_set_drvdata(pdev, dma_pkt_sched_info);

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

        return 0;
}

static int dma_pkt_sched_remove(struct platform_device *pdev)
{
        struct dma_pkt_sched_info *dma_pkt_sched_info = platform_get_drvdata(pdev);

//        pr_debug("xlnx,dma-pkt-sched-axi-1.0: removed\n");
        pr_info("xlnx,dma-pkt-sched-axi-1.0: removed\n");

        /* free allocated dma memory */
        dma_pool_free(dma_pkt_sched_info->pool, dma_pkt_sched_info->dma_vaddr, dma_pkt_sched_info->dma_handle);
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
