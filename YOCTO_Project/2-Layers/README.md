# LAYERS

In Yocto Project, a "layer" is a fundamental concept used to organize and manage the configuration, recipes, and other components needed to build an embedded Linux distribution. Layers provide a modular and flexible way to extend and customize the Yocto Project to meet the specific requirements of your embedded system.

## Layer priority

In the Yocto Project, "layer priority" refers to the order in which Yocto Project layers are evaluated and applied when building an image or recipe. Layer priority plays a crucial role in determining which recipes and configurations take precedence when there are overlapping or conflicting definitions in multiple layers. It ensures that the desired behavior and components are included in the final image or recipe.

## Build a layer

To create a layer we need to run the following command

```bash
# create a layer
bitbake-layers create-layer < path/to/meta-mynewlayer >
```

entering to the new layer added we will find conf file it has the configuration `meta-mynewlayer/conf/layer.conf` of the the layer

```bash
# We have a conf and classes directory, add to BBPATH
BBPATH .= ":${LAYERDIR}"

# We have recipes-* directories, add to BBFILES
BBFILES += "${LAYERDIR}/recipes-*/*/*.bb \
            ${LAYERDIR}/recipes-*/*/*.bbappend"

BBFILE_COLLECTIONS += "meta-mylayer"
BBFILE_PATTERN_meta-mylayer = "^${LAYERDIR}/"
BBFILE_PRIORITY_meta-mylayer = "6"

LAYERDEPENDS_meta-mylayer = "core"
LAYERSERIES_COMPAT_meta-mylayer = "dunfell"
```
## Adding the layer

```bash
# Add the layer
bitbake-layers add-layer <path/to/meta-mynewlayer>
```

## Recipes Example
we also will see example recipe we can run it by the following command

```bash
# run the example recipe
bitbake -e example
```
