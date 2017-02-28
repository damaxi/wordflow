#include "datehelper.h"

DateHelper::DateHelper(QObject *parent) : QObject(parent), m_today(QDate::currentDate())
{}

QDate DateHelper::getWeekAgoDate() const
{
    return QDate(m_today).addDays(-6);
}

QDate DateHelper::getMonthAgoDate() const
{
    return QDate(m_today).addMonths(-1).addDays(1);
}

QDate DateHelper::getYearAgoDate() const
{
    return QDate(m_today).addYears(-1).addMonths(1);
}

QDate DateHelper::getCurrentDate() const
{
    return m_today;
}

int DateHelper::getDaysInCurrentMonth() const
{
    return m_today.day() + getMonthAgoDate().daysInMonth() - getMonthAgoDate().day();
}
