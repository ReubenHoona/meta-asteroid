SUMMARY = "Libhybris backend for GeoClue"
HOMEPAGE = "https://github.com/mer-hybris/geoclue-providers-hybris"
LICENSE = "LGPL-2.1-or-later"
LIC_FILES_CHKSUM = "file://COPYING;md5=4fbd65380cdd255951079008b364516c"

SRC_URI = "git://github.com/mer-hybris/geoclue-providers-hybris.git;protocol=https;branch=master \
    file://0001-pri-Fix-host-contamination-path-issue.patch \
    file://0002-Drop-nemo-qml-plugin-systemsettings-dependency.patch \
    file://0003-pri-Use-Qt6-pkg-config-module-names.patch \
    file://0004-dbus-Annotate-signal-args-with-QtTypeName-Out-for-Qt6.patch \
    file://0005-backends-Qualify-stream-manipulators-with-Qt-for-Qt6.patch \
    file://0006-Make-oFono-optional-CONFIG-no_ofono.patch \
    "
SRCREV = "0.2.40"
PR = "r1"
PV = "+git${SRCPV}"

DEPENDS += "geoclue libhybris libconnman-qt"
inherit qt6-qmake pkgconfig

# AsteroidOS runs no oFono stack, and qofono-qt6/qofonoext are not built: compile out
# the cellular-APN lookup for online aGPS (standalone GNSS and XTRA/NTP over Wi-Fi
# are unaffected).
EXTRA_QMAKEVARS_PRE += "CONFIG+=no_ofono"

# Ensures that the root sources can be found.
B = "${S}"

FILES:${PN} += "/usr/share/dbus-1 /usr/share/geoclue-providers /usr/lib/systemd/user"

# See asteroid-no-sandbox.conf: the upstream user unit's sandboxing makes the
# provider abort at start-up on AsteroidOS.
SRC_URI += "file://asteroid-no-sandbox.conf"
do_install:append() {
    install -d ${D}/usr/lib/systemd/user/geoclue-providers-hybris.service.d
    install -m 0644 ${UNPACKDIR}/asteroid-no-sandbox.conf \
        ${D}/usr/lib/systemd/user/geoclue-providers-hybris.service.d/asteroid-no-sandbox.conf
}
