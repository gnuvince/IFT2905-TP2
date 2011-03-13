#ifndef CALENDAR_H
#define CALENDAR_H

#include <QObject>
#include <QList>
#include "calendarevent.h"

class Calendar : public QObject
{
    Q_OBJECT
public:
    explicit Calendar(QObject *parent = 0);
    void add_event(CalendarEvent *ce);
    void remove_event(int i);
    CalendarEvent* get_event(int i);

signals:

public slots:

private:
    QList<CalendarEvent*> *events;

    // Serialization
    friend QDataStream& operator>>(QDataStream &s, Calendar &c);
    friend QDataStream& operator<<(QDataStream &s, Calendar &c);
};

#endif // CALENDAR_H
