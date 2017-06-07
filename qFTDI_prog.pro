#-------------------------------------------------
#
# Project created by QtCreator 2017-05-07T06:04:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qFTDI_prog
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += c++11
CONFIG += debug
CONFIG += console

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libftdipp1
unix: PKGCONFIG += libusb-1.0

DISTFILES += \
    settings.xml
