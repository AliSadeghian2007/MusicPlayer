#include "artistwindow.h"
#include "ui_artistwindow.h"
#include "artistmanager.h"
#include "sharedfeaturesmanager.h"
#include "artist.h"
#include "album.h"
#include "song.h"
#include "addalbumdialog.h"
#include "addsongdialog.h"

#include <QPushButton>
#include <QToolButton>
#include <QMessageBox>
#include <QLayoutItem>
#include <QFrame>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPixmap>
#include <QIcon>
#include <QLineEdit>
#include <QComboBox>
#include <algorithm>

ArtistWindow::ArtistWindow(ArtistManager *artistManager,
                           Artist *artist,
                           SharedFeaturesManager *sharedFeaturesManager,
                           QWidget *parent)
    : QMainWindow(parent),
    currentSelectedAlbumId(-1),
    ui(new Ui::ArtistWindow),
    artistManager(artistManager),
    artist(artist),
    sharedFeaturesManager(sharedFeaturesManager)
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

    buildSongsSection();

    refreshAlbums();
    refreshSongs();
}

ArtistWindow::~ArtistWindow()
{
    delete ui;
}

void ArtistWindow::buildSongsSection()
{

    songsFrame = new QFrame(ui->centralwidget);
    songsFrame->setObjectName("songsFrame");
    songsFrame->setStyleSheet(
        "QFrame#songsFrame {"
        "  background-color: #ffffff;"
        "  border: 1px solid #888888;"
        "  border-radius: 15px;"
        "}");

    QVBoxLayout *songsFrameLayout = new QVBoxLayout(songsFrame);
    songsFrameLayout->setContentsMargins(10, 8, 10, 8);
    songsFrameLayout->setSpacing(6);

    songsTitleLabel = new QLabel("Select an album (or Singles) to view its songs.", songsFrame);
    songsTitleLabel->setStyleSheet("font-size: 14px; font-weight: 600; color: #242424; background: transparent; border: none;");
    songsFrameLayout->addWidget(songsTitleLabel);

    QHBoxLayout *songsFilterLayout = new QHBoxLayout();
    songsFilterLayout->setSpacing(8);

    songsSearchEdit = new QLineEdit(songsFrame);
    songsSearchEdit->setPlaceholderText("Search songs...");
    songsSearchEdit->setClearButtonEnabled(true);
    songsSearchEdit->setStyleSheet(
        "QLineEdit {"
        "  padding: 5px 8px;"
        "  border: 1px solid #cccccc;"
        "  border-radius: 6px;"
        "  background-color: #ffffff;"
        "  color: #242424;"
        "  font-size: 12px;"
        "}");

    genreFilterCombo = new QComboBox(songsFrame);
    genreFilterCombo->addItem("All Genres");
    genreFilterCombo->setStyleSheet(
        "QComboBox {"
        "  padding: 4px 8px;"
        "  border: 1px solid #cccccc;"
        "  border-radius: 6px;"
        "  background-color: #ffffff;"
        "  color: #242424;"
        "  font-size: 12px;"
        "}");

    connect(songsSearchEdit, &QLineEdit::textChanged, this, [this](const QString &)
            {
                refreshSongs();
            });

    connect(genreFilterCombo, &QComboBox::currentTextChanged, this, [this](const QString &)
            {
                refreshSongs();
            });

    songsFilterLayout->addWidget(songsSearchEdit, 1);
    songsFilterLayout->addWidget(genreFilterCombo);
    songsFrameLayout->addLayout(songsFilterLayout);

    QScrollArea *songsScrollArea = new QScrollArea(songsFrame);
    songsScrollArea->setWidgetResizable(true);
    songsScrollArea->setFrameShape(QFrame::NoFrame);
    songsScrollArea->setStyleSheet("QScrollArea { background-color: transparent; border: none; }");

    songsContainerWidget = new QWidget();
    songsContainerWidget->setStyleSheet("background-color: transparent;");
    songsContainerLayout = new QVBoxLayout(songsContainerWidget);
    songsContainerLayout->setSpacing(6);
    songsContainerLayout->setContentsMargins(4, 4, 4, 4);

    emptySongsLabel = new QLabel("No songs here yet.", songsContainerWidget);
    emptySongsLabel->setStyleSheet("color: #777777; font-size: 13px; background: transparent; border: none;");
    emptySongsLabel->setAlignment(Qt::AlignCenter);
    songsContainerLayout->addWidget(emptySongsLabel);
    songsContainerLayout->addStretch();

    songsScrollArea->setWidget(songsContainerWidget);
    songsFrameLayout->addWidget(songsScrollArea);

    songsFrame->setMinimumHeight(180);


    int insertIndex = ui->mainVerticalLayout->indexOf(ui->albumsFrame) + 1;
    ui->mainVerticalLayout->insertWidget(insertIndex, songsFrame);
}

