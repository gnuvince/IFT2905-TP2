#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QtGui/QWidget>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QModelIndex>
#include <QLocale>

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
    void disableButtons();
    void enableButtons();
    void setDateLabelsText(QDate date);
    void disableListButtons();

signals:
    void dateSelected(QDate date);
    void createEvent();
    void selectView(int view);
    void dataModelChanged();

private:
    static int CALENDAR_VIEW;
    static int FILTER_VIEW;
    Ui::MainWindow *ui;
    //AddModDialog *AMDialog;
    QStackedLayout *stackedLayout;
    QHBoxLayout *hBoxLayout;
    QWidget *pane1Widget;
    QWidget *pane2Widget;
    QDate activeDate;
    int activeView;
    Calendar *calendar;
    DayEventFilterProxy *dayProxy;
    EventListProxy *listProxy;
    QLocale francais;
    void setEnabledButtons(int view, bool b);
};

#endif // MAINWINDOW_H
