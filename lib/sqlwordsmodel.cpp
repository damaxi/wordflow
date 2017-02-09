#include "sqlwordsmodel.h"

#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDebug>

static const char *wordsTableName = "words";

static void createTable()
{
    if (QSqlDatabase::database().tables().contains(wordsTableName))
        return;

    QSqlQuery query;
    if (!query.exec("CREATE TABLE words (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "vocabulary INTEGER NOT NULL, "
                 "origin TEXT NOT NULL UNIQUE, "
                 "translated TEXT NOT NULL, "
                 "progress INTEGER DEFAULT 0, "
                 "FOREIGN KEY(vocabulary) REFERENCES vocabularies(id))")) {
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }
}

SqlWordsModel::SqlWordsModel(QObject *parent) :
    QSqlTableModel(parent),
    m_vocabularyfiter(-1)
{
    createTable();
    setTable(wordsTableName);
    setSort(2, Qt::DescendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant SqlWordsModel::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    const QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> SqlWordsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Qt::UserRole] = "id";
    names[Qt::UserRole + 2] = "origin";
    names[Qt::UserRole + 3] = "translated";
    names[Qt::UserRole + 4] = "progress";
    return names;
}

int SqlWordsModel::vocabularyfilter() const
{
    return m_vocabularyfiter;
}

void SqlWordsModel::setVocabularyfilter(int vocabularyId)
{
    if (vocabularyId == m_vocabularyfiter)
        return;

    m_vocabularyfiter = vocabularyId;
    mergeFilters();

    emit vocabularyfilterChanged();
}

void SqlWordsModel::updateProgress(int row, int progress)
{
    QSqlRecord updatedRecord = record(row);
    updatedRecord.setValue("progress", progress);
    if (!setRecord(row, updatedRecord)) {
        qWarning() << "Failed to update progress: " << lastError().text();
        return;
    }
    submitAll();
}

void SqlWordsModel::mergeFilters()
{
    QString filterString =  QString::fromLatin1("vocabulary = %1").arg(m_vocabularyfiter);
    setFilter(filterString);
    select();
}
