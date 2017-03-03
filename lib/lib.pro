#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T16:50:35
#
#-------------------------------------------------

QT       += sql charts
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
    localemodel.cpp \
    statisticchartmodel.cpp \
    datehelper.cpp \
    sqlstatisticmodel.cpp \
    sqltotalwordsstatisticmodel.cpp \
    sqlstatisticscommon.cpp

HEADERS += database.h \
    sqlerror.h \
    sqlwordsmodel.h \
    sqlvocabularyquerymodel.h \
    sqlwordseditmodel.h \
    sqllearningwordsmodel.h \
    sqlvocabularyeditmodel.h \
    sqlvocabularymodel.h \
    localemodel.h \
    statisticchartmodel.h \
    datehelper.h \
    sqlstatisticmodel.h \
    sqltotalwordsstatisticmodel.h \
    sqlstatisticscommon.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
