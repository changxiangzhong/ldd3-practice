#define LINUX

#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/init.h>

#define DRIVER_AUTHOR "Chang Xiangzhong"
#define DRIVER_DESC "A very simple kernel driver"

static unsigned int param1 = 32;
static char param2[64] = "default param2";
// static uint param3[10] = {0, 420};

module_param(param1, uint, S_IRUGO);
MODULE_PARM_DESC(param1, "This is the 1st param.");

module_param_string(param2, param2, 64, S_IRUGO);
MODULE_PARM_DESC(param2, "This is the 2nd param.");
// module_param(param3, "1-9i", "0444");

static int hello_2_init(void)
{
    pr_alert("Hello, world!\nparam1 = %d, param2 = %s\n", param1, param2);
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

