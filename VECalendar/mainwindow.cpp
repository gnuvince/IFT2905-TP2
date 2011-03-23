#include <QDebug>
#include <QIODevice>
#include <QFile>
#include <QLocale>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calendarevent.h"
#include "calendar.h"
#include "dayeventfilterproxy.h"
#include "eventlistproxy.h"

#include <QDebug>

#define DEFAULT_COLOR QColor(0xEB, 0x6E, 0x10)

int MainWindow::CALENDAR_VIEW = 0;
int MainWindow::FILTER_VIEW = 1;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    francais(QLocale::French, QLocale::Canada)
{
    ui->setupUi(this);

    settings = new QSettings("VECalendar", "diro");
    backgroundColor = settings->value("backgroundColor", DEFAULT_COLOR).value<QColor>();


    calendar = new Calendar(this);
    dayProxy = new DayEventFilterProxy(this);
    dayProxy->setDynamicSortFilter(true);
    dayProxy->setSourceModel(calendar);

    listProxy = new EventListProxy(this);
    listProxy->setDynamicSortFilter(true);
    listProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    listProxy->setSourceModel(calendar);

    connect(this, SIGNAL(dateSelected(QDate)), this, SLOT(setDateLabelsText(QDate)));
    connect(this, SIGNAL(selectView(int)), this, SLOT(setViewButtonText(int)));
    connect(this, SIGNAL(selectView(int)), ui->leftPane, SLOT(setCurrentIndex(int)));
    connect(calendar, SIGNAL(date_modified(const QDate&)), dayProxy, SLOT(invalidate()));
    connect(calendar, SIGNAL(date_modified(const QDate&)), listProxy, SLOT(invalidate()));
    connect(calendar, SIGNAL(date_modified(const QDate&)), this, SLOT(highlight_date(const QDate&)));
    connect(calendar, SIGNAL(loadedEvent(QDate)), this, SLOT(highlight_date(QDate)));
    connect(ui->addEventButton, SIGNAL(clicked()), this, SLOT(addEventRequest()));
    connect(ui->addEventButtonList, SIGNAL(clicked()), this, SLOT(addEventRequest()));
    connect(ui->calendarWidget, SIGNAL(clicked(QDate)), dayProxy, SLOT(setFilterDate(QDate)));
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(dateActivated()));
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(disableButtons()));
    connect(ui->dayEventsLong, SIGNAL(clicked(QModelIndex)), this, SLOT(setDateLabel(QModelIndex)));
    connect(ui->dayEventsLong, SIGNAL(clicked(QModelIndex)), this, SLOT(viewEvent(QModelIndex)));
    connect(ui->dayEventsLong, SIGNAL(clicked(QModelIndex)), this, SLOT(enableButtons()));
    connect(ui->dayEventsShort, SIGNAL(clicked(QModelIndex)), this, SLOT(enableButtons()));
    connect(ui->dayEventsShort, SIGNAL(clicked(QModelIndex)), this, SLOT(viewEvent(QModelIndex)));
    connect(ui->delEventButton, SIGNAL(clicked()), this, SLOT(deleteEventRequest()));
    connect(ui->delEventButtonList, SIGNAL(clicked()), this, SLOT(deleteEventRequest()));
    connect(ui->filterString, SIGNAL(textChanged(QString)), listProxy, SLOT(setFilterFixedString(QString)));
    connect(ui->filterString, SIGNAL(textChanged(QString)), this, SLOT(disableListButtons()));
    connect(ui->modEventButton, SIGNAL(clicked()), this, SLOT(modifyEventRequest()));
    connect(ui->modEventButtonList, SIGNAL(clicked()), this, SLOT(modifyEventRequest()));
    connect(ui->viewButton, SIGNAL(clicked()), this, SLOT(ToggleView()));

    // Menu actions
    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionSauvegarder_calendrier, SIGNAL(triggered()), this, SLOT(saveCalendar()));
    connect(ui->actionOuvrir_calendrier, SIGNAL(triggered()), this, SLOT(loadCalendar()));
    connect(ui->actionCouleur, SIGNAL(triggered()), this, SLOT(setColor()));


    dateActivated();
    setEnabledButtons(CALENDAR_VIEW, false);
    setEnabledButtons(FILTER_VIEW, false);
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

    if (calendar->countForDate(date) > 0) {
        fmt.setFontWeight(QFont::Bold);
        fmt.setForeground(Qt::white);
        fmt.setBackground(backgroundColor);
    }
    ui->calendarWidget->setDateTextFormat(date, fmt);
}

