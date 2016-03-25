#define LINUX

#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/init.h>
#include <linux/slab.h>

#define DRIVER_AUTHOR "Chang Xiangzhong"
#define DRIVER_DESC "A very simple kernel driver"

static unsigned int param1 = 32;
static char param2[64];
static unsigned int param3[10];
static unsigned int param3_len;

module_param(param1, uint, S_IRUGO);
MODULE_PARM_DESC(param1, "This is the 1st param.");

module_param_string(param2, param2, 64, S_IRUGO);
MODULE_PARM_DESC(param2, "This is the 2nd param.");

module_param_array(param3, uint, &param3_len, S_IRUGO);
MODULE_PARM_DESC(param3, "This is the 3rd param, which is an array.");

static int hello_2_init(void)
{
    int off = 0, i = 0;
    size_t pt_buf_len = 512;
//     char print_buf[512];
    char* print_buf = (char*) kmalloc(pt_buf_len, GFP_KERNEL);

    if (!print_buf) {
        pr_alert("Failed to allocated memory\n");
        return 1;
    }

    for (i = 0; i < param3_len; i++) {
        off += snprintf(print_buf + off, pt_buf_len - off, "%d, ", param3[i]);
    }
    pr_alert("Hello, world!\nparam1 = %d, param2 = %s\n", param1, param2);
    pr_alert("param3 = %s\n", print_buf);

    kfree(print_buf);
    return 0;
}


static void hello_2_exit(void)
{
    pr_alert("Goodbye, world 2\n");
}

module_init(hello_2_init);

module_exit(hello_2_exit);

MODULE_LICENSE("MIT");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

