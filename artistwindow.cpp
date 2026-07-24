#include "artistwindow.h"
#include "ui_artistwindow.h"
#include "artistmanager.h"
#include "artist.h"
#include "album.h"
#include "addalbumdialog.h"
#include "addsongdialog.h"

#include <QPushButton>
#include <QToolButton>
#include <QMessageBox>
#include <QLayoutItem>

ArtistWindow::ArtistWindow(ArtistManager *artistManager,
                           Artist *artist,
                           QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::ArtistWindow),
    artistManager(artistManager),
    artist(artist),
    currentSelectedAlbumId(-1)
{
    ui->setupUi(this);

    if (this->artist != nullptr)
    {
        ui->welcomeLabel->setText(
            "Welcome, " + QString::fromStdString(this->artist->getUserName()));
    }

    ui->editAlbumButton->setEnabled(false);
    ui->deleteAlbumButton->setEnabled(false);

    connect(ui->addAlbumButton, &QAbstractButton::clicked,
            this, &ArtistWindow::onAddAlbumClicked);

    connect(ui->addSongButton, &QAbstractButton::clicked,
            this, &ArtistWindow::onAddSongClicked);

    connect(ui->editAlbumButton, &QAbstractButton::clicked,
            this, &ArtistWindow::onEditClicked);

    connect(ui->deleteAlbumButton, &QAbstractButton::clicked,
            this, &ArtistWindow::onDeleteClicked);

    connect(ui->logoutButton, &QAbstractButton::clicked,
            this, &ArtistWindow::onLogoutClicked);

    refreshAlbums();
}

ArtistWindow::~ArtistWindow()
{
    delete ui;
}

void ArtistWindow::clearAlbumsLayout()
{
    QLayoutItem *item = nullptr;

    while ((item = ui->albumsContainerLayout->takeAt(0)) != nullptr)
    {
        QWidget *widget = item->widget();

        if (widget != nullptr)
        {
            widget->deleteLater();
        }

        delete item;
    }
}

void ArtistWindow::refreshAlbums()
{
    if (artistManager == nullptr || artist == nullptr)
    {
        return;
    }

    clearAlbumsLayout();

    std::vector<Album *> albums = artistManager->getAlbums(artist->getId());

    if (albums.empty())
    {
        ui->emptyAlbumsLabel->show();
        return;
    }

    ui->emptyAlbumsLabel->hide();

    for (int i = 0; i < static_cast<int>(albums.size()); ++i)
    {
        addAlbumWidget(albums[i]);
    }
}

void ArtistWindow::addAlbumWidget(Album *album)
{
    if (album == nullptr)
    {
        return;
    }

    QPushButton *card = new QPushButton(ui->albumsContainerWidget);
    card->setCheckable(true);
    card->setText(QString::fromStdString(album->getName()));

    connect(card, &QPushButton::clicked, this, [this, album, card]()
            {
                currentSelectedAlbumId = album->getId();
                ui->editAlbumButton->setEnabled(true);
                ui->deleteAlbumButton->setEnabled(true);

                QList<QPushButton *> buttons =
                    ui->albumsContainerWidget->findChildren<QPushButton *>();

                for (int i = 0; i < buttons.size(); ++i)
                {
                    if (buttons[i] != card)
                    {
                        buttons[i]->setChecked(false);
                    }
                }

                card->setChecked(true);
            });

    ui->albumsContainerLayout->addWidget(card);
}


void ArtistWindow::onAddAlbumClicked()
{
    if (artistManager == nullptr || artist == nullptr)
    {
        return;
    }

    AddAlbumDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted)
    {
        artistManager->createAlbum(
            dialog.getCoverPath(),
            artist->getId(),
            dialog.getAlbumName());

        refreshAlbums();
    }
}

void ArtistWindow::onAddSongClicked()
{
    if (artistManager == nullptr || artist == nullptr)
    {
        return;
    }

    AddSongDialog dialog(this);

    std::vector<Album *> albums = artistManager->getAlbums(artist->getId());
    dialog.populateAlbums(albums);

    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    int albumId = dialog.getSelectedAlbumId();

    artistManager->createSong(
        albumId,
        artist->getId(),
        dialog.getSongName(),
        dialog.getFilePath(),
        dialog.getGenre(),
        dialog.getReleaseYear(),
        dialog.getCoverPath());

    refreshAlbums();
}


void ArtistWindow::onEditClicked()
{
    if (artistManager == nullptr || artist == nullptr)
    {
        return;
    }

    if (currentSelectedAlbumId == -1)
    {
        QMessageBox::warning(this, "Edit Album", "Please select an album first.");
        return;
    }

    std::vector<Album *> albums = artistManager->getAlbums(artist->getId());
    Album *selectedAlbum = nullptr;

    for (int i = 0; i < static_cast<int>(albums.size()); ++i)
    {
        if (albums[i] != nullptr && albums[i]->getId() == currentSelectedAlbumId)
        {
            selectedAlbum = albums[i];
            break;
        }
    }

    if (selectedAlbum == nullptr)
    {
        QMessageBox::warning(this, "Edit Album", "Selected album not found.");
        return;
    }

    AddAlbumDialog dialog(this);
    dialog.setAlbumData(selectedAlbum->getName(), selectedAlbum->getCoverPath());

    if (dialog.exec() == QDialog::Accepted)
    {
        bool success = artistManager->editAlbum(
            artist->getId(),
            currentSelectedAlbumId,
            dialog.getAlbumName(),
            dialog.getCoverPath());

        if (success)
        {
            refreshAlbums();
        }
        else
        {
            QMessageBox::critical(this, "Edit Album", "Failed to edit album.");
        }
    }
}

void ArtistWindow::onDeleteClicked()
{
    if (artistManager == nullptr || artist == nullptr)
    {
        return;
    }

    if (currentSelectedAlbumId == -1)
    {
        QMessageBox::warning(this, "Delete Album", "Please select an album first.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        "Delete Album",
        "Are you sure you want to delete this album?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No)
    {
        return;
    }

    bool success = artistManager->deleteAlbum(artist->getId(), currentSelectedAlbumId);

    if (success)
    {
        currentSelectedAlbumId = -1;
        ui->editAlbumButton->setEnabled(false);
        ui->deleteAlbumButton->setEnabled(false);
        refreshAlbums();
    }
    else
    {
        QMessageBox::critical(this, "Delete Album", "Failed to delete album.");
    }
}

void ArtistWindow::onLogoutClicked()
{
    emit logoutRequested();
    this->close();
}
