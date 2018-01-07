QT -= gui
QT += core network qml
###CONFIG += qt shared
CONFIG += qt plugin

! include(../common.pri) {
    error("Couldn't find the common.pri file")
}

TARGET = deepstats
TEMPLATE = lib

DEFINES += DEEPSTATS_LIBRARY

SOURCES += \
    stravaaccess.cpp \
    stravastats.cpp \
    stravaactivities.cpp \
    stravaactivity.cpp \
    stravarangesummary.cpp \
    stravaportal.cpp \
    portalactivitiesmodel.cpp

HEADERS += \
    deepstats_global.h \
    stravaaccess.h \
    stravastats.h \
    stravaactivities.h \
    stravaactivity.h \
    stravarangesummary.h \
    stravaportal.h \
    deepstats_plugin.h \
    portalactivitiesmodel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    ../common.pri

##########################################################################
# Below is the installation of the plugin to my special plugin location...
win32 {
    # The dir I want the plugin installed to...
    WAYNES_PLUGIN_DIR = C:\Users\wayne_000\Documents\QtProjects\WaynesPlugins\ca\scumpyware\deepstats
    ##message($$WAYNES_PLUGIN_DIR)

    # If my dir doesn't exist, create it...
    PLUGIN_INSTALL_DIR = $$WAYNES_PLUGIN_DIR
    if (!exists($$PLUGIN_INSTALL_DIR)) {
        message("CREATING DIR")
        createpluginsdir.commands = $(MKDIR) $$PLUGIN_INSTALL_DIR

        QMAKE_EXTRA_TARGETS += createpluginsdir
        PRE_TARGETDEPS += createpluginsdir
    }
    else {
        message("NOT CREATING DIR")
    }


    # Now, copy the lib's & the qmldir file to the plugin install dir...
    EXTRA_BINFILES += \
        $$DESTDIR/*.dll \
        $$DESTDIR/*.lib \
        $$DESTDIR/*.pdb \
        $$PWD/qmldir
    EXTRA_BINFILES_WIN = $${EXTRA_BINFILES}
    EXTRA_BINFILES_WIN ~= s,/,\\,g
        DESTDIR_WIN = $${PLUGIN_INSTALL_DIR}
    DESTDIR_WIN ~= s,/,\\,g
    for(FILE,EXTRA_BINFILES_WIN){
                QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${FILE} $${DESTDIR_WIN}$$escape_expand(\n\t))
    }
}
