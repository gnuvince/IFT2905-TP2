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

CalendarEvent* Calendar::get_event(const QModelIndex &index) const {
    return events->at(index.row());
}

void Calendar::remove_event(int i) {
    events->removeAt(i);
}

int Calendar::count() {
    return events->count();
}


QList<CalendarEvent *>& Calendar::getEvents() {
    return *events;
}

int Calendar::countForDate(const QDate &date) {
    int n = 0;
    for (int i = 0; i < events->count(); ++i) {
        if (events->at(i)->date == date) {
            n++;
        }
    }
    return n;
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
    Q_UNUSED(parent);
    return events->count();
}

int Calendar::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
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


bool Calendar::removeRows(int row, int count, const QModelIndex &parent) {
    Q_UNUSED(parent);

    beginRemoveRows(QModelIndex(), row, row+count-1);
    for (int i = row; i < row+count; ++i) {
        CalendarEvent *ce = events->at(i);
        remove_event(i);
        emit date_modified(ce->date);
    }
    endRemoveRows();
    return true;
}

bool Calendar::insertRows(int row, int count, const QModelIndex &parent) {

    Q_UNUSED(parent);

    beginInsertRows(QModelIndex(), row, row+count-1);
    for (int i = row; i < row+count; ++i) {
        CalendarEvent *ce = new CalendarEvent(QString(), QDate(), QTime(), QTime(), QString());
        add_event(ce);
    }
    endInsertRows();
    return true;
}

bool Calendar::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
         CalendarEvent *ce = get_event(index);

         switch (index.column()) {
         case TITLE_INDEX:
             ce->title = value.toString();
             break;
         case DATE_INDEX:
             ce->date = value.toDate();
             emit date_modified(ce->date);
             break;
         case START_TIME_INDEX:
             ce->start_time = value.toTime();
             break;
         case END_TIME_INDEX:
             ce->end_time = value.toTime();
             break;
         case DESCRIPTION_INDEX:
             ce->description = value.toString();
             break;
         default: ;
         }

         emit(dataChanged(index, index));

         return true;
     }
     return false;
}


QDataStream& operator>>(QDataStream &s, Calendar &c) {
    c.beginResetModel();
    c.events->clear();
    quint32 count;
    s >> count;
    for (quint32 i = 0; i < count; ++i) {
        CalendarEvent *ce = new CalendarEvent;
        s >> *ce;
        c.events->append(ce);
    }
    c.endResetModel();
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
