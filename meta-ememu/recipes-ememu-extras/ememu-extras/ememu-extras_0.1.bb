DESCRIPTION = "utils"
LICENSE = "CLOSED"
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
    file://utils.txt \
    file://drivers \
    file://qemu \
    file://installation_scripts/* \
    file://readme.rst \
    file://issue_temp \
    file://issue_compile \
"

do_install () {
	install -m 755 -d ${D}${bindir}/codesys
	install -d ${D}${sysconfdir}
	install -d ${D}${sysconfdir}/init.d

	cp -r ${WORKDIR}/utils.txt ${D}${bindir}/codesys
	cp ${WORKDIR}/issue_temp ${D}${sysconfdir}
	install -m 0755 ${WORKDIR}/issue_compile ${D}${sysconfdir}/init.d

	update-rc.d -r ${D} issue_compile defaults 99
}

inherit deploy
addtask deploy before do_package after do_install

do_deploy () {
	mkdir -p ${DEPLOYDIR}/ememu
	mkdir -p ${DEPLOYDIR}/ememu/ememu
	cp -r ${WORKDIR}/drivers ${DEPLOYDIR}/ememu
	cp -r ${WORKDIR}/qemu ${DEPLOYDIR}/ememu/ememu/

	cp ${WORKDIR}/installation_scripts/* ${DEPLOYDIR}/ememu
	cp ${WORKDIR}/readme.rst ${DEPLOYDIR}/ememu
}