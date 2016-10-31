QT += core testlib
QT -= gui

CONFIG += c++11

TARGET = UnitTests
CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase

TEMPLATE = app

! include(../common.pri) {
    error("Couldn't find the common.pri file")
}

SOURCES += \
    mainut.cpp \
    bytequeuehelperut.cpp

INCLUDEPATH += ../CppSrc

DEFINES += SRCDIR=\\\"$$PWD/\\\"

QMAKE_RPATHDIR += $$DESTDIR

LIBS += -L$$DESTDIR -ltheLib

HEADERS += \
    bytequeuehelperut.h
