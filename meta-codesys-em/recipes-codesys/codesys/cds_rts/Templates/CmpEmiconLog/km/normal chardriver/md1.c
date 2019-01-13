#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/hid.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mikhail Shvetsov <lameli67@gmail.com>");

#define MD1_DEVICE_NAME "eudyptula"
#define MD1_MY_ID "d1e88e706c32"

/* Number of devices to create */
#ifndef MD1_FIRST_MINOR
#define MD1_FIRST_MINOR 0
#endif

#ifndef MD1_NUMBER_DEVICES
#define MD1_NUMBER_DEVICES 1
#endif

int md1_major = 0;
struct cdev *md1_cdev = NULL;

struct md1_dev {
	struct cdev cdev;	  /* Char device structure		*/
	char *id;
} *my_dev;

int i = 0;
ssize_t md1_read(struct file *filp, char __user *buf, size_t count,
	loff_t *f_pos)
{

	ssize_t size = strlen(my_dev->id);
	if (*f_pos >= size)
        	return 0;
	if (*f_pos + count > size)
		count = size - *f_pos;

	if (copy_to_user(buf, my_dev->id, count))
		return -EFAULT;	
	
	*f_pos += count;
	return count;
}
ssize_t md1_write(struct file *filp, const char __user *buf, size_t count,
	loff_t *f_pos)
{
	pr_debug("md1: write\n");
	return 0;
}

int md1_open(struct inode *inode, struct file *filp)
{
	pr_debug("md1: open\n");
	return 0;
}

int md1_release(struct inode *inode, struct file *filp)
{
	pr_debug("md1: release\n");
	return 0;
}

struct file_operations md1_fops = {
	.owner 	= THIS_MODULE,
	.read 	= md1_read,
	.write 	= md1_write,
	.open 	= md1_open,
	.release = md1_release,
};

static int __init md_init(void)
{
	int result;
	int err; 
	dev_t dev = 0;
	int dev_no;

	pr_debug("+ My module md1: Hello World!\n");

	result = alloc_chrdev_region(&dev, MD1_FIRST_MINOR, MD1_NUMBER_DEVICES, 
		MD1_DEVICE_NAME);
	md1_major = MAJOR(dev);

	if (result < 0){
		pr_debug("md1: can't get major %d\n", md1_major);
		return result;
	}
	pr_debug("md1: get major %d\n", md1_major);

	/* Allocate the array of devices */
	my_dev = (struct md1_dev *)kzalloc(sizeof(struct md1_dev), GFP_KERNEL);
	if (my_dev == NULL)
		return -ENOMEM;

	 my_dev->id = MD1_MY_ID;

	/* Construct device */
	dev_no = MKDEV(md1_major, MD1_FIRST_MINOR); // one device
	cdev_init(&my_dev->cdev, &md1_fops);
	my_dev->cdev.owner = THIS_MODULE;
	// my_dev->cdev.ops = &md1_fops;
	err = cdev_add(&my_dev->cdev, dev_no, 1);
	if (err)
		pr_debug("Error %d adding md1", err);
	
}

static void __exit md_exit(void)
{
	pr_debug("+ My module md1: Goodbye World!\n");
	cdev_del(md1_cdev);
	unregister_chrdev_region(MKDEV(md1_major, 0), MD1_NUMBER_DEVICES);
}

module_init(md_init);
module_exit(md_exit);
