#include "database.h"

#include <QDir>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QStandardPaths>
#include <QCoreApplication>

Database::Database()
    :
      m_path(QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0]),
      m_database(QSqlDatabase::addDatabase("QSQLITE")),
       m_query(),
      m_database_name("/wordflow.sql")
{
    openDatabase();
}

Database::~Database()
{
    m_database.close();
}

void Database::openDatabase()
{
    QDir dir(m_path);
    if(!dir.exists())
        dir.mkpath(m_path);
    m_path += m_database_name;
    m_database.setDatabaseName(m_path);
    if(!m_database.open()) {
        qFatal("No database connection.");
        qDebug() << m_database.lastError().text();
        QCoreApplication::quit();
    }
}

void Database::createDatabase()
{
    m_query.exec("CREATE TABLE IF NOT EXISTS vocabularies "
                       "(ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "vocabulary_name TEXT UNIQUE NOT NULL, "
                       "vocabulary_description TEXT UNIQUE NOT NULL)");
    m_query.exec("CREATE TABLE words (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "vocabulary INTEGER NOT NULL, origin TEXT UNIQUE NOT NULL, "
                 "translated TEXT UNIQUE NOT NULL, progress INTEGER DEFAULT 0, "
                 "FOREIGN KEY(vocabulary) REFERENCES vocabularies(id))");
}

QString Database::path() const
{
    return m_path;
}

//void Database::create_vocabulary(QString vocabulary, QString description) const
//{
//    QSqlQuery query;

//    query.exec("INSERT INTO vocabularies (vocabulary_name, vocabulary_description) VALUES "
//               "('" + vocabulary + "','" + description + "')");
//}

void Database::clean_tables() const
{
    QSqlQuery query;
    query.exec("DROP table vocabularies");
}

void Database::removeDatabase()
{
    m_database.close();
    QFile file(m_path);
    if (file.exists())
        file.remove();
}

QVariantList Database::listVocabularies() const
{
    QVariantList vocabulary_list;
    QSqlQuery query;
    query.exec("SELECT vocabulary_name, vocabulary_description FROM vocabularies");
    while (query.next()) {
        QString name = query.value(0).toString();
        QString description = query.value(1).toString();
        QVariantMap map = { {"name", name}, {"description", description} };
        vocabulary_list << QVariant::fromValue(map);
    }

    return vocabulary_list;
}
