QT += qml quick

CONFIG += c++11

! include(../common.pri) {
    error("Couldn't find the common.pri file")
}

SOURCES += main.cpp

INCLUDEPATH += ../cppSrc

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

QMAKE_RPATHDIR += $$DESTDIR

LIBS += -L$$DESTDIR -ldeepstats
