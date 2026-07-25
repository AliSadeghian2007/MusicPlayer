#include "listenerwindow.h"
#include "ui_listenerwindow.h"


#include "listenermanager.h"
#include "listener.h"
#include "playlist.h"
#include "song.h"


#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QLayoutItem>
#include <vector>
#include <string>


ListenerWindow::ListenerWindow(ListenerManager* listenerManager,
                               Listener* listener,
                               QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ListenerWindow)
    , listenerManager(listenerManager)
    , currentListener(listener)
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


    std::vector<Playlist*> userPlaylists = listenerManager->getPlaylistsByUserId(listenerId);

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


    if (selectedPlaylistId == playlistId && selectedIsFavorites == isFavorites)
    {
        openButton->setText("Selected");
        openButton->setEnabled(false);
        openButton->setStyleSheet("background-color: #dcdcdc; color: #888888; border-radius: 5px; padding: 4px 10px;");
    }
    else
    {
        openButton->setText("Open");
        openButton->setStyleSheet("background-color: #eff8e8; color: #252525; border: 1px solid #727272; border-radius: 5px; padding: 4px 10px;");
    }


    connect(openButton, &QPushButton::clicked, this, [this, playlistId, isFavorites]() {
        this->setSelectedPlaylist(playlistId, isFavorites);
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


void ListenerWindow::onExploreClicked()
{

    QMessageBox::information(this, "Explore", "Explore feature will be connected to Search/Music window soon.");
}


void ListenerWindow::onLogoutClicked()
{

    this->close();
}
