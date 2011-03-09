#ifndef CALENDAREVENT_H
#define CALENDAREVENT_H

#include <QObject>
#include <QDate>
#include <QTime>
#include <QDataStream>


class CalendarEvent : public QObject
{
    Q_OBJECT
public:
    explicit CalendarEvent(QObject *parent = 0);
    CalendarEvent(const QString &title,
                  const QDate &date,
                  const QTime &start_time,
                  const QTime &end_time,
                  const QString &description
                  );

    QString title; // Title of the event
    QDate date; // Date of the event
    QTime start_time; // Time the event starts
    QTime end_time; // Time the event ends
    QString description; // Description of the event




signals:

public slots:

private:
    // Serialization
    friend QDataStream& operator>>(QDataStream &s, CalendarEvent &ce);
    friend QDataStream& operator<<(QDataStream &s, CalendarEvent &ce);

};

#endif // CALENDAREVENT_H
