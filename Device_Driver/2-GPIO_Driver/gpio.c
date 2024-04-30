#include "gpio.h"

/*
 * Function: driver_read
 * ---------------------
 * Called when data is read from a device file.
 */
ssize_t driver_read(struct file *file, char __user *user_buffer, size_t count, loff_t *offs){
    
    int not_copied;
    printk("%s: The count to read %ld \n", __func__, count);
    printk("%s: the offset %lld \n", __func__, *offs);

    // Count adjustment
    if (count + *offs > SIZE) //
    {
        count = SIZE - *offs;
    }

    not_copied = copy_to_user(user_buffer, &buffer[*offs], count);

    if (not_copied)
    {
        return -1;
    }

    *offs = count;
    return 0;
}
/*
 * Function: driver_write
 * ----------------------
 * Called when data is written to a device file.
 * 
 * Parameters:
 * - File: Pointer to the file structure representing the device file.
 * - user_buffer: Pointer to the buffer containing the data to be written.
 * - count: Number of bytes to write.
 * - offs: Pointer to the current file position.
 * 
 * Returns:
 * - Number of bytes successfully written, or a negative error code on failure.
 */
ssize_t driver_write(struct file *file, const char __user *user_buff, size_t count, loff_t *offs){
     
     int not_copied;
    printk("%s: The count to write  %ld \n", __func__, count);
    printk("%s: the offset %lld \n", __func__, *offs);
    // Count adjustment
    if (count + *offs > SIZE) //
    {
        count = SIZE - *offs;
    }

    if (!count){
        printk ("No space left!");
        return -1;        
    }

    not_copied = copy_from_user(&buffer[*offs], user_buff, count);

    switch(buffer[0]){
        case '1':
        gpio_set_value(led_pin, 1);
        break;

        case'0':
        gpio_set_value(led_pin, 0);
        break;
    }


    if (not_copied)
    {
        return -1;
    }
    *offs = count;

    return count;
}
/*
 * Function: driver_open
 * ---------------------
 * Called when the device file is opened.
 * 
 * Parameters:
 * - device_file: Pointer to the inode structure representing the device file.
 * - instance: Pointer to the file structure representing the opened file instance.
 * 
 * Returns:
 * - 0 on success, otherwise an error code.
 */
int driver_open (struct inode *device_file , struct file *instance)
{

    printk("%s Device is opened \n",__FUNCTION__);
    return 0;

}
/*
 * Function: driver_close
 * ----------------------
 * Called when the device file is closed.
 */
int driver_close (struct inode *device_file , struct file *instance)
{

    printk("%s Device is closed \n",__FUNCTION__);
    return 0;

}

struct file_operations fops = 
{
    .owner = THIS_MODULE, 
    .open = driver_open ,
    .release = driver_close,
    .read = driver_read,
    .write = driver_write
};

static int __init GPIO_init(void)
{
    int retval ;
    retval = alloc_chrdev_region(&device_number, 0, 2, "gpio_driver");
    if(retval == 0 )
    {
        printk("%s retval = 0 - registered Device number Major : %d - Minor %d\n", __FUNCTION__, MAJOR(device_number), MINOR(device_number));

    }else
    {
        printk("Couldn't register device number!\n");  
         return -1;
    }

    cdev_init(&st_char_dev, &fops);
    retval = cdev_add(&st_char_dev , device_number , number_of_devices);
    if (0 != retval)
    {
        printk("Couldn't register the device To the Kernel\n");
        goto CHAR_ERROR;
    }

    gpio_class = class_create("gpio_driver");
    if(gpio_class == NULL )
    {
        printk("Device class cannot be created!\n");
        goto CLASS_ERROR;
    }
    
    led_device = device_create(gpio_class , NULL , device_number ,NULL, "gpio_driver"); 

    if (led_device == NULL)
    {
        printk("Device class cannot be created!\n");
        goto DEVICE_ERROR;
    }
    
    printk("GPIO Driver has been Created Succesfully \n");

    if (gpio_request(led_pin, "rpi4_gpio_led")){
        printk("Cannot allocate this GPIO");
        goto GPIO_REQUEST_ERROR;
    }

    if (gpio_direction_output(led_pin, 0)){
        printk("cannot set the GPIO pin direction to be O/P \n");
        goto GPIO_DIR_ERROR;
    }


    return 0;


    GPIO_DIR_ERROR:
        gpio_free(led_pin);
    GPIO_REQUEST_ERROR:
        device_destroy(gpio_class, device_number);
    DEVICE_ERROR:
        class_destroy(gpio_class);
    CLASS_ERROR:
        cdev_del(&st_char_dev);
    CHAR_ERROR:
        unregister_chrdev_region(device_number, number_of_devices);
    return -1;
} 

static void __exit GPIO_exit(void)  
{   
    gpio_set_value(led_pin, 0);
    gpio_free(led_pin);
    cdev_del(&st_char_dev);
    device_destroy(gpio_class, device_number);
    class_destroy(gpio_class);
    unregister_chrdev_region(device_number, number_of_devices);

    printk("GPIO is unprobed \n");

}
module_init(GPIO_init);
module_exit(GPIO_exit);

//  lsmod
//  insmod $ modprobe
// rmmod delete mod
// mknod to access manual to the driver 
