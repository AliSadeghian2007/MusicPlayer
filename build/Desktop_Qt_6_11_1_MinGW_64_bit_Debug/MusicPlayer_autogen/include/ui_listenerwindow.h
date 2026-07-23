/********************************************************************************
** Form generated from reading UI file 'listenerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTENERWINDOW_H
#define UI_LISTENERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListenerWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ListenerWindow)
    {
        if (ListenerWindow->objectName().isEmpty())
            ListenerWindow->setObjectName("ListenerWindow");
        ListenerWindow->resize(800, 600);
        centralwidget = new QWidget(ListenerWindow);
        centralwidget->setObjectName("centralwidget");
        ListenerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ListenerWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        ListenerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ListenerWindow);
        statusbar->setObjectName("statusbar");
        ListenerWindow->setStatusBar(statusbar);

        retranslateUi(ListenerWindow);

        QMetaObject::connectSlotsByName(ListenerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ListenerWindow)
    {
        ListenerWindow->setWindowTitle(QCoreApplication::translate("ListenerWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListenerWindow: public Ui_ListenerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTENERWINDOW_H
