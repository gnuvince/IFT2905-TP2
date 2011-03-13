#include <QDebug>
#include <QIODevice>
#include <QFile>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calendarevent.h"
#include "calendar.h"
#include "dayeventfilterproxy.h"
#include "eventlistproxy.h"

#include <QDebug>

int MainWindow::CALENDAR_VIEW = 0;
int MainWindow::FILTER_VIEW = 1;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AMDialog = new AddModDialog(this);
    calendar = new Calendar(this);
    DayEventFilterProxy *dayProxy = new DayEventFilterProxy(this);
    dayProxy->setDynamicSortFilter(true);
    dayProxy->setSourceModel(calendar);

    EventListProxy *listProxy = new EventListProxy(this);
    listProxy->setDynamicSortFilter(true);
    listProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    listProxy->setSourceModel(calendar);



    connect(ui->addEventButton, SIGNAL(clicked()), this, SLOT(addEventRequest()));
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(dateActivated()));
    connect(ui->viewButton, SIGNAL(clicked()), this, SLOT(ToggleView()));
    connect(this, SIGNAL(selectView(int)), ui->leftPane, SLOT(setCurrentIndex(int)));
    connect(this, SIGNAL(selectView(int)), this, SLOT(setViewButtonText(int)));


    // Éventuellement, connecter calendarWidget avec calendrier et faire proxy pour filtrer.

    connect(this, SIGNAL(dateSelected(QString)), ui->selectedDate, SLOT(setText(QString)));
    connect(this, SIGNAL(createEntry(QDate&)), AMDialog, SLOT(addEventRequest(QDate&)));
    connect(ui->calendarWidget, SIGNAL(clicked(QDate)), dayProxy, SLOT(setFilterDate(QDate)));
    connect(ui->filterString, SIGNAL(textChanged(QString)), listProxy, SLOT(setFilterFixedString(QString)));

    dateActivated(); // XXX
    emit selectView(0);

    activeView = CALENDAR_VIEW;

    /* Pour mettre un élément en gras/sous-ligné
    QTextCharFormat fmt;
    fmt.setUnderlineStyle(QTextCharFormat::SingleUnderline);
    fmt.setFontWeight(QFont::Bold);
    ui->calendarWidget->setDateTextFormat(QDate(2011,3,10), fmt);
    */

    calendar->add_event(new CalendarEvent(tr("Foo1"),
                                          QDate(2011, 3, 10),
                                          QTime(12, 0),
                                          QTime(13, 0),
                                          tr("Bar1")));
    calendar->add_event(new CalendarEvent(tr("Foo2"),
                                          QDate(2011, 3, 11),
                                          QTime(12, 0),
                                          QTime(13, 0),
                                          tr("Bar2")));
    calendar->add_event(new CalendarEvent(tr("Foo3"),
                                          QDate(2011, 3, 10),
                                          QTime(12, 0),
                                          QTime(13, 0),
                                          tr("Bar3")));

    ui->dayEventsLong->setModel(listProxy);
    ui->dayEventsShort->setModel(dayProxy);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HiliteDate()
{
}

void MainWindow::ToggleView()
{
    activeView = 1 - activeView;
    emit selectView(activeView);
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

void MainWindow::setViewButtonText(int view) {
    switch (view) {
    case 0: ui->viewButton->setText(tr("Liste")); break;
    case 1: ui->viewButton->setText(tr("Calendrier")); break;
    default: ;
    }
}
