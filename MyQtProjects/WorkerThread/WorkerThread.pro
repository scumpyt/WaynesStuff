#-------------------------------------------------
#
# Project created by QtCreator 2016-10-31T12:33:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorkerThread
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    threadmanager.cpp

HEADERS  += mainwindow.h \
    threadmanager.h \
    threadsafequeue.h
