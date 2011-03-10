#ifndef ADDMODDIALOG_H
#define ADDMODDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
    class AddModDialog;
}

class AddModDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddModDialog(QWidget *parent = 0);
    ~AddModDialog();
    QDate *entryDate;


public slots:
    void addEventRequest(QDate &date);

private:
    Ui::AddModDialog *ui;
};

#endif // ADDMODDIALOG_H
