#include "listenerwindow.h"
#include "ui_listenerwindow.h"


#include "listenermanager.h"
#include "sharedfeaturesmanager.h"
#include "listener.h"
#include "artist.h"
#include "album.h"
#include "playlist.h"
#include "song.h"


#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QToolButton>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QLayoutItem>
#include <QScrollArea>
#include <QMenu>
#include <QDialogButtonBox>
#include <QPoint>
#include <QPixmap>
#include <QIcon>
#include <QComboBox>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>


ListenerWindow::ListenerWindow(ListenerManager* listenerManager,
                               Listener* listener,
                               SharedFeaturesManager* sharedFeaturesManager,
                               QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ListenerWindow)
    , listenerManager(listenerManager)
    , currentListener(listener)
    , sharedFeaturesManager(sharedFeaturesManager)
    , selectedPlaylistId(-1)
    , selectedIsFavorites(false)
{

    ui->setupUi(this);


    if (currentListener != nullptr)
    {
        std::string fullName = currentListener->getFullName();
        QString welcomeText = "Welcome back, " + QString::fromStdString(fullName) + "!";
        ui->welcomeLabel->setText(welcomeText);
    }


    setupConnections();


    refreshPlaylists();


    updateActionButtons();
}


ListenerWindow::~ListenerWindow()
{
    delete ui;
}


void ListenerWindow::setupConnections()
{

    connect(ui->addPlaylistButton, &QToolButton::clicked,
            this, &ListenerWindow::onAddPlaylistClicked);


    connect(ui->editPlaylistButton, &QToolButton::clicked,
            this, &ListenerWindow::onEditPlaylistClicked);


    connect(ui->deletePlaylistButton, &QToolButton::clicked,
            this, &ListenerWindow::onDeletePlaylistClicked);


    connect(ui->exploreButton, &QPushButton::clicked,
            this, &ListenerWindow::onExploreClicked);


    connect(ui->logoutButton, &QToolButton::clicked,
            this, &ListenerWindow::onLogoutClicked);
}


std::vector<Playlist*> ListenerWindow::sortedUserPlaylists() const
{
    if (currentListener == nullptr || listenerManager == nullptr)
    {
        return std::vector<Playlist*>();
    }

    std::vector<Playlist*> playlists = listenerManager->getPlaylistsByUserId(currentListener->getId());

    if (sharedFeaturesManager == nullptr || playlists.empty())
    {
        return playlists;
    }

    std::vector<Playlist> values;
    for (size_t i = 0; i < playlists.size(); ++i)
    {
        if (playlists[i] != nullptr)
        {
            values.push_back(*playlists[i]);
        }
    }

    values = sharedFeaturesManager->sortPlaylistsByName(values, true);

    std::vector<Playlist*> result;
    for (size_t i = 0; i < values.size(); ++i)
    {
        for (size_t j = 0; j < playlists.size(); ++j)
        {
            if (playlists[j] != nullptr && playlists[j]->getId() == values[i].getId())
            {
                result.push_back(playlists[j]);
                break;
            }
        }
    }

    return result;
}

std::vector<Album*> ListenerWindow::sortedArtistAlbums(int artistId) const
{
    if (listenerManager == nullptr)
    {
        return std::vector<Album*>();
    }

    std::vector<Album*> albums = listenerManager->getArtistAlbums(artistId);

    if (sharedFeaturesManager == nullptr || albums.empty())
    {
        return albums;
    }

    std::vector<Album> values;
    for (size_t i = 0; i < albums.size(); ++i)
    {
        if (albums[i] != nullptr)
        {
            values.push_back(*albums[i]);
        }
    }

    values = sharedFeaturesManager->sortAlbumsByName(values, true);

    std::vector<Album*> result;
    for (size_t i = 0; i < values.size(); ++i)
    {
        for (size_t j = 0; j < albums.size(); ++j)
        {
            if (albums[j] != nullptr && albums[j]->getId() == values[i].getId())
            {
                result.push_back(albums[j]);
                break;
            }
        }
    }

    return result;
}

