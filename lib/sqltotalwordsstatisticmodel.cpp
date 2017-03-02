#include "sqltotalwordsstatisticmodel.h"

#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <limits>

static const char *totalStatisticTableName = "total_statistics_change";

static void createTable()
{
    if (QSqlDatabase::database().tables().contains(totalStatisticTableName))
        return;

    QSqlQuery query;
    if (!query.exec("CREATE TABLE total_statistics_change (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "vocabulary INTEGER NOT NULL, "
                    "date TEXT NOT NULL, "
                    "total INTEGER NOT NULL, "
                    "FOREIGN KEY(vocabulary) REFERENCES vocabularies(id))")) {
       qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }
}

SqlTotalWordsStatisticModel::SqlTotalWordsStatisticModel(QObject *parent) : QObject(parent)
{
    createTable();
}

void SqlTotalWordsStatisticModel::updateChange(int vocabulary, int total)
{
    if (checkExisting(vocabulary)) {
        update(vocabulary, total);
    } else {
        insert(vocabulary, total);
    }
}

QString SqlTotalWordsStatisticModel::currentDate() const
{
    return QDate::currentDate().toString(Qt::ISODate);
}

bool SqlTotalWordsStatisticModel::checkExisting(int vocabulary)
{
    QString query = "SELECT * FROM %1 WHERE vocabulary = :vocabulary_id "
            "AND date LIKE :current_date";
    query = query.arg(totalStatisticTableName);
    m_query.prepare(query);
    m_query.bindValue(":vocabulary_id", vocabulary);
    m_query.bindValue(":current_date", currentDate());
    if (!m_query.exec()) {
        qFatal("Failed to select total statistics: %s", qPrintable(m_query.lastError().text()));
    }
    if (m_query.first()) return true;

    return false;
}

void SqlTotalWordsStatisticModel::update(int vocabulary, int total)
{
    QString query = "UPDATE %1 SET total = :total WHERE vocabulary = :vocabulary_id "
            "AND date LIKE :current_date";
    query = query.arg(totalStatisticTableName);
    m_query.prepare(query);
    m_query.bindValue(":vocabulary_id", vocabulary);
    m_query.bindValue(":total", total);
    m_query.bindValue(":current_date", currentDate());
    if (!m_query.exec()) {
        qFatal("Failed to update total statistics: %s", qPrintable(m_query.lastError().text()));
    }
}

void SqlTotalWordsStatisticModel::insert(int vocabulary, int total)
{
    QString query = "INSERT INTO %1 (vocabulary, date, total) VALUES (:vocabulary_id, "
            ":current_date, :total)";
    query = query.arg(totalStatisticTableName);
    m_query.prepare(query);
    m_query.bindValue(":vocabulary_id", vocabulary);
    m_query.bindValue(":total", total);
    m_query.bindValue(":current_date", currentDate());
    if (!m_query.exec()) {
        qFatal("Failed to insert total statistics: %s", qPrintable(m_query.lastError().text()));
    }
}

void SqlTotalWordsStatisticModel::deleteAll(int vocabulary)
{
    QString query = "DELETE FROM %1 WHERE vocabulary = :vocabulary_id";
    query = query.arg(totalStatisticTableName);
    m_query.prepare(query);
    m_query.bindValue(":vocabulary_id", vocabulary);
    if (!m_query.exec()) {
        qFatal("Failed to delete total statistics: %s", qPrintable(m_query.lastError().text()));
    }
}
