#include "sqlwordseditmodel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

SqlWordsEditModel::SqlWordsEditModel(QObject *parent)
    : SqlWordsModel(parent), m_originfilter(), m_statisticModel(),
      m_totalStatisticModel() {
  setSort(2, Qt::AscendingOrder);
}

QString SqlWordsEditModel::originfilter() const { return m_originfilter; }

void SqlWordsEditModel::setOriginfilter(const QString &filter) {
  if (filter == m_originfilter)
    return;

  m_originfilter = filter;
  mergeFilters();

  emit originfilterChanged();
}

void SqlWordsEditModel::addWord(const QString &origin,
                                const QString &translated) {
  QSqlRecord newRecord = record();
  newRecord.setValue("vocabulary", m_vocabularyfiter);
  newRecord.setValue("origin", origin);
  newRecord.setValue("translated", translated);
  newRecord.setValue("progress", QString::number(0));
  if (!insertRecord(rowCount(), newRecord)) {
    qWarning() << "Failed to insert word: " << lastError().text();
    return;
  }
  submitAll();
  m_totalStatisticModel.updateChange(m_vocabularyfiter, rowCount());
}

bool SqlWordsEditModel::ifExist(const QString &origin) {
  QString exist_query =
      "SELECT EXISTS(SELECT * FROM words "
      "WHERE vocabulary = :vocabulary AND origin LIKE :origin LIMIT 1)";
  QSqlQuery query;
  query.prepare(exist_query);
  query.bindValue(":vocabulary", m_vocabularyfiter);
  query.bindValue(":origin", origin);
  if (!query.exec()) {
    qFatal("Failed to query exist words: %s",
           qPrintable(query.lastError().text()));
  }
  if (query.first()) {
    return query.value(0).toBool();
  }
  return false;
}

void SqlWordsEditModel::updateWord(int row, const QString &origin,
                                   const QString &translated) {
  QSqlRecord updatedRecord = record(row);
  updatedRecord.setValue("origin", origin);
  updatedRecord.setValue("translated", translated);
  if (!setRecord(row, updatedRecord)) {
    qWarning() << "Failed to update word: " << lastError().text();
    return;
  }
  submitAll();
}

void SqlWordsEditModel::resetWordProgress(int row) {
  m_statisticModel.downgradeDailyLearningStatistics(m_vocabularyfiter);
  updateProgress(row, 0);
}

void SqlWordsEditModel::removeWord(int row) {
  QSqlRecord removedRow = record(row);
  if (removedRow.value("progress").toInt() > 0) {
    m_statisticModel.downgradeDailyLearningStatistics(m_vocabularyfiter);
  }
  if (!removeRows(row, 1)) {
    qWarning() << "Failed to remove world: " << lastError().text();
    return;
  }
  submitAll();
  m_totalStatisticModel.updateChange(m_vocabularyfiter, rowCount());
}

void SqlWordsEditModel::removeAll() {
  m_totalStatisticModel.deleteAll(m_vocabularyfiter);
  m_statisticModel.deleteAll(m_vocabularyfiter);
  removeRows(0, rowCount());
  submitAll();
}

void SqlWordsEditModel::resetAll() {
  for (int row = 0; row < rowCount(); ++row) {
    QSqlRecord updatedRecord = record(row);
    updatedRecord.setValue("progress", 0);
    if (!setRecord(row, updatedRecord)) {
      qWarning() << "Failed to update progress: " << lastError().text();
      return;
    }
  }
  submitAll();
}

void SqlWordsEditModel::mergeFilters() {
  QString filterString;
  if (m_vocabularyfiter != -1 && m_originfilter.isEmpty())
    filterString =
        QString::fromLatin1("vocabulary = %1").arg(m_vocabularyfiter);
  else if (m_vocabularyfiter != -1 && !m_originfilter.isEmpty())
    filterString = QString::fromLatin1("vocabulary = %1 AND origin LIKE '%2%'")
                       .arg(m_vocabularyfiter)
                       .arg(m_originfilter);
  else if (m_vocabularyfiter == -1 && !m_originfilter.isEmpty())
    filterString = QString::fromLatin1("origin LIKE '%2%'").arg(m_originfilter);
  else
    qWarning() << "Unknown words filter";
  setFilter(filterString);
  select();
}
