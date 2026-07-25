#include "mainwindow.h"
#include "ui_mainwindow.h"
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
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
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
        return;
    }

    User *user = accountManager->Login(username.toStdString(), password.toStdString());

    if (user == nullptr)
    {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
        return;
    }

    Artist *artist = dynamic_cast<Artist *>(user);
    if (artist != nullptr)
    {
        ArtistWindow *artistWindow = new ArtistWindow(artistManager, artist);
        artistWindow->setAttribute(Qt::WA_DeleteOnClose);

        connect(artistWindow, &ArtistWindow::logoutRequested,
                this, &MainWindow::onArtistLogoutRequested);

        artistWindow->show();
        this->hide();
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
}
