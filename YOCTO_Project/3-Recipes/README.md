# Recipes in Yocto Project

## What are Yocto Recipes?

In Yocto, a recipe is a set of metadata and instructions that describe how to build a specific component or software package. Recipes are written using the Recipe Specific Language (RSL) and typically have a `.bb` extension. They play a crucial role in the Yocto build system as they define the steps needed to fetch, configure, compile, and package software components or applications.

## Components of a Yocto Recipe

A typical Yocto recipe includes the following components:

- **Metadata**: Information such as package name (`PN`), version (`PV`), license (`LICENSE`), maintainer (`MAINTAINER`), and a brief description (`SUMMARY`) of the package.
- **Source Fetching**: Instructions on where to fetch the source code using the `SRC_URI` variable.
- **Dependency Management**: Definition of dependencies using the `DEPENDS` variable.
- **Configuration**: Instructions for configuring the build system, often done in functions like `do_configure()`.
- **Compilation**: Instructions for compiling the source code, typically in functions like `do_compile()`.
- **Installation**: Installation of the package into a temporary directory (`${D}`) using `do_install()`.
- **Packaging**: Packaging of installed files into a suitable format for deployment.


## How to Find Packages?

```bash
bitbake-layers show-recipes <Package_Name>
```

## How to Add Package?

After creating a layer like how we did before, and create a recipe inside the layer.

Add the following line in `local.conf` file.

```bash
IMAGE_INSTALL:append = " Package_name"
```

## Organizing Recipes

Recipes are organized within Yocto layers, where each layer can contain one or more recipes. Layers allow for modularization and separation of concerns in the build system, making it easier to manage and maintain complex projects.

## Conclusion

Recipes in Yocto provide a standardized and structured way to describe how software components should be built and integrated into custom Linux distributions. They are essential for creating custom embedded Linux systems tailored to specific hardware platforms and use cases.
