SECTION = "kernel"
DESCRIPTION = "Linux kernel for TI devices"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

inherit kernel

require recipes-kernel/linux/linux-dtb.inc
require recipes-kernel/linux/setup-defconfig.inc
#require recipes-kernel/linux/multi-kernel.inc
require recipes-kernel/linux/cmem.inc

# Look in the generic major.minor directory for files
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-4.4:"

# Pull in the devicetree files into the rootfs
RDEPENDS_kernel-base += "kernel-devicetree"

# Add a run-time dependency for the PM firmware to be installed
# on the target file system.
RDEPENDS_kernel-base_append_ti33x = " amx3-cm3"
RDEPENDS_kernel-base_append_ti43x = " amx3-cm3"

# Add a run-time dependency for the VPE VPDMA firmware to be installed
# on the target file system.
RDEPENDS_kernel-base_append_dra7xx = " vpdma-fw"

# Install boot-monitor skern file into /boot dir of rootfs
RDEPENDS_kernel-base_append_keystone = " boot-monitor"

# Default is to package all dtb files for ti33x devices unless building
# for the specific beaglebone machine.
KERNEL_DEVICETREE_ti33x = "am335x-evm.dtb am335x-evmsk.dtb am335x-bone.dtb am335x-boneblack.dtb"
KERNEL_DEVICETREE_varsomam33 = "var-som-am33.dtb"

KERNEL_EXTRA_ARGS += "LOADADDR=${UBOOT_ENTRYPOINT}"

COMPATIBLE_MACHINE = "ti33x|ti43x|omap-a15|omap3|omap4|keystone"

S = "${WORKDIR}/git"

BRANCH = "var-som-AMx3-sdk-linux-03.01.00"

SRCREV = "${AUTOREV}"
PV = "4.4.19+git${SRCPV}"

# Append to the MACHINE_KERNEL_PR so that a new SRCREV will cause a rebuild
MACHINE_KERNEL_PR_append = "m"
PR = "${MACHINE_KERNEL_PR}"

KERNEL_CONFIG_DIR = "${S}/ti_config_fragments"

# SoC specific config fragments are not enabled yet
KERNEL_CONFIG_FRAGMENTS_append_ti33x = " ${KERNEL_CONFIG_DIR}/am33xx_only.cfg"
KERNEL_CONFIG_FRAGMENTS_append_ti43x = " ${KERNEL_CONFIG_DIR}/am43xx_only.cfg"
KERNEL_CONFIG_FRAGMENTS_append_dra7xx = " ${KERNEL_CONFIG_DIR}/dra7_only.cfg"

MULTI_CONFIG_BASE_SUFFIX = ""

# KERNEL_GIT_URI = "git://github.com/varigit/VAR-SOM-AMx3-Kernel-4-x.git"
KERNEL_GIT_URI = "git://github.com/emicon-cpu47/VAR-SOM-AMx3-Kernel-4-x.git"

KERNEL_GIT_PROTOCOL = "git"
SRC_URI += "${KERNEL_GIT_URI};protocol=${KERNEL_GIT_PROTOCOL};branch=${BRANCH} \
            file://defconfig"


SRC_URI_append_emcpu47 += " \
    file://emcpu47.dts \
    file://patch-4.4.19-rt27.patch \
"

do_compile_prepend_emcpu47 () {
    cp -f ${WORKDIR}/*.dts ${WORKDIR}/*.dtsi ${S}/arch/arm/boot/dts/
}

SRC_URI_append_emcpu47n1g += " \
    file://emcpu47n1g.dts \
    file://patch-4.4.19-rt27.patch \
    file://patch-dts-1Gnand.patch \
"

do_compile_prepend_emcpu47n1g () {
    cp -f ${WORKDIR}/*.dts ${WORKDIR}/*.dtsi ${S}/arch/arm/boot/dts/
}


SRC_URI_append_emcpu47n1g2 += " \
    file://emcpu47n1g2.dts \
    file://patch-4.4.19-rt27.patch \
    file://patch-dts-1Gnand_new.patch \
"

do_compile_prepend_emcpu47n1g2 () {
    cp -f ${WORKDIR}/*.dts ${WORKDIR}/*.dtsi ${S}/arch/arm/boot/dts/
}