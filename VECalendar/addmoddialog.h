#ifndef ADDMODDIALOG_H
#define ADDMODDIALOG_H

#include <QDialog>
#include <QDate>
#include "calendarevent.h"

namespace Ui {
    class AddModDialog;
}

class AddModDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddModDialog(QWidget *parent = 0);
    ~AddModDialog();

public slots:
    void addEventRequest(CalendarEvent *ce);

signals:
    void eventCreated(CalendarEvent *ce);
    void titleSelected(QString title);
    void dateSelected(QString date);
    void startTimeSelected(QTime startTime);
    void endTimeSelected(QTime endTime);
    void descriptionSelected(QString description);

private:
    Ui::AddModDialog *ui;
    CalendarEvent calEvent;
};

#endif // ADDMODDIALOG_H
