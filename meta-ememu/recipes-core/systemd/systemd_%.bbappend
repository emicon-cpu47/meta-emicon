FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
    file://10-eth.network \
"

PACKAGECONFIG_append = " networkd"

do_install_append() {
    install -d ${D}${sysconfdir}/systemd/network
    install -m 0755 ${WORKDIR}/10-eth.network ${D}${sysconfdir}/systemd/network
}
