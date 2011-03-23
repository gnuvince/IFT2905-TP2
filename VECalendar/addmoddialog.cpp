#include <QDate>
#include <QModelIndex>
#include <QDebug>
#include <QDialogButtonBox>
#include <QPushButton>

#include "addmoddialog.h"
#include "ui_addmoddialog.h"
#include "calendar.h"
#include "calendarevent.h"



AddModDialog::AddModDialog(Calendar *calendarModel, CalendarEvent *event, QWidget *parent) :
    QDialog(parent),
    calendarEvent(event),
    calendar(calendarModel),
    ui(new Ui::AddModDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(event == 0 ? trUtf8("Ajouter un événement") : trUtf8("Modifier un événement"));

    connect(this, SIGNAL(titleSelected(QString)), ui->eventTitle, SLOT(setText(QString)));
    connect(this, SIGNAL(dateSelected(QDate)), ui->eventDate, SLOT(setDate(QDate)));
    connect(this, SIGNAL(startTimeSelected(QTime)), ui->eventStartTime, SLOT(setTime(QTime)));
    connect(this, SIGNAL(endTimeSelected(QTime)), ui->eventEndTime, SLOT(setTime(QTime)));
    connect(this, SIGNAL(descriptionSelected(QString)), ui->eventDescription, SLOT(setText(QString)));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(saveEvent()));
}

AddModDialog::~AddModDialog()
{
    delete ui;
}

void AddModDialog::setDate(QDate date) {
    ui->eventDate->setDate(date);
}


void AddModDialog::saveEvent() {
    if (calendarEvent != 0) { // calendarEvent is not null
        modifyEvent(ui->eventTitle->text(),
                    ui->eventDate->date(),
                    ui->eventStartTime->time(),
                    ui->eventEndTime->time(),
                    ui->eventDescription->toPlainText());
    }
    else {
        addEvent(ui->eventTitle->text(),
                 ui->eventDate->date(),
                 ui->eventStartTime->time(),
                 ui->eventEndTime->time(),
                 ui->eventDescription->toPlainText());
    }
}

void AddModDialog::addEvent(QString title, QDate date, QTime start, QTime end, QString description) {
    int row = calendar->count();
    calendar->insertRows(row, 1, QModelIndex());

    QModelIndex index = calendar->index(row, TITLE_INDEX, QModelIndex());
    calendar->setData(index, title);
    index = calendar->index(row, DATE_INDEX, QModelIndex());
    calendar->setData(index, date);
    index = calendar->index(row, START_TIME_INDEX, QModelIndex());
    calendar->setData(index, start);
    index = calendar->index(row, END_TIME_INDEX, QModelIndex());
    calendar->setData(index, end);
    index = calendar->index(row, DESCRIPTION_INDEX, QModelIndex());
    calendar->setData(index, description);
}


void AddModDialog::modifyEvent(QString title, QDate date, QTime start, QTime end, QString description) {
    calendarEvent->title = title;
    calendarEvent->date = date;
    calendarEvent->start_time = start;
    calendarEvent->end_time = end;
    calendarEvent->description = description;
}


void AddModDialog::displayInformation(CalendarEvent *ce) {
    ui->eventTitle->setText(ce->title);
    ui->eventDate->setDate(ce->date);
    ui->eventStartTime->setTime(ce->start_time);
    ui->eventEndTime->setTime(ce->end_time);
    ui->eventDescription->setPlainText(ce->description);
}


