
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "file://demoapp.c"

S = "${WORKDIR}/build"


do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/demoapp.c -o ${S}/demoapp
}

do_install() {
install -d ${D}${bindir}
install -m 0755 ${S}/demoapp ${D}${bindir}
}




# * **Fetch** (do_fetch) :   Fetches the source code
# * **Unpack** (do_upack) : Unpacks the source code into a working directory
# * **Patch** (do_patch) : Locates patch files and applies them to the source code
# * **Configure** (do_configure) : Configures the source by enabling and disabling any build-time and configuration options for the software being built.
# * **Compile** (do_compile) : Compiles the source in the compilation directory
# * **Install** (do_install) : Copies files from the compilation directory to a holding area