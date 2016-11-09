# This file is the place to put anything we want shared by the .pro files.

# Changing the config variable here will ensure the build settings
# apply to all .pro files that import this.
defined (RELEASE, var) {
    equals (RELEASE, 1) {
        CONFIG += release
    }
} else {
    defined (DEBUG, var) {
        equals (DEBUG, 1) {
            CONFIG += debug
        }
    } else  {
        defined(DEBUG_AND_RELEASE, var) {
            equals (DEBUG_AND_RELEASE, 1) {
                CONFIG += debug_and_release build_all
            }
        } else {
            CONFIG += debug
        }
    }
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build/debug
}
CONFIG(release, debug|release) {
    DESTDIR = ../build/release
}

#QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_RPATHDIR += .

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
