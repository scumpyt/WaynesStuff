#-------------------------------------------------
#
# Project created by QtCreator 2016-10-17T14:33:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProducerConsumer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    threadmanager.cpp

HEADERS  += mainwindow.h \
    threadsafequeue.h \
    threadmanager.h