std::vector<Song*> ListenerWindow::sortedSongList(std::vector<Song*> songs) const
{
    if (sharedFeaturesManager == nullptr || songs.empty())
    {
        return songs;
    }

    std::vector<Song> values;
    for (size_t i = 0; i < songs.size(); ++i)
    {
        if (songs[i] != nullptr)
        {
            values.push_back(*songs[i]);
        }
    }

    values = sharedFeaturesManager->sortSongsByName(values, true);

    std::vector<Song*> result;
    for (size_t i = 0; i < values.size(); ++i)
    {
        for (size_t j = 0; j < songs.size(); ++j)
        {
            if (songs[j] != nullptr && songs[j]->get_Id() == values[i].get_Id())
            {
                result.push_back(songs[j]);
                break;
            }
        }
    }

    return result;
}


void ListenerWindow::clearPlaylistsLayout()
{

    QLayoutItem* item = ui->playlistsContainerLayout->takeAt(0);
    while (item != nullptr)
    {

        QWidget* widget = item->widget();
        if (widget != nullptr)
        {
            delete widget;
        }

        delete item;


        item = ui->playlistsContainerLayout->takeAt(0);
    }
}


void ListenerWindow::refreshPlaylists()
{

    clearPlaylistsLayout();

    if (currentListener == nullptr || listenerManager == nullptr)
    {
        return;
    }

    int listenerId = currentListener->getId();


    std::vector<int> likedSongIds = currentListener->getIdLikedSong();
    int likedSongsCount = static_cast<int>(likedSongIds.size());

    QWidget* favoritesItemWidget = createPlaylistItem(
        -1,
        "Favorites (Liked Songs)",
        likedSongsCount,
        true
        );
    ui->playlistsContainerLayout->addWidget(favoritesItemWidget);


    std::vector<Playlist*> userPlaylists = sortedUserPlaylists();

    for (size_t i = 0; i < userPlaylists.size(); ++i)
    {
        Playlist* playlist = userPlaylists[i];
        if (playlist != nullptr)
        {

            int songCount = static_cast<int>(playlist->getSongIds().size());

            QWidget* itemWidget = createPlaylistItem(
                playlist->getId(),
                QString::fromStdString(playlist->getName()),
                songCount,
                false
                );
            ui->playlistsContainerLayout->addWidget(itemWidget);
        }
    }


    ui->playlistsContainerLayout->addStretch();
}


QWidget* ListenerWindow::createPlaylistItem(int playlistId,
                                            const QString& playlistName,
                                            int songCount,
                                            bool isFavorites)
{

    QFrame* itemFrame = new QFrame(ui->playlistsContainerWidget);
    itemFrame->setObjectName("playlistItemFrame");


    if (isFavorites)
    {
        itemFrame->setStyleSheet(
            "QFrame#playlistItemFrame {"
            "  background-color: #fff9e6;"
            "  border: 1px solid #ffd54f;"
            "  border-radius: 10px;"
            "}"
            );
    }
    else
    {
        itemFrame->setStyleSheet(
            "QFrame#playlistItemFrame {"
            "  background-color: #ffffff;"
            "  border: 1px solid #e0e0e0;"
            "  border-radius: 10px;"
            "}"
            );
    }


    QHBoxLayout* itemLayout = new QHBoxLayout(itemFrame);
    itemLayout->setContentsMargins(15, 10, 15, 10);
    itemLayout->setSpacing(10);


    QLabel* nameLabel = new QLabel(playlistName, itemFrame);
    nameLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #333333;");


    QString songCountText = QString::number(songCount) + " songs";
    QLabel* countLabel = new QLabel(songCountText, itemFrame);
    countLabel->setStyleSheet("font-size: 12px; color: #666666;");


    QPushButton* openButton = new QPushButton(itemFrame);
    openButton->setCursor(Qt::PointingHandCursor);
    openButton->setText("Open");
    openButton->setStyleSheet("background-color: #eff8e8; color: #252525; border: 1px solid #727272; border-radius: 5px; padding: 4px 10px;");


    connect(openButton, &QPushButton::clicked, this, [this, playlistId, isFavorites]() {
        this->setSelectedPlaylist(playlistId, isFavorites);
        this->openPlaylistSongsDialog(playlistId, isFavorites);
    });


    itemLayout->addWidget(nameLabel);
    itemLayout->addWidget(countLabel);
    itemLayout->addStretch();
    itemLayout->addWidget(openButton);

    return itemFrame;
}


