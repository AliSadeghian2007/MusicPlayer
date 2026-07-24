#ifndef ADDALBUMDIALOG_H
#define ADDALBUMDIALOG_H

#include <QDialog>
#include <string>

namespace Ui {
class AddAlbumDialog;
}

class AddAlbumDialog : public QDialog
{
    Q_OBJECT

public:

    explicit AddAlbumDialog(QWidget *parent = nullptr);
    ~AddAlbumDialog();


    std::string getAlbumName() const;


    std::string getCoverPath() const;


    void setAlbumData(const std::string& name, const std::string& coverPath);

private slots:

    void onBrowseClicked();


    void onAccept();

private:
    Ui::AddAlbumDialog *ui;
};

#endif // ADDALBUMDIALOG_H
