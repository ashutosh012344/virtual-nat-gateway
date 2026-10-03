#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define PROC_NAME "virtual_nat"

static struct proc_dir_entry *proc_entry;

static int virtual_nat_show(
    struct seq_file *m,
    void *v
)
{
    seq_printf(
        m,
        "Virtual NAT Gateway Kernel Monitor\n"
    );

    seq_printf(
        m,
        "--------------------------------\n"
    );

    seq_printf(
        m,
        "Status: Kernel module loaded\n"
    );

    seq_printf(
        m,
        "Component: virtual_nat_monitor\n"
    );

    return 0;
}

static int virtual_nat_open(
    struct inode *inode,
    struct file *file
)
{
    return single_open(
        file,
        virtual_nat_show,
        NULL
    );
}

static const struct proc_ops virtual_nat_proc_ops = {
    .proc_open = virtual_nat_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init virtual_nat_init(void)
{
    printk(KERN_INFO
           "virtual_nat_monitor: module loaded\n");

    proc_entry = proc_create(
        PROC_NAME,
        0444,
        NULL,
        &virtual_nat_proc_ops
    );

    if (!proc_entry) {
        printk(KERN_ERR
               "virtual_nat_monitor: failed to create /proc/%s\n",
               PROC_NAME);

        return -ENOMEM;
    }

    printk(KERN_INFO
           "virtual_nat_monitor: /proc/%s created\n",
           PROC_NAME);

    return 0;
}

static void __exit virtual_nat_exit(void)
{
    proc_remove(proc_entry);

    printk(KERN_INFO
           "virtual_nat_monitor: module unloaded\n");
}

module_init(virtual_nat_init);
module_exit(virtual_nat_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ashutosh Das");
MODULE_DESCRIPTION(
    "Virtual NAT Gateway Linux Kernel Monitor"
);
MODULE_VERSION("1.0");
