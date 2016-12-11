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
   // void initTestCase();
//    void add_new_database();
   // void cleanupTestCase();
    void createDatabaseWithInitialConfiguration();
private:
    Database m_database;
};

#endif // DATABASETEST_H
