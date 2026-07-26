#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <vector>
#include <string>

class ArtistManager;
class SharedFeaturesManager;
class Artist;
class Album;
class Song;

namespace Ui {
class ArtistWindow;
}

static const int SINGLES_ALBUM_ID = 0;

class ArtistWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArtistWindow(ArtistManager *artistManager,
                          Artist *artist,
                          SharedFeaturesManager *sharedFeaturesManager = nullptr,
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
    void buildSongsSection();

    void refreshAlbums();
    void clearAlbumsLayout();
    void addAlbumWidget(int albumId, const QString &name, const std::string &coverPath, bool isSingles);

    void refreshSongs();
    void clearSongsLayout();
    void addSongWidget(Song *song);
    void populateGenreFilter(const std::vector<Song*> &songs);
    std::vector<Song*> applySongFilter(std::vector<Song*> songs) const;

    void onEditSong(int songId);
    void onDeleteSong(int songId);

    std::vector<Album*> sortedAlbums() const;
    std::vector<Song*> sortedSongs(std::vector<Song*> songs) const;

private:
    bool singlesSelected = false;
    int currentSelectedAlbumId = -1;

    Ui::ArtistWindow *ui;
    ArtistManager *artistManager;
    Artist *artist;
    SharedFeaturesManager *sharedFeaturesManager;

    QWidget *albumsContainer;
    QVBoxLayout *albumsLayout;


    QWidget *songsFrame;
    QLabel *songsTitleLabel;
    QLabel *emptySongsLabel;
    QWidget *songsContainerWidget;
    QVBoxLayout *songsContainerLayout;


    QLineEdit *songsSearchEdit;
    QComboBox *genreFilterCombo;
};

#endif // ARTISTWINDOW_H
