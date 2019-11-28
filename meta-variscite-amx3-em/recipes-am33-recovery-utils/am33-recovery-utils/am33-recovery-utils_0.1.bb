DESCRIPTION = "LCD driver for Emicon CPU47 PLC"
LICENSE = "CLOSED"
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

COMPATIBLE_MACHINE = "emcpu47|emcpu47n1g"

SYS_VER_SHOW_IN_MENU = "4.4 0002"

# FILES_SOLIBSDEV = ""
# INSANE_SKIP_${PN} += "dev-so"

SRC_URI = " \
			file://u-boot-sd \
			file://nand-recovery.sh \
"

do_install () {
	install -d ${D}${sysconfdir}/init.d
}
