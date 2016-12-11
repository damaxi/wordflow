#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T16:50:35
#
#-------------------------------------------------

QT       += sql core
QT       -= gui

TARGET = lib
TEMPLATE = lib
CONFIG += staticlib c++11

SOURCES += database.cpp

HEADERS += database.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
