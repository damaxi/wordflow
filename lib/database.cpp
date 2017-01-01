#include "database.h"

#include <QDir>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QStandardPaths>
#include <QCoreApplication>
#include "sqlerror.h"

Database::Database(QObject *parent)
    :
      QObject(parent),
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
    m_database.setDatabaseName(m_path + m_database_name);
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
                       "vocabulary_description TEXT NOT NULL)");
    m_query.exec("CREATE TABLE words (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "vocabulary INTEGER NOT NULL, origin TEXT NOT NULL, "
                 "translated TEXT NOT NULL, progress INTEGER DEFAULT 0, "
                 "FOREIGN KEY(vocabulary) REFERENCES vocabularies(id))");
}

bool Database::createVocabulary(QString vocabulary, QString description)
{
        m_query.prepare("INSERT INTO vocabularies (vocabulary_name, vocabulary_description) "
                   "VALUES (:vocabulary, :description)");
        m_query.bindValue(":vocabulary", vocabulary);
        m_query.bindValue(":description", description);
        return m_query.exec();
}

bool Database::createWord(QString origin, QString translated, int vocabulary_id)
{
    m_query.prepare("INSERT INTO words (vocabulary, origin, translated) "
               "VALUES (:vocabulary, :origin, :translated)");
    m_query.bindValue(":vocabulary", vocabulary_id);
    m_query.bindValue(":origin", origin);
    m_query.bindValue(":translated", translated);
    return m_query.exec();
}

bool Database::updateProgress(QString origin, int vocabulary_id, int progress)
{
    m_query.prepare("UPDATE words SET progress = :progress "
                    "WHERE origin = :origin AND vocabulary = :vocabulary_id");
    m_query.bindValue(":progress", progress);
    m_query.bindValue(":origin", origin);
    m_query.bindValue(":vocabulary_id", vocabulary_id);
    return m_query.exec();
}

QVariantList Database::listWords(int vocabulary, int limit, bool sort)
{
    QString query = "SELECT origin, translated, progress FROM words WHERE vocabulary = :vocabulary ";
    if (sort)
        query += "ORDER BY progress ASC ";
    if (limit != std::numeric_limits<int>::max())
        query += "LIMIT :limit";

    m_query.prepare(query);
    m_query.bindValue(":vocabulary", vocabulary);
    if (limit != std::numeric_limits<int>::max())
        m_query.bindValue(":limit", limit);
    m_query.exec();
    QVariantList word_list;
    while (m_query.next()) {
        QString origin = m_query.value(0).toString();
        QString translated = m_query.value(1).toString();
        int progress = m_query.value(2).toInt();
        QVariantList word = { origin, translated, progress };
        word_list << QVariant::fromValue(word);
    }

    return word_list;
}

QString Database::path() const
{
    return m_path + m_database_name;
}

void Database::runSql()
{
    if(!m_query.exec())
        throw SqlError(m_query.lastError().text().toStdString());
}

void Database::cleanTables()
{
    m_query.exec("SELECT name FROM sqlite_master WHERE type='table'");
    while (m_query.next()) {
        m_query.exec("DROP TABLE " + m_query.value(0).toString());
    }
}

void Database::removeDatabase()
{
    m_database.close();
    QFile file(m_path + m_database_name);
    if (file.exists())
        file.remove();
}

QVariantList Database::listVocabularies()
{
    QVariantList vocabulary_list;
    m_query.exec("SELECT vocabulary_name, vocabulary_description FROM vocabularies");
    while (m_query.next()) {
        QString name = m_query.value(0).toString();
        QString description = m_query.value(1).toString();
        QVariantMap map = { {"name", name}, {"description", description} };
        vocabulary_list << QVariant::fromValue(map);
    }

    return vocabulary_list;
}
