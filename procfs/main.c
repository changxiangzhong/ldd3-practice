#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>

#include <asm/uaccess.h>

#define PROC_FILE_NAME "hello_procfs"

#define MESSAGE_LENGTH 80

static struct proc_dir_entry *proc_file;
static char message[MESSAGE_LENGTH];
static char *msg_ptr;

static ssize_t proc_file_read(struct file *filp,
        __user char *buffer,
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

ssize_t proc_file_write(struct file * flip, const char __user * buf, size_t length, loff_t * offset)
{
    int i;
    for(i = 0; i< MESSAGE_LENGTH - 1 && i < length; i++) {
        get_user(message[i], buf + i);
    }

    message[i] = '\0';

    return i;
}
static int proc_file_open(struct inode *inode, struct file *flip)
{
    msg_ptr = message;
    return 0;
}

struct file_operations fops = {
    .read = proc_file_read,
    .write = proc_file_write,
    .open = proc_file_open
};

int init_module()
{
    static const char def_msg[] = "Hello, procfs 2.0!\n";
    memcpy(message, def_msg, sizeof(def_msg));
    proc_file = proc_create(PROC_FILE_NAME, S_IRUGO | S_IWUGO, NULL, &fops);
    return 0;
}

void cleanup_module()
{
    proc_remove(proc_file);

}
