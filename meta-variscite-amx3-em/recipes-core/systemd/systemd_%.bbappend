FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
    file://10-eth.network \
"

PACKAGECONFIG_append = " --disable-polkit"

do_install_append() {
    install -m 0775 -d ${D}${sysconfdir}/systemd/network
    install -m 0775 ${WORKDIR}/10-eth.network ${D}${sysconfdir}/systemd/network
}

pkg_postinst_${PN}() {
	chmod 0775 $D${sysconfdir}/systemd/network/10-eth.network
	chmod 0775 $D${sysconfdir}/systemd/network
}