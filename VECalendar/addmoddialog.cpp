#include "addmoddialog.h"
#include "ui_addmoddialog.h"
#include "calendar.h"
#include "calendarevent.h"

#include <QDate>
#include <QModelIndex>
#include <QDebug>
#include <QDialogButtonBox>
#include <QPushButton>

AddModDialog::AddModDialog(Calendar *calendarModel, QWidget *parent) :
    QDialog(parent),
    calendar(calendarModel),
    ui(new Ui::AddModDialog)
{
    ui->setupUi(this);

    connect(this, SIGNAL(titleSelected(QString)), ui->eventTitle, SLOT(setText(QString)));
    connect(this, SIGNAL(dateSelected(QDate)), ui->eventDate, SLOT(setDate(QDate)));
    connect(this, SIGNAL(startTimeSelected(QTime)), ui->eventStartTime, SLOT(setTime(QTime)));
    connect(this, SIGNAL(endTimeSelected(QTime)), ui->eventEndTime, SLOT(setTime(QTime)));
    connect(this, SIGNAL(descriptionSelected(QString)), ui->eventDescription, SLOT(setText(QString)));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(addEvent()));
}

AddModDialog::~AddModDialog()
{
    delete ui;
}

void AddModDialog::setDate(QDate date) {
    ui->eventDate->setDate(date);
}


void AddModDialog::addEvent() {
    addEvent(ui->eventTitle->text(),
             ui->eventDate->date(),
             ui->eventStartTime->time(),
             ui->eventEndTime->time(),
             ui->eventDescription->toHtml());
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
