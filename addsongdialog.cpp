#include "addsongdialog.h"
#include "ui_addsongdialog.h"
#include <QFileDialog>
#include <QMessageBox>

AddSongDialog::AddSongDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSongDialog)
{
    ui->setupUi(this);


    ui->spinBoxYear->setRange(1900, 2100);
    ui->spinBoxYear->setValue(2026);


    connect(ui->pushButtonBrowseFile, &QPushButton::clicked, this, &AddSongDialog::onBrowseFileClicked);
    connect(ui->pushButtonBrowseCover, &QPushButton::clicked, this, &AddSongDialog::onBrowseCoverClicked);

    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddSongDialog::onAccept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

AddSongDialog::~AddSongDialog()
{
    delete ui;
}

void AddSongDialog::populateAlbums(const std::vector<Album *> &albums)
{
    ui->comboBoxAlbum->clear();

    if (albums.empty())
    {
        ui->comboBoxAlbum->addItem("Singles", -1);
        return;
    }

    for (int i = 0; i < static_cast<int>(albums.size()); ++i)
    {
        ui->comboBoxAlbum->addItem(
            QString::fromStdString(albums[i]->getName()),
            albums[i]->getId());
    }
}

void AddSongDialog::onBrowseFileClicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Audio File",
        QString(),
        "Audio Files (*.mp3 *.wav *.flac *.aac)"
        );
    if (!filePath.isEmpty())
    {
        ui->lineEditFilePath->setText(filePath);
    }
}

void AddSongDialog::onBrowseCoverClicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Song Cover",
        QString(),
        "Images (*.png *.jpg *.jpeg *.bmp)"
        );
    if (!filePath.isEmpty())
    {
        ui->lineEditCoverPath->setText(filePath);
    }
}

void AddSongDialog::onAccept()
{
    if (ui->comboBoxAlbum->currentIndex() == -1)
    {
        QMessageBox::warning(this, "Validation Error", "Please select an album.");
        return;
    }
    if (ui->lineEditSongName->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Validation Error", "Song name cannot be empty.");
        return;
    }
    if (ui->lineEditFilePath->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Validation Error", "Song file path cannot be empty.");
        return;
    }
    if (ui->lineEditGenre->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Validation Error", "Genre cannot be empty.");
        return;
    }
    if (ui->lineEditCoverPath->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Validation Error", "Song cover path cannot be empty.");
        return;
    }

    accept();
}

std::string AddSongDialog::getSongName() const { return ui->lineEditSongName->text().trimmed().toStdString(); }
std::string AddSongDialog::getFilePath() const { return ui->lineEditFilePath->text().trimmed().toStdString(); }
std::string AddSongDialog::getGenre() const { return ui->lineEditGenre->text().trimmed().toStdString(); }
int AddSongDialog::getReleaseYear() const { return ui->spinBoxYear->value(); }
std::string AddSongDialog::getCoverPath() const { return ui->lineEditCoverPath->text().trimmed().toStdString(); }
int AddSongDialog::getSelectedAlbumId() const { return ui->comboBoxAlbum->currentData().toInt(); }

void AddSongDialog::setSongData(const std::string& name, const std::string& filePath,
                                const std::string& genre, int year, const std::string& coverPath, int albumId)
{
    ui->lineEditSongName->setText(QString::fromStdString(name));
    ui->lineEditFilePath->setText(QString::fromStdString(filePath));
    ui->lineEditGenre->setText(QString::fromStdString(genre));
    ui->spinBoxYear->setValue(year);
    ui->lineEditCoverPath->setText(QString::fromStdString(coverPath));


    for (int i = 0; i < ui->comboBoxAlbum->count(); ++i)
    {
        if (ui->comboBoxAlbum->itemData(i).toInt() == albumId)
        {
            ui->comboBoxAlbum->setCurrentIndex(i);
            break;
        }
    }
    this->setWindowTitle("Edit Song");
}