void ListenerWindow::setSelectedPlaylist(int playlistId, bool isFavorites)
{
    selectedPlaylistId = playlistId;
    selectedIsFavorites = isFavorites;


    refreshPlaylists();

    updateActionButtons();
}


void ListenerWindow::updateActionButtons()
{

    bool hasSelection = (selectedPlaylistId != -1 || selectedIsFavorites);

    if (hasSelection)
    {
        if (selectedIsFavorites)
        {

            ui->editPlaylistButton->setEnabled(false);
            ui->deletePlaylistButton->setEnabled(false);
        }
        else
        {

            ui->editPlaylistButton->setEnabled(true);
            ui->deletePlaylistButton->setEnabled(true);
        }
    }
    else
    {

        ui->editPlaylistButton->setEnabled(false);
        ui->deletePlaylistButton->setEnabled(false);
    }
}


void ListenerWindow::openPlaylistSongsDialog(int playlistId, bool isFavorites)
{
    if (currentListener == nullptr || listenerManager == nullptr)
    {
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle(isFavorites ? "Favorites (Liked Songs)" : "Playlist Songs");
    dialog.resize(480, 420);

    QVBoxLayout* dialogLayout = new QVBoxLayout(&dialog);

    QScrollArea* scrollArea = new QScrollArea(&dialog);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget* container = new QWidget();
    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    containerLayout->setSpacing(6);
    scrollArea->setWidget(container);

    int listenerId = currentListener->getId();


    std::function<void()> rebuild = [this, containerLayout, container, playlistId, isFavorites, listenerId, &dialog, &rebuild]() {
        QLayoutItem* item = nullptr;
        while ((item = containerLayout->takeAt(0)) != nullptr)
        {
            if (item->widget() != nullptr)
            {
                item->widget()->deleteLater();
            }
            delete item;
        }

        std::vector<Song*> songs = isFavorites
                                        ? listenerManager->getLikedSongs(listenerId)
                                        : listenerManager->getSongsInPlaylist(playlistId);

        songs = sortedSongList(songs);

        if (songs.empty())
        {
            QLabel* emptyLabel = new QLabel("No songs here yet.", container);
            emptyLabel->setAlignment(Qt::AlignCenter);
            emptyLabel->setStyleSheet("color: #777777; font-size: 13px;");
            containerLayout->addWidget(emptyLabel);
        }

        for (size_t i = 0; i < songs.size(); ++i)
        {
            Song* song = songs[i];
            if (song == nullptr)
            {
                continue;
            }

            QFrame* row = new QFrame(container);
            row->setStyleSheet(
                "QFrame { background-color: #f8f8f8; border: 1px solid #e0e0e0; border-radius: 8px; }");

            QHBoxLayout* rowLayout = new QHBoxLayout(row);
            rowLayout->setContentsMargins(12, 6, 12, 6);

            QLabel* nameLabel = new QLabel(QString::fromStdString(song->getName()), row);
            nameLabel->setStyleSheet("font-size: 13px; font-weight: bold; color: #333333; border: none; background: transparent;");

            QLabel* infoLabel = new QLabel(
                QString::fromStdString(song->getGenre()) + " \xC2\xB7 " + QString::number(song->getReleaseYear()),
                row);
            infoLabel->setStyleSheet("font-size: 12px; color: #777777; border: none; background: transparent;");

            QPushButton* removeButton = new QPushButton(isFavorites ? "Unlike" : "Remove", row);
            removeButton->setCursor(Qt::PointingHandCursor);
            removeButton->setStyleSheet("background-color: #fdecea; color: #b3261e; border: 1px solid #b3261e; border-radius: 5px; padding: 4px 10px;");

            int songId = song->get_Id();

            connect(removeButton, &QPushButton::clicked, this, [this, &dialog, &rebuild, playlistId, isFavorites, songId, listenerId]() {
                bool success = isFavorites
                                   ? listenerManager->unlikeSong(listenerId, songId)
                                   : listenerManager->removeSongFromPlaylist(playlistId, listenerId, songId);

                if (success)
                {
                    rebuild();
                }
                else
                {
                    QMessageBox::critical(&dialog, "Error", "Failed to remove the song.");
                }
            });

            rowLayout->addWidget(nameLabel);
            rowLayout->addWidget(infoLabel);
            rowLayout->addStretch();
            rowLayout->addWidget(removeButton);

            containerLayout->addWidget(row);
        }

        containerLayout->addStretch();
    };

    rebuild();
    dialogLayout->addWidget(scrollArea);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, &dialog);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    dialogLayout->addWidget(buttonBox);

    dialog.exec();

    refreshPlaylists();
}


