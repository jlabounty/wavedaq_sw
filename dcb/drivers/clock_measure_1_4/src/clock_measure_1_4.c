// SPDX-License-Identifier: GPL-2.0
/*
 * PSI AXI Clock Measure Vivado IP.
 *
 * Driver for Xilinx Vivado IP for measuring clock frequencies in
 * programmable logic via AXI bus.
 *
 * Vivado Clock Measure IP and documentation available at
 * <https://github.com/paulscherrerinstitute/vivadoIP_clock_measure>
 *
 * 2020 Elmar Schmid <elmar.schmid@psi.ch>
 */

#include <linux/module.h>
#include <linux/property.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/io.h>

/*
 * A global framework for clock measure devices.
 */
static struct clk_meas_framework {
        /* A class of drivers for devices and sysfs framework */
        struct class *class;

        /* All clock measure devices will have this major device number */
        unsigned int major;

        void *cmdata[255];
} clk_meas;

/* Simple device registration */
#define CLK_MEAS_DATA(minor) clk_meas.cmdata[(minor)]
#define REGISTER_CLK_MEAS(minor, private) CLK_MEAS_DATA((minor)) = (private)

struct clk_meas_item {
        const char *label;
        int offset;
};

struct clk_meas_set {
        struct device *dev;
        unsigned int minor;
        void __iomem *base_addr;
        int n_meas;
        struct clk_meas_item *clk_meas;
};

static struct clk_meas_set * clk_meas_get_pdata(struct platform_device *pdev)
{
        struct clk_meas_set *pdata;
        struct fwnode_handle *parent, *child;
        struct clk_meas_item *clk_meas;
        unsigned int i;
        int count = -1;
        int status;
        struct resource *res;
        u32 reg;

        parent = pdev->dev.fwnode;

        count = device_get_child_node_count(&pdev->dev);
        if (count < 1)
                return ERR_PTR(-ENODEV);

        clk_meas = devm_kcalloc(&pdev->dev, count, sizeof(struct clk_meas_item), GFP_KERNEL);
        if (!clk_meas)
                return ERR_PTR(-ENOMEM);

        pdata = devm_kzalloc(&pdev->dev, sizeof(struct clk_meas_set), GFP_KERNEL);
        if (!pdata)
                return ERR_PTR(-ENOMEM);

        res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
        pdata->base_addr = devm_ioremap_resource(&pdev->dev, res);
        if (IS_ERR(pdata->base_addr))
                return pdata->base_addr;

        /* Check for available clock measurements */
        i = 0;
        device_for_each_child_node(&pdev->dev, child)
        {
                const char *label;

                status = fwnode_property_read_u32(child, "reg", &reg);
                if (status != 0)
                        return ERR_PTR(status);

                status = fwnode_property_read_string(child, "label", &label);
                if ((status != 0) && is_of_node(child))
                        label = to_of_node(child)->name;

                clk_meas[i].label = label;
                clk_meas[i].offset = 4 * reg;

                i++;
        }

        pdata->n_meas = count;
        pdata->clk_meas = clk_meas;

        return pdata;
}

static int clk_meas_open(struct inode *inode, struct file *file)
{
        int minor = iminor(inode);

        /* Identify this device, and associate the device data with the file */
        file->private_data = CLK_MEAS_DATA(minor);

        /* nonseekable_open removes seek, and pread()/pwrite() permissions */
        return nonseekable_open(inode, file);
}

static ssize_t clk_meas_read(struct file *file, char __user *buf, size_t count, loff_t * ppos)
{
        struct clk_meas_set *data = file->private_data;
        int len;
        unsigned int val;
        char str[256];
        int i;
        size_t lbl_size, max_lbl_size;

        /* Get max. label size */
        max_lbl_size = 0;
        for(i=0;i<data->n_meas;i++)
        {
                lbl_size = strlen(data->clk_meas[i].label);
                if(lbl_size>max_lbl_size)
                {
                        max_lbl_size = lbl_size;
                }
        }

        len = 0;
        for(i=0;i<data->n_meas;i++)
        {
                val = ioread32(data->base_addr + data->clk_meas[i].offset);
                len += snprintf(&str[len], sizeof(str)-len, "%-*s %10d\n", max_lbl_size, data->clk_meas[i].label, val);
        }

        if (len>count)
                /* inform user that buf is too small */
                len = -EINVAL;
        else if (copy_to_user(buf, str, len))
                len = -EFAULT;

        if(*ppos == 0)
        {
                *ppos = len;
                return len;
        }
        return 0;
}

static int clk_meas_release(struct inode *inode, struct file *file)
{
        return 0;
}

static const struct file_operations clk_meas_fops = {
        .owner   = THIS_MODULE,  /* used for reference counting */
        .open    = clk_meas_open,
        .read    = clk_meas_read,
        .release = clk_meas_release,
        .llseek  = no_llseek,
};

static int clk_meas_probe(struct platform_device *pdev)
{
        struct clk_meas_set *clk_meas_set;
        int ret;

        pr_debug("xlnx,clock-measure-1.4: probed\n");

        clk_meas_set = clk_meas_get_pdata(pdev);
        if(IS_ERR(clk_meas_set))
                return PTR_ERR(clk_meas_set);

        platform_set_drvdata(pdev, clk_meas_set);

        /*
         * A 'clk_meas' framework should be responsible for creating the class.
         * We do not have such a framework, so we create the class ourselves.
         */
        clk_meas.class = class_create(THIS_MODULE, "clk_meas");
        if (IS_ERR(clk_meas.class))
                return PTR_ERR(clk_meas.class);

        ret = register_chrdev(0, "clk_meas", &clk_meas_fops);
        if (ret < 0)
                return ret;

        /* Successfully registered */
        clk_meas.major = ret;

        /* Create only a single clk_meas device with minor 0. */
        clk_meas_set->minor = 0;

        /* Create the device file for userspace to interact with. */
        clk_meas_set->dev = device_create(clk_meas.class, NULL,
                                          MKDEV(clk_meas.major, clk_meas_set->minor),
                                          clk_meas_set, "clk_meas%d", clk_meas_set->minor);
        if (IS_ERR(clk_meas_set->dev))
                return PTR_ERR(clk_meas_set->dev);

        /* Register the device in the clk_meas device list. */
        REGISTER_CLK_MEAS(clk_meas_set->minor, clk_meas_set);

        return 0;
}

static int clk_meas_remove(struct platform_device *pdev)
{
        struct clk_meas_set *clk_meas_set = platform_get_drvdata(pdev);

        pr_debug("xlnx,clock-measure-1.4: removed\n");

        device_del(clk_meas_set->dev);
        /* kfree(clk_meas_set); not needed, cleanup done in platform_device.c */

        /* Framework cleanup. */
        unregister_chrdev(clk_meas.major, "clk_meas");
        class_destroy(clk_meas.class);

        return 0;
}

static const struct of_device_id clk_meas_dt_match[] = {
        { .compatible = "xlnx,clock-measure-1.4", },
        { }
};
MODULE_DEVICE_TABLE(of, clk_meas_dt_match);

static struct platform_driver clk_meas_driver = {
        .driver = {
                .owner = THIS_MODULE,
                .name = "clock-measure-1.4",
                .of_match_table = clk_meas_dt_match,
        },
        .probe = clk_meas_probe,
        .remove = clk_meas_remove,
};

module_platform_driver(clk_meas_driver);

MODULE_DESCRIPTION("PSI AXI Clock Measure Vivado IP driver");
MODULE_AUTHOR("Elmar Schmid <elmar.schmid@psi.ch>");
MODULE_LICENSE("GPL");
