#include "sqlvocabularyquerymodel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

SqlVocabularyQueryModel::SqlVocabularyQueryModel(QObject *parent) : SqlVocabularyModel(parent)
{
    refresh();
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
