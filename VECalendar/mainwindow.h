#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QtGui/QWidget>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QModelIndex>

#include "addmoddialog.h"
#include "calendar.h"
#include "dayeventfilterproxy.h"
#include "eventlistproxy.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void dateActivated();
    void addEventRequest();
    void deleteEventRequest();
    void modifyEventRequest();
    void viewEvent(QModelIndex index);
    void ToggleView();
    void setViewButtonText(int view);
    void highlight_date(const QDate &date);
    void setDateLabel(QModelIndex index);

signals:
    void dateSelected(QString date);
    void createEntry(QDate &date);
    void selectView(int view);

private:
    static int CALENDAR_VIEW;
    static int FILTER_VIEW;
    Ui::MainWindow *ui;
    AddModDialog *AMDialog;
    QStackedLayout *stackedLayout;
    QHBoxLayout *hBoxLayout;
    QWidget *pane1Widget;
    QWidget *pane2Widget;
    int activeView;
    Calendar *calendar;
    DayEventFilterProxy *dayProxy;
    EventListProxy *listProxy;
};

#endif // MAINWINDOW_H
