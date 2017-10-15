QT += core
QT -= gui

CONFIG += c++11

! include(../common.pri) {
    error("Couldn't find the common.pri file")
}

INCLUDEPATH += ../CppSrc

TARGET = main
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    apiexplorer.cpp

DISTFILES += \
    ../common.pri

QMAKE_RPATHDIR += $$DESTDIR

LIBS += -L$$DESTDIR -ltheLib

HEADERS += \
    apiexplorer.h
