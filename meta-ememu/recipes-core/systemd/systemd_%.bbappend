FILESEXTRAPATHS_prepend := "${THISDIR}/systemd:"

SRC_URI += " \
    file://10-eth.network \
"

PACKAGECONFIG_append = " networkd"

do_install_append_ememu() {
    install -d ${D}${sysconfdir}/systemd/network
    cp ${WORKDIR}/10-eth.network ${D}${sysconfdir}/systemd/network
}
