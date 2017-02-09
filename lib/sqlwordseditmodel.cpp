#include "sqlwordseditmodel.h"

#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDebug>

SqlWordsEditModel::SqlWordsEditModel(QObject *parent) :
    SqlWordsModel(parent),
    m_originfilter()
{

}

QString SqlWordsEditModel::originfilter() const
{
    return m_originfilter;
}

void SqlWordsEditModel::setOriginfilter(const QString &filter)
{
    if (filter == m_originfilter)
        return;

    m_originfilter = filter;
    mergeFilters();

    emit originfilterChanged();
}

void SqlWordsEditModel::addWord(const QString &origin, const QString &translated, int vocabulary)
{
    QSqlRecord newRecord = record();
    newRecord.setValue("vocabulary", vocabulary);
    newRecord.setValue("origin", origin);
    newRecord.setValue("translated", translated);
    newRecord.setValue("progress", QString::number(0));
    if (!insertRecord(rowCount(), newRecord)) {
        qWarning() << "Failed to insert word: " << lastError().text();
        return;
    }
    submitAll();
}

void SqlWordsEditModel::updateWord(int row, const QString &origin, const QString &translated)
{
    QSqlRecord updatedRecord = record(row);
    updatedRecord.setValue("origin", origin);;
    updatedRecord.setValue("translated", translated);
    if (!setRecord(row, updatedRecord)) {
        qWarning() << "Failed to update word: " << lastError().text();
        return;
    }
    submitAll();
}

void SqlWordsEditModel::removeWord(int row)
{
    if (!removeRows(row, 1)) {
        qWarning() << "Failed to remove world: " << lastError().text();
        return;
    }
    submitAll();
}

void SqlWordsEditModel::removeAll()
{
    removeRows(0, rowCount());
    submitAll();
}

void SqlWordsEditModel::resetAll()
{
    for (int row = 0; row < rowCount(); ++row)
    {
        QSqlRecord updatedRecord = record(row);
        updatedRecord.setValue("progress", 0);
        if (!setRecord(row, updatedRecord)) {
            qWarning() << "Failed to update progress: " << lastError().text();
            return;
        }
    }
    submitAll();
}

void SqlWordsEditModel::mergeFilters()
{
    QString filterString;
    if (m_vocabularyfiter != -1 && m_originfilter.isEmpty())
        filterString =  QString::fromLatin1("vocabulary = %1").arg(m_vocabularyfiter);
    else if (m_vocabularyfiter != -1 && !m_originfilter.isEmpty())
        filterString = QString::fromLatin1("vocabulary = %1 AND origin LIKE '%2%'")
            .arg(m_vocabularyfiter).arg(m_originfilter);
    else if (m_vocabularyfiter == -1 && !m_originfilter.isEmpty())
        filterString = QString::fromLatin1("origin LIKE '%2%'").arg(m_originfilter);
    else
        qWarning() << "Unknown words filter";
    setFilter(filterString);
    select();
}
