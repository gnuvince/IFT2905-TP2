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

public slots:
    void setDate(QDate date);
    void addEvent();
    void addEvent(QString title, QDate date, QTime start, QTime end, QString description);

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
};

#endif // ADDMODDIALOG_H
