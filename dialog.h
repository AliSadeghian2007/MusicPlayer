#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "accountmanager.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(AccountManager *manager, QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_submitRegisterButton_clicked();
    void on_backButton_clicked();

private:
    Ui::Dialog *ui;
    AccountManager *accountManager;
};

#endif
