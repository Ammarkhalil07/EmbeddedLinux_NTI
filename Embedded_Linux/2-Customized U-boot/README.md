# U-boot

U-Boot, the widely used boot loader in Linux-based embedded devices, is released as open source under the GNU GPLv2 license. It supports a broad range of microprocessors, including MIPS, ARM, PPC, Blackfin, AVR32, and x86.

## Setup U-boot

### Download U-Boot

```bash
git clone git@github.com:u-boot/u-boot.git
cd u-boot/
git checkout v2022.07
```

### Configure U-Boot Machine

In order to find the machine supported by U-Boot:

```bash
ls configs/ | grep [your machine] 
```

#### Vexpress Cortex A9 (Qemu)

In the U-boot directory, assign this value:

```bash
# Set the Cross Compiler into the environment
# To be used by the u-boot
export CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf-
export ARCH=arm

# load the default configuration of ARM Vexpress Cortex A9
make vexpress_ca9x4_defconfig
```



### Configure U-Boot 

In this part, configure some U-boot configurations for the specific board chosen:

```bash
make menuconfig
```

**The customer requirement are like following**:

- [ ] Support **editenv**.
- [ ] Support **bootd**.
- [ ] Store the environment variable inside file call **uboot.env**.
- [ ] Unset support of **Flash**
- [ ] Support **FAT file system**
  - [ ] Configure the FAT interface to **mmc**
  - [ ] Configure the partition where the fat is store to **0:1**

## SD Card

In this section it's required to have SD card with first partition to be FAT as pre configured in **U-boot Menuconfig**.

### Qemu

In order to Emulate SD card to attached to Qemu following steps will be followed:

```bash
# Change directory to the directory before U-Boot
cd ..

# Create a file with 1 GB filled with zeros
dd if=/dev/zero of=sd.img bs=1M count=1024
```


### Configure the Partition Table for the SD card

```bash
# for the VIRTUAL SD card
cfdisk sd.img
```

| Partition Size | Partition Format | Bootable  |
| :------------: | :--------------: | :-------: |
|    `200 MB`    |     `FAT 16`     | ***Yes*** |
|    `800 MB`    |     `Linux`      | ***No***  |

**write** to apply changes

### Loop Driver

To emulate the sd.img file as a sd card we need to attach it to **loop driver** to be as a **block storage**

```bash
# attach the sd.img to be treated as block storage
sudo losetup -f --show --partscan sd.img

# Running the upper command will show you
# Which loop device the sd.img is connected
# take it and assign it like down bellow command

# Assign the Block device as global variable to be treated as MACRO
export DISK=/dev/loop<x>
```

### Format Partition Table

As pre-configured from **cfdisk** command, first partition is **FAT**:

```bash
# Formating the first partition as FAT
sudo mkfs.vfat -F 16 -n boot ${DISK}p1
```

 As pre-configured from **cfdisk** Command second partition is **Linux**:

```bash
# format the created partition by ext4
sudo mkfs.ext4 -L rootfs ${DISK}p2
```

## Test U-Boot

Check that **U-Boot** and the **SD card** are working.

### Vexpress-a9 (QEMU)

Start Qemu with the **Emulated** SD card:

```bash
qemu-system-arm -M vexpress-a9 -m 128M -nographic \
-kernel u-boot/u-boot \
-sd sd.img
```

## Initialize TFTP protocol

### Ubuntu

```bash
#Switch to root
sudo su
#Make sure you are connected to internet
ping google.com
#Download tftp protocol
sudo apt-get install tftpd-hpa
#Check the tftp ip address
ip addr `will be needed`
#Change the configuration of tftp
nano /etc/default/tftpd-hpa
	#write inside the file
    tftf_option = “--secure –-create”
#Restart the protocal
Systemctl restart tftpd-hpa
#Make sure the tftp protocol is running
Systemctl status tftpd-hpa
#Change the file owner
cd /srv
chown tftp:tftp tftp 
#Move your image or file to the server
cp [File name] /srv/tftp
```

### Create Virtual Ethernet For QEMU


Create a script `qemu-ifup` :

```bash
#!/bin/sh
ip a add 192.168.0.1/24 dev $1
ip link set $1 up
```

#### Start Qemu

In order to start Qemu with the new virtual ethernet:

```bash
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic \
-kernel u-boot/u-boot \
-sd sd.img \
-net tap,script=./qemu-ifup -net nic
```

## Setup U-Boot IP address

```bash
#Apply ip address for embedded device
setenv ipaddr [chose]
#Set the server ip address that we get from previous slide
setenv serverip [host ip address]

#### WARNING ####
#the ip address should has the same net mask

```

## Load File to RAM

First we need to know the ram address by running the following command:

```bash
# this commend will show all the board information and it start ram address
bdinfo
```

### Load from FAT

```bash
# addressRam is a variable knowen from bdinfo commend
fatload mmc 0:1 [addressRam] [fileName]
```

### Load from TFTP

```bash
# addressRam is a variable knowen from bdinfo commend
tftp [addressRam] [fileName]
```

