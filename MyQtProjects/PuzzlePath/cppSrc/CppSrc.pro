#-------------------------------------------------
#
# Project created by QtCreator 2016-10-31T13:48:15
#
#-------------------------------------------------

QT       -= gui

! include(../common.pri) {
    error("Couldn't find the common.pri file")
}

TARGET = theLib
TEMPLATE = lib

DEFINES += CPPSRC_LIBRARY

SOURCES += \
    pathfinder.cpp

HEADERS +=\
    cppsrc_global.h \
    pathfinder.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    ../common.pri
