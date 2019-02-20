DESCRIPTION = "LCD driver for Emicon CPU47 PLC"
LICENSE = "CLOSED"
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

COMPATIBLE_MACHINE = "emcpu47"

SYS_VER_SHOW_IN_MENU = "4.4 0001"

# FILES_SOLIBSDEV = ""
# INSANE_SKIP_${PN} += "dev-so"

SRC_URI += " \
	file://lcd_menu \
    file://lcd_menu.sh \
    file://net_file_create.sh \
    file://update_codesys_reboot.sh \
"

S="${WORKDIR}/lcd_menu"

do_compile () {
  make
}

do_install () {
	install -m 755 -d ${D}${bindir}/codesys
	install -m 0755 ${S}/lcd_menu ${D}${bindir}/codesys
	echo ${CDS_IMAGE_VER} > ${D}${bindir}/codesys/sysversion.txt

	install -d ${D}${sysconfdir}
	install -d ${D}${sysconfdir}/init.d

	install -m 0755 ${WORKDIR}/lcd_menu.sh ${D}${sysconfdir}/init.d/lcd_menu
	update-rc.d -r ${D} lcd_menu defaults

	install -m 0755 ${WORKDIR}/net_file_create.sh ${D}${sysconfdir}
	install -m 0755 ${WORKDIR}/update_codesys_reboot.sh ${D}${sysconfdir}

}

FILES_${PN} += " \ 
   ${bindir}/codesys/lcd_menu \
   ${sysconfdir}/init.d/lcd_menu \
   ${D}${sysconfdir}/net_file_create.sh \
   ${D}${sysconfdir}/update_codesys_reboot.sh \
"
