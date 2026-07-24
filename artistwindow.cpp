#include "artistwindow.h"
#include "ui_artistwindow.h"
#include "artistmanager.h"
#include "artist.h"
#include "album.h"
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

ArtistWindow::ArtistWindow(ArtistManager *artistManager,
                           Artist *artist,
                           QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::ArtistWindow),
    artistManager(artistManager),
    artist(artist),
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

    refreshAlbums();
}

ArtistWindow::~ArtistWindow()
{
    delete ui;
}

void ArtistWindow::clearAlbumsLayout()
{
    QLayoutItem *child;
    while ((child = albumsLayout->takeAt(0)) != nullptr)
    {
        QWidget *w = child->widget();
        if (w != nullptr)
        {
            delete w;
        }
        delete child;
    }
}

void ArtistWindow::refreshAlbums()
{
    clearAlbumsLayout();

    if (artist == nullptr || artistManager == nullptr)
    {
        return;
    }

    std::vector<Album*> albums = artistManager->getAlbums(artist->getId());

    if (albums.empty())
    {
        QLabel *emptyLabel = new QLabel("No albums have been added yet.", albumsContainer);
        emptyLabel->setAlignment(Qt::AlignCenter);
        albumsLayout->addWidget(emptyLabel);
        return;
    }

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

void ArtistWindow::onAddAlbumClicked()
{
    if (artistManager == nullptr || artist == nullptr)
    {
        return;
    }

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
}

void ArtistWindow::onAddSongClicked()
{
    if (artistManager == nullptr || artist == nullptr)
    {
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

    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

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

    artistManager->createSong(
        albumId,
        artist->getId(),
        name.toStdString(),
        fileName.toStdString(),
        genre.toStdString(),
        releaseYear,
        coverPath.toStdString());

    QMessageBox::information(this, "Add Song", "Song added successfully.");
    refreshAlbums();
}


void ArtistWindow::onEditClicked()
{
    QMessageBox::information(this, "Edit", "Edit logic should be connected here.");
}

void ArtistWindow::onDeleteClicked()
{
    QMessageBox::information(this, "Delete", "Delete logic should be connected here.");
}

void ArtistWindow::onLogoutClicked()
{
    emit logoutRequested();
    close();
}
