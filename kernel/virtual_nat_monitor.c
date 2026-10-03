
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

#define PROC_NAME "virtual_nat"
static struct proc_dir_entry *proc_entry;

static unsigned long total_packets;
static unsigned long outgoing_packets;
static unsigned long incoming_packets;
static unsigned long nat_translations;
static unsigned long reverse_nat_translations;
static unsigned long port_forwarded_packets;

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
        "Total packets          : %lu\n",
        total_packets
    );

    seq_printf(
        m,
        "Outgoing packets       : %lu\n",
        outgoing_packets
    );

    seq_printf(
        m,
        "Incoming packets       : %lu\n",
        incoming_packets
    );

    seq_printf(
        m,
        "NAT translations       : %lu\n",
        nat_translations
    );

    seq_printf(
        m,
        "Reverse translations   : %lu\n",
        reverse_nat_translations
    );

    seq_printf(
        m,
        "Port-forwarded packets : %lu\n",
        port_forwarded_packets
    );

    return 0;
}

static ssize_t virtual_nat_write(
    struct file *file,
    const char __user *buffer,
    size_t count,
    loff_t *position
)
{
    char data[256];

    if (count >= sizeof(data)) {
        return -EINVAL;
    }

    if (copy_from_user(data, buffer, count)) {
        return -EFAULT;
    }

    data[count] = '\0';

    if (sscanf(
            data,
            "total=%lu outgoing=%lu incoming=%lu nat=%lu reverse=%lu forward=%lu",
            &total_packets,
            &outgoing_packets,
            &incoming_packets,
            &nat_translations,
            &reverse_nat_translations,
            &port_forwarded_packets
        ) != 6) {

        return -EINVAL;
    }

    return count;
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
    .proc_write = virtual_nat_write,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init virtual_nat_init(void)
{
    total_packets = 0;
    outgoing_packets = 0;
    incoming_packets = 0;
    nat_translations = 0;
    reverse_nat_translations = 0;
    port_forwarded_packets = 0;

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
