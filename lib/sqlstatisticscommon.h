#ifndef SQLSTATISTICSCOMMON_H
#define SQLSTATISTICSCOMMON_H

#include <QObject>
#include <QDate>
#include <QSqlQuery>

class SqlStatisticsCommon : public QObject
{
    Q_OBJECT
public:
    explicit SqlStatisticsCommon(QObject *parent = 0);
    virtual ~SqlStatisticsCommon() = default;

    QList<QPair<QDate, int> > listAll(int vocabulary);
    void deleteAll(int vocabulary);

protected:
    QString currentDate() const;
    virtual void setListQuery() = 0;
    virtual void setDeleteQuery() = 0;

    QSqlQuery m_query;
    QString m_listQuery;
    QString m_deleteQuery;
};

#endif // SQLSTATISTICSCOMMON_H
