#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
<<<<<<< HEAD
#include <QWidget>

class ArtistManager;
class Artist;
class Album;
=======
#include <vector>
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82

class ArtistManager;
class Artist;
class Album;
class Song;

QT_BEGIN_NAMESPACE
namespace Ui {
class ArtistWindow;
}
QT_END_NAMESPACE

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
<<<<<<< HEAD
=======
    void refreshDashboard();
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
    void refreshAlbums();
    void clearAlbumsLayout();
    void addAlbumWidget(Album *album);

<<<<<<< HEAD
private:
    int currentSelectedAlbumId = -1;
    Ui::ArtistWindow *ui;
    ArtistManager *artistManager;
    Artist *artist;

    QWidget *albumsContainer;
    QVBoxLayout *albumsLayout;
=======

    void renderAlbumSongs(int albumId, QVBoxLayout* albumCardLayout);
    void refreshSingles();

    Ui::ArtistWindow *ui;
    ArtistManager *artistManager;
    Artist *artist;
    QWidget *albumsContainer;
    QVBoxLayout *albumsLayout;


    QWidget *singlesContainer;
    QVBoxLayout *singlesLayout;
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
};

#endif // ARTISTWINDOW_H
