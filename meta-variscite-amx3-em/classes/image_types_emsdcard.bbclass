inherit image_types

# The sdcard requires the rootfs filesystem to be built before using
# it so we must make this dependency explicit.
IMAGE_TYPEDEP_sdcard-beijer += " tar"

IMAGE_DEPENDS_sdcard-emicon = "parted-native:do_populate_sysroot \
                        dosfstools-native:do_populate_sysroot \
                        mtools-native:do_populate_sysroot \
                        virtual/kernel:do_deploy \
                        ${@d.getVar('IMAGE_BOOTLOADER', True) and d.getVar('IMAGE_BOOTLOADER', True) + ':do_deploy' or ''}"

SDCARD_B = "${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.rootfs.sdcard-emicon"

IMAGE_CMD_sdcard-emicon () {

	SD_ROOTFS=${DEPLOY_DIR_IMAGE}/sdrootfs
	out="${DEPLOY_DIR_IMAGE}"

	mkdir -p ${SD_ROOTFS}
	tar -xf ${DEPLOY_DIR_IMAGE}/${IMAGE_BASENAME}-${MACHINE}.tar -C ${SD_ROOTFS}

	mkdir -p ${SD_ROOTFS}/opt/TISDK/nand
	cp ${DEPLOY_DIR_IMAGE}/MLO ${SD_ROOTFS}/opt/TISDK/nand
	cp ${DEPLOY_DIR_IMAGE}/u-boot.img ${SD_ROOTFS}/opt/TISDK/nand
	cp ${DEPLOY_DIR_IMAGE}/${KERNEL_IMAGETYPE} ${SD_ROOTFS}/opt/TISDK/
	# cp ${DEPLOY_DIR_IMAGE}/${KERNEL_IMAGETYPE}-${KERNEL_DEVICETREE_varsomam33} ${SD_ROOTFS}/opt/TISDK/
	cp ${DEPLOY_DIR_IMAGE}/${IMAGE_BASENAME}-${MACHINE}.ubi ${SD_ROOTFS}/opt/TISDK/rootfs-emicon.ubi.img
	cp ${DEPLOY_DIR_IMAGE}/nand-recovery.sh ${SD_ROOTFS}/sbin

#	BUILDDIR="${TOPDIR}" wic create sdimage-bootpart -o "$out/" -r "${SD_ROOTFS}" -k "${DEPLOY_DIR_IMAGE}"  -n " /home/mike/yocto_varsomam33/tisdk/build/arago-tmp-external-linaro-toolchain/sysroots/x86_64-linux" -b "${DEPLOY_DIR_IMAGE}" --vars "${STAGING_DIR_TARGET}/imgdata/"

}

