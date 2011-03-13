#include "calendar.h"
#include "calendarevent.h"
#include <QList>
#include <QDebug>

Calendar::Calendar(QObject *parent) :
    QObject(parent)
{
    events = new QList<CalendarEvent*>();
}

void Calendar::add_event(CalendarEvent *ce) {
    events->append(ce);
}

CalendarEvent* Calendar::get_event(int i) {
    return events->at(i);
}

void Calendar::remove_event(int i) {
    events->removeAt(i);
}


QDataStream& operator>>(QDataStream &s, Calendar &c) {
    quint32 count;
    s >> count;
    for (quint32 i = 0; i < count; ++i) {
        CalendarEvent *ce = new CalendarEvent;
        s >> *ce;
        c.events->append(ce);
    }
    return s;
}

QDataStream& operator<<(QDataStream &s, Calendar &c) {
    quint32 count = c.events->count();
    s << count;
    foreach (CalendarEvent *ce, *(c.events)) {
        s << *ce;
    }
    return s;
}
