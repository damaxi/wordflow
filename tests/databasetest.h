#ifndef DATABASETEST_H
#define DATABASETEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "database.h"

class DatabaseTest : public QObject
{
    Q_OBJECT
public:
private slots:
    void init();
    void createNewVocabulary();
    void createNewWorld();
    void updateProgress();
    void listWordsForMultipleDistinctWords();
    void cleanup();
    void createDatabaseWithInitialConfiguration();
private:
    Database m_database;
};

#endif // DATABASETEST_H
