#ifndef STATISTICCHARTMODEL_H
#define STATISTICCHARTMODEL_H

#include <QObject>
#include <QtCharts/QLineSeries>
#include "sqlstatisticmodel.h"
#include "datehelper.h"

QT_CHARTS_USE_NAMESPACE

class StatisticChartModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int vocabulary READ vocabulary WRITE setVocabulary NOTIFY vocabularyChanged)
public:
    explicit StatisticChartModel(QObject *parent = 0);

    Q_INVOKABLE void setAllWeekSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setAllMonthSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setAllYearSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setLearnedWeekSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setLearnedMonthSeries(QLineSeries* lineSeries);
    Q_INVOKABLE void setLearnedYearSeries(QLineSeries* lineSeries);

    int vocabulary() const;
signals:
    void vocabularyChanged();

public slots:
    void setVocabulary(int vocabulary);

private:
    void generateStatisticChart(const QList<QPair<QDate, int>>& statisticList,
                                const QDate& startDate,
                                QLineSeries *lineSeries);

    int m_vocabulary;
    DateHelper m_dateHelper;
    SqlStatisticModel m_statisticModel;
    QList<QPair<QDate, int>> m_statisticList;
    //TODO add total statistics make cleaning of common statistics elements
};

#endif // STATISTICCHARTMODEL_H
