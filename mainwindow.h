#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

<<<<<<< HEAD

class AccountManager;
class ArtistManager;
class ListenerManager;
=======
class AccountManager;
class ArtistManager;
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
<<<<<<< HEAD

    explicit MainWindow(AccountManager *accountManager,
                        ArtistManager *artistManager,
                        ListenerManager *listenerManager,
=======
    explicit MainWindow(AccountManager *accountManager,
                        ArtistManager *artistManager,
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
                        QWidget *parent = nullptr);
    ~MainWindow();

private slots:
<<<<<<< HEAD
    void on_pushButton_2_clicked();
    void on_registerButton_clicked();
    void onArtistLogoutRequested();
    void onListenerLogoutRequested();
=======
    void on_pushButton_2_clicked(); // دکمه لاگین
    void on_registerButton_clicked();
    void onArtistLogoutRequested(); // بازگردانی پنجره اصلی پس از خروج هنرمند
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82

private:
    Ui::MainWindow *ui;
    AccountManager *accountManager;
    ArtistManager *artistManager;
<<<<<<< HEAD
    ListenerManager *listenerManager;
=======
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
};

#endif // MAINWINDOW_H

<<<<<<< HEAD

=======
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
