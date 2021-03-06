#-------------------------------------------------
#
# Project created by QtCreator 2014-05-29T22:08:52
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = heriot
TEMPLATE = app


SOURCES += src/main.cpp\
        src/ui/windows/browser/browserwindow.cpp \
    src/ui/heriot/web/heriotwebview.cpp \
    src/ui/tabs/opentab.cpp \
    src/heriotapplication.cpp \
    src/ui/heriot/web/heriotwebpage.cpp \
    src/ui/tabs/sidetabs.cpp \
    src/ui/heriot/tabs/browsertab.cpp \
    src/ui/heriot/tabs/maintabwidget.cpp \
    src/ui/heriot/web/webviewwrapper.cpp \
    src/web/cookiejar.cpp \
    src/settings/heriotsettings.cpp \
    src/settings/tabsettings.cpp

HEADERS  += src/ui/windows/browser/browserwindow.h \
    src/ui/heriot/web/heriotwebview.h \
    src/ui/tabs/opentab.h \
    src/heriotapplication.h \
    src/ui/heriot/web/heriotwebpage.h \
    src/ui/tabs/sidetabs.h \
    src/ui/heriot/tabs/browsertab.h \
    src/ui/heriot/tabs/maintabwidget.h \
    src/ui/heriot/web/webviewwrapper.h \
    src/web/cookiejar.h \
    src/settings/heriotsettings.h \
    src/settings/tabsettings.h

FORMS    += src/ui/windows/browser/browserwindow.ui \
    src/ui/tabs/sidetabs.ui

OTHER_FILES += \
    TODO.txt

RESOURCES += \
    data.qrc

win32 {
    RC_ICONS = heriot.ico
}

mac {
    ICON = heriot.icns
    QMAKE_INFO_PLIST = heriot.plist
    TARGET = Heriot
    contains(QT_CONFIG, x86) {
        CONFIG -= x86_64
        CONFIG += x86
    }
}

INSTALLS += target