void MainWindow::ToggleView()
{
    activeView = 1 - activeView;
    emit selectView(activeView);
}

void MainWindow::addEventRequest()
{
    AddModDialog AMDialog(calendar, 0, this);
    AMDialog.setDate(ui->calendarWidget->selectedDate());
    AMDialog.exec();
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
    CalendarEvent *ce;

    if (activeView == CALENDAR_VIEW) {
        QModelIndex index = ui->dayEventsShort->currentIndex();
        QModelIndex index2 = dayProxy->mapToSource(index);
        ce = calendar->get_event(index2);
    }
    else {
        QModelIndex index = ui->dayEventsLong->currentIndex();
        QModelIndex index2 = listProxy->mapToSource(index);
        ce = calendar->get_event(index2);
    }
    AddModDialog AMDialog(calendar, ce, this);
    AMDialog.displayInformation(ce);
    AMDialog.exec();
}


void MainWindow::dateActivated()
{
    activeDate = ui->calendarWidget->selectedDate();
    emit dateSelected(activeDate);
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

void MainWindow::setEnabledButtons(int view, bool b) {
    if (view == CALENDAR_VIEW) {
        ui->delEventButton->setEnabled(b);
        ui->modEventButton->setEnabled(b);
    }
    else {
        ui->delEventButtonList->setEnabled(b);
        ui->modEventButtonList->setEnabled(b);
    }
}

void MainWindow::enableButtons() {
    setEnabledButtons(activeView, true);
}


void MainWindow::disableButtons() {
    setEnabledButtons(activeView, false);
}

void MainWindow::setDateLabelsText(QDate date) {
    ui->selectedDate->setText(date.toString("dd MMMM yyyy"));
}


void MainWindow::disableListButtons() {
    if (ui->dayEventsLong->currentIndex().internalPointer() == 0) {
        disableButtons();
    }
}

void MainWindow::saveCalendar() {
    QString filename = QFileDialog::getSaveFileName();
    QFile f(filename);
    if (f.open(QIODevice::WriteOnly)) {
        QDataStream s(&f);
        s << *calendar;
        f.close();
        QMessageBox::warning(this, trUtf8("Sauvegarde réussie"), trUtf8("La sauvegarde du calendrier a réussi."));
    }
    else {
        QMessageBox::warning(this, trUtf8("Sauvegarde échouée"), trUtf8("La sauvegarde du calendrier a échouée."));
    }
}


void MainWindow::loadCalendar() {
    QString filename = QFileDialog::getOpenFileName();
    QFile f(filename);
    if (f.open(QIODevice::ReadOnly)) {
        QDataStream s(&f);
        s >> *calendar;
        f.close();
        QMessageBox::warning(this, trUtf8("Ouverture réussie"), trUtf8("L'ouverture du calendrier a réussi."));
    }
    else {
        QMessageBox::warning(this, trUtf8("Ouvertureéchouée"), trUtf8("L'ouverture' du calendrier a échouée."));
    }
}

void MainWindow::setColor() {
   QColor newColor = QColorDialog::getColor(backgroundColor);
   if (!newColor.isValid()) {
       return;
   }
   backgroundColor = newColor;
   settings->setValue("backgroundColor", backgroundColor);
   foreach (CalendarEvent *ce, calendar->getEvents()) {
       emit highlight_date(ce->date);
   }
}
