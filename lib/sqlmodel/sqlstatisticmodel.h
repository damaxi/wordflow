#ifndef SQLSTATISTICMODEL_H
#define SQLSTATISTICMODEL_H

#include <QSqlQuery>
#include <QDate>
#include <QString>
#include <QList>
#include <QPair>
#include <QDate>
#include "sqlstatisticscommon.h"

class SqlStatisticModel : public SqlStatisticsCommon
{
    Q_OBJECT
public:
    explicit SqlStatisticModel(QObject *parent = 0);

    void updateDailyLearningStatistics(int vocabulary);
    void downgradeDailyLearningStatistics(int vocabulary);

protected:
    void setListQuery() override;
    void setDeleteQuery() override;

private:
    int getCurrentCount(int vocabulary);
    void updateStatistics(int vocabulary, int count);
    void insertStatistics(int vocabulary, int count = 1);
    void removeStatistics(int vocabulary);   
};

#endif // SQLSTATISTICMODEL_H
