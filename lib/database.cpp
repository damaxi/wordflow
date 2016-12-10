#include "database.h"

#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QStandardPaths>
#include <QCoreApplication>

Database::Database()
    :
      m_path(QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0]),
      m_database(QSqlDatabase::addDatabase("QSQLITE")),
      m_database_name("/wordflow.sql")
{
    QDir dir(m_path);
    if(!dir.exists()) {
        dir.mkpath(m_path);
    }
    m_database.setDatabaseName(m_path + m_database_name);
    if(!m_database.open()) {
        qDebug() << m_database.lastError().text();
        QCoreApplication::quit();
    }
}

Database::~Database()
{
    m_database.close();
}

void Database::create_vocabulary(QString vocabulary, QString description) const
{
    QSqlQuery query;
    query.exec("CREATE table vocabularies "
                         "(ID INTEGER PRIMARY KEY, "
                         "vocabulary_name TEXT UNIQUE, "
                         "vocabulary_description TEXT UNIQUE)");
    query.exec("INSERT INTO vocabularies (vocabulary_name, vocabulary_description) VALUES "
               "('" + vocabulary + "','" + description + "')");
}

void Database::clean_tables() const
{
    QSqlQuery query;
    query.exec("DROP table vocabularies");
}

void Database::remove_database() const
{
    QFile file(m_path + m_database_name);
    if(file.exists()) file.remove();
}

QVariantList Database::list_vocabularies() const
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
