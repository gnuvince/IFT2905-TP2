#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
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

signals:
    void dateSelected(QString date);
    void createEntry(QDate &date);

private:
    Ui::MainWindow *ui;
    AddModDialog *AMDialog;
};

#endif // MAINWINDOW_H
