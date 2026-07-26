#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class AccountManager;
class ArtistManager;
class ListenerManager;
class SharedFeaturesManager;

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
                        ListenerManager *listenerManager,
                        SharedFeaturesManager *sharedFeaturesManager,
                        QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_registerButton_clicked();
    void onArtistLogoutRequested();
    void onListenerLogoutRequested();

private:
    Ui::MainWindow *ui;
    AccountManager *accountManager;
    ArtistManager *artistManager;
    ListenerManager *listenerManager;
    SharedFeaturesManager *sharedFeaturesManager;
};

#endif // MAINWINDOW_H
