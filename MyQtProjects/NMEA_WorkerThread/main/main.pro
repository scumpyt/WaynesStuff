QT += core
#QT -= gui  # For CONSOLE Apps...

# For widget apps...
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

! include(../common.pri) {
    error("Couldn't find the common.pri file")
}

INCLUDEPATH += ../CppSrc

#TARGET = main
#CONFIG += console
#CONFIG -= app_bundle

#TEMPLATE = app

DISTFILES += \
    ../common.pri

###DEFINES += SRCDIR=\\\"$$PWD/\\\"

QMAKE_RPATHDIR += $$DESTDIR

LIBS += -L$$DESTDIR -ltheLib

SOURCES += main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h
