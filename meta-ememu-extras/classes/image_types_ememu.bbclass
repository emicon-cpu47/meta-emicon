inherit image_types

IMAGE_BOOTLOADER ?= "u-boot"

# Handle u-boot suffixes
UBOOT_SUFFIX ?= "bin"
UBOOT_SUFFIX_SDCARD ?= "${UBOOT_SUFFIX}"

# Boot partition volume id
BOOTDD_VOLUME_ID ?= "Boot ${MACHINE}"

# Boot partition size [in KiB]
BOOT_SPACE ?= "8192"

# Set alignment to 4MB [in KiB]
IMAGE_ROOTFS_ALIGNMENT = "4096"

IMAGE_DEPENDS_sdcard-ememu = "parted-native:do_populate_sysroot \
                        dosfstools-native:do_populate_sysroot \
                        mtools-native:do_populate_sysroot \
                        virtual/kernel:do_deploy \
                        codesys:do_deploy \
                        ${@d.getVar('IMAGE_BOOTLOADER', True) and d.getVar('IMAGE_BOOTLOADER', True) + ':do_deploy' or ''}"

# ememu-extras:do_deploy 

# SDCARD_B = "${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.rootfs.sdcard-ememu"
UPDATE = "${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.supdate"
UPDATE_OLD = "${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.update"


IMAGE_CMD_sdcard-ememu () {
	mkdir -p ${DEPLOY_DIR_IMAGE}/ememu/ememu/system
	cp ${DEPLOY_DIR_IMAGE}/${IMAGE_LINK_NAME}.ext3 ${DEPLOY_DIR_IMAGE}/ememu/ememu/system/emufs.ext3
	cp ${DEPLOY_DIR_IMAGE}/zImage ${DEPLOY_DIR_IMAGE}/ememu/ememu/system/emu_kernel
	cp ${DEPLOY_DIR_IMAGE}/zImage-vexpress-v2p-ca9.dtb ${DEPLOY_DIR_IMAGE}/ememu/ememu/system/emu.dtb
	
	rm -r ${DEPLOY_DIR_IMAGE}/ememu/CODESYS
	cp -rl ${DEPLOY_DIR_IMAGE}/CODESYS ${DEPLOY_DIR_IMAGE}/ememu/
	rm -r ${DEPLOY_DIR_IMAGE}/CODESYS
}

# The sdcard requires the rootfs filesystem to be built before using
# it so we must make this dependency explicit.

IMAGE_TYPEDEP_sdcard-ememu += "ext3"
