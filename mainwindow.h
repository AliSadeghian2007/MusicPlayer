#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AccountManager;
class ArtistManager;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(AccountManager *accountManager,
                        ArtistManager *artistManager,
                        QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked(); // دکمه لاگین
    void on_registerButton_clicked();
    void onArtistLogoutRequested(); // بازگردانی پنجره اصلی پس از خروج هنرمند

private:
    Ui::MainWindow *ui;
    AccountManager *accountManager;
    ArtistManager *artistManager;
};

#endif // MAINWINDOW_H

