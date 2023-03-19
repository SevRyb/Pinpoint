QT += core network gui widgets

VERSION = 1.0.0.0
QMAKE_TARGET_COMPANY = "SevRyb"
QMAKE_TARGET_PRODUCT = "PinpointServer"
QMAKE_TARGET_DESCRIPTION = "PinpointServer - server for Pinpoint messenger"
QMAKE_TARGET_COPYRIGHT = "Copyright © 2023 SevRyb"

TARGET = PinpointServer
TEMPLATE = app

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += debug_and_release

HEADERS += \
    chatserver.h \
    defines.h \
    serverworker.h \
    serverwindow.h

SOURCES += \
    chatserver.cpp \
    servermain.cpp \
    serverworker.cpp \
    serverwindow.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_ICONS = icon.ico

DISTFILES += \
    resources.rc
