FILESEXTRAPATHS_prepend := "${THISDIR}/systemd:"

SRC_URI += " \
    file://10-eth.network \
"

PACKAGECONFIG_append = " networkd"

do_install_append() {
    install -d ${D}${sysconfdir}/systemd/network
    cp ${WORKDIR}/10-eth.network ${D}${sysconfdir}/systemd/network
}

# FILES_${PN} += " \
#    ${D}${sysconfdir}/systemd/network \
# "
