# Implementing Custom Daemon App with BusyBox Init Process

## Objective:
In this lab, we will utilize the BusyBox init process to run a custom daemon application in the background. Participants will gain hands-on experience in configuring the system initialization process and managing daemon processes using BusyBox.

## Step 1: Prepare the System:
   - Mount the SD card and navigate to the root filesystem.

## Step 2: Edit inittab File:
   - Open the `/etc/inittab` file and configure the system initialization process:
```bash
     # Mount proc and sys filesystems
     null::sysinit:/bin/mount -t proc proc /proc
     null::sysinit:/bin/mount -t sysfs sysfs /sys

     # Execute when the system starts
     ::sysinit:/etc/init.d/rcS

     # Prompt to enter the shell
     console::askfirst:-/bin/sh

     # Execute when the system shuts down
     ::shutdown:/etc/init.d/rcK
```

## Step 3: Edit rcS Script:
   - Modify the `/etc/init.d/rcS` script to start the daemon application:
```bash
     #!/bin/sh
     echo "Initializing rcS..."
     daemonapp &
```

# Step 4: Edit rcK Script:
   - Modify the `/etc/init.d/rcK` script to stop the daemon application gracefully:
```bash
     echo "Shutting down rcK..."
     pkill -e daemonapp
     sleep 3
```

## Step 5: Create Daemon App:
   - Create the `daemonapp` script in `/usr/bin` to define the behavior of the daemon application:
```bash
     #!/bin/sh
     while true 
     do 
         date >> /tmp/daemon.test
         sleep 10
     done
```

## Step 6: Run QEMU Virtual Machine:
   - Execute the QEMU virtual machine using the provided script `bootcmdscript`:
```bash
#!/usr/bin/bash

#load the zimage and dtb to kernel and fdt from SD card
setenv loadfrom_fat "fatload mmc 0:1 $kernel_addr_r zImage ; fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb"

#load the image and dtb to kernel and fdt from tftp
setenv loadfrom_tftp "tftp $kernel_addr_r zImage ; tftp $fdt_addr_r vexpress-v2p-ca9.dtb"

#if the image and dtb are found -> it will print "kernel found"
setenv booting "if bootz $kernel_addr_r - $fdt_addr_r;then echo "Kernel Found";else echo "Kernel not found";fi"

#if the image and dtb are not found in the SD card -> load them from tftp / runbooting check
setenv load_image "if run loadfrom_fat ;then true ;else run loadfrom_tftp ;fi ; run booting"

#set boot arguments
#setenv bootargs "console=ttyAMA0,38400n8 root=/dev/mmcblk0p2 rootfstype=ext4 rw rootwait init=/sbin/init"

#if the SD card is found -> echo dev found and load the image from the SD card
#if SD card is not found -> echo dev not found and load the image from tftp 
setenv bootcmd "if mmc dev; then echo "dev found"; run load_image; else echo "dev not found"; run loadfrom_tftp; run booting; fi"

run bootcmd

bash
```

## Step 7: Verify Daemon Functionality:
   - After booting the system, observe the initialization message "Initializing rcS...".
   - Verify the daemon application functionality by monitoring the log output:
```bash
     tail -f /tmp/daemon.test
```

## Step 8: Check Process ID:
   - Confirm the daemon application process is running using the `ps` command:
```bash
     ps -ef | grep daemonapp
```

## Conclusion:
Participants have successfully configured the BusyBox init process to manage a custom daemon application, demonstrating practical knowledge in system initialization and process management using BusyBox.



