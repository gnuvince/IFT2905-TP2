#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

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
    void addEventRequest(QDate *date);
    void deleteEventRequest();
    void modifyEventRequest();

signals:
    void dateSelected(QString date);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
