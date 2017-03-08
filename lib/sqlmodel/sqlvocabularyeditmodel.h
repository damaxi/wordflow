#ifndef SQLVOCABULARYEDITMODEL_H
#define SQLVOCABULARYEDITMODEL_H

#include <QSqlTableModel>
#include "sqlvocabularymodel.h"
#include "sqlstatisticmodel.h"
#include "sqltotalwordsstatisticmodel.h"

class SqlVocabularyEditModel : public SqlVocabularyModel2
{
    Q_OBJECT
public:
    explicit SqlVocabularyEditModel(QObject *parent = 0);

    Q_INVOKABLE void updateVocabulary(int row, const QString &vocabulary, const QString &description);
    Q_INVOKABLE void addVocabulary(const QString &vocabulary, const QString &description);
    Q_INVOKABLE void deleteVocabulary(int row);

private:
    SqlStatisticModel m_statisticModel;
    SqlTotalWordsStatisticModel m_totalStatisticsModel;
};

#endif // SQLVOCABULARYEDITMODEL_H
