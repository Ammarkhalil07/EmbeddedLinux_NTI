# Customizing the Linux Kernel for ARM Cortex-A9 Architecture on Vexpress [ Qemu ]

The Linux kernel is the foundational component of the Linux operating system, responsible for managing hardware resources, processes, and system calls. This guide outlines the process of customizing and building the Linux kernel tailored for ARM Cortex-A9 architecture using the arm-linux-cortexa9 compiler for the Vexpress platform.

## Downloading the Linux Kernel

Clone the Linux kernel repository from the official source:

```bash
git clone --depth=1 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
cd linux
```

---

## Configuring the Kernel


Configure the kernel for the Vexpress platform:
```bash
make ARCH=arm vexpress_defconfig
```


Identify the kernel version:
```bash
make ARCH=arm kernelversion
```

---

## Kernel Configuration


Ensure the following configurations are set in the kernel:

1) Enable devtmpfs
2) Change kernel compression to XZ
3) Personalize kernel local version to your name and append '-v1.0'

---

## Building the Kernel

Export compiler and architecture variables:

```bash
export CROSS_COMPILE=PathToCompiler/arm-linux-cortexa9Compiler
export ARCH=arm
```

Set maximum open file descriptors:
```bash
ulimit -n 8192
```


Configure the kernel:
```bash
make menuconfig
```


Build the kernel, modules, and device tree binary:

```bash
make -j4 zImage modules dtbs
```

---

## Compiling Modules and Storing in Rootfs


Install compiled modules into the root filesystem staging area:

```bash
make -j4 ARCH=arm CROSS_COMPILE=PathToCOmpiler/arm-cortex_a9-linux-gnueabihf- INSTALL_MOD_PATH=$HOME/rootfs modules_install
```


_Note: Kernel modules are put into the directory /lib/modules/[kernel version], relative to the root of the filesystem._

---

## Booting from TFTP Server


Copy zImage and device tree binary to the TFTP server:

```bash
cp linux/arch/arm/boot/zImage /srv/tftp/
cp linux/arch/arm/boot/dts/*-ca9.dtb /srv/tftp/
```


Start Qemu to boot on U-boot:

```bash
bashscript_QemuStartUboot ~/u-boot/u-boot ~/sdCard/sd.img ~/sdCard/tftp_bash
```


Set the bootargs:


```bash
bootargs=console=ttyAMA0 root=/dev/mmcblk0p2 rootfstype=ext4 rw rootwait init=/sbin/init
saveenv
```
you could set the init process as you like as **example** `init=/bin/sh`

---

## Using my own Bash Scripts


Using **"ubootScript_imageLoading"** Script:

- Load kernel image `zImage`, DTB `vexpress-v2p-ca9.dtb` from TFTP into RAM and then boot the kernel with its device tree.

```bash
setenv ipaddr 192.168.1.102
setenv serverip 192.168.1.100

#intial value to LOAD_SUCCESS to false 
setenv LOAD_SUCCESS "false"

setenv LOAD_FROM_SERVER 'echo "Loading from Server.."; if tftp $kernel_addr_r zImage; then if tftp $fdt_addr_r vexpress-v2p-ca9.dtb; then echo "Loading zImage and dtb from Server is DONE!"; bootz $kernel_addr_r - $fdt_addr_r; else echo "Failed to load dtb from server"; fi; else echo "Failed to load zImage from Server!"; setenv LOAD_SUCCESS "true"; fi'

setenv LOAD_FROM_FAT 'echo "Loading from FAT.."; if "$LOAD_SUCCESS" != "true"; then if mmc dev; then if fatload mmc 0:1 $kernel_addr_r zImage; then if fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb; then echo "Loading zImage and dtb from FAT is DONE!"; bootz $kernel_addr_r - $fdt_addr_r; else echo "Failed to load dtb from FAT"; setenv LOAD_SUCCESS "true"; fi; else echo "Failed to load zImage from FAT"; fi; else echo "mmc device not found"; fi; else echo "Error: Already Loaded from Server"; fi'

run LOAD_FROM_SERVER

run LOAD_FROM_FAT

```
