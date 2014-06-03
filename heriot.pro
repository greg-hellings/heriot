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
    maintabswidget.cpp \
    heriotwebview.cpp \
    opentab.cpp

HEADERS  += browserwindow.h \
    tabrotatestyle.h \
    maintabswidget.h \
    heriotwebview.h \
    opentab.h

FORMS    += browserwindow.ui \
    maintabswidget.ui
