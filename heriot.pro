#-------------------------------------------------
#
# Project created by QtCreator 2014-05-29T22:08:52
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = heriot
TEMPLATE = app


SOURCES += main.cpp\
        browserwindow.cpp \
    heriotwebview.cpp \
    opentab.cpp \
    heriotapplication.cpp \
    heriotwebpage.cpp \
    sidetabs.cpp \
    browsertab.cpp \
    maintabwidget.cpp

HEADERS  += browserwindow.h \
    tabrotatestyle.h \
    heriotwebview.h \
    opentab.h \
    heriotapplication.h \
    heriotwebpage.h \
    sidetabs.h \
    browsertab.h \
    maintabwidget.h

FORMS    += browserwindow.ui \
    sidetabs.ui

OTHER_FILES += \
    TODO.txt

RESOURCES += \
    data.qrc
