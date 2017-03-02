#include "statisticchartmodel.h"

#include <QDateTime>
#include <QtAlgorithms>
#include <QDebug>

StatisticChartModel::StatisticChartModel(QObject *parent) :
    QObject(parent),
    m_vocabulary(-1),
    m_dateHelper(),
    m_statisticModel(),
    m_statisticList()
{}

void StatisticChartModel::setAllWeekSeries(QLineSeries* lineSeries)
{
//    QDateTime xValue;
//    xValue.setDate(QDate::currentDate());
//    xValue.setTime(QTime(0,0));
//    lineSeries->append(xValue.toMSecsSinceEpoch(), 100);
//    lineSeries->append(xValue.addDays(-1).toMSecsSinceEpoch(), 100);
//    lineSeries->append(xValue.addDays(-2).toMSecsSinceEpoch(), 50);
//    lineSeries->append(xValue.addDays(-3).toMSecsSinceEpoch(), 10);
//    lineSeries->append(xValue.addDays(-4).toMSecsSinceEpoch(), 50);
//    lineSeries->append(xValue.addDays(-5).toMSecsSinceEpoch(), 90);
//    lineSeries->append(xValue.addDays(-6).toMSecsSinceEpoch(), 110);
}

void StatisticChartModel::setAllMonthSeries(QLineSeries *lineSeries)
{
//    QDateTime xValue;
//    xValue.setDate(QDate::currentDate());
//    xValue.setTime(QTime(0,0));
//    lineSeries->clear();
//    lineSeries->append(xValue.toMSecsSinceEpoch(), 100);
//    lineSeries->append(xValue.addDays(-1).toMSecsSinceEpoch(), 100);
//    lineSeries->append(xValue.addDays(-2).toMSecsSinceEpoch(), 50);
//    lineSeries->append(xValue.addDays(-3).toMSecsSinceEpoch(), 10);
//    lineSeries->append(xValue.addDays(-14).toMSecsSinceEpoch(), 50);
//    lineSeries->append(xValue.addDays(-15).toMSecsSinceEpoch(), 90);
//    lineSeries->append(xValue.addDays(-28).toMSecsSinceEpoch(), 110);
}

void StatisticChartModel::setAllYearSeries(QLineSeries *lineSeries)
{
//    QDateTime xValue;
//    xValue.setDate(QDate::currentDate());
//    xValue.setTime(QTime(0,0));
//    lineSeries->clear();
//    lineSeries->append(xValue.toMSecsSinceEpoch(), 100);
//    lineSeries->append(xValue.addMonths(-1).toMSecsSinceEpoch(), 100);
//    lineSeries->append(xValue.addMonths(-2).toMSecsSinceEpoch(), 50);
//    lineSeries->append(xValue.addMonths(-3).toMSecsSinceEpoch(), 10);
//    lineSeries->append(xValue.addMonths(-4).toMSecsSinceEpoch(), 50);
//    lineSeries->append(xValue.addMonths(-5).toMSecsSinceEpoch(), 90);
//    lineSeries->append(xValue.addMonths(-6).toMSecsSinceEpoch(), 110);
//    lineSeries->append(xValue.addMonths(-7).toMSecsSinceEpoch(), 110);
//    lineSeries->append(xValue.addMonths(-8).toMSecsSinceEpoch(), 110);
//    lineSeries->append(xValue.addMonths(-9).toMSecsSinceEpoch(), 110);
//    lineSeries->append(xValue.addMonths(-10).toMSecsSinceEpoch(), 110);
//    lineSeries->append(xValue.addMonths(-11).toMSecsSinceEpoch(), 10);
}

void StatisticChartModel::setLearnedWeekSeries(QLineSeries *lineSeries)
{
    lineSeries->clear();
    QDate startDate = m_dateHelper.getWeekAgoDate();
    generateStatisticChart(m_statisticList, startDate, lineSeries);
}

void StatisticChartModel::setLearnedMonthSeries(QLineSeries *lineSeries)
{
    lineSeries->clear();
    QDate startDate = m_dateHelper.getMonthAgoDate();
    generateStatisticChart(m_statisticList, startDate, lineSeries);
}

void StatisticChartModel::setLearnedYearSeries(QLineSeries *lineSeries)
{
    lineSeries->clear();
    QDate startDate = m_dateHelper.getYearAgoDate();
    generateStatisticChart(m_statisticList, startDate, lineSeries);
}

int StatisticChartModel::vocabulary() const
{
    return m_vocabulary;
}

void StatisticChartModel::setVocabulary(int vocabulary)
{
    if (vocabulary == m_vocabulary)
        return;

    m_vocabulary = vocabulary;
    m_statisticList = m_statisticModel.listAllStatistics(m_vocabulary);
    qSort(m_statisticList.begin(), m_statisticList.end(),
        [](const QPair<QDate, int>& pair1, const QPair<QDate, int>& pair2) -> bool {
            return pair1 < pair2;
        });
    emit vocabularyChanged();
}

void StatisticChartModel::generateStatisticChart(const QList<QPair<QDate, int> > &statisticList, const QDate &startDate, QLineSeries *lineSeries)
{
    QDate tempDate = startDate;
    int yValue = 0;
    for (auto iter = statisticList.begin(); iter != statisticList.end(); ++iter) {
         if (iter->first < startDate) {
                yValue += iter->second;
         } else {
             for (QDate date = tempDate; date <= m_dateHelper.getCurrentDate(); date = date.addDays(1))
             {
                if (date == iter->first && iter + 1 != statisticList.end()) {
                    yValue += iter->second;
                    tempDate = date;
                    lineSeries->append(QDateTime(date).toMSecsSinceEpoch(), yValue);
                    break;
                } else if (date == iter->first) {
                    yValue += iter->second;
                }
                lineSeries->append(QDateTime(date).toMSecsSinceEpoch(), yValue);
             }
         }
    }
}
