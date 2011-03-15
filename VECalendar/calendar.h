#ifndef CALENDAR_H
#define CALENDAR_H

#include <QObject>
#include <QList>
#include <QAbstractTableModel>
#include <QStringList>

#include "calendarevent.h"


#define NUMBER_OF_FIELDS    5

#define TITLE_INDEX         0
#define DATE_INDEX          1
#define START_TIME_INDEX    2
#define END_TIME_INDEX      3
#define DESCRIPTION_INDEX   4


class Calendar : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit Calendar(QObject *parent = 0);
    void add_event(CalendarEvent *ce);
    void remove_event(int i);
    CalendarEvent* get_event(int i);
    int count();
    QString get_description(const QModelIndex &index) const;

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

signals:
    void event_added(const QDate &date);

public slots:

private:
    QList<CalendarEvent*> *events;

    // Serialization
    friend QDataStream& operator>>(QDataStream &s, Calendar &c);
    friend QDataStream& operator<<(QDataStream &s, Calendar &c);
};

#endif // CALENDAR_H
