#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QtGui/QWidget>
#include <QStackedLayout>
#include <QHBoxLayout>

#include "addmoddialog.h"

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
    void HiliteDate();
    void addEventRequest();
    void deleteEventRequest();
    void modifyEventRequest();
    void ToggleView();

signals:
    void dateSelected(QString date);
    void createEntry(QDate &date);
    void selectView(int view);

private:
    int CALENDAR_VIEW;
    int FILTER_VIEW;
    Ui::MainWindow *ui;
    AddModDialog *AMDialog;
    QStackedLayout *stackedLayout;
    QHBoxLayout *hBoxLayout;
    QWidget *pane1Widget;
    QWidget *pane2Widget;
    int activeView;
};

#endif // MAINWINDOW_H