QString ListenerWindow::getPlaylistDisplayName(Playlist *playlist) const
{
    if (playlist == nullptr)
    {
        return QString();
    }

    return QString::fromStdString(playlist->getName());
}


void ListenerWindow::onAddPlaylistClicked()
{
    if (currentListener == nullptr || listenerManager == nullptr)
    {
        return;
    }

    bool okPressed = false;

    QString playlistName = QInputDialog::getText(
        this,
        "New Playlist",
        "Enter playlist name:",
        QLineEdit::Normal,
        "",
        &okPressed
        );


    if (!okPressed)
    {
        return;
    }


    playlistName = playlistName.trimmed();

    if (playlistName.isEmpty())
    {
        QMessageBox::warning(this, "Validation Error", "Playlist name cannot be empty.");
        return;
    }

    int listenerId = currentListener->getId();


    bool isCreated = listenerManager->createPlaylist(listenerId, playlistName.toStdString());

    if (isCreated)
    {
        refreshPlaylists();
    }
    else
    {
        QMessageBox::critical(this, "Database Error", "Failed to create playlist. The name might be duplicated.");
    }
}


void ListenerWindow::onEditPlaylistClicked()
{

    if (selectedPlaylistId == -1 || selectedIsFavorites || listenerManager == nullptr || currentListener == nullptr)
    {
        return;
    }

    int listenerId = currentListener->getId();


    std::vector<Playlist*> userPlaylists = listenerManager->getPlaylistsByUserId(listenerId);
    Playlist* targetPlaylist = nullptr;

    for (size_t i = 0; i < userPlaylists.size(); ++i)
    {
        if (userPlaylists[i] != nullptr && userPlaylists[i]->getId() == selectedPlaylistId)
        {
            targetPlaylist = userPlaylists[i];
            break;
        }
    }

    if (targetPlaylist == nullptr)
    {
        QMessageBox::warning(this, "Execution Error", "Selected playlist was not found.");
        return;
    }

    bool okPressed = false;
    QString currentName = QString::fromStdString(targetPlaylist->getName());


    QString newPlaylistName = QInputDialog::getText(
        this,
        "Edit Playlist Name",
        "Enter new playlist name:",
        QLineEdit::Normal,
        currentName,
        &okPressed
        );

    if (!okPressed)
    {
        return;
    }

    newPlaylistName = newPlaylistName.trimmed();

    if (newPlaylistName.isEmpty())
    {
        QMessageBox::warning(this, "Validation Error", "Playlist name cannot be empty.");
        return;
    }


    bool isEdited = listenerManager->editPlaylist(selectedPlaylistId, listenerId, newPlaylistName.toStdString());

    if (isEdited)
    {
        refreshPlaylists();
    }
    else
    {
        QMessageBox::critical(this, "Database Error", "Failed to update playlist name.");
    }
}


void ListenerWindow::onDeletePlaylistClicked()
{
    if (selectedPlaylistId == -1 || selectedIsFavorites || listenerManager == nullptr || currentListener == nullptr)
    {
        return;
    }


    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        "Delete Playlist",
        "Are you sure you want to delete this playlist permanently?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply != QMessageBox::Yes)
    {
        return;
    }

    int listenerId = currentListener->getId();


    bool isDeleted = listenerManager->deletePlaylist(listenerId, selectedPlaylistId);

    if (isDeleted)
    {

        selectedPlaylistId = -1;
        selectedIsFavorites = false;

        refreshPlaylists();
        updateActionButtons();
    }
    else
    {
        QMessageBox::critical(this, "Database Error", "Failed to delete the playlist.");
    }
}