void ArtistWindow::clearAlbumsLayout()
{
    QLayoutItem *item = nullptr;

    while ((item = ui->albumsContainerLayout->takeAt(0)) != nullptr)
    {
        QWidget *widget = item->widget();

        if (widget != nullptr && widget != ui->emptyAlbumsLabel)
        {
            widget->deleteLater();
        }

        delete item;
    }
}

std::vector<Album *> ArtistWindow::sortedAlbums() const
{
    std::vector<Album *> albums = artistManager->getAlbums(artist->getId());

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

    std::vector<Album *> result;
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

std::vector<Song *> ArtistWindow::sortedSongs(std::vector<Song *> songs) const
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

    std::vector<Song *> result;
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

void ArtistWindow::refreshAlbums()
{
    if (artistManager == nullptr || artist == nullptr)
    {
        return;
    }

    clearAlbumsLayout();

    std::vector<Album *> albums = sortedAlbums();

    addAlbumWidget(SINGLES_ALBUM_ID, "Singles", std::string(), true);

    for (int i = 0; i < static_cast<int>(albums.size()); ++i)
    {
        if (albums[i] != nullptr)
        {
            addAlbumWidget(albums[i]->getId(), QString::fromStdString(albums[i]->getName()),
                           albums[i]->getCoverPath(), false);
        }
    }

    ui->emptyAlbumsLabel->hide();
}

void ArtistWindow::addAlbumWidget(int albumId, const QString &name, const std::string &coverPath, bool isSingles)
{
    QPushButton *card = new QPushButton(ui->albumsContainerWidget);
    card->setCheckable(true);
    card->setText(isSingles ? QString::fromUtf8("\xF0\x9F\x8E\xB5 ") + name : "  " + name);
    card->setCursor(Qt::PointingHandCursor);


    if (!isSingles)
    {
        QPixmap coverPixmap(QString::fromStdString(coverPath));

        if (!coverPixmap.isNull())
        {
            card->setIcon(QIcon(coverPixmap.scaled(
                40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            card->setIconSize(QSize(40, 40));
        }
    }


    card->setStyleSheet(
        "QPushButton {"
        "  text-align: left;"
        "  padding: 8px 10px;"
        "  background-color: #ffffff;"
        "  color: #242424;"
        "  border: 1px solid #d0d0d0;"
        "  border-radius: 8px;"
        "  font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #f2f2f2;"
        "}"
        "QPushButton:checked {"
        "  background-color: #eaf3e0;"
        "  border: 2px solid #6aa84f;"
        "  color: #1f3d0c;"
        "}");

    bool isCurrentlySelected = isSingles ? singlesSelected
                                         : (!singlesSelected && currentSelectedAlbumId == albumId);
    card->setChecked(isCurrentlySelected);

    connect(card, &QPushButton::clicked, this, [this, albumId, isSingles, card]()
            {
                singlesSelected = isSingles;
                currentSelectedAlbumId = isSingles ? -1 : albumId;

                ui->editAlbumButton->setEnabled(!isSingles);
                ui->deleteAlbumButton->setEnabled(!isSingles);

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

                refreshSongs();
            });

    ui->albumsContainerLayout->addWidget(card);
}


void ArtistWindow::clearSongsLayout()
{
    QLayoutItem *item = nullptr;

    while ((item = songsContainerLayout->takeAt(0)) != nullptr)
    {
        QWidget *widget = item->widget();

        if (widget != nullptr && widget != emptySongsLabel)
        {
            widget->deleteLater();
        }

        delete item;
    }
}

void ArtistWindow::populateGenreFilter(const std::vector<Song*> &songs)
{
    QString previousSelection = genreFilterCombo->currentText();

    if (previousSelection.isEmpty())
    {
        previousSelection = "All Genres";
    }

    genreFilterCombo->blockSignals(true);
    genreFilterCombo->clear();
    genreFilterCombo->addItem("All Genres");

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
        genreFilterCombo->addItem(genres[i]);
    }

    int previousIndex = genreFilterCombo->findText(previousSelection);
    genreFilterCombo->setCurrentIndex(previousIndex >= 0 ? previousIndex : 0);
    genreFilterCombo->blockSignals(false);
}

std::vector<Song*> ArtistWindow::applySongFilter(std::vector<Song*> songs) const
{
    QString searchText = songsSearchEdit->text().trimmed();
    QString genre = genreFilterCombo->currentText();

    std::vector<Song*> result;

    for (size_t i = 0; i < songs.size(); ++i)
    {
        if (songs[i] == nullptr)
        {
            continue;
        }

        bool matchesSearch = searchText.isEmpty() ||
                             QString::fromStdString(songs[i]->getName()).contains(searchText, Qt::CaseInsensitive);

        bool matchesGenre = genre.isEmpty() || genre == "All Genres" ||
                            QString::fromStdString(songs[i]->getGenre()) == genre;

        if (matchesSearch && matchesGenre)
        {
            result.push_back(songs[i]);
        }
    }

    return result;
}

void ArtistWindow::refreshSongs()
{
    if (artistManager == nullptr || artist == nullptr)
    {
        return;
    }

    clearSongsLayout();


    songsContainerLayout->addStretch();

    std::vector<Song *> songs;

    if (singlesSelected)
    {
        songsTitleLabel->setText("Songs in Singles");
        songs = artistManager->getSingles(artist->getId());
    }
    else if (currentSelectedAlbumId != -1)
    {
        std::vector<Album *> albums = artistManager->getAlbums(artist->getId());
        QString albumName;

        for (size_t i = 0; i < albums.size(); ++i)
        {
            if (albums[i] != nullptr && albums[i]->getId() == currentSelectedAlbumId)
            {
                albumName = QString::fromStdString(albums[i]->getName());
                break;
            }
        }

        songsTitleLabel->setText("Songs in " + albumName);
        songs = artistManager->getAlbumSongs(artist->getId(), currentSelectedAlbumId);
    }
    else
    {
        songsTitleLabel->setText("Select an album (or Singles) to view its songs.");
        songsContainerLayout->insertWidget(0, emptySongsLabel);
        emptySongsLabel->show();
        return;
    }

    populateGenreFilter(songs);
    songs = applySongFilter(songs);
    songs = sortedSongs(songs);

    if (songs.empty())
    {
        songsContainerLayout->insertWidget(0, emptySongsLabel);
        emptySongsLabel->show();
        return;
    }

    emptySongsLabel->hide();

    for (int i = 0; i < static_cast<int>(songs.size()); ++i)
    {
        addSongWidget(songs[i]);
    }
}

void ArtistWindow::addSongWidget(Song *song)
{
    if (song == nullptr)
    {
        return;
    }

    QFrame *row = new QFrame(songsContainerWidget);
    row->setObjectName("songRowFrame");
    row->setStyleSheet(
        "QFrame#songRowFrame {"
        "  background-color: #f8f8f8;"
        "  border: 1px solid #e0e0e0;"
        "  border-radius: 8px;"
        "}");

    QHBoxLayout *rowLayout = new QHBoxLayout(row);
    rowLayout->setContentsMargins(12, 6, 12, 6);
    rowLayout->setSpacing(10);

    QLabel *coverLabel = new QLabel(row);
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

    QLabel *nameLabel = new QLabel(QString::fromStdString(song->getName()), row);
    nameLabel->setStyleSheet("font-size: 13px; font-weight: bold; color: #333333; background: transparent; border: none;");

    QLabel *infoLabel = new QLabel(
        QString::fromStdString(song->getGenre()) + " \xC2\xB7 " + QString::number(song->getReleaseYear()),
        row);
    infoLabel->setStyleSheet("font-size: 12px; color: #777777; background: transparent; border: none;");

    QPushButton *editButton = new QPushButton("Edit", row);
    editButton->setCursor(Qt::PointingHandCursor);
    editButton->setStyleSheet("background-color: #eff8e8; color: #252525; border: 1px solid #727272; border-radius: 5px; padding: 4px 10px;");

    QPushButton *deleteButton = new QPushButton("Delete", row);
    deleteButton->setCursor(Qt::PointingHandCursor);
    deleteButton->setStyleSheet("background-color: #fdecea; color: #b3261e; border: 1px solid #b3261e; border-radius: 5px; padding: 4px 10px;");

    int songId = song->get_Id();

    connect(editButton, &QPushButton::clicked, this, [this, songId]()
            {
                onEditSong(songId);
            });

    connect(deleteButton, &QPushButton::clicked, this, [this, songId]()
            {
                onDeleteSong(songId);
            });

    rowLayout->addWidget(coverLabel);
    rowLayout->addWidget(nameLabel);
    rowLayout->addWidget(infoLabel);
    rowLayout->addStretch();
    rowLayout->addWidget(editButton);
    rowLayout->addWidget(deleteButton);

    songsContainerLayout->insertWidget(songsContainerLayout->count() - 1, row);
}

void ArtistWindow::onEditSong(int songId)
{
    if (artistManager == nullptr || artist == nullptr)
    {
        return;
    }

    std::vector<Song *> songs;

    if (singlesSelected)
    {
        songs = artistManager->getSingles(artist->getId());
    }
    else if (currentSelectedAlbumId != -1)
    {
        songs = artistManager->getAlbumSongs(artist->getId(), currentSelectedAlbumId);
    }

    Song *targetSong = nullptr;

    for (size_t i = 0; i < songs.size(); ++i)
    {
        if (songs[i] != nullptr && songs[i]->get_Id() == songId)
        {
            targetSong = songs[i];
            break;
        }
    }

    if (targetSong == nullptr)
    {
        QMessageBox::warning(this, "Edit Song", "Selected song was not found.");
        return;
    }

    AddSongDialog dialog(this);

    std::vector<Album *> albums = artistManager->getAlbums(artist->getId());
    dialog.populateAlbums(albums);

    dialog.setSongData(
        targetSong->getName(),
        targetSong->getFileName(),
        targetSong->getGenre(),
        targetSong->getReleaseYear(),
        targetSong->getCoverPath(),
        targetSong->getAlbumId());

    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    bool success = artistManager->editSong(
        artist->getId(),
        songId,
        dialog.getSongName(),
        dialog.getFilePath(),
        dialog.getGenre(),
        dialog.getReleaseYear(),
        dialog.getCoverPath(),
        dialog.getSelectedAlbumId());

    if (success)
    {
        refreshAlbums();
        refreshSongs();
    }
    else
    {
        QMessageBox::critical(this, "Edit Song", "Failed to edit song.");
    }
}

void ArtistWindow::onDeleteSong(int songId)
{
    if (artistManager == nullptr || artist == nullptr)
    {
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Delete Song",
        "Are you sure you want to delete this song?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes)
    {
        return;
    }

    bool success = artistManager->deleteSong(artist->getId(), songId);

    if (success)
    {
        refreshAlbums();
        refreshSongs();
    }
    else
    {
        QMessageBox::critical(this, "Delete Song", "Failed to delete song.");
    }
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
    refreshSongs();
}


void ArtistWindow::onEditClicked()
{
    if (artistManager == nullptr || artist == nullptr)
    {
        return;
    }

    if (currentSelectedAlbumId == -1 || singlesSelected)
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
            refreshSongs();
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

    if (currentSelectedAlbumId == -1 || singlesSelected)
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
        singlesSelected = false;
        ui->editAlbumButton->setEnabled(false);
        ui->deleteAlbumButton->setEnabled(false);
        refreshAlbums();
        refreshSongs();
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
