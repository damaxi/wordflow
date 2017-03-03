#ifndef SQLTOTALWORDSSTATISTICMODEL_H
#define SQLTOTALWORDSSTATISTICMODEL_H

#include <QSqlQuery>
#include <QDate>
#include <QString>
#include <QList>
#include <QPair>
#include <QDate>
#include "sqlstatisticscommon.h"

class SqlTotalWordsStatisticModel : public SqlStatisticsCommon
{
    Q_OBJECT
public:
    explicit SqlTotalWordsStatisticModel(QObject *parent = 0);

    void updateChange(int vocabulary, int total);

protected:
    void setListQuery() override;
    void setDeleteQuery() override;

private:
    bool checkExisting(int vocabulary);
    void update(int vocabulary, int total);
    void insert(int vocabulary, int total);
};

#endif // SQLTOTALWORDSSTATISTICMODEL_H
