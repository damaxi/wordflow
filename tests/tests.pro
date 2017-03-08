#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T16:49:59
#
#-------------------------------------------------

QT       += testlib sql

QT       -= gui

TARGET = unittest
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp \
    databasetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    databasetest.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lwordflow
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lwordflow
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lwordflow

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/release/libwordflow.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/debug/libwordflow.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/release/lib.wordflow
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/debug/lib.wordflow
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/libwordflow.a
