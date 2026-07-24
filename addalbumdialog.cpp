#include "addalbumdialog.h"
#include "ui_addalbumdialog.h"
#include <QFileDialog>
#include <QMessageBox>

AddAlbumDialog::AddAlbumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAlbumDialog)
{
    ui->setupUi(this);


    connect(ui->pushButtonBrowse, &QPushButton::clicked, this, &AddAlbumDialog::onBrowseClicked);


    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddAlbumDialog::onAccept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

AddAlbumDialog::~AddAlbumDialog()
{
    delete ui;
}

void AddAlbumDialog::onBrowseClicked()
{

    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Album Cover",
        QString(),
        "Images (*.png *.jpg *.jpeg *.bmp)"
        );


    if (!filePath.isEmpty())
    {
        ui->lineEditCoverPath->setText(filePath);
    }
}

void AddAlbumDialog::onAccept()
{

    QString name = ui->lineEditName->text().trimmed();
    QString coverPath = ui->lineEditCoverPath->text().trimmed();


    if (name.isEmpty())
    {
        QMessageBox::warning(this, "Validation Error", "Album name cannot be empty.");
        return;
    }


    if (coverPath.isEmpty())
    {
        QMessageBox::warning(this, "Validation Error", "Cover path cannot be empty.");
        return;
    }


    accept();
}

std::string AddAlbumDialog::getAlbumName() const
{
    return ui->lineEditName->text().trimmed().toStdString();
}

std::string AddAlbumDialog::getCoverPath() const
{
    return ui->lineEditCoverPath->text().trimmed().toStdString();
}

void AddAlbumDialog::setAlbumData(const std::string& name, const std::string& coverPath)
{

    ui->lineEditName->setText(QString::fromStdString(name));
    ui->lineEditCoverPath->setText(QString::fromStdString(coverPath));
    this->setWindowTitle("Edit Album");
}
