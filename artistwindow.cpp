#include "artistwindow.h"
#include "ui_artistwindow.h"

ArtistWindow::ArtistWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ArtistWindow)
{
    ui->setupUi(this);
}

ArtistWindow::~ArtistWindow()
{
    delete ui;
}