void ListenerWindow::showAddToPlaylistMenu(QWidget *anchor, int songId)
{
    if (currentListener == nullptr || listenerManager == nullptr || anchor == nullptr)
    {
        return;
    }

    std::vector<Playlist*> userPlaylists = sortedUserPlaylists();

    if (userPlaylists.empty())
    {
        QMessageBox::information(this, "Add to Playlist",
                                 "You don't have any playlists yet. Create one first from your dashboard.");
        return;
    }

    QMenu menu(anchor);
    int listenerId = currentListener->getId();

    for (size_t i = 0; i < userPlaylists.size(); ++i)
    {
        Playlist* playlist = userPlaylists[i];
        if (playlist == nullptr)
        {
            continue;
        }

        int playlistId = playlist->getId();
        QAction* action = menu.addAction(QString::fromStdString(playlist->getName()));

        connect(action, &QAction::triggered, this, [this, playlistId, listenerId, songId]() {
            bool success = listenerManager->addSongToPlaylist(playlistId, listenerId, songId);

            if (success)
            {
                refreshPlaylists();
                QMessageBox::information(this, "Add to Playlist", "Song added to the playlist.");
            }
            else
            {
                QMessageBox::warning(this, "Add to Playlist", "Could not add the song (it may already be in this playlist).");
            }
        });
    }

    menu.exec(anchor->mapToGlobal(QPoint(0, anchor->height())));
}


