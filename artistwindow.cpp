#include "artistwindow.h"
#include "ui_artistwindow.h"
#include "artistmanager.h"
#include "artist.h"
#include "album.h"
<<<<<<< HEAD
#include "addalbumdialog.h"
#include "addsongdialog.h"

#include <QPushButton>
#include <QToolButton>
#include <QMessageBox>
#include <QLayoutItem>
=======
#include "song.h"
#include <QPushButton>
#include <QDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>


#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QPixmap>
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82

ArtistWindow::ArtistWindow(ArtistManager *artistManager,
                           Artist *artist,
                           QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::ArtistWindow),
    artistManager(artistManager),
    artist(artist),
<<<<<<< HEAD
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

=======
    albumsContainer(nullptr),
    albumsLayout(nullptr)
{
    ui->setupUi(this);

    albumsContainer = new QWidget(this);
    albumsLayout = new QVBoxLayout(albumsContainer);
    albumsLayout->setAlignment(Qt::AlignTop);
    albumsLayout->setSpacing(12);
    albumsLayout->setContentsMargins(12, 12, 12, 12);

    ui->albumsScrollArea->setWidget(albumsContainer);
    ui->albumsScrollArea->setWidgetResizable(true);

    connect(ui->addAlbumButton, &QPushButton::clicked, this, &ArtistWindow::onAddAlbumClicked);
    connect(ui->addSongButton, &QPushButton::clicked, this, &ArtistWindow::onAddSongClicked);
    connect(ui->editAlbumButton, &QPushButton::clicked, this, &ArtistWindow::onEditClicked);
    connect(ui->deleteAlbumButton, &QPushButton::clicked, this, &ArtistWindow::onDeleteClicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &ArtistWindow::onLogoutClicked);

    if (artist != nullptr)
    {
        ui->welcomeLabel->setText(QString::fromStdString(artist->getBiography()));

        QString photoPath = QString::fromStdString(artist->getProfilePhotoPath());
        if (!photoPath.isEmpty())
        {
            QPixmap pixmap(photoPath);
            if (!pixmap.isNull())
            {
                ui->profilePhotoLabel->setPixmap(pixmap.scaled(ui->profilePhotoLabel->size(),
                                                              Qt::KeepAspectRatioByExpanding,
                                                              Qt::SmoothTransformation));
            }
        }
    }

>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
    refreshAlbums();
}

ArtistWindow::~ArtistWindow()
{
    delete ui;
}

