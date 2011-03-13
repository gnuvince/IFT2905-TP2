#include "calendar.h"
#include "calendarevent.h"
#include <QList>
#include <QDebug>
#include <QStringList>




Calendar::Calendar(QObject *parent) :
    QAbstractTableModel(parent)
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

int Calendar::count() {
    return events->count();
}

QString Calendar::get_description(const QModelIndex &index) const {
    int i = index.row();
    return events->at(i)->description;
}


QVariant Calendar::data(const QModelIndex &index, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (index.isValid()) {
        CalendarEvent *event = events->at(index.row());
        switch (index.column()) {
        case TITLE_INDEX: return event->title;
        case DATE_INDEX: return event->date;
        case START_TIME_INDEX: return event->start_time.toString("HH:mm");
        case END_TIME_INDEX: return event->end_time.toString("HH:mm");
        case DESCRIPTION_INDEX: return event->description;
        default: ;
        }
    }
    return QVariant();
}

int Calendar::rowCount(const QModelIndex &parent) const {
    return events->count();
}

int Calendar::columnCount(const QModelIndex &parent) const {
    return NUMBER_OF_FIELDS;
}

QVariant Calendar::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case TITLE_INDEX: return trUtf8("Titre");
        case DATE_INDEX: return trUtf8("Date");
        case START_TIME_INDEX: return trUtf8("Début");
        case END_TIME_INDEX: return trUtf8("Fin");
        case DESCRIPTION_INDEX: return trUtf8("Description");
        default: ;
        }
    }
    return QVariant();
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
