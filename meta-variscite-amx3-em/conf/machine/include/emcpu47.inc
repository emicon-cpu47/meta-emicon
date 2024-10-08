require conf/machine/include/var-ti33x.inc

CUSTOM_IMAGE_VER = "6.0"

# Use built-in LCD by default
XSERVER += "xf86-input-tslib"
MACHINE_GUI_CLASS = "smallscreen"
MACHINE_FEATURES += "touchscreen"

IMAGE_CLASSES += "image_types_sdrecovery"

IMAGE_FSTYPES += " ubi tar.gz sdcard-recovery wic"

# Should be same as BASENAME
IMAGE_NAME_VERSION ??= "${DATETIME}"
IMAGE_NAME = "${IMAGE_BASENAME}-${MACHINE}-${IMAGE_NAME_VERSION}-${CUSTOM_IMAGE_VER}"

IMAGE_NAME[vardepsexclude] = "IMAGE_NAME_VERSION"

SERIAL_CONSOLE = "115200;ttyS0"

# ignore arago psplash changes
BBMASK = "meta-arago/meta-arago-distro/recipes-core/psplash"

# UBI information.  Note that this is board and kernel specific.  Changes
# in your kernel port may require changes in these variables.  For more
# details about this board please see
# http://processors.wiki.ti.com/index.php/UBIFS_Support

# do ubiattach /dev/ubi_ctrl -m 7 -O 2048
# From dmesg:
# UBI: smallest flash I/O unit:    2048
# UBI: logical eraseblock size:    126976 bytes
# from ubiattach stdout:
# UBI device number 0, total 1988 LEBs
MKUBIFS_ARGS = "-F -m 2048 -e 126976 -c 4900"

# do ubiattach /dev/ubi_ctrl -m 7 -O 2048
# from dmesg:
# UBI: smallest flash I/O unit:    2048
# UBI: physical eraseblock size:   131072 bytes (128 KiB)
# UBI: sub-page size:              512
# UBI: VID header offset:          2048 (aligned 2048)
UBINIZE_ARGS = "-m 2048 -p 128KiB -s 512 -O 2048"

DISTRO_FEATURES_append = " bluez5"
#DISTRO_FEATURES_remove = "x11 wayland opengl pulseaudio opengles egl wifi bluetooth"

# tisdk-images: openssh conflicts with dropbear: 

RDEPENDS_packagegroup-arago-tisdk-addons_remove = " dropbear"
BBMASK = "oe-core/meta/recipes-core/dropbear"

IMAGE_INSTALL_append = " libstdc++ mtd-utils mtd-utils-ubifs htop openssh codesys am33-recovery-utils lcd-menu-cpu47 rt-tests devmem2"

# SDCARD parameters
WKS_FILE = "sdimage-bootpart.wks"
IMAGE_BOOT_FILES = "u-boot-sd/*"
IMAGE_ROOTFS = "${DEPLOY_DIR_IMAGE}/rootfs"
IMAGE_TYPEDEP_wic +=" sdcard-recovery"
do_image_wic[depends] += " mtools-native:do_populate_sysroot dosfstools-native:do_populate_sysroot "

#IMAGE_ROOTFS_EXTRA_SPACE = "409600"

# password generated: openssl passwd <password>
inherit extrausers
EXTRA_USERS_PARAMS = "\
    usermod -p PAi8fUWK9BpUo root; \
"