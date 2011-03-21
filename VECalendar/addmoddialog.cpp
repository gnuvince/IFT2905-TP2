#include "addmoddialog.h"
#include "ui_addmoddialog.h"

#include <QDate>

AddModDialog::AddModDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddModDialog)
{
    ui->setupUi(this);

    connect(this, SIGNAL(titleSelected(QString)), ui->eventTitle, SLOT(setText(QString)));
    connect(this, SIGNAL(dateSelected(QString)), ui->eventDate, SLOT(setText(QString)));
    connect(this, SIGNAL(startTimeSelected(QTime)), ui->eventStartTime, SLOT(setTime(QTime)));
    connect(this, SIGNAL(endTimeSelected(QTime)), ui->eventEndTime, SLOT(setTime(QTime)));
    connect(this, SIGNAL(descriptionSelected(QString)), ui->eventDescription, SLOT(setText(QString)));
    //connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()),
}

AddModDialog::~AddModDialog()
{
    delete ui;
}

void AddModDialog::addEventRequest(CalendarEvent *ce)
{
    //calEvent = ce;

    emit titleSelected(ce->title);
    emit dateSelected(ce->date.toString("dd MMMM yyyy"));
    emit startTimeSelected(ce->start_time);
    emit endTimeSelected(ce->end_time);
    emit descriptionSelected(ce->description);

    this->setVisible(true);
}
