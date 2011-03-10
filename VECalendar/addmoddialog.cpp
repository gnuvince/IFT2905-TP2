#include "addmoddialog.h"
#include "ui_addmoddialog.h"

#include <QDate>

AddModDialog::AddModDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddModDialog)
{
    ui->setupUi(this);
}

AddModDialog::~AddModDialog()
{
    delete ui;
}

void AddModDialog::addEventRequest(QDate &date)
{

}
