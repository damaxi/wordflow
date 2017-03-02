#ifndef SQLTOTALWORDSSTATISTICMODEL_H
#define SQLTOTALWORDSSTATISTICMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QDate>
#include <QString>
#include <QList>
#include <QPair>
#include <QDate>

class SqlTotalWordsStatisticModel : public QObject
{
    Q_OBJECT
public:
    explicit SqlTotalWordsStatisticModel(QObject *parent = 0);

    void updateChange(int vocabulary, int total);
    void deleteAll(int vocabulary);
signals:

public slots:

private:
    QString currentDate() const;
    bool checkExisting(int vocabulary);
    void update(int vocabulary, int total);
    void insert(int vocabulary, int total);

    QSqlQuery m_query;
};

#endif // SQLTOTALWORDSSTATISTICMODEL_H
