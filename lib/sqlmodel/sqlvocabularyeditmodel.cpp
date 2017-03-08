#include "sqlvocabularyeditmodel.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

SqlVocabularyEditModel::SqlVocabularyEditModel(QObject *parent) :
        SqlVocabularyModel2(parent),
        m_statisticModel(),
        m_totalStatisticsModel()
{
    setSort(1, Qt::AscendingOrder);
    setEditStrategy(QSqlTableModel::OnRowChange);
    select();
}

void SqlVocabularyEditModel::updateVocabulary(int row, const QString &vocabulary, const QString &description)
{
    QSqlRecord updatedRecord = record(row);
    updatedRecord.setValue("vocabulary_name", vocabulary);;
    updatedRecord.setValue("vocabulary_description", description);
    if (!setRecord(row, updatedRecord)) {
        qWarning() << "Failed to update vocabulary: " << lastError().text();
        return;
    }
    selectRow(row);
}

void SqlVocabularyEditModel::addVocabulary(const QString &vocabulary, const QString &description)
{
    QSqlRecord newRecord = record();
    newRecord.setValue("vocabulary_name", vocabulary);
    newRecord.setValue("vocabulary_description", description);
    if (!insertRecord(rowCount(), newRecord)) {
        qWarning() << "Failed to insert vocabulary: " << lastError().text();
        return;
    }
    select();
}

void SqlVocabularyEditModel::deleteVocabulary(int row)
{
    if (rowCount() == 1) {
        qWarning() << "Cann't delete last vocabulary.";
        return;
    }
    int deletedVocabularyId = record(row).value("id").toInt();
    m_statisticModel.deleteAll(deletedVocabularyId);
    m_totalStatisticsModel.deleteAll(deletedVocabularyId);
    if (!removeRows(row, 1)) {
        qWarning() << "Failed to remove vocabulary: " << lastError().text();
        return;
    }
    QSqlQuery query;
    query.prepare("DELETE FROM words WHERE vocabulary = :vocabulary_id");
    query.bindValue(":vocabulary_id", deletedVocabularyId);
    if (!query.exec()) {
        qFatal("Failed to delete vocabulary: %s", qPrintable(query.lastError().text()));
    }
    select();
}
