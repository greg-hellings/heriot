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
    src/ui/heriot/web/webviewwrapper.cpp

HEADERS  += src/ui/windows/browser/browserwindow.h \
    tabrotatestyle.h \
    src/ui/heriot/web/heriotwebview.h \
    src/ui/tabs/opentab.h \
    src/heriotapplication.h \
    src/ui/heriot/web/heriotwebpage.h \
    src/ui/tabs/sidetabs.h \
    src/ui/heriot/tabs/browsertab.h \
    src/ui/heriot/tabs/maintabwidget.h \
    src/ui/heriot/web/webviewwrapper.h

FORMS    += src/ui/windows/browser/browserwindow.ui \
    src/ui/tabs/sidetabs.ui

OTHER_FILES += \
    TODO.txt

RESOURCES += \
    data.qrc
