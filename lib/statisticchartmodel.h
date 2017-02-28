#ifndef STATISTICCHARTMODEL_H
#define STATISTICCHARTMODEL_H

#include <QObject>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

class StatisticChartModel : public QObject
{
    Q_OBJECT
public:
    explicit StatisticChartModel(QObject *parent = 0);

    Q_INVOKABLE void setAllWeekSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setAllMonthSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setAllYearSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setLearnedWeekSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setLearnedMonthSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setLearnedYearSeries(QLineSeries* lineSeries);
signals:

public slots:
};

#endif // STATISTICCHARTMODEL_H
