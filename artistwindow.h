#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <vector>

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
    void refreshDashboard();
    void refreshAlbums();
    void clearAlbumsLayout();
    void addAlbumWidget(Album *album);


    void renderAlbumSongs(int albumId, QVBoxLayout* albumCardLayout);
    void refreshSingles();

    Ui::ArtistWindow *ui;
    ArtistManager *artistManager;
    Artist *artist;
    QWidget *albumsContainer;
    QVBoxLayout *albumsLayout;


    QWidget *singlesContainer;
    QVBoxLayout *singlesLayout;
};

#endif // ARTISTWINDOW_H
