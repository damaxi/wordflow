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

    Q_INVOKABLE void setWeekSeries(QLineSeries* lineSeries);
signals:

public slots:
};

#endif // STATISTICCHARTMODEL_H
