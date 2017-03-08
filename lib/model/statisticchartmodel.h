#ifndef STATISTICCHARTMODEL_H
#define STATISTICCHARTMODEL_H

#include <QObject>
#include <QtCharts/QLineSeries>
#include "../sqlmodel/sqlstatisticmodel.h"
#include "../sqlmodel/sqltotalwordsstatisticmodel.h"
#include "../helpers/datehelper.h"

QT_CHARTS_USE_NAMESPACE


class StatisticChartModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int vocabulary READ vocabulary WRITE setVocabulary NOTIFY vocabularyChanged)
    Q_PROPERTY(int total READ total WRITE setTotal NOTIFY totalChanged)
    Q_PROPERTY(int average READ average WRITE setAverage NOTIFY averageChanged)
    Q_PROPERTY(int learned READ learned WRITE setLearned NOTIFY learnedChanged)
    Q_PROPERTY(int maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
    Q_ENUMS(ChartType)
public:
    explicit StatisticChartModel(QObject *parent = 0);

    enum class ChartType
    {
        WEEKLY,
        MONTHLY,
        ANNUAL
    };

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
    int maxValue() const;
signals:
    void vocabularyChanged();
    void totalChanged();
    void averageChanged();
    void learnedChanged();
    void maxValueChanged();

public slots:
    void setVocabulary(int vocabulary);
    void setTotal(int total);
    void setAverage(int average);
    void setLearned(int learned);
    void setMaxValue(int max);

private:
    void generateStatisticChart(const QList<QPair<QDate, int>>& statisticList,
                                const QDate& startDate,
                                QLineSeries *lineSeries);

    void generateTotalStatisticChart(const QList<QPair<QDate, int>>& statisticList,
                                const QDate& startDate,
                                QLineSeries *lineSeries);

    void findMaxElement();
    void calculateAverage();

    int m_vocabulary;
    int m_total;
    int m_average;
    int m_learned;
    int m_maxValue;
    const int MAX_VALUE_ADDER;
    DateHelper m_dateHelper;
    SqlStatisticModel m_statisticModel;
    SqlTotalWordsStatisticModel m_totalStatisticModel;
    QList<QPair<QDate, int>> m_statisticList;
    QList<QPair<QDate, int>> m_totalStatisticList;
};

#endif // STATISTICCHARTMODEL_H
