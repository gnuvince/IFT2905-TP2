#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QtGui/QWidget>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QModelIndex>
#include <QLocale>
#include <QColor>
#include <QSettings>

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
    void saveCalendar();
    void loadCalendar();
    void setColor();
    void shutdown();

signals:
    void dateSelected(QDate date);
    void createEvent();
    void selectView(int view);
    void dataModelChanged();


private:
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
    QColor backgroundColor;
    QSettings *settings;
    bool loadCalendar(QString filename);
    bool saveCalendar(QString filename);


};

#endif // MAINWINDOW_H
