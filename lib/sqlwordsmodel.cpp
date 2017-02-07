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
    m_filter()
{
    createTable();
    setTable(wordsTableName);
    setSort(2, Qt::DescendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
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

QString SqlWordsModel::originfilter() const
{
    return m_filter;
}

void SqlWordsModel::setOriginfilter(const QString &filter)
{
    if (filter == m_filter)
        return;

    m_filter = filter;
    const QString filterString = QString::fromLatin1("origin LIKE '%1%'").arg(m_filter);
    setFilter(filterString);
    select();

    emit originfilterChanged();
}

void SqlWordsModel::addWord(const QString &origin, const QString &translated, int vocabulary)
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

void SqlWordsModel::updateWord(int row, const QString &origin, const QString &translated)
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

void SqlWordsModel::removeWord(int row)
{
    if (!removeRows(row, 1)) {
        qWarning() << "Failed to remove world: " << lastError().text();
        return;
    }
    submitAll();
}

void SqlWordsModel::removeAll()
{
    removeRows(0, rowCount());
    submitAll();
}

void SqlWordsModel::resetAll()
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
