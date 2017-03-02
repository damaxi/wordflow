#ifndef STATISTICCHARTMODEL_H
#define STATISTICCHARTMODEL_H

#include <QObject>
#include <QtCharts/QLineSeries>
#include "sqlstatisticmodel.h"

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
    int m_vocabulary;
    SqlStatisticModel m_statisticModel;
    QList<QPair<QDate, int>> m_statisticList;
};

#endif // STATISTICCHARTMODEL_H
