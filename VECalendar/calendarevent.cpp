#include "calendarevent.h"
#include <QDate>
#include <QTime>
#include <QDataStream>

CalendarEvent::CalendarEvent(QObject *parent) :
    QObject(parent)
{
}


CalendarEvent::CalendarEvent(const QString &title,
                             const QDate &date,
                             const QTime &start_time,
                             const QTime &end_time,
                             const QString &description) {
    this->title = title;
    this->date = date;
    this->start_time = start_time;
    this->end_time = end_time;
    this->description = description;
}



QDataStream& operator>>(QDataStream &s, CalendarEvent &ce) {
    s >> ce.title;
    s >> ce.date;
    s >> ce.start_time;
    s >> ce.end_time;
    s >> ce.description;
    return s;
}

QDataStream& operator<<(QDataStream &s, CalendarEvent &ce) {
    s << ce.title;
    s << ce.date;
    s << ce.start_time;
    s << ce.end_time;
    s << ce.description;
    return s;
}