void ArtistWindow::clearAlbumsLayout()
{
<<<<<<< HEAD
    QLayoutItem *item = nullptr;

    while ((item = ui->albumsContainerLayout->takeAt(0)) != nullptr)
    {
        QWidget *widget = item->widget();

        if (widget != nullptr)
        {
            widget->deleteLater();
        }

        delete item;
=======
    QLayoutItem *child;
    while ((child = albumsLayout->takeAt(0)) != nullptr)
    {
        QWidget *w = child->widget();
        if (w != nullptr)
        {
            delete w;
        }
        delete child;
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
    }
}

void ArtistWindow::refreshAlbums()
{
<<<<<<< HEAD
    if (artistManager == nullptr || artist == nullptr)
=======
    clearAlbumsLayout();

    if (artist == nullptr || artistManager == nullptr)
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
    {
        return;
    }

<<<<<<< HEAD
    clearAlbumsLayout();

    std::vector<Album *> albums = artistManager->getAlbums(artist->getId());

    if (albums.empty())
    {
        ui->emptyAlbumsLabel->show();
        return;
    }

    ui->emptyAlbumsLabel->hide();

=======
    std::vector<Album*> albums = artistManager->getAlbums(artist->getId());

    if (albums.empty())
    {
        QLabel *emptyLabel = new QLabel("No albums have been added yet.", albumsContainer);
        emptyLabel->setAlignment(Qt::AlignCenter);
        albumsLayout->addWidget(emptyLabel);
        return;
    }

>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
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

<<<<<<< HEAD
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


=======
    QWidget *card = new QWidget(albumsContainer);
    card->setStyleSheet("background: white; border-radius: 12px; padding: 10px;");

    QVBoxLayout *cardLayout = new QVBoxLayout(card);

    QLabel *nameLabel = new QLabel(QString::fromStdString(album->getName()), card);
    nameLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    QLabel *idLabel = new QLabel(QString("Album ID: %1").arg(album->getId()), card);

    QLabel *coverLabel = new QLabel(card);
    coverLabel->setFixedSize(160, 160);
    coverLabel->setAlignment(Qt::AlignCenter);

    QString coverPath = QString::fromStdString(album->getCoverPath());
    if (!coverPath.isEmpty())
    {
        QPixmap pixmap(coverPath);
        if (!pixmap.isNull())
        {
            coverLabel->setPixmap(pixmap.scaled(160, 160, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        }
        else
        {
            coverLabel->setText("No Image");
        }
    }
    else
    {
        coverLabel->setText("No Image");
    }

    cardLayout->addWidget(nameLabel);
    cardLayout->addWidget(idLabel);
    cardLayout->addWidget(coverLabel);

    albumsLayout->addWidget(card);
}

>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
void ArtistWindow::onAddAlbumClicked()
{
    if (artistManager == nullptr || artist == nullptr)
    {
        return;
    }

<<<<<<< HEAD
    AddAlbumDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted)
    {
        artistManager->createAlbum(
            dialog.getCoverPath(),
            artist->getId(),
            dialog.getAlbumName());

        refreshAlbums();
    }
=======
    bool ok = false;
    QString name = QInputDialog::getText(this, "Add Album", "Album name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.trimmed().isEmpty())
    {
        return;
    }

    QString coverPath = QFileDialog::getOpenFileName(this, "Select Album Cover", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!ok)
    {
        return;
    }

    artistManager->createAlbum(coverPath.toStdString(), artist->getId(), name.toStdString());
    refreshAlbums();
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
}

void ArtistWindow::onAddSongClicked()
{
    if (artistManager == nullptr || artist == nullptr)
    {
<<<<<<< HEAD
        return;
    }

    AddSongDialog dialog(this);

    std::vector<Album *> albums = artistManager->getAlbums(artist->getId());
    dialog.populateAlbums(albums);
=======
        QMessageBox::warning(this, "Add Song", "Artist manager is not available.");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Add Song");
    dialog.setMinimumWidth(420);

    QFormLayout *formLayout = new QFormLayout(&dialog);

    QLineEdit *nameEdit = new QLineEdit(&dialog);

    QLineEdit *fileEdit = new QLineEdit(&dialog);
    fileEdit->setReadOnly(true);

    QPushButton *browseFileButton = new QPushButton("Browse...", &dialog);

    QWidget *fileWidget = new QWidget(&dialog);
    QHBoxLayout *fileLayout = new QHBoxLayout(fileWidget);
    fileLayout->setContentsMargins(0, 0, 0, 0);
    fileLayout->addWidget(fileEdit);
    fileLayout->addWidget(browseFileButton);

    QLineEdit *genreEdit = new QLineEdit(&dialog);

    QSpinBox *yearSpin = new QSpinBox(&dialog);
    yearSpin->setRange(1900, 2100);
    yearSpin->setValue(2026);

    QLineEdit *coverEdit = new QLineEdit(&dialog);
    coverEdit->setReadOnly(true);

    QPushButton *browseCoverButton = new QPushButton("Browse...", &dialog);

    QWidget *coverWidget = new QWidget(&dialog);
    QHBoxLayout *coverLayout = new QHBoxLayout(coverWidget);
    coverLayout->setContentsMargins(0, 0, 0, 0);
    coverLayout->addWidget(coverEdit);
    coverLayout->addWidget(browseCoverButton);

    QComboBox *albumCombo = new QComboBox(&dialog);
    albumCombo->addItem("Single", 0);

    std::vector<Album *> albums = artistManager->getAlbums(artist->getId());
    for (int i = 0; i < static_cast<int>(albums.size()); ++i)
    {
        Album *album = albums[i];
        if (album != nullptr)
        {
            QString itemText = QString::fromStdString(album->getName());
            albumCombo->addItem(itemText, album->getId());
        }
    }

    formLayout->addRow("Song Name:", nameEdit);
    formLayout->addRow("Audio File:", fileWidget);
    formLayout->addRow("Genre:", genreEdit);
    formLayout->addRow("Release Year:", yearSpin);
    formLayout->addRow("Cover Image:", coverWidget);
    formLayout->addRow("Album:", albumCombo);

    QDialogButtonBox *buttonBox =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);

    formLayout->addRow(buttonBox);

    connect(browseFileButton, &QPushButton::clicked, &dialog, [fileEdit, &dialog]()
            {
                QString fileName = QFileDialog::getOpenFileName(
                    &dialog,
                    "Select Audio File",
                    "",
                    "Audio Files (*.mp3 *.wav *.flac *.aac);;All Files (*)");

                if (!fileName.isEmpty())
                {
                    fileEdit->setText(fileName);
                }
            });

    connect(browseCoverButton, &QPushButton::clicked, &dialog, [coverEdit, &dialog]()
            {
                QString coverPath = QFileDialog::getOpenFileName(
                    &dialog,
                    "Select Cover Image",
                    "",
                    "Images (*.png *.jpg *.jpeg *.bmp);;All Files (*)");

                if (!coverPath.isEmpty())
                {
                    coverEdit->setText(coverPath);
                }
            });

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, [&dialog]()
            {
                dialog.accept();
            });

    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, [&dialog]()
            {
                dialog.reject();
            });
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82

    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

<<<<<<< HEAD
    int albumId = dialog.getSelectedAlbumId();
=======
    QString name = nameEdit->text().trimmed();
    QString fileName = fileEdit->text().trimmed();
    QString genre = genreEdit->text().trimmed();
    QString coverPath = coverEdit->text().trimmed();
    int releaseYear = yearSpin->value();
    int albumId = albumCombo->currentData().toInt();

    if (name.isEmpty())
    {
        QMessageBox::warning(this, "Add Song", "Song name cannot be empty.");
        return;
    }

    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, "Add Song", "Audio file cannot be empty.");
        return;
    }

    if (genre.isEmpty())
    {
        QMessageBox::warning(this, "Add Song", "Genre cannot be empty.");
        return;
    }
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82

    artistManager->createSong(
        albumId,
        artist->getId(),
<<<<<<< HEAD
        dialog.getSongName(),
        dialog.getFilePath(),
        dialog.getGenre(),
        dialog.getReleaseYear(),
        dialog.getCoverPath());

=======
        name.toStdString(),
        fileName.toStdString(),
        genre.toStdString(),
        releaseYear,
        coverPath.toStdString());

    QMessageBox::information(this, "Add Song", "Song added successfully.");
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
    refreshAlbums();
}


void ArtistWindow::onEditClicked()
{
<<<<<<< HEAD
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
=======
    QMessageBox::information(this, "Edit", "Edit logic should be connected here.");
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
}

void ArtistWindow::onDeleteClicked()
{
<<<<<<< HEAD
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
=======
    QMessageBox::information(this, "Delete", "Delete logic should be connected here.");
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
}

void ArtistWindow::onLogoutClicked()
{
    emit logoutRequested();
<<<<<<< HEAD
    this->close();
=======
    close();
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
}
