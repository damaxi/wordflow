#include "database.h"

#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QStandardPaths>
#include <QCoreApplication>
#include "sqlerror.h"

Database::Database(QObject *parent)
    :
      QObject(parent),
      m_path(QStandardPaths::writetableLocation(QStandardPaths::AppDataLocation)),
      m_database(QSqlDatabase::addDatabase("QSQLITE")),
      m_query(),
      m_database_name("/wordflow.sqlite3")
{
    openDatabase();
}

Database::~Database()
{
    m_database.close();
}

void Database::openDatabase()
{
    if(!m_path.mkpath("."))
        qFatal("Failed to create writable directory at %s", qPrintable(m_path.absolutePath()));
    m_database.setDatabaseName(m_path.absolutePath() + m_database_name);
    if(!m_database.open()) {
        qFatal("No database connection.");
        qDebug() << m_database.lastError().text();
        QCoreApplication::quit();
    }
}

void Database::createDatabase()
{
    m_query.exec("CREATE TABLE IF NOT EXISTS vocabularies "
                       "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
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

bool Database::updateWord(int word_id, QString origin, QString translated)
{
    m_query.prepare("UPDATE words SET origin = :origin, translated = :translated "
                    "WHERE id = :word_id");
    m_query.bindValue(":origin", origin);
    m_query.bindValue(":translated", translated);
    m_query.bindValue(":word_id", word_id);
    return m_query.exec();
}

bool Database::deleteWord(int word_id)
{
    m_query.prepare("DELETE FROM words WHERE id = :word_id");
    m_query.bindValue(":word_id", word_id);
    return m_query.exec();
}

bool Database::deleteAll(int vocabulary_id)
{
    m_query.prepare("DELETE FROM words WHERE vocabulary = :vocabulary_id");
    m_query.bindValue(":vocabulary_id", vocabulary_id);
    return m_query.exec();
}

bool Database::updateProgress(int word_id, int progress)
{
    m_query.prepare("UPDATE words SET progress = :progress "
                    "WHERE id = :word_id");
    m_query.bindValue(":progress", progress);
    m_query.bindValue(":word_id", word_id);
    return m_query.exec();
}

bool Database::resetProgresses(int vocabulary_id)
{
    m_query.prepare("UPDATE words SET progress = 0 "
                    "WHERE vocabulary = :vocabulary_id");
    m_query.bindValue(":vocabulary_id", vocabulary_id);
    return m_query.exec();
}

int Database::countWords(int vocabulary_id)
{
    QString query = "SELECT COUNT(*) FROM words WHERE vocabulary = :vocabulary_id";
    m_query.prepare(query);
    m_query.bindValue(":vocabulary_id", vocabulary_id);
    m_query.exec();
    m_query.next();
    return m_query.value(0).toInt();
}

QVariantList Database::listWords(int vocabulary, int limit, bool sort, bool onlyNotCompleted)
{
    QString query = "SELECT id, origin, translated, progress FROM words WHERE vocabulary = :vocabulary ";
    if (onlyNotCompleted)
        query += "AND progress < 100 ";
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
        int id = m_query.value(0).toInt();
        QString origin = m_query.value(1).toString();
        QString translated = m_query.value(2).toString();
        int progress = m_query.value(3).toInt();
        QVariantMap map = { {"id", id}, {"origin", origin},
                            {"translated", translated}, {"progress", progress} };
        word_list << QVariant::fromValue(map);
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
    m_query.exec("SELECT id, vocabulary_name, vocabulary_description FROM vocabularies");
    while (m_query.next()) {
        int id = m_query.value(0).toInt();
        QString name = m_query.value(1).toString();
        QString description = m_query.value(2).toString();
        QVariantMap map = { {"id", id}, {"name", name}, {"description", description} };
        vocabulary_list << QVariant::fromValue(map);
    }

    return vocabulary_list;
}
