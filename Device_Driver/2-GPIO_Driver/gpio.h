#ifndef GPIO
#define GPIO

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include <linux/gpio.h>
#include <linux/string.h>


/*
 * 1st : S_IRUSR > Read For USER
 * 2nd : S_IWUSR > Write for USER
 * 3rd : S_IRGRP > Read for GROUP
 * 4th : S_IWGRP > Write for GROUP
 */

/*
 * 1st :
 * 2nd : 6 >> USER Read-Write
 * 3rd : 6 >> Group Read-Write
 * 4th : 4 >> OTHER Read Only
 */


MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("Ammar");
MODULE_DESCRIPTION ("GPIO Driver for linux");

#define SIZE 15 
#define led_pin 23
#define number_of_devices 1


dev_t device_number;
static unsigned char buffer[SIZE] = "";

struct cdev st_char_dev;
struct class *gpio_class;
struct device *led_device;

int driver_open(struct inode *device_file, struct file *instance);
int driver_close(struct inode *device_file, struct file *instance);
ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs);
ssize_t driver_read(struct file *File,char *user_buffer, size_t count, loff_t *offs);

#endif // !GPIO