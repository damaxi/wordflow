#ifndef SQLSTATISTICMODEL_H
#define SQLSTATISTICMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QDate>
#include <QString>

class SqlStatisticModel : public QObject
{
    Q_OBJECT
public:
    explicit SqlStatisticModel(QObject *parent = 0);

    void updateDailyLearningStatistics(int vocabulary);
signals:

public slots:

private:
    QString currentDate() const;

    QSqlQuery m_query;
};

#endif // SQLSTATISTICMODEL_H
