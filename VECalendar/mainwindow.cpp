#include <QDebug>
#include <QIODevice>
#include <QFile>
#include <QLocale>

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
    ui(new Ui::MainWindow),
    francais(QLocale::French, QLocale::Canada)
{
    ui->setupUi(this);

    AMDialog = new AddModDialog(this);
    calendar = new Calendar(this);
    dayProxy = new DayEventFilterProxy(this);
    dayProxy->setDynamicSortFilter(true);
    dayProxy->setSourceModel(calendar);

    listProxy = new EventListProxy(this);
    listProxy->setDynamicSortFilter(true);
    listProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    listProxy->setSourceModel(calendar);

    connect(ui->addEventButton, SIGNAL(clicked()), this, SLOT(addEventRequest()));
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(dateActivated()));
    connect(ui->viewButton, SIGNAL(clicked()), this, SLOT(ToggleView()));
    connect(this, SIGNAL(selectView(int)), ui->leftPane, SLOT(setCurrentIndex(int)));
    connect(this, SIGNAL(selectView(int)), this, SLOT(setViewButtonText(int)));
    connect(this, SIGNAL(dateSelected(QString)), ui->selectedDate, SLOT(setText(QString)));
    connect(this, SIGNAL(createEntry(QDate&)), AMDialog, SLOT(addEventRequest(QDate&)));
    connect(ui->calendarWidget, SIGNAL(clicked(QDate)), dayProxy, SLOT(setFilterDate(QDate)));
    connect(ui->filterString, SIGNAL(textChanged(QString)), listProxy, SLOT(setFilterFixedString(QString)));
    connect(ui->dayEventsShort, SIGNAL(clicked(QModelIndex)), this, SLOT(viewEvent(QModelIndex)));
    connect(ui->dayEventsLong, SIGNAL(clicked(QModelIndex)), this, SLOT(viewEvent(QModelIndex)));
    connect(ui->dayEventsLong, SIGNAL(clicked(QModelIndex)), this, SLOT(setDateLabel(QModelIndex)));
    connect(calendar, SIGNAL(event_added(const QDate&)), this, SLOT(highlight_date(const QDate&)));
    connect(calendar, SIGNAL(event_added(const QDate&)), dayProxy, SLOT(invalidate()));
    connect(calendar, SIGNAL(event_added(const QDate&)), listProxy, SLOT(invalidate()));


    dateActivated();
    emit selectView(0);

    activeView = CALENDAR_VIEW;

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

void MainWindow::highlight_date(const QDate& date) {
    QTextCharFormat fmt;
    fmt.setFontWeight(QFont::Bold);
    fmt.setForeground(Qt::white);
    fmt.setBackground(QColor(0xEB, 0x6E, 0x10));
    ui->calendarWidget->setDateTextFormat(date, fmt);
}

void MainWindow::ToggleView()
{
    activeView = 1 - activeView;
    emit selectView(activeView);
}

void MainWindow::addEventRequest()
{
    /*
    QDate date = ui->calendarWidget->selectedDate();
    AMDialog->entryDate = &date;

    QString str = date.toString("dd MMMM yyyy");
    emit createEntry(date);
    AMDialog->setVisible(true);
    */
    calendar->add_event(new CalendarEvent(tr("Foo4"),
                                          QDate(2011, 3, 16),
                                          QTime(12, 0),
                                          QTime(13, 0),
                                          tr("<h1>Bar4</h1><u>Hihih</u>")));
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
    QString frDate = francais.toString(date, "dd MMMM yyyy");
    emit dateSelected(frDate);
}

void MainWindow::setViewButtonText(int view) {
    switch (view) {
    case 0: ui->viewButton->setText(tr("Liste >>")); break;
    case 1: ui->viewButton->setText(tr("<< Calendrier")); break;
    default: ;
    }
}

void MainWindow::viewEvent(QModelIndex index) {
    //ui->eventDetails->setHtml(calendar->get_description(index));
    QString description;
    if (activeView == CALENDAR_VIEW) {
        description = dayProxy->get_description(index);
    }
    else {
        description = listProxy->get_description(index);
    }
    ui->eventDetails->setHtml(description);
}

void MainWindow::setDateLabel(QModelIndex index) {
    QModelIndex index2 = listProxy->index(index.row(), 1);
    QDate date = listProxy->data(index2).toDate();
    QString frDate = francais.toString(date, "dd MMMM yyyy");

    ui->list_date_label->setText(frDate);
}
