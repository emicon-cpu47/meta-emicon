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

S="${THISDIR}/cds_rts/Templates"

do_compile () {
  make
}

do_install () {
    install -d ${D}${bindir}
    install -m 755 -d ${D}${bindir}/codesys
    install -m 755 -d ${D}${bindir}/codesys/CODESYSControl

    install -m 0755 ../Platforms/Linux/Bin/codesyscontrol ${D}${bindir}/codesys/CODESYSControl
    install -m 0755 ${WORKDIR}/CODESYSControl/CODESYSControl.cfg ${D}${bindir}/codesys/CODESYSControl

    install -m 0755 CmpEmiconEmu/Linux/libCmpEmiconEmu.so ${D}${bindir}/codesys/CODESYSControl
    install -m 0755 CmpEmiconEventsControl/Linux/libCmpEmiconEventsControl.so ${D}${bindir}/codesys/CODESYSControl
    install -m 0755 CmpEmiconLCD/Linux/libCmpEmiconLCD.so ${D}${bindir}/codesys/CODESYSControl
    install -m 0755 CmpEmiconLog/Linux/libCmpEmiconLog.so ${D}${bindir}/codesys/CODESYSControl
    install -m 0755 CmpEmiconMemManager/Linux/libCmpEmiconMemManager.so ${D}${bindir}/codesys/CODESYSControl
    install -m 0755 CmpEmiconNetwork/Linux/libCmpEmiconNetwork.so ${D}${bindir}/codesys/CODESYSControl
    install -m 0755 CmpEmiconPlcShellHandler/Linux/libCmpPlcShellHandler.so ${D}${bindir}/codesys/CODESYSControl
    install -m 0755 CmpEmiconStopControl/Linux/libCmpEmiconStopControl.so ${D}${bindir}/codesys/CODESYSControl
    install -m 0755 CmpEmiconSys/Linux/libCmpEmiconSys.so ${D}${bindir}/codesys/CODESYSControl

}

inherit deploy
addtask deploy before do_package after do_install

do_deploy () {
   mkdir -p ${DEPLOYDIR}/CODESYS
   cp -r ${WORKDIR}/Packages ${DEPLOYDIR}/CODESYS
}

#FILES_${PN} += " \ 
#   /usr/bin/codesys \
#"