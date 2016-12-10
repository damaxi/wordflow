#include "databasetest.h"

void DatabaseTest::initTestCase()
{
    m_database.clean_tables();
}

void DatabaseTest::add_new_database()
{
    QString name = "English Vocabulary";
    QString description = "B2 Mode";
    m_database.create_vocabulary(name, description);
    QVariantList vocabulary_list = m_database.list_vocabularies();
    QVariantMap map = vocabulary_list.at(0).value<QVariantMap>();
    QCOMPARE(map["name"].value<QString>(), name);
    QCOMPARE(map["description"].value<QString>(), description);
}

void DatabaseTest::cleanupTestCase()
{
    m_database.remove_database();
}
