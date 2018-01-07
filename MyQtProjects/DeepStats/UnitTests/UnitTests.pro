
QT += core testlib network
QT -= gui

TARGET = UnitTests
CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase

TEMPLATE = app

! include(../common.pri) {
    error("Couldn't find the common.pri file")
}

HEADERS += \
    stravaaccessut.h \
    stravastatsut.h \
    stravaactivitiesut.h \
    stravaactivitiesmodelut.h

SOURCES += mainut.cpp \
    stravaaccessut.cpp \
    stravastatsut.cpp \
    stravaactivitiesut.cpp \
    stravaactivitiesmodelut.cpp

#INCLUDEPATH += $$PWD/cppSrc
INCLUDEPATH += ../cppSrc

DEFINES += SRCDIR=\\\"$$PWD/\\\"

QMAKE_RPATHDIR += $$DESTDIR

LIBS += -L$$DESTDIR -ldeepstats


