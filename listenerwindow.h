#ifndef LISTENERWINDOW_H
#define LISTENERWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>
#include <QDialog>
#include <vector>

class ListenerManager;
class SharedFeaturesManager;
class AccountManager;
class Listener;
class Artist;
class Album;
class Playlist;
class Song;

namespace Ui {
class ListenerWindow;
}


class ListenerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListenerWindow(ListenerManager *listenerManager,
                            Listener *listener,
                            SharedFeaturesManager *sharedFeaturesManager = nullptr,
                            AccountManager *accountManager = nullptr,
                            QWidget *parent = nullptr);
    ~ListenerWindow();


signals:
    void logoutRequested();



private slots:
    void onAddPlaylistClicked();
    void onEditPlaylistClicked();
    void onDeletePlaylistClicked();
    void onExploreClicked();
    void onLogoutClicked();
    void onEditAccountClicked();
    void onDeleteAccountClicked();

private:
    void setupConnections();
    void refreshPlaylists();
    void clearPlaylistsLayout();
    QWidget* createPlaylistItem(int playlistId,
                                const QString& playlistName,
                                int songCount,
                                bool isFavorites);
    void setSelectedPlaylist(int playlistId, bool isFavorites);
    void updateActionButtons();
    QString getPlaylistDisplayName(Playlist *playlist) const;


    std::vector<Playlist*> sortedUserPlaylists() const;
    std::vector<Album*> sortedArtistAlbums(int artistId) const;
    std::vector<Song*> sortedSongList(std::vector<Song*> songs) const;


    void openPlaylistSongsDialog(int playlistId, bool isFavorites);


    void openArtistBrowserDialog();
    void openArtistDetailDialog(Artist *artist);
    QWidget* buildBrowseSongRow(QWidget *parent, Song *song);
    void showAddToPlaylistMenu(QWidget *anchor, int songId);

private:
    Ui::ListenerWindow *ui;
    ListenerManager *listenerManager;
    Listener *currentListener;
    SharedFeaturesManager *sharedFeaturesManager;
    AccountManager *accountManager;

    int selectedPlaylistId;
    bool selectedIsFavorites;
};

#endif // LISTENERWINDOW_H