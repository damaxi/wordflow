#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T16:50:35
#
#-------------------------------------------------

QT       += sql
QT       -= gui

TARGET = lib
TEMPLATE = lib
CONFIG += staticlib c++11

SOURCES += database.cpp \
    sqlerror.cpp \
    sqlwordsmodel.cpp \
    sqlvocabularyquerymodel.cpp \
    sqlwordseditmodel.cpp \
    sqllearningwordsmodel.cpp \
    sqlvocabularyeditmodel.cpp \
    sqlvocabularymodel.cpp \
    localemodel.cpp

HEADERS += database.h \
    sqlerror.h \
    sqlwordsmodel.h \
    sqlvocabularyquerymodel.h \
    sqlwordseditmodel.h \
    sqllearningwordsmodel.h \
    sqlvocabularyeditmodel.h \
    sqlvocabularymodel.h \
    localemodel.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
