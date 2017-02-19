#include "sqlvocabularymodel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

static const char *wordsTableName = "vocabularies";

static void createTable()
{
    if (QSqlDatabase::database().tables().contains(wordsTableName))
        return;

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS vocabularies "
                       "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "vocabulary_name TEXT UNIQUE NOT NULL, "
                       "vocabulary_description TEXT NOT NULL)")) {
        qFatal("Failed to query database: %s", qPrintable(query.lastError().text()));
    }
}

SqlVocabularyModel::SqlVocabularyModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    createTable();
}

QVariant SqlVocabularyModel::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(index, role);

    const QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> SqlVocabularyModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Qt::UserRole] = "id";
    names[Qt::UserRole + 1] = "name";
    names[Qt::UserRole + 2] = "description";
    return names;
}

// ====================================================================================

SqlVocabularyModel2::SqlVocabularyModel2(QObject *parent) :
    QSqlTableModel(parent)
{
    createTable();
    setTable(wordsTableName);
}

QVariant SqlVocabularyModel2::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(index, role);

    const QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> SqlVocabularyModel2::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Qt::UserRole] = "id";
    names[Qt::UserRole + 1] = "name";
    names[Qt::UserRole + 2] = "description";
    return names;
}
