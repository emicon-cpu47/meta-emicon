inherit image_types

# The sdcard requires the rootfs filesystem to be built before using
# it so we must make this dependency explicit.
IMAGE_TYPEDEP_sdcard-recovery += " tar"

IMAGE_DEPENDS_sdcard-recovery = "parted-native:do_populate_sysroot \
                        dosfstools-native:do_populate_sysroot \
                        mtools-native:do_populate_sysroot \
                        virtual/kernel:do_deploy \
                        ${@d.getVar('IMAGE_BOOTLOADER', True) and d.getVar('IMAGE_BOOTLOADER', True) + ':do_deploy' or ''}"

IMAGE_CMD_sdcard-recovery () {

	SD_ROOTFS=${IMAGE_ROOTFS}
	
	mkdir -p ${SD_ROOTFS}/opt/TISDK/nand
	cp ${DEPLOY_DIR_IMAGE}/MLO ${SD_ROOTFS}/opt/TISDK/nand
	cp ${DEPLOY_DIR_IMAGE}/u-boot.img ${SD_ROOTFS}/opt/TISDK/nand
	cp ${DEPLOY_DIR_IMAGE}/${KERNEL_IMAGETYPE} ${SD_ROOTFS}/opt/TISDK/

	cp ${DEPLOY_DIR_IMAGE}/${KERNEL_IMAGETYPE}-${KERNEL_DEVICETREE_NAND} ${SD_ROOTFS}/opt/TISDK/zImage-devicetree.dtb
	cp ${DEPLOY_DIR_IMAGE}/${IMAGE_BASENAME}-${MACHINE}.ubi ${SD_ROOTFS}/opt/TISDK/rootfs.ubi.img
	cp ${DEPLOY_DIR_IMAGE}/nand-recovery.sh ${SD_ROOTFS}/sbin

	# codesys is not needed for sdcard image
	rm  ${SD_ROOTFS}/etc/init.d/codesys
}

