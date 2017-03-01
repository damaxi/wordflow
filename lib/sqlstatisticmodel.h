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
    void downgradeDailyLearningStatistics(int vocabulary);
    void removeAllVocabularyStatistics(int vocabulary);
signals:

public slots:

private:
    QString currentDate() const;
    int getCurrentCount(int vocabulary);
    void updateStatistics(int vocabulary, int count);
    void insertStatistics(int vocabulary, int count = 1);
    void removeStatistics(int vocabulary);

    QSqlQuery m_query;
};

#endif // SQLSTATISTICMODEL_H
