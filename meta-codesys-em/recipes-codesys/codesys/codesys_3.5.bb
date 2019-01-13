DESCRIPTION = "Runtime CODESYS"
LICENSE = "CLOSED"
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

FILES_SOLIBSDEV = ""
INSANE_SKIP_${PN} += "dev-so"

SRC_URI += " \
    file://CODESYSControl \
    file://codesys \
    file://lcd_menu \
    file://run_lcd_menu \
    file://etc \
    file://Packages \
"

S="${THISDIR}/cds_rts/Templates"

do_compile () {
  make
}

do_install () {
    install -d ${D}${bindir}
    install -d ${D}${libdir}
    install -m 755 -d ${D}${bindir}/codesys
    install -m 755 -d ${D}${bindir}/codesys/CODESYSControl

    install -d ${D}${sysconfdir}
    cp ${WORKDIR}/etc/*.sh ${D}${sysconfdir}
    
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/codesys ${D}${sysconfdir}/init.d
    update-rc.d -r ${D} codesys defaults

    install -m 0755 ../Platforms/Linux/Bin/codesyscontrol ${D}${bindir}/codesys/CODESYSControl
    install -m 0755 ${WORKDIR}/CODESYSControl/CODESYSControl.cfg ${D}${bindir}/codesys/CODESYSControl

    install -m 0755 CmpEmiconEmu/Linux/libCmpEmiconEmu.so ${D}${libdir}
    install -m 0755 CmpEmiconEventsControl/Linux/libCmpEmiconEventsControl.so ${D}${libdir}
    install -m 0755 CmpEmiconLCD/Linux/libCmpEmiconLCD.so ${D}${libdir}
    install -m 0755 CmpEmiconLog/Linux/libCmpEmiconLog.so ${D}${libdir}
    install -m 0755 CmpEmiconMemManager/Linux/libCmpEmiconMemManager.so ${D}${libdir}
    install -m 0755 CmpEmiconNetwork/Linux/libCmpEmiconNetwork.so ${D}${libdir}
    install -m 0755 CmpEmiconPlcShellHandler/Linux/libCmpPlcShellHandler.so ${D}${libdir}
    install -m 0755 CmpEmiconStopControl/Linux/libCmpEmiconStopControl.so ${D}${libdir}
    install -m 0755 CmpEmiconSys/Linux/libCmpEmiconSys.so ${D}${libdir}

}

inherit deploy
addtask deploy before do_package after do_install

do_deploy () {
   mkdir -p ${DEPLOYDIR}/ForCODESYS
   cp -r ${WORKDIR}/Packages ${DEPLOYDIR}/ForCODESYS
}

FILES_${PN} += "${libdir}/*.so"

#FILES_${PN} += " \ 
#   /usr/bin/codesys \
#"