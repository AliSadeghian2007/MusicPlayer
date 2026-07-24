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
    if (accountManager == nullptr || artistManager == nullptr)
    {
        QMessageBox::critical(this, "Error", "Internal manager is not available.");
        return;
    }

    QString username = ui->lineEdit->text().trimmed();
    QString password = ui->lineEdit_2->text().trimmed();

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Login Failed", "Please enter username and password.");
        return;
    }

    User *user = accountManager->Login(username.toStdString(), password.toStdString());

    if (user == nullptr)
    {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
        return;
    }

    Artist *artist = dynamic_cast<Artist *>(user);

    if (artist == nullptr)
    {
        QMessageBox::warning(this, "Login Failed", "Only artist users can open Artist Dashboard.");
        return;
    }

    ArtistWindow *artistWindow = new ArtistWindow(artistManager, artist);
    artistWindow->setAttribute(Qt::WA_DeleteOnClose);

    connect(artistWindow, &ArtistWindow::logoutRequested,
            this, &MainWindow::onArtistLogoutRequested);

    artistWindow->show();
    this->hide();
}


void MainWindow::on_registerButton_clicked()
{
    QMessageBox::information(this, "Register", "Registration logic should be completed via dialogs.");
}

void MainWindow::onArtistLogoutRequested()
{
    this->show();
}

