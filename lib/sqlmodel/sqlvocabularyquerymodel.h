#ifndef SQLVOCABULARYQUERYMODEL_H
#define SQLVOCABULARYQUERYMODEL_H

#include <QSqlQueryModel>
#include "sqlvocabularymodel.h"

class SqlVocabularyQueryModel : public SqlVocabularyModel
{
    Q_OBJECT
public:
    explicit SqlVocabularyQueryModel(QObject *parent = 0);

    Q_INVOKABLE int getItemId(int rowIndex) const;
    Q_INVOKABLE void refresh();

signals:

public slots:

};

#endif // SQLVOCABULARYQUERYMODEL_H
