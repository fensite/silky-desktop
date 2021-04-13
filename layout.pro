QT       += core gui svg dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 link_pkgconfig
PKGCONFIG+=glib-2.0 gio-unix-2.0 gsettings-qt libbamf3
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TestListView.cpp \
    animation.cpp \
    getApp.cpp \
    getCapp.cpp \
    itemdef.cpp \
    itemdelegate.cpp \
    itemevent.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    TestListView.h \
    animation.h \
    getApp.h \
    getCapp.h \
    itemdef.h \
    itemdelegate.h \
    itemevent.h \
    widget.h

FORMS += \
    newwidget.ui \
    widget.ui

TRANSLATIONS += \
    layout_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    pics/background.jpeg \
    pics/cursor.png \
    pics/disp.jpeg \
    pics/icon.jpeg
