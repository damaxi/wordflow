#include "statisticchartmodel.h"

#include <QDateTime>
#include <QtAlgorithms>
#include <functional>
#include <QDebug>

StatisticChartModel::StatisticChartModel(QObject *parent) :
    QObject(parent),
    m_vocabulary(-1),
    m_total(0),
    m_average(0),
    m_learned(0),
    m_dateHelper(),
    m_statisticModel(),
    m_totalStatisticModel(),
    m_statisticList(),
    m_totalStatisticList()
{}

void StatisticChartModel::setAllWeekSeries(QLineSeries* lineSeries)
{
    lineSeries->clear();
    QDate startDate = m_dateHelper.getWeekAgoDate();
    generateTotalStatisticChart(m_totalStatisticList, startDate, lineSeries);
}

void StatisticChartModel::setAllMonthSeries(QLineSeries *lineSeries)
{
    lineSeries->clear();
    QDate startDate = m_dateHelper.getMonthAgoDate();
    generateTotalStatisticChart(m_totalStatisticList, startDate, lineSeries);
}

void StatisticChartModel::setAllYearSeries(QLineSeries *lineSeries)
{
    lineSeries->clear();
    QDate startDate = m_dateHelper.getYearAgoDate();
    generateTotalStatisticChart(m_totalStatisticList, startDate, lineSeries);
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

int StatisticChartModel::total() const
{
    return m_total;
}

int StatisticChartModel::average() const
{
    return m_average;
}

int StatisticChartModel::learned() const
{
    return m_learned;
}

void StatisticChartModel::setVocabulary(int vocabulary)
{
    if (vocabulary == m_vocabulary)
        return;

    m_vocabulary = vocabulary;
    m_statisticList = m_statisticModel.listAllStatistics(m_vocabulary);
    m_totalStatisticList = m_totalStatisticModel.listAllTotalStatistics(m_vocabulary);
    std::function<bool(const QPair<QDate, int>&, const QPair<QDate, int>&)> f_compare_dates =
        [](const QPair<QDate, int>& pair1, const QPair<QDate, int>& pair2) -> bool {
            return pair1 < pair2;
        };
    qSort(m_statisticList.begin(), m_statisticList.end(), f_compare_dates);
    qSort(m_totalStatisticList.begin(), m_totalStatisticList.end(), f_compare_dates);
    emit vocabularyChanged();
}

void StatisticChartModel::setTotal(int total)
{
    if (total == m_total)
        return;

    m_total = total;
    emit totalChanged();
}

void StatisticChartModel::setAverage(int average)
{
    if (average == m_average)
        return;

    m_average = average;
    emit averageChanged();
}

void StatisticChartModel::setLearned(int learned)
{
    if (learned == m_learned)
        return;

    m_learned = learned;
    emit learnedChanged();
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

void StatisticChartModel::generateTotalStatisticChart(const QList<QPair<QDate, int> > &statisticList, const QDate &startDate, QLineSeries *lineSeries)
{
    QDate tempDate = startDate;
    int yValue = 0;
    for (auto iter = statisticList.begin(); iter != statisticList.end(); ++iter) {
         if (iter->first < startDate) {
                yValue = iter->second;
         } else {
             for (QDate date = tempDate; date <= m_dateHelper.getCurrentDate(); date = date.addDays(1))
             {
                if (date == iter->first && iter + 1 != statisticList.end()) {
                    yValue = iter->second;
                    tempDate = date;
                    lineSeries->append(QDateTime(date).toMSecsSinceEpoch(), yValue);
                    break;
                } else if (date == iter->first) {
                    yValue = iter->second;
                }
                lineSeries->append(QDateTime(date).toMSecsSinceEpoch(), yValue);
             }
         }
    }
}
