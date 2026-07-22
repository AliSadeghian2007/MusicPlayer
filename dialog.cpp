#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <string>

Dialog::Dialog(AccountManager* accountManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    accountManager(accountManager)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_submitRegisterButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString fullName = ui->nameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString biography = ui->bioTextEdit->toPlainText();

    QString role = "";
    if (ui->artistRadioButton->isChecked()) {
        role = "Artist";
    } else if (ui->listenerRadioButton->isChecked()) {
        role = "Listener";
    } else {
        QMessageBox::warning(this, "Registration Error", "Please select a role.");
        return;
    }

    if (username.isEmpty() || fullName.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Registration Error", "Please fill in all required fields.");
        return;
    }


    std::string stdUsername = username.toStdString();
    std::string stdPassword = password.toStdString();
    std::string stdFullName = fullName.toStdString();
    std::string stdBiography = biography.toStdString();
    std::string stdRole = role.toStdString();
    std::string stdProfilePhoto = "";

    if (accountManager->usernameExists(stdUsername))
    {
        QMessageBox::critical(this, "Registration Error", "This username has already been selected.");
        return;
    }

    if (accountManager->passwordExists(stdPassword))
    {
        QMessageBox::critical(this, "Registration Error", "This password has already been selected.");
        return;
    }

    try {

        bool success = accountManager->registerAccount(stdUsername, stdPassword, stdFullName, stdBiography, stdRole, stdProfilePhoto);

        if (success) {
            QMessageBox::information(this, "Success", "Registration successful!");
            accept();
        } else {
            QMessageBox::critical(this, "Registration Error", "Account already exists or registration failed.");
        }
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void Dialog::on_backButton_clicked()
{
    reject();
}
