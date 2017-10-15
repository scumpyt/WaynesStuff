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
    vehicleut.cpp \
    oilchangeut.cpp \
    tirerotationut.cpp \
    scheduledmaintut.cpp \
    misceventut.cpp \
    maintenancelogut.cpp \
    persistenceenginefactoryut.cpp \
    persistenceenginecsvut.cpp \
    persistenceengineut.cpp

INCLUDEPATH += ../CppSrc

DEFINES += SRCDIR=\\\"$$PWD/\\\"

QMAKE_RPATHDIR += $$DESTDIR

LIBS += -L$$DESTDIR -ltheLib

HEADERS += \
    vehicleut.h \
    oilchangeut.h \
    tirerotationut.h \
    scheduledmaintut.h \
    misceventut.h \
    maintenancelogut.h \
    persistenceenginefactoryut.h \
    persistenceenginecsvut.h \
    persistenceengineut.h
