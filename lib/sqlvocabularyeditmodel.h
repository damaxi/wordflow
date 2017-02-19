#ifndef SQLVOCABULARYEDITMODEL_H
#define SQLVOCABULARYEDITMODEL_H

#include <QSqlTableModel>
#include "sqlvocabularymodel.h"

class SqlVocabularyEditModel : public SqlVocabularyModel2
{
    Q_OBJECT
public:
    explicit SqlVocabularyEditModel(QObject *parent = 0);

    Q_INVOKABLE void updateVocabulary(int row, const QString &vocabulary, const QString &description);
    Q_INVOKABLE void addVocabulary(const QString &vocabulary, const QString &description);
    Q_INVOKABLE void deleteVocabulary(int row);
};

#endif // SQLVOCABULARYEDITMODEL_H
