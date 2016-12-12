#include "databasetest.h"

#include <QList>
#include <QDebug>

void DatabaseTest::init()
{
    m_database.createDatabase();
}

void DatabaseTest::cleanup()
{
    m_database.cleanTables();
}

void DatabaseTest::createNewVocabulary()
{
    QString name = "English Vocabulary";
    QString description = "B2 Mode";
    m_database.createVocabulary(name, description);
    QVariantList vocabulary_list = m_database.listVocabularies();
    QVariantMap map = vocabulary_list.at(0).value<QVariantMap>();
    QCOMPARE(map["name"].value<QString>(), name);
    QCOMPARE(map["description"].value<QString>(), description);
}

void DatabaseTest::createDatabaseWithInitialConfiguration()
{
    QVERIFY2(QFile(m_database.path()).exists(), "Database not created.");
    QSqlQuery query;
    query.exec("SELECT name FROM sqlite_master WHERE type='table'");
    QList<QString> tables;
    while (query.next()) {
        tables.push_back(query.value(0).toString());
    }
    QVERIFY2(tables.contains("vocabularies"), "Database not contain vocabulary table");
    QVERIFY2(tables.contains("words"), "Database not contain words table");
    m_database.removeDatabase();
    QVERIFY2(!QFile(m_database.path()).exists(), "Database not destroyed.");
    m_database.openDatabase();
    m_database.createDatabase();
}
