#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ArtistWindow;
}

class ArtistWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArtistWindow(QWidget *parent = nullptr);
    ~ArtistWindow();

private:
    Ui::ArtistWindow *ui;
};

#endif // ARTISTWINDOW_H
