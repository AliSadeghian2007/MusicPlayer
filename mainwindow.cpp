#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "accountmanager.h"
#include "artistmanager.h"
#include "artistwindow.h"
#include "user.h"
#include "artist.h"

#include <QMessageBox>

MainWindow::MainWindow(AccountManager *accountManager,
                       ArtistManager *artistManager,
                       QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    accountManager(accountManager),
    artistManager(artistManager)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString username = ui->lineEdit->text().trimmed();
    QString password = ui->lineEdit_2->text();

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Login Input Error", "Fields cannot be empty.");
        return;
    }

    User *user = accountManager->Login(username.toStdString(), password.toStdString());

    if (user == nullptr)
    {
        QMessageBox::critical(this, "Login Failure", "Invalid username or password.");
        return;
    }

    Artist *artist = dynamic_cast<Artist*>(user);
    if (artist != nullptr)
    {
        ArtistWindow *artistWindow = new ArtistWindow(artistManager, artist);
        artistWindow->setAttribute(Qt::WA_DeleteOnClose);

        // اتصال ایمن سیگنال خروج هنرمند به فعال‌سازی مجدد پنجره لاگین اصلی
        connect(artistWindow, &ArtistWindow::logoutRequested,
                this, &MainWindow::onArtistLogoutRequested);

        artistWindow->show();
        this->hide();

        // ریست کردن فیلدها برای ورودهای بعدی بعد از خروج
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
    }
    else
    {
        QMessageBox::information(this, "Login", "Welcome listener!");
    }
}

void MainWindow::on_registerButton_clicked()
{
    QMessageBox::information(this, "Register", "Registration logic should be completed via dialogs.");
}

void MainWindow::onArtistLogoutRequested()
{
    this->show();
}

