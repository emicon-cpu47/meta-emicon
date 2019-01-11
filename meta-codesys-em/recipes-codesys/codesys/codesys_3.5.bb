DESCRIPTION = "Runtime CODESYS"
LICENSE = "CLOSED"
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
 
SRC_URI += " \
    file://CODESYSControl \
    file://codesys \
    file://lcd_menu \
    file://run_lcd_menu \
    file://etc \
    file://Packages \
    file://setenv_codesys.sh \
"

do_install () {
    install -m 755 -d ${D}${bindir}/codesys
    cp -r ${WORKDIR}/CODESYSControl ${D}${bindir}/codesys
    install -m 0755 ${WORKDIR}/lcd_menu ${D}${bindir}/codesys

    install -d ${D}${sysconfdir}
    cp ${WORKDIR}/etc/*.sh ${D}${sysconfdir}

    install -d ${D}${sysconfdir}/profile.d
    install -m 0755 ${WORKDIR}/setenv_codesys.sh ${D}${sysconfdir}/profile.d   

    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/codesys ${D}${sysconfdir}/init.d
    update-rc.d -r ${D} codesys defaults

    install -m 0755 ${WORKDIR}/run_lcd_menu ${D}${sysconfdir}/init.d
    #update-rc.d -r ${D} run_lcd_menu defaults

}

inherit deploy
addtask deploy before do_package after do_install

do_deploy () {
    mkdir -p ${DEPLOYDIR}/CODESYS
    cp -r ${WORKDIR}/Packages ${DEPLOYDIR}/CODESYS
}

#FILES_${PN} += " \ 
#	/usr/bin/codesys \
#"