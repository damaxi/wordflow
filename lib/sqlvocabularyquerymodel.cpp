#include "sqlvocabularyquerymodel.h"

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

SqlVocabularyQueryModel::SqlVocabularyQueryModel(QObject *parent) : QSqlQueryModel(parent)
{
    createTable();
    refresh();
}

QVariant SqlVocabularyQueryModel::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(index, role);

    const QSqlRecord sqlRecord = record(index.row());
    return sqlRecord.value(role - Qt::UserRole);
}

QHash<int, QByteArray> SqlVocabularyQueryModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Qt::UserRole] = "id";
    names[Qt::UserRole + 1] = "name";
    names[Qt::UserRole + 2] = "description";
    return names;
}

int SqlVocabularyQueryModel::getItemId(int rowIndex) const
{
    return record(rowIndex).value("id").toInt();
}

void SqlVocabularyQueryModel::refresh()
{
    QSqlQuery query;
    if (!query.exec("SELECT id, vocabulary_name, vocabulary_description FROM vocabularies"))
        qFatal("Vocabularies SELECT query failed: %s", qPrintable(query.lastError().text()));

    setQuery(query);
    if (lastError().isValid())
        qFatal("Cannot set query on SqlContactModel: %s", qPrintable(lastError().text()));
}
