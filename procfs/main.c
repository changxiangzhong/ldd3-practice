#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>

#include <asm/uaccess.h>

#define PROC_FILE_NAME "hello_procfs"

static struct proc_dir_entry *proc_file;
static char message[] = "hello, procfs!\n";
static char *msg_ptr;

static ssize_t proc_file_read(struct file *filp,
        char *buffer,
        size_t length,
        loff_t *offset) {
    ssize_t bytes_read = 0;

    if (!*msg_ptr)
        return 0;

    msg_ptr = message;
    printk(KERN_INFO "procfile read (/proc/%s) called\n", PROC_FILE_NAME);

    while (length && *msg_ptr) {
        put_user(*(msg_ptr++), buffer++);
        length--;
        bytes_read++;
    }

    return bytes_read;
}

static int proc_file_open(struct inode *inode, struct file *flip)
{
    msg_ptr = message;
    return 0;
}

struct file_operations fops = {
    .read = proc_file_read,
    .open = proc_file_open
};

int init_module()
{
    proc_file = proc_create(PROC_FILE_NAME, S_IRUGO | S_IWUSR, NULL, &fops);
    return 0;
}

void cleanup_module()
{
    proc_remove(proc_file);
}
