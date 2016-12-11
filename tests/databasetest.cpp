#include "databasetest.h"

#include <QList>

//void DatabaseTest::initTestCase()
//{
//    m_database.clean_tables();
//}

//void DatabaseTest::add_new_database()
//{
//    QString name = "English Vocabulary";
//    QString description = "B2 Mode";
//    m_database.create_vocabulary(name, description);
//    QVariantList vocabulary_list = m_database.list_vocabularies();
//    QVariantMap map = vocabulary_list.at(0).value<QVariantMap>();
//    QCOMPARE(map["name"].value<QString>(), name);
//    QCOMPARE(map["description"].value<QString>(), description);
//}

//void DatabaseTest::cleanupTestCase()
//{
//    m_database.remove_database();
//}

void DatabaseTest::createDatabaseWithInitialConfiguration()
{
    m_database.createDatabase();
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
}
