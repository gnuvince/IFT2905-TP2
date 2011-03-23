#ifndef ADDMODDIALOG_H
#define ADDMODDIALOG_H

#include <QDialog>
#include <QDate>
#include "calendarevent.h"
#include "calendar.h"

namespace Ui {
    class AddModDialog;
}

class AddModDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddModDialog(Calendar *calendarModel, QWidget *parent = 0);
    ~AddModDialog();
    void setCalendarEvent(CalendarEvent *ce);
    void setModify(bool b);

public slots:
    void setDate(QDate date);
    void setInformation(CalendarEvent *ce);
    void saveEvent();
    void addEvent(QString title, QDate date, QTime start, QTime end, QString description);
    void modifyEvent(QString title, QDate date, QTime start, QTime end, QString description);


signals:
    void eventCreated(CalendarEvent *ce);
    void titleSelected(QString title);
    void dateSelected(QDate date);
    void startTimeSelected(QTime startTime);
    void endTimeSelected(QTime endTime);
    void descriptionSelected(QString description);

private:
    Ui::AddModDialog *ui;
    Calendar *calendar;
    CalendarEvent *calendarEvent;
    bool modify;
};

#endif // ADDMODDIALOG_H
