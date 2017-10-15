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
    vehicle.cpp \
    serviceeventbase.cpp \
    oilchangeevent.cpp \
    tirerotationevent.cpp \
    scheduledmaintevent.cpp \
    miscevent.cpp \
    maintenancelog.cpp \
    persistenceenginefactory.cpp \
    persistenceengine.cpp \
    persistenceenginecsv.cpp \
    persistenceenginesql.cpp

HEADERS +=\
    vehicle.h \
    vehicletypes.h \
    curve_global.h \
    serviceeventbase.h \
    oilchangeevent.h \
    tirerotationevent.h \
    scheduledmaintevent.h \
    scheduledmainttypes.h \
    miscevent.h \
    maintenancelog.h \
    persistenceengine.h \
    persistenceenginefactory.h \
    persistenceenginetypes.h \
    persistenceenginecsv.h \
    persistenceenginesql.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    ../common.pri
