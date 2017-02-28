#include "statisticchartmodel.h"

#include <QDateTime>
#include <QDebug>

StatisticChartModel::StatisticChartModel(QObject *parent) : QObject(parent)
{

}

void StatisticChartModel::setAllWeekSeries(QLineSeries* lineSeries)
{
    QDateTime xValue;
    xValue.setDate(QDate::currentDate());
    xValue.setTime(QTime(0,0));
    lineSeries->clear();
    lineSeries->append(xValue.toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addDays(-1).toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addDays(-2).toMSecsSinceEpoch(), 50);
    lineSeries->append(xValue.addDays(-3).toMSecsSinceEpoch(), 10);
    lineSeries->append(xValue.addDays(-4).toMSecsSinceEpoch(), 50);
    lineSeries->append(xValue.addDays(-5).toMSecsSinceEpoch(), 90);
    lineSeries->append(xValue.addDays(-6).toMSecsSinceEpoch(), 110);
}

void StatisticChartModel::setAllMonthSeries(QLineSeries *lineSeries)
{
    QDateTime xValue;
    xValue.setDate(QDate::currentDate());
    xValue.setTime(QTime(0,0));
    lineSeries->clear();
    lineSeries->append(xValue.toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addDays(-1).toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addDays(-2).toMSecsSinceEpoch(), 50);
    lineSeries->append(xValue.addDays(-3).toMSecsSinceEpoch(), 10);
    lineSeries->append(xValue.addDays(-14).toMSecsSinceEpoch(), 50);
    lineSeries->append(xValue.addDays(-15).toMSecsSinceEpoch(), 90);
    lineSeries->append(xValue.addDays(-28).toMSecsSinceEpoch(), 110);
}

void StatisticChartModel::setAllYearSeries(QLineSeries *lineSeries)
{
    QDateTime xValue;
    xValue.setDate(QDate::currentDate());
    xValue.setTime(QTime(0,0));
    lineSeries->clear();
    lineSeries->append(xValue.toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addMonths(-1).toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addMonths(-2).toMSecsSinceEpoch(), 50);
    lineSeries->append(xValue.addMonths(-3).toMSecsSinceEpoch(), 10);
    lineSeries->append(xValue.addMonths(-4).toMSecsSinceEpoch(), 50);
    lineSeries->append(xValue.addMonths(-5).toMSecsSinceEpoch(), 90);
    lineSeries->append(xValue.addMonths(-6).toMSecsSinceEpoch(), 110);
    lineSeries->append(xValue.addMonths(-7).toMSecsSinceEpoch(), 110);
    lineSeries->append(xValue.addMonths(-8).toMSecsSinceEpoch(), 110);
    lineSeries->append(xValue.addMonths(-9).toMSecsSinceEpoch(), 110);
    lineSeries->append(xValue.addMonths(-10).toMSecsSinceEpoch(), 110);
    lineSeries->append(xValue.addMonths(-11).toMSecsSinceEpoch(), 10);
}

void StatisticChartModel::setLearnedWeekSeries(QLineSeries *lineSeries)
{
    QDateTime xValue;
    xValue.setDate(QDate::currentDate());
    xValue.setTime(QTime(0,0));
    lineSeries->clear();
    lineSeries->append(xValue.toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addDays(-1).toMSecsSinceEpoch(), 10);
    lineSeries->append(xValue.addDays(-2).toMSecsSinceEpoch(), 5);
    lineSeries->append(xValue.addDays(-3).toMSecsSinceEpoch(), 1);
    lineSeries->append(xValue.addDays(-4).toMSecsSinceEpoch(), 5);
    lineSeries->append(xValue.addDays(-5).toMSecsSinceEpoch(), 9);
    lineSeries->append(xValue.addDays(-6).toMSecsSinceEpoch(), 100);
}

void StatisticChartModel::setLearnedMonthSeries(QLineSeries *lineSeries)
{
    QDateTime xValue;
    xValue.setDate(QDate::currentDate());
    xValue.setTime(QTime(0,0));
    lineSeries->clear();
    lineSeries->append(xValue.toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addDays(-1).toMSecsSinceEpoch(), 10);
    lineSeries->append(xValue.addDays(-2).toMSecsSinceEpoch(), 40);
    lineSeries->append(xValue.addDays(-3).toMSecsSinceEpoch(), 20);
    lineSeries->append(xValue.addDays(-14).toMSecsSinceEpoch(), 30);
    lineSeries->append(xValue.addDays(-15).toMSecsSinceEpoch(), 50);
    lineSeries->append(xValue.addDays(-28).toMSecsSinceEpoch(), 100);
}

void StatisticChartModel::setLearnedYearSeries(QLineSeries *lineSeries)
{
    QDateTime xValue;
    xValue.setDate(QDate::currentDate());
    xValue.setTime(QTime(0,0));
    lineSeries->clear();
    lineSeries->append(xValue.toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addMonths(-1).toMSecsSinceEpoch(), 10);
    lineSeries->append(xValue.addMonths(-2).toMSecsSinceEpoch(), 5);
    lineSeries->append(xValue.addMonths(-3).toMSecsSinceEpoch(), 1);
    lineSeries->append(xValue.addMonths(-4).toMSecsSinceEpoch(), 5);
    lineSeries->append(xValue.addMonths(-5).toMSecsSinceEpoch(), 9);
    lineSeries->append(xValue.addMonths(-6).toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addMonths(-7).toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addMonths(-8).toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addMonths(-9).toMSecsSinceEpoch(), 100);
    lineSeries->append(xValue.addMonths(-10).toMSecsSinceEpoch(), 10);
    lineSeries->append(xValue.addMonths(-11).toMSecsSinceEpoch(), 40);
}
