QT += core network gui widgets

VERSION = 1.0.0.0
QMAKE_TARGET_COMPANY = "SevRyb"
QMAKE_TARGET_PRODUCT = "Pinpoint"
QMAKE_TARGET_DESCRIPTION = "Pinpoint messenger"
QMAKE_TARGET_COPYRIGHT = "Copyright © 2023 SevRyb"

TARGET = Pinpoint
TEMPLATE = app

CONFIG += c++11 utf8_source

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    chatmember.cpp \
    chatmemberswindow.cpp \
    clientmain.cpp \
    chatwindow.cpp \
    chatclient.cpp \
    emojiwindow.cpp \
    message.cpp \
    profilewindow.cpp \
    serversetupwindow.cpp \
    textmessage.cpp \
    ui/animbutton.cpp \
    ui/infomessagewidget.cpp \
    ui/messagetextedit.cpp \
    ui/messagewidget.cpp \
    ui/textmessagewidget.cpp

HEADERS += \
    chatmember.h \
    chatmemberswindow.h \
    chatwindow.h \
    chatclient.h \
    defines.h \
    emojiwindow.h \
    message.h \
    profilewindow.h \
    serversetupwindow.h \
    textmessage.h \
    ui/animbutton.h \
    ui/infomessagewidget.h \
    ui/messagetextedit.h \
    ui/messagewidget.h \
    ui/textmessagewidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_ICONS = icon.ico
