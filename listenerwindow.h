#ifndef LISTENERWINDOW_H
#define LISTENERWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>

class ListenerManager;
class Listener;
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

private:
    Ui::ListenerWindow *ui;
    ListenerManager *listenerManager;
    Listener *currentListener;

    int selectedPlaylistId;
    bool selectedIsFavorites;
};

#endif // LISTENERWINDOW_H
