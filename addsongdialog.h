#ifndef ADDSONGDIALOG_H
#define ADDSONGDIALOG_H

#include <QDialog>
#include <string>
#include <vector>
#include "album.h"

namespace Ui {
class AddSongDialog;
}

class AddSongDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSongDialog(QWidget *parent = nullptr);
    ~AddSongDialog();


    void populateAlbums(const std::vector<Album*>& albums);


    std::string getSongName() const;
    std::string getFilePath() const;
    std::string getGenre() const;
    int getReleaseYear() const;
    std::string getCoverPath() const;
    int getSelectedAlbumId() const;


    void setSongData(const std::string& name, const std::string& filePath,
                     const std::string& genre, int year, const std::string& coverPath, int albumId);

private slots:
    void onBrowseFileClicked();
    void onBrowseCoverClicked();
    void onAccept();

private:

    void updateCoverPreview(const QString &path);

    Ui::AddSongDialog *ui;
};

#endif // ADDSONGDIALOG_H