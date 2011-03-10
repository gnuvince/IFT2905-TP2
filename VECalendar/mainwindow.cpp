#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AMDialog = new AddModDialog(this);


    connect(ui->addEventButton, SIGNAL(clicked()), this, SLOT(addEventRequest()));

    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(dateActivated()));

    // Éventuellement, connecter calendarWidget avec calendrier et faire proxy pour filtrer.


    connect(this, SIGNAL(dateSelected(QString)), ui->selectedDate, SLOT(setText(QString)));
    connect(this, SIGNAL(createEntry(QDate&)), AMDialog, SLOT(addEventRequest(QDate&)));

    dateActivated(); // XXX

}

MainWindow::~MainWindow()
{
    delete ui;
    delete AMDialog;
}

void MainWindow::HiliteDate()
{

}

void MainWindow::addEventRequest()
{
    QDate date = ui->calendarWidget->selectedDate();
    AMDialog->entryDate = &date;

    QString str = date.toString("dd MMMM yyyy");
    emit createEntry(date);
    AMDialog->setVisible(true);
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
