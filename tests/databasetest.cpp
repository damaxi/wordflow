#include "databasetest.h"

#include <QList>
#include <QPair>
#include <QDebug>

//void DatabaseTest::init()
//{
//    m_database.createDatabase();
//}

//void DatabaseTest::cleanup()
//{
//    m_database.cleanTables();
//}

//void DatabaseTest::createNewVocabulary()
//{
//    QString name = "English Vocabulary";
//    QString description = "B2 Mode";
//    m_database.createVocabulary(name, description);
//    QVariantList vocabulary_list = m_database.listVocabularies();
//    QVariantMap map = vocabulary_list.at(0).value<QVariantMap>();
//    QCOMPARE(map["name"].value<QString>(), name);
//    QCOMPARE(map["description"].value<QString>(), description);
//}

//void DatabaseTest::createNewWorld()
//{
//    QString origin = "cat";
//    QString translated = "kot";
//    m_database.createWord(origin, translated);
//    QSqlQuery query;
//    query.exec("SELECT COUNT(*) FROM words");
//    QVERIFY2(query.numRowsAffected() == 1, "No rows affected.");
//    while (query.next()) {
//        QVERIFY2(query.value(0).toInt() == 1, "There more than 1 row in words table.");
//    }
//    QVariantList words_list = m_database.listWords(0);
//    QVariantList words = words_list.at(0).value<QVariantList>();
//    QCOMPARE(words.at(0).value<QString>(), origin);
//    QCOMPARE(words.at(1).value<QString>(), translated);
//    QCOMPARE(words.at(2).value<int>(), 0);
//}

//void DatabaseTest::updateProgress()
//{
////    QString origin = "cat";
////    QString translated = "kot";
////    m_database.createWord(origin, translated);
////    QVariantList words_list = m_database.listWords(0);
////    QVariantList words = words_list.at(0).value<QVariantList>();
////    QCOMPARE(words.at(0).value<QString>(), origin);
////    QCOMPARE(words.at(1).value<QString>(), translated);
////    QCOMPARE(words.at(2).value<int>(), 0);
////    m_database.updateProgress(origin, 0, 2);
////    words_list = m_database.listWords(0);
////    words = words_list.at(0).value<QVariantList>();
////    QCOMPARE(words.at(0).value<QString>(), origin);
////    QCOMPARE(words.at(1).value<QString>(), translated);
////    QCOMPARE(words.at(2).value<int>(), 2);
//}

//void DatabaseTest::listWordsForMultipleDistinctWords()
//{
////    QList<QPair<QString, QString>> word_list = {{"cat", "kot"}, {"dog", "pies"}, {"hey", "hej"}};
////    foreach (auto &pair, word_list) {
////        m_database.createWord(pair.first, pair.second);
////    }
////    m_database.updateProgress(word_list.at(0).first, 0, 2);
////    QVariantList words_list = m_database.listWords(0, 2);
////    QVERIFY2(words_list.size() == 2, "No Limits do its job.");
////    QVariantList words = words_list.at(0).value<QVariantList>();
////    QCOMPARE(words.at(0).value<QString>(), word_list.at(1).first);
////    words = words_list.at(1).value<QVariantList>();
////    QCOMPARE(words.at(0).value<QString>(), word_list.at(2).first);
//}

//void DatabaseTest::createDatabaseWithInitialConfiguration()
//{
//    QVERIFY2(QFile(m_database.path()).exists(), "Database not created.");
//    QSqlQuery query;
//    query.exec("SELECT name FROM sqlite_master WHERE type='table'");
//    QList<QString> tables;
//    while (query.next()) {
//        tables.push_back(query.value(0).toString());
//    }
//    QVERIFY2(tables.contains("vocabularies"), "Database not contain vocabulary table");
//    QVERIFY2(tables.contains("words"), "Database not contain words table");
//    m_database.removeDatabase();
//    QVERIFY2(!QFile(m_database.path()).exists(), "Database not destroyed.");
//    m_database.openDatabase();
//    m_database.createDatabase();
//}
