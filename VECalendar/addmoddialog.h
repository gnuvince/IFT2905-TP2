#ifndef ADDMODDIALOG_H
#define ADDMODDIALOG_H

#include <QDialog>

namespace Ui {
    class AddModDialog;
}

class AddModDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddModDialog(QWidget *parent = 0);
    ~AddModDialog();

private:
    Ui::AddModDialog *ui;
};

#endif // ADDMODDIALOG_H