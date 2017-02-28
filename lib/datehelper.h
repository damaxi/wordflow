#ifndef DATEHELPER_H
#define DATEHELPER_H

#include <QObject>
#include <QDate>

class DateHelper : public QObject
{
    Q_OBJECT
public:
    explicit DateHelper(QObject *parent = 0);

    Q_INVOKABLE QDate getWeekAgoDate() const;
    Q_INVOKABLE QDate getMonthAgoDate() const;
    Q_INVOKABLE QDate getYearAgoDate() const;
    Q_INVOKABLE QDate getCurrentDate() const;
    Q_INVOKABLE int getDaysInCurrentMonth() const;
signals:

public slots:

private:
    QDate m_today;
};

#endif // DATEHELPER_H
