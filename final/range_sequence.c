#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define FILE_NAME "result.txt"

static int start = 0;
static int stop = 10;
static int step = 1;

module_param(start, int, S_IRUGO);
module_param(stop, int, S_IRUGO);
module_param(step, int, S_IRUGO);

MODULE_LICENSE("GPL");

static int __init range_sequence_init(void)
{
    int i;
    printk(KERN_INFO "range_sequence started\n");

    for (i = start; i <= stop; i += step) {
        printk(KERN_INFO "%d ", i);
    }
    printk(KERN_INFO "\n");

    struct file *file;
    loff_t pos;

    file = filp_open(FILE_NAME, O_CREAT | O_WRONLY, 0644);
    if (IS_ERR(file)) {
        printk(KERN_ALERT "range_sequence: failed to open file\n");
        return -1;
    }


    pos = 0;
    kernel_write(file, "range_sequence: ", 16, &pos);

    char buffer[20];
    for (i = start; i <= stop; i += step) {
        sprintf(buffer, "%d ", i);
        kernel_write(file, buffer, strlen(buffer), &pos);
    }

    filp_close(file, NULL);
    printk(KERN_INFO "range_sequence: result saved to %s\n", FILE_NAME);

    return 0;
}

static void __exit range_sequence_exit(void)
{
    printk(KERN_INFO "range_sequence stopped\n");
}

module_init(range_sequence_init);
module_exit(range_sequence_exit);
