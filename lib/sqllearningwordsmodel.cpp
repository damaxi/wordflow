#include "sqllearningwordsmodel.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

SqlLearningWordsModel::SqlLearningWordsModel(QObject *parent) :
    SqlWordsModel(parent),
    m_ordersort(true),
    m_limit(10),
    m_maxprogress(100),
    m_statisticsModel()
{}

void SqlLearningWordsModel::setProgressEasy(int row)
{
    m_statisticsModel.updateDailyLearningStatistics(m_vocabularyfiter);
    updateProgress(row, EasyProgress);
}

void SqlLearningWordsModel::setProgressGood(int row)
{
    updateProgress(row, GoodProgress);
}

void SqlLearningWordsModel::setProgressHard(int row)
{
    updateProgress(row, HardProgress);
}

void SqlLearningWordsModel::setProgressAgain(int row)
{
    updateProgress(row, AgainProgress);
}

int SqlLearningWordsModel::countWords() const
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM words WHERE vocabulary = :vocabulary_id");
    query.bindValue(":vocabulary_id", m_vocabularyfiter);
    if (!query.exec()) {
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }
    if (!query.first()) {
        qFatal("Failed cannot count all rows: %s", qPrintable(query.lastError().text()));
        return -1;
    }
    return query.value(0).toInt();
}

void SqlLearningWordsModel::setOrdersort(bool ordersort)
{
    if (m_ordersort == ordersort)
        return;

    m_ordersort = ordersort;
    mergeFilters();
    emit ordersortChanged(ordersort);
}

void SqlLearningWordsModel::setLimit(int limit)
{
    if (m_limit == limit)
        return;

    m_limit = limit;
    mergeFilters();
    emit limitChanged(limit);
}

void SqlLearningWordsModel::setMaxprogress(int maxprogress)
{
    if (m_maxprogress == maxprogress)
        return;

    m_maxprogress = maxprogress;
    mergeFilters();
    emit maxprogressChanged(maxprogress);
}

bool SqlLearningWordsModel::ordersort() const
{
    return m_ordersort;
}

int SqlLearningWordsModel::limit() const
{
    return m_limit;
}

int SqlLearningWordsModel::maxprogress() const
{
    return m_maxprogress;
}

void SqlLearningWordsModel::mergeFilters()
{
    QString filterString;
    if (m_vocabularyfiter != -1 && m_maxprogress != -1)
        filterString = QString::fromLatin1("vocabulary = %1 AND progress < %2")
            .arg(m_vocabularyfiter).arg(m_maxprogress);
    else if (m_vocabularyfiter != -1 && m_maxprogress == -1)
        filterString =  QString::fromLatin1("vocabulary = %1").arg(m_vocabularyfiter);
    else if (m_vocabularyfiter == -1 && m_maxprogress != -1)
        filterString = QString::fromLatin1("progress < %2").arg(m_maxprogress);

    if (m_ordersort)
        setSort(4, Qt::AscendingOrder);

    setFilter(filterString);
    select();
}

void SqlLearningWordsModel::immediatetelySubmitDefaultProperties()
{
    // not update immediatly cause it shouldn't be reselected all the time
    // virtual method to disable it
}
