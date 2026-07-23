#include "listenerwindow.h"
#include "ui_listenerwindow.h"

ListenerWindow::ListenerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ListenerWindow)
{
    ui->setupUi(this);
}

ListenerWindow::~ListenerWindow()
{
    delete ui;
}
