#-------------------------------------------------
#
# Project created by QtCreator 2016-12-01T15:32:18
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt65Network
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    networker.cpp \
    weatherdetail.cpp

HEADERS  += mainwindow.h \
    networker.h \
    weatherdetail.h \
    global.h

DISTFILES += trans.ts

TRANSLATIONS += \
    trans.ts
