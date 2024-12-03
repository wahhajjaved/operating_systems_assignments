/*
 * vfifofum.c - implementation of a character based FIFO device driver
 * for CMPT 332 Lab 9 in 2024
 * Nakhba Mubashir, epl482, 11317060
 */

#include <linux/atomic.h> 
#include <linux/cdev.h> 
#include <linux/fs.h> 
#include <linux/init.h> 
#include <linux/kobject.h> 
#include <linux/module.h> 
#include <linux/string.h> 
#include <linux/sysfs.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/version.h>


#define DEVICE_NAME "vfifofum"
#define DEVNAME_SIZE 1024
#define EOF -1
#define N 8
#define MAXBUFF 32


struct Buffer{
    spinlock_t lock;
	unsigned int writers;
	unsigned int readers;
};

static struct Buffer buff[N];
static int vfifofum_open(struct inode *, struct file *);
static int vfifofum_release(struct inode *, struct file *);
static ssize_t vfifofum_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t vfifofum_write(struct file *, const char __user *, size_t, loff_t *);



static int major; /* our major number */
static struct class *cls;
static struct file_operations vfifofum_fops = {
  .read = vfifofum_read,
  .write = vfifofum_write,
  .open = vfifofum_open,
  .release = vfifofum_release,
};

static int __init vfifofum_init(void)
{
    int i;  
  major = register_chrdev(0, DEVICE_NAME, &vfifofum_fops);
  /* check to see that we got a major number back, else bail. */
  if (major < 0) {
    pr_alert("Registering vfifofum char device failed with %d\n", major);
    return major;
  }

  pr_info("vfifofum was assigned major %d\n", major);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0) 
    cls = class_create(DEVICE_NAME); 
#else 
    cls = class_create(THIS_MODULE, DEVICE_NAME); 
#endif 
    /* we will get assigned a major number, and will use 0 for the minor */
    for (i=0;i<(2*N); i+=2){
        /* two times to handle prod and consumer*/
        device_create(cls, NULL, MKDEV(major, i), NULL, DEVICE_NAME);
        pr_info("vfifofum created as /dev/%s\n", DEVICE_NAME);
        device_create(cls, NULL, MKDEV(major, i+1), NULL, DEVICE_NAME);
        pr_info("vfifofum created as /dev/%s\n", DEVICE_NAME);
        memset(buff,'\0',MAXBUFF);

        buff[i>>1].writers =0;
        buff[i>>1].readers =0;
    }
    /* happy happy, joy joy */
    return 0;
}


static void __exit vfifofum_exit(void)
{
    int i;
    for (i=0;i<(2*N); i++)
  /* say good night, Charlie... */ 
  device_destroy(cls, MKDEV(major, i));
  class_destroy(cls); 
  unregister_chrdev(major, DEVICE_NAME); 
  pr_info("vfifofum shutdown\n");
}

static int vfifofum_open(struct inode *, struct file *)
{
    int i=MAXBUFF;
  try_module_get(THIS_MODULE);
    spin_lock(&buff[i>>1].lock);
  if (i&0x1) buff[i>>1].readers++;
  else buff[i>>1].writers++;
  spin_unlock(&buff[i>>1].lock);
  return 0;
}


static int vfifofum_release(struct inode *, struct file *)
{
 int i=MAXBUFF;
    spin_lock(&buff[i>>1].lock);
  if (i&0x1) buff[i>>1].readers--;
  else buff[i>>1].writers--;
  spin_unlock(&buff[i>>1].lock);

  module_put(THIS_MODULE);
  return 0;
}


static ssize_t vfifofum_read(struct file *file, char __user *buffer, size_t length, loff_t *offset)
{
    int i=MAXBUFF;
  spin_lock(&buff[i>>1].lock);
  pr_alert("read not implmented!\n");
  return -EINVAL;
}

static ssize_t vfifofum_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset)
{
    int i=MAXBUFF;
    spin_lock(&buff[i>>1].lock);
  pr_alert("write not implmented!\n");
  return -EINVAL;
}

module_init(vfifofum_init); 
module_exit(vfifofum_exit); 

MODULE_LICENSE("GPL");
