QT += core
QT -= gui

CONFIG += c++11

TARGET = uttests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    suiteone.cpp \
    classone.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../../../../Program Files/UnitTest++/lib/' -lUnitTest++
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../../../../Program Files/UnitTest++/lib/' -lUnitTest++
else:unix: LIBS += -L$$PWD/'../../../../../../../Program Files/UnitTest++/lib/' -lUnitTest++

INCLUDEPATH += $$PWD/'../../../../../../../Program Files/UnitTest++/include'
DEPENDPATH += $$PWD/'../../../../../../../Program Files/UnitTest++/include'

HEADERS += \
    suiteone.h \
    classone.h
