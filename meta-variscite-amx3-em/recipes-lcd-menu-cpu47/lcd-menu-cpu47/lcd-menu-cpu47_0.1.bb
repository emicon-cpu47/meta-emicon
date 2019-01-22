DESCRIPTION = "LCD driver for Emicon CPU47 PLC"
LICENSE = "CLOSED"
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"


COMPATIBLE_MACHINE = "emcpu47"

# FILES_SOLIBSDEV = ""
# INSANE_SKIP_${PN} += "dev-so"

SRC_URI += " \
    file://lcd_menu.sh \
"

S="${THISDIR}/lcd_menu"

do_compile () {
  make
}

do_install () {
	install -m 755 -d ${D}${bindir}/codesys
	install -m 0755 lcd_menu ${D}${bindir}/codesys

	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ${WORKDIR}/lcd_menu.sh ${D}${sysconfdir}/init.d/lcd_menu
	update-rc.d -r ${D} lcd_menu defaults
}

FILES_${PN} += " \ 
   ${bindir}/codesys/lcd_menu \
   ${sysconfdir}/init.d/lcd_menu \
"
