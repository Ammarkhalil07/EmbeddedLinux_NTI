
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("Ammar");
MODULE_DESCRIPTION ("Hello world device driver");


/*
 * 1st : S_IRUSR > Read For USER
 * 2nd : S_IWUSR > Write for USER
 * 3rd : S_IRGRP > Read for GROUP
 * 4th : S_IWGRP > Write for GROUP
 */
// module_param(cnt, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
// module_param(major_num, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

/*
 * 1st :
 * 2nd : 6 >> USER Read-Write
 * 3rd : 6 >> Group Read-Write
 * 4th : 4 >> OTHER Read Only
 */


int number =0;
int major_number = 0;
dev_t device_no;

static int driver_open (struct inode *device_file , struct file *instance)
{

    printk("%s Device is opened \n",__FUNCTION__);
    return 0;

}

static int driver_close (struct inode *device_file , struct file *instance)
{

    printk("%s Device is closed \n",__FUNCTION__);
    return 0;

}

struct file_operations fops = 
{
    .owner = THIS_MODULE, 
    .open = driver_open ,
    .release = driver_close
};

module_param( number , int , S_IRUSR |S_IWUSR | S_IRGRP | S_IWGRP );
MODULE_PARM_DESC(number , "major number");


static int __init hellodriver_init(void)
{
    int retval ;
    //major_number = number;
    //printk(" hello world \n");
    retval = alloc_chrdev_region(&device_no, 0, 1, "my_test_num"); // Atomatically Assign Number for the device
    //retval = register_chrdev (major_number ,"my_test_driver", &fops);
    if(retval == 0 )
    {
        printk("%s retval = 0 - registered Device number Major : %d - Minor %d\n", __FUNCTION__, MAJOR(device_no), MINOR(device_no));

    }else
    {
        printk("Couldn't register device number!\n");  
         return -1;
    }
    /*int i =0;
    for ( i =0 ; i < number ; ++i)
    {    
        printk(" helloworld \n");
    }*/
    return 0;
} 

static void __exit hellodriver_exit(void)
{
    //unregister_chrdev(238 ,"my_test_driver");
    unregister_chrdev_region (device_no,1);
    printk(" goodbye \n");

}
module_init(hellodriver_init);
module_exit(hellodriver_exit);

//  lsmod
//  insmod $ modprobe
// rmmod delete mod
// mknod to access manual to the driver 