QWidget* ListenerWindow::buildBrowseSongRow(QWidget *parent, Song *song)
{
    if (song == nullptr)
    {
        return nullptr;
    }

    QFrame* row = new QFrame(parent);
    row->setStyleSheet(
        "QFrame { background-color: #f8f8f8; border: 1px solid #e0e0e0; border-radius: 8px; }");

    QHBoxLayout* rowLayout = new QHBoxLayout(row);
    rowLayout->setContentsMargins(12, 6, 12, 6);
    rowLayout->setSpacing(8);

    QLabel* coverLabel = new QLabel(row);
    coverLabel->setFixedSize(40, 40);
    coverLabel->setAlignment(Qt::AlignCenter);
    coverLabel->setStyleSheet(
        "border: 1px solid #d0d0d0; border-radius: 4px; background-color: #eeeeee; color: #999999; font-size: 9px;");

    QPixmap coverPixmap(QString::fromStdString(song->getCoverPath()));

    if (!coverPixmap.isNull())
    {
        coverLabel->setPixmap(coverPixmap.scaled(
            40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else
    {
        coverLabel->setText(QString::fromUtf8("\xF0\x9F\x8E\xB5"));
    }

    QLabel* nameLabel = new QLabel(QString::fromStdString(song->getName()), row);
    nameLabel->setStyleSheet("font-size: 13px; font-weight: bold; color: #333333; border: none; background: transparent;");

    QLabel* infoLabel = new QLabel(
        QString::fromStdString(song->getGenre()) + " \xC2\xB7 " + QString::number(song->getReleaseYear()),
        row);
    infoLabel->setStyleSheet("font-size: 12px; color: #777777; border: none; background: transparent;");

    int songId = song->get_Id();
    bool liked = (currentListener != nullptr && listenerManager != nullptr)
                     ? listenerManager->isSongLiked(currentListener->getId(), songId)
                     : false;

    QPushButton* likeButton = new QPushButton(liked ? "\xE2\x99\xA5" : "\xE2\x99\xA1", row);
    likeButton->setCursor(Qt::PointingHandCursor);
    likeButton->setFlat(true);
    likeButton->setFixedSize(30, 30);
    likeButton->setToolTip(liked ? "Unlike" : "Like");
    likeButton->setStyleSheet(liked
                                  ? "border: none; background: transparent; color: #c0392b; font-size: 16px;"
                                  : "border: none; background: transparent; color: #aaaaaa; font-size: 16px;");

    QPushButton* addButton = new QPushButton("+ Playlist", row);
    addButton->setCursor(Qt::PointingHandCursor);
    addButton->setStyleSheet("background-color: #eff8e8; color: #252525; border: 1px solid #727272; border-radius: 5px; padding: 4px 10px;");

    int listenerId = currentListener != nullptr ? currentListener->getId() : -1;

    connect(likeButton, &QPushButton::clicked, this, [this, likeButton, songId, listenerId]() {
        if (listenerManager == nullptr || listenerId == -1)
        {
            return;
        }

        bool nowLiked = listenerManager->isSongLiked(listenerId, songId);
        bool success = nowLiked
                           ? listenerManager->unlikeSong(listenerId, songId)
                           : listenerManager->likeSong(listenerId, songId);

        if (success)
        {
            bool liked = listenerManager->isSongLiked(listenerId, songId);
            likeButton->setText(liked ? "\xE2\x99\xA5" : "\xE2\x99\xA1");
            likeButton->setToolTip(liked ? "Unlike" : "Like");
            likeButton->setStyleSheet(liked
                                          ? "border: none; background: transparent; color: #c0392b; font-size: 16px;"
                                          : "border: none; background: transparent; color: #aaaaaa; font-size: 16px;");
            refreshPlaylists();
        }
    });

    connect(addButton, &QPushButton::clicked, this, [this, addButton, songId]() {
        showAddToPlaylistMenu(addButton, songId);
    });

    rowLayout->addWidget(coverLabel);
    rowLayout->addWidget(nameLabel);
    rowLayout->addWidget(infoLabel);
    rowLayout->addStretch();
    rowLayout->addWidget(likeButton);
    rowLayout->addWidget(addButton);

    return row;
}


void ListenerWindow::onExploreClicked()
{
    openArtistBrowserDialog();
}


void ListenerWindow::openArtistBrowserDialog()
{
    if (listenerManager == nullptr)
    {
        return;
    }

    std::vector<Artist*> artists = listenerManager->getAllArtists();

    std::sort(artists.begin(), artists.end(), [](Artist* a, Artist* b) {
        if (a == nullptr || b == nullptr)
        {
            return false;
        }
        return a->getUserName() < b->getUserName();
    });

    QDialog dialog(this);
    dialog.setWindowTitle("Explore The World of Music");
    dialog.resize(420, 480);

    QVBoxLayout* dialogLayout = new QVBoxLayout(&dialog);

    QLabel* titleLabel = new QLabel("Artists", &dialog);
    titleLabel->setStyleSheet("font-size: 15px; font-weight: 600;");
    dialogLayout->addWidget(titleLabel);

    QLineEdit* artistSearchEdit = new QLineEdit(&dialog);
    artistSearchEdit->setPlaceholderText("Search artists...");
    artistSearchEdit->setClearButtonEnabled(true);
    artistSearchEdit->setStyleSheet(
        "QLineEdit {"
        "  padding: 6px 8px;"
        "  border: 1px solid #cccccc;"
        "  border-radius: 6px;"
        "  background-color: #ffffff;"
        "  color: #242424;"
        "  font-size: 13px;"
        "}");
    dialogLayout->addWidget(artistSearchEdit);

    QScrollArea* scrollArea = new QScrollArea(&dialog);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget* container = new QWidget();
    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    containerLayout->setSpacing(6);

    if (artists.empty())
    {
        QLabel* emptyLabel = new QLabel("No artists have registered yet.", container);
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet("color: #777777;");
        containerLayout->addWidget(emptyLabel);
    }

    for (size_t i = 0; i < artists.size(); ++i)
    {
        Artist* artist = artists[i];
        if (artist == nullptr)
        {
            continue;
        }

        QPushButton* artistButton = new QPushButton(
            QString::fromStdString(artist->getUserName()), container);
        artistButton->setCursor(Qt::PointingHandCursor);
        artistButton->setStyleSheet(
            "text-align: left; padding: 10px; background-color: #ffffff; color: #242424; "
            "border: 1px solid #e0e0e0; border-radius: 8px; font-size: 13px;");

        connect(artistButton, &QPushButton::clicked, this, [this, &dialog, artist]() {
            dialog.close();
            openArtistDetailDialog(artist);
        });

        containerLayout->addWidget(artistButton);
    }

    connect(artistSearchEdit, &QLineEdit::textChanged, this, [container](const QString &text)
            {
                QList<QPushButton*> buttons = container->findChildren<QPushButton*>();

                for (int i = 0; i < buttons.size(); ++i)
                {
                    bool matches = text.trimmed().isEmpty() ||
                                   buttons[i]->text().contains(text.trimmed(), Qt::CaseInsensitive);
                    buttons[i]->setVisible(matches);
                }
            });

    containerLayout->addStretch();
    scrollArea->setWidget(container);
    dialogLayout->addWidget(scrollArea);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, &dialog);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    dialogLayout->addWidget(buttonBox);

    dialog.exec();
}


void ListenerWindow::openArtistDetailDialog(Artist *artist)
{
    if (listenerManager == nullptr || artist == nullptr)
    {
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle(QString::fromStdString(artist->getUserName()));
    dialog.resize(680, 480);

    QHBoxLayout* rootLayout = new QHBoxLayout(&dialog);


    QVBoxLayout* leftLayout = new QVBoxLayout();
    QLabel* albumsTitle = new QLabel("Albums", &dialog);
    albumsTitle->setStyleSheet("font-size: 14px; font-weight: 600;");
    leftLayout->addWidget(albumsTitle);

    QScrollArea* albumsScrollArea = new QScrollArea(&dialog);
    albumsScrollArea->setWidgetResizable(true);
    albumsScrollArea->setFrameShape(QFrame::NoFrame);
    albumsScrollArea->setMaximumWidth(220);

    QWidget* albumsContainer = new QWidget();
    QVBoxLayout* albumsContainerLayout = new QVBoxLayout(albumsContainer);
    albumsContainerLayout->setSpacing(6);

    QVBoxLayout* rightLayout = new QVBoxLayout();
    QLabel* songsTitle = new QLabel("Select an album to see its songs.", &dialog);
    songsTitle->setStyleSheet("font-size: 14px; font-weight: 600;");
    rightLayout->addWidget(songsTitle);

    QHBoxLayout* songsFilterLayout = new QHBoxLayout();
    songsFilterLayout->setSpacing(8);

    QLineEdit* songSearchEdit = new QLineEdit(&dialog);
    songSearchEdit->setPlaceholderText("Search songs...");
    songSearchEdit->setClearButtonEnabled(true);
    songSearchEdit->setStyleSheet(
        "QLineEdit {"
        "  padding: 5px 8px;"
        "  border: 1px solid #cccccc;"
        "  border-radius: 6px;"
        "  background-color: #ffffff;"
        "  color: #242424;"
        "  font-size: 12px;"
        "}");

    QComboBox* songGenreCombo = new QComboBox(&dialog);
    songGenreCombo->addItem("All Genres");
    songGenreCombo->setStyleSheet(
        "QComboBox {"
        "  padding: 4px 8px;"
        "  border: 1px solid #cccccc;"
        "  border-radius: 6px;"
        "  background-color: #ffffff;"
        "  color: #242424;"
        "  font-size: 12px;"
        "}");

    songsFilterLayout->addWidget(songSearchEdit, 1);
    songsFilterLayout->addWidget(songGenreCombo);
    rightLayout->addLayout(songsFilterLayout);

    QScrollArea* songsScrollArea = new QScrollArea(&dialog);
    songsScrollArea->setWidgetResizable(true);
    songsScrollArea->setFrameShape(QFrame::NoFrame);

    QWidget* songsContainer = new QWidget();
    QVBoxLayout* songsContainerLayout = new QVBoxLayout(songsContainer);
    songsContainerLayout->setSpacing(6);
    songsContainerLayout->addStretch();

    songsScrollArea->setWidget(songsContainer);
    rightLayout->addWidget(songsScrollArea);

    int artistId = artist->getId();


    std::shared_ptr<std::vector<Song*>> currentRawSongs = std::make_shared<std::vector<Song*>>();

    auto renderFilteredSongs = [this, songsContainerLayout, songsContainer,
                                songSearchEdit, songGenreCombo, currentRawSongs]() {
        QLayoutItem* item = nullptr;
        while ((item = songsContainerLayout->takeAt(0)) != nullptr)
        {
            if (item->widget() != nullptr)
            {
                item->widget()->deleteLater();
            }
            delete item;
        }

        QString searchText = songSearchEdit->text().trimmed();
        QString genre = songGenreCombo->currentText();

        std::vector<Song*> filtered;
        for (size_t i = 0; i < currentRawSongs->size(); ++i)
        {
            Song* song = (*currentRawSongs)[i];
            if (song == nullptr)
            {
                continue;
            }

            bool matchesSearch = searchText.isEmpty() ||
                                 QString::fromStdString(song->getName()).contains(searchText, Qt::CaseInsensitive);
            bool matchesGenre = genre.isEmpty() || genre == "All Genres" ||
                                QString::fromStdString(song->getGenre()) == genre;

            if (matchesSearch && matchesGenre)
            {
                filtered.push_back(song);
            }
        }

        filtered = sortedSongList(filtered);

        if (filtered.empty())
        {
            QLabel* emptyLabel = new QLabel("No songs here yet.", songsContainer);
            emptyLabel->setAlignment(Qt::AlignCenter);
            emptyLabel->setStyleSheet("color: #777777;");
            songsContainerLayout->addWidget(emptyLabel);
        }
        else
        {
            for (size_t i = 0; i < filtered.size(); ++i)
            {
                QWidget* row = buildBrowseSongRow(songsContainer, filtered[i]);
                if (row != nullptr)
                {
                    songsContainerLayout->addWidget(row);
                }
            }
        }

        songsContainerLayout->addStretch();
    };

    connect(songSearchEdit, &QLineEdit::textChanged, this, [renderFilteredSongs](const QString &)
            {
                renderFilteredSongs();
            });
    connect(songGenreCombo, &QComboBox::currentTextChanged, this, [renderFilteredSongs](const QString &)
            {
                renderFilteredSongs();
            });

    auto showSongs = [this, songsTitle, songGenreCombo, currentRawSongs, renderFilteredSongs](
                         const QString& title, std::vector<Song*> songs) {
        songsTitle->setText(title);
        *currentRawSongs = songs;

        // Repopulate the genre combo for this album's songs, reset
        // to "All Genres" since we just switched selection.
        songGenreCombo->blockSignals(true);
        songGenreCombo->clear();
        songGenreCombo->addItem("All Genres");

        std::vector<QString> genres;
        for (size_t i = 0; i < songs.size(); ++i)
        {
            if (songs[i] == nullptr)
            {
                continue;
            }

            QString genre = QString::fromStdString(songs[i]->getGenre());

            if (genre.trimmed().isEmpty() || genres.end() != std::find(genres.begin(), genres.end(), genre))
            {
                continue;
            }

            genres.push_back(genre);
        }
        std::sort(genres.begin(), genres.end());

        for (size_t i = 0; i < genres.size(); ++i)
        {
            songGenreCombo->addItem(genres[i]);
        }

        songGenreCombo->setCurrentIndex(0);
        songGenreCombo->blockSignals(false);

        renderFilteredSongs();
    };

    // "Singles" pseudo-album button.
    QPushButton* singlesButton = new QPushButton("\xF0\x9F\x8E\xB5 Singles", albumsContainer);
    singlesButton->setCursor(Qt::PointingHandCursor);
    singlesButton->setStyleSheet(
        "text-align: left; padding: 8px; background-color: #ffffff; color: #242424; "
        "border: 1px solid #e0e0e0; border-radius: 8px; font-size: 13px;");

    connect(singlesButton, &QPushButton::clicked, this, [this, artistId, showSongs]() {
        showSongs("Singles", listenerManager->getArtistSingles(artistId));
    });

    albumsContainerLayout->addWidget(singlesButton);

    std::vector<Album*> albums = sortedArtistAlbums(artistId);

    for (size_t i = 0; i < albums.size(); ++i)
    {
        Album* album = albums[i];
        if (album == nullptr)
        {
            continue;
        }

        QPushButton* albumButton = new QPushButton(
            "  " + QString::fromStdString(album->getName()), albumsContainer);
        albumButton->setCursor(Qt::PointingHandCursor);
        albumButton->setStyleSheet(
            "text-align: left; padding: 8px; background-color: #ffffff; color: #242424; "
            "border: 1px solid #e0e0e0; border-radius: 8px; font-size: 13px;");

        QPixmap albumCoverPixmap(QString::fromStdString(album->getCoverPath()));

        if (!albumCoverPixmap.isNull())
        {
            albumButton->setIcon(QIcon(albumCoverPixmap.scaled(
                28, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            albumButton->setIconSize(QSize(28, 28));
        }

        int albumId = album->getId();
        QString albumName = QString::fromStdString(album->getName());

        connect(albumButton, &QPushButton::clicked, this, [this, albumId, albumName, showSongs]() {
            showSongs(albumName, listenerManager->getAlbumSongs(albumId));
        });

        albumsContainerLayout->addWidget(albumButton);
    }

    albumsContainerLayout->addStretch();
    albumsScrollArea->setWidget(albumsContainer);
    leftLayout->addWidget(albumsScrollArea);

    rootLayout->addLayout(leftLayout, 1);
    rootLayout->addLayout(rightLayout, 2);

    dialog.exec();
}


void ListenerWindow::onLogoutClicked()
{
    emit logoutRequested();
    this->close();
}
