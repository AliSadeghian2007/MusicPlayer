#include "mainwindow.h"
#include "ui_mainwindow.h"
<<<<<<< HEAD
#include "accountmanager.h"
#include "artistmanager.h"
#include "listenermanager.h"
#include "artist.h"
#include "listener.h"
#include "artistwindow.h"
#include "listenerwindow.h"
#include "dialog.h"
#include <QMessageBox>

MainWindow::MainWindow(AccountManager *accountManager,
                       ArtistManager *artistManager,
                       ListenerManager *listenerManager,
                       QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , accountManager(accountManager)
    , artistManager(artistManager)
    , listenerManager(listenerManager)
=======

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
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
<<<<<<< HEAD
    if (accountManager == nullptr || artistManager == nullptr || listenerManager == nullptr)
    {
        QMessageBox::critical(this, "Error", "Internal manager is not available.");
        return;
    }

    QString username = ui->lineEdit->text().trimmed();
    QString password = ui->lineEdit_2->text().trimmed();

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Login Failed", "Please enter username and password.");
=======
    QString username = ui->lineEdit->text().trimmed();
    QString password = ui->lineEdit_2->text();

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Login Input Error", "Fields cannot be empty.");
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
        return;
    }

    User *user = accountManager->Login(username.toStdString(), password.toStdString());

    if (user == nullptr)
    {
<<<<<<< HEAD
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
        return;
    }

    Artist *artist = dynamic_cast<Artist *>(user);
=======
        QMessageBox::critical(this, "Login Failure", "Invalid username or password.");
        return;
    }

    Artist *artist = dynamic_cast<Artist*>(user);
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
    if (artist != nullptr)
    {
        ArtistWindow *artistWindow = new ArtistWindow(artistManager, artist);
        artistWindow->setAttribute(Qt::WA_DeleteOnClose);

<<<<<<< HEAD
=======
        // اتصال ایمن سیگنال خروج هنرمند به فعال‌سازی مجدد پنجره لاگین اصلی
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
        connect(artistWindow, &ArtistWindow::logoutRequested,
                this, &MainWindow::onArtistLogoutRequested);

        artistWindow->show();
        this->hide();
<<<<<<< HEAD
        return;
    }

    Listener *listener = dynamic_cast<Listener *>(user);
    if (listener != nullptr)
    {
        ListenerWindow *listenerWindow = new ListenerWindow(listenerManager, listener);
        listenerWindow->setAttribute(Qt::WA_DeleteOnClose);

        connect(listenerWindow, &ListenerWindow::logoutRequested,
                this, &MainWindow::onListenerLogoutRequested);

        listenerWindow->show();
        this->hide();
        return;
    }

    QMessageBox::warning(this, "Login Failed", "Unsupported user type.");
}


void MainWindow::on_registerButton_clicked()
{
    if (accountManager == nullptr)
    {
        QMessageBox::critical(
            this,
            "Error",
            "Internal account manager is not available.");
        return;
    }

    Dialog dialog(accountManager, this);

    if (dialog.exec() == QDialog::Accepted)
    {

    }
}

void MainWindow::onArtistLogoutRequested()
{
    this->show();
}

void MainWindow::onListenerLogoutRequested()
{
    this->show();
=======

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
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
}

void MainWindow::onArtistLogoutRequested()
{
    this->show();
}

