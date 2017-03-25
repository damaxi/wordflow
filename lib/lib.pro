#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T16:50:35
#
#-------------------------------------------------

QT       += sql charts
QT       -= gui

TARGET = wordflow
TEMPLATE = lib
CONFIG += staticlib c++11

SOURCES += database.cpp \
    helpers/datehelper.cpp \
    model/localemodel.cpp \
    sqlmodel/sqllearningwordsmodel.cpp \
    sqlmodel/sqlstatisticmodel.cpp \
    sqlmodel/sqlstatisticscommon.cpp \
    sqlmodel/sqltotalwordsstatisticmodel.cpp \
    sqlmodel/sqlvocabularyeditmodel.cpp \
    sqlmodel/sqlvocabularymodel.cpp \
    sqlmodel/sqlvocabularyquerymodel.cpp \
    sqlmodel/sqlwordseditmodel.cpp \
    sqlmodel/sqlwordsmodel.cpp \
    model/statisticchartmodel.cpp

HEADERS += database.h \
    helpers/datehelper.h \
    model/localemodel.h \
    sqlmodel/sqllearningwordsmodel.h \
    sqlmodel/sqlstatisticmodel.h \
    sqlmodel/sqlstatisticscommon.h \
    sqlmodel/sqltotalwordsstatisticmodel.h \
    sqlmodel/sqlvocabularyeditmodel.h \
    sqlmodel/sqlvocabularymodel.h \
    sqlmodel/sqlvocabularyquerymodel.h \
    sqlmodel/sqlwordseditmodel.h \
    sqlmodel/sqlwordsmodel.h \
    model/statisticchartmodel.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
