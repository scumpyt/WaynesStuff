#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T13:23:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtProducerConsumer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    threadmanager.cpp \
    producer.cpp

HEADERS  += mainwindow.h \
    threadmanager.h \
    threadsafequeue.h \
    producer.h
