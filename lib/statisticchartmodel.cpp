#include "statisticchartmodel.h"

#include <QDateTime>
#include <QDebug>

StatisticChartModel::StatisticChartModel(QObject *parent) : QObject(parent)
{

}

void StatisticChartModel::setWeekSeries(QLineSeries* lineSeries)
{
    QPen penBloodSugar;
    penBloodSugar.setColor(QColor(34, 102, 102));
    penBloodSugar.setWidth(5);
    QDateTime xValue;
    xValue.setDate(QDate::currentDate());
    xValue.setTime(QTime(0,0));
    lineSeries->append(xValue.toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addDays(1).toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addDays(2).toMSecsSinceEpoch(), 50);
    lineSeries->append(xValue.addDays(3).toMSecsSinceEpoch(), 10);
    lineSeries->append(xValue.addDays(4).toMSecsSinceEpoch(), 50);
    lineSeries->append(xValue.addDays(5).toMSecsSinceEpoch(), 90);
    lineSeries->append(xValue.addDays(6).toMSecsSinceEpoch(), 110);
    qDebug() << xValue.toMSecsSinceEpoch();
    qDebug() << xValue.addDays(6).toMSecsSinceEpoch();
    lineSeries->setPen(penBloodSugar);
}
