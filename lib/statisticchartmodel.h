#ifndef STATISTICCHARTMODEL_H
#define STATISTICCHARTMODEL_H

#include <QObject>
#include <QtCharts/QLineSeries>
#include "sqlstatisticmodel.h"
#include "sqltotalwordsstatisticmodel.h"
#include "datehelper.h"

QT_CHARTS_USE_NAMESPACE

class StatisticChartModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int vocabulary READ vocabulary WRITE setVocabulary NOTIFY vocabularyChanged)
    Q_PROPERTY(int total READ total WRITE setTotal NOTIFY totalChanged)
    Q_PROPERTY(int average READ average WRITE setAverage NOTIFY averageChanged)
    Q_PROPERTY(int learned READ learned WRITE setLearned NOTIFY learnedChanged)
public:
    explicit StatisticChartModel(QObject *parent = 0);

    Q_INVOKABLE void setAllWeekSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setAllMonthSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setAllYearSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setLearnedWeekSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setLearnedMonthSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setLearnedYearSeries(QLineSeries* lineSeries);

    int vocabulary() const;
    int total() const;
    int average() const;
    int learned() const;
signals:
    void vocabularyChanged();
    void totalChanged();
    void averageChanged();
    void learnedChanged();

public slots:
    void setVocabulary(int vocabulary);
    void setTotal(int total);
    void setAverage(int average);
    void setLearned(int learned);

private:
    void generateStatisticChart(const QList<QPair<QDate, int>>& statisticList,
                                const QDate& startDate,
                                QLineSeries *lineSeries);

    void generateTotalStatisticChart(const QList<QPair<QDate, int>>& statisticList,
                                const QDate& startDate,
                                QLineSeries *lineSeries);

    int m_vocabulary;
    int m_total;
    int m_average;
    int m_learned;
    DateHelper m_dateHelper;
    SqlStatisticModel m_statisticModel;
    SqlTotalWordsStatisticModel m_totalStatisticModel;
    QList<QPair<QDate, int>> m_statisticList;
    QList<QPair<QDate, int>> m_totalStatisticList;
};

#endif // STATISTICCHARTMODEL_H
