## Poky in Yocto Project

Welcome to the Poky in Yocto Project README! This document provides an overview of Poky, the reference system for the Yocto Project, and instructions on how to use the qemux86 target.

## What is Poky?

Poky is the reference system for the Yocto Project, providing a set of default configurations, recipes, and metadata to build a complete Linux distribution for embedded devices. It includes the OpenEmbedded build framework and BitBake build tool, along with additional layers and configurations specific to the Yocto Project.

## Using the qemux86 Target

The qemux86 target in Poky allows you to emulate an x86-based machine using the QEMU emulator. This is useful for testing and development purposes without the need for physical hardware.

### Prerequisites

Before using the qemux86 target, ensure you have the following prerequisites installed:

- Yocto Project and Poky environment set up. Follow the official documentation for installation instructions.
- Install the necessary dependencies and set up your development environment according to the Poky documentation.
- QEMU emulator installed on your system. You can install QEMU using your package manager or download it from the official website.

## Cloning Poky

To clone the OpenEmbedded repository, follow these steps:

1. Open a terminal window.
2. Navigate to the directory where you want to clone Poky.
3. Run the following command:
```bash
git clone -b dunfell git://git.yoctoproject.org/poky.git --depth=1
```

### Building the qemux86 Image

To build the qemux86 image using Poky, follow these steps:

1. Navigate to your Poky build directory.
2. Source the environment setup script:
```bash
source oe-init-build-env
```
3. Choose your target `export` MACHINE=qemux86
4. Building your image in a minimum size
```bash
bitbake -k core-image-minimal 
## The usage of -k is very important to avoid building errors til the end of builing and give you a summary for error if there any
```

### Troubleshoot Some Errors 
If you are facing an Error while building the image like 

`(gcc-9.5.0-r0 :do_compile) Failed` To resolve it or any corrupted package

```bash
bitbake -c clean gcc ## clean command makes you remove this package only 
```

