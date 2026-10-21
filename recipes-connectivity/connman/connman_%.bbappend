FILESEXTRAPATHS:prepend := "${THISDIR}/connman:"
SRC_URI += "file://settings \
            file://main.conf \
            file://connman-dbus.conf"

do_install:append() {
    install -d ${D}/var/lib/connman/
    install -m 644 ${UNPACKDIR}/settings ${D}/var/lib/connman/settings
    install -d ${D}${sysconfdir}/connman/
    install -m 644 ${UNPACKDIR}/main.conf ${D}${sysconfdir}/connman/main.conf
    install -d ${D}/etc/dbus-1/system.d/
    install -m 644 ${UNPACKDIR}/connman-dbus.conf ${D}/etc/dbus-1/system.d/connman.conf
}
