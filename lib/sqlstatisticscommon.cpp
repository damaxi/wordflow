#include "sqlstatisticscommon.h"

#include <QSqlQuery>
#include <QDate>
#include <QString>
#include <QList>
#include <QPair>
#include <QDate>
#include <QSqlError>
#include <QSqlRecord>

SqlStatisticsCommon::SqlStatisticsCommon(QObject *parent) : QObject(parent)
{}

QList<QPair<QDate, int> > SqlStatisticsCommon::listAll(int vocabulary)
{
    m_query.prepare(m_listQuery);
    m_query.bindValue(":vocabulary_id", vocabulary);
    if (!m_query.exec()) {
        qFatal("Failed to select statistics: %s", qPrintable(m_query.lastError().text()));
    }
    QList<QPair<QDate, int>> statisticList;
    while (m_query.next()) {
        QString dateString = m_query.value(0).toString();
        int count = m_query.value(1).toInt();
        statisticList.append(qMakePair(QDate::fromString(dateString, Qt::ISODate), count));
    }

    return statisticList;
}

void SqlStatisticsCommon::deleteAll(int vocabulary)
{
    m_query.prepare(m_deleteQuery);
    m_query.bindValue(":vocabulary_id", vocabulary);
    if (!m_query.exec()) {
        qFatal("Failed to delete statistics: %s", qPrintable(m_query.lastError().text()));
    }
}

QString SqlStatisticsCommon::currentDate() const
{
    return QDate::currentDate().toString(Qt::ISODate);
}
