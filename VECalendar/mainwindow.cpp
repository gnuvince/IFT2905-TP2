#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addmoddialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AddModDialog *AMDialog = new AddModDialog(this);
    //AMDialog->setVisible(true);

    connect(ui->addEventButton, SIGNAL(clicked()), this, SLOT(addEventRequest(QDate)));
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(dateActivated()));

    // Éventuellement, connecter calendarWidget avec calendrier et faire proxy pour filtrer.

    connect(this, SIGNAL(dateSelected(QString)), ui->selectedDate, SLOT(setText(QString)));

    dateActivated(); // XXX

    delete AMDialog;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HiliteDate()
{

}

void MainWindow::addEventRequest(QDate *date)
{

}

void MainWindow::deleteEventRequest()
{

}

void MainWindow::modifyEventRequest()
{

}


void MainWindow::dateActivated()
{
    QDate date = ui->calendarWidget->selectedDate();
    QString str = date.toString("dd MMMM yyyy");
    emit dateSelected(str);
}
