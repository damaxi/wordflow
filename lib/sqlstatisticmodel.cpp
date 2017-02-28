#include "sqlstatisticmodel.h"

#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

static const char *statisticTableName = "statistics";

static void createTable()
{
    if (QSqlDatabase::database().tables().contains(statisticTableName))
        return;

    QSqlQuery query;
    if (!query.exec("CREATE TABLE statistics (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "vocabulary INTEGER NOT NULL, "
                    "date TEXT NOT NULL, "
                    "count INTEGER NOT NULL, "
                    "FOREIGN KEY(vocabulary) REFERENCES vocabularies(id))")) {
       qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }
}

SqlStatisticModel::SqlStatisticModel(QObject *parent) :
    QObject(parent)
{
    createTable();
}

void SqlStatisticModel::updateDailyLearningStatistics(int vocabulary)
{
    QString query = "SELECT count FROM %1 WHERE vocabulary = :vocabulary_id "
            "AND date LIKE ':current_date'";
    query = query.arg(statisticTableName);
    qDebug() << query;
    m_query.prepare(query);
    m_query.bindValue(":vocabulary_id", vocabulary);
    m_query.bindValue(":current_date", currentDate());
    if (!m_query.exec()) {
        qFatal("Failed to query statistics: %s", qPrintable(m_query.lastError().text()));
    }
    if (m_query.first()) {
        int count = m_query.value(0).toInt();
        query = "UPDATE %1 SET count = :count WHERE vocabulary = :vocabulary_id "
                "AND date LIKE ':current_date'";
        query = query.arg(statisticTableName);
        m_query.prepare(query);
        m_query.bindValue(":count", ++count);
        m_query.bindValue(":vocabulary_id", vocabulary);
        m_query.bindValue(":current_date", currentDate());
        if (!m_query.exec()) {
            qFatal("Failed to update statistics: %s", qPrintable(m_query.lastError().text()));
        }
    } else {
        query = "INSERT INTO %1 (vocabulary, date, count) VALUES (:vocabulary_id, "
                ":current_date, :count)";
        query = query.arg(statisticTableName);
        m_query.prepare(query);
        m_query.bindValue(":vocabulary_id", vocabulary);
        m_query.bindValue(":current_date", currentDate());
        m_query.bindValue(":count", 1);
        if (!m_query.exec()) {
            qFatal("Failed to create statistics: %s", qPrintable(m_query.lastError().text()));
        }
    }
}

QString SqlStatisticModel::currentDate() const
{
   return QDate::currentDate().toString(Qt::ISODate);
}
