#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>

class ArtistManager;
class Artist;
class Album;

namespace Ui {
class ArtistWindow;
}

class ArtistWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArtistWindow(ArtistManager *artistManager,
                          Artist *artist,
                          QWidget *parent = nullptr);
    ~ArtistWindow();

signals:
    void logoutRequested();

private slots:
    void onAddAlbumClicked();
    void onAddSongClicked();
    void onEditClicked();
    void onDeleteClicked();
    void onLogoutClicked();

private:
    void setupConnections();
    void refreshAlbums();
    void clearAlbumsLayout();
    void addAlbumWidget(Album *album);

private:
    int currentSelectedAlbumId = -1;
    Ui::ArtistWindow *ui;
    ArtistManager *artistManager;
    Artist *artist;

    QWidget *albumsContainer;
    QVBoxLayout *albumsLayout;
};

#endif // ARTISTWINDOW_H
