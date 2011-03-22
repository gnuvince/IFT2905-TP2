#include <QDebug>
#include <QIODevice>
#include <QFile>
#include <QLocale>
#include <QMessageBox>

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

    calendar = new Calendar(this);
    AMDialog = new AddModDialog(calendar, this);
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
    connect(this, SIGNAL(createEvent()), AMDialog, SLOT(exec()));
    connect(ui->calendarWidget, SIGNAL(clicked(QDate)), dayProxy, SLOT(setFilterDate(QDate)));
    connect(ui->filterString, SIGNAL(textChanged(QString)), listProxy, SLOT(setFilterFixedString(QString)));
    connect(ui->dayEventsShort, SIGNAL(clicked(QModelIndex)), this, SLOT(viewEvent(QModelIndex)));
    connect(ui->dayEventsLong, SIGNAL(clicked(QModelIndex)), this, SLOT(viewEvent(QModelIndex)));
    connect(ui->dayEventsLong, SIGNAL(clicked(QModelIndex)), this, SLOT(setDateLabel(QModelIndex)));
    connect(calendar, SIGNAL(event_added(const QDate&)), this, SLOT(highlight_date(const QDate&)));
    connect(calendar, SIGNAL(event_added(const QDate&)), dayProxy, SLOT(invalidate()));
    connect(calendar, SIGNAL(event_added(const QDate&)), listProxy, SLOT(invalidate()));
    connect(ui->dayEventsShort, SIGNAL(clicked(QModelIndex)), this, SLOT(enableButtons()));
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(disableButtons()));
    connect(ui->delEventButton, SIGNAL(clicked()), this, SLOT(deleteEventRequest()));
    connect(ui->delEventButtonList, SIGNAL(clicked()), this, SLOT(deleteEventRequest()));
    connect(ui->calendarWidget, SIGNAL(clicked(QDate)), AMDialog, SLOT(setDate(QDate)));dateA


    dateActivated();
    setEnabledButtons(false);
    emit selectView(0);


    activeView = CALENDAR_VIEW;

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
    emit createEvent();
}


void MainWindow::deleteEventRequest() {
    if (QMessageBox::warning(this, trUtf8("Confirmation"),
                             trUtf8("Voulez-vous vraiment supprimer cet événement?"),
                             QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        return;
    }

    QTableView *view;
    QSortFilterProxyModel *proxy;

    if (activeView == CALENDAR_VIEW) {
        view = ui->dayEventsShort;
        proxy = dayProxy;
    }
    else {
        view = ui->dayEventsLong;
        proxy = listProxy;
    }

    QModelIndex index = view->currentIndex();
    QModelIndex index2 = proxy->mapToSource(index);
    int row = index2.row();
    calendar->removeRow(row, index2);
    ui->eventDetails->clear();
    emit dataModelChanged();
}

void MainWindow::modifyEventRequest() {

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

void MainWindow::setEnabledButtons(bool b) {
    ui->delEventButton->setEnabled(b);
    ui->modEventButton->setEnabled(b);
}

void MainWindow::enableButtons() {
    setEnabledButtons(true);
}


void MainWindow::disableButtons() {
    setEnabledButtons(false);
}
