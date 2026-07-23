/********************************************************************************
** Form generated from reading UI file 'artistwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARTISTWINDOW_H
#define UI_ARTISTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ArtistWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainVerticalLayout;
    QWidget *headerWidget;
    QHBoxLayout *headerLayout;
    QLabel *profilePhotoLabel;
    QLabel *welcomeLabel;
    QSpacerItem *headerHorizontalSpacer;
    QFrame *albumsFrame;
    QVBoxLayout *albumsFrameLayout;
    QScrollArea *albumsScrollArea;
    QWidget *albumsContainerWidget;
    QVBoxLayout *albumsContainerLayout;
    QLabel *emptyAlbumsLabel;
    QSpacerItem *albumsVerticalSpacer;
    QWidget *bottomBarWidget;
    QHBoxLayout *bottomBarLayout;
    QWidget *leftBalanceWidget;
    QSpacerItem *leftBottomSpacer;
    QWidget *albumActionsWidget;
    QHBoxLayout *albumActionsLayout;
    QToolButton *addAlbumButton;
    QToolButton *addSongButton;
    QToolButton *editAlbumButton;
    QToolButton *deleteAlbumButton;
    QSpacerItem *rightBottomSpacer;
    QToolButton *logoutButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ArtistWindow)
    {
        if (ArtistWindow->objectName().isEmpty())
            ArtistWindow->setObjectName("ArtistWindow");
        ArtistWindow->resize(900, 650);
        ArtistWindow->setMinimumSize(QSize(700, 500));
        ArtistWindow->setStyleSheet(QString::fromUtf8("QMainWindow#ArtistWindow {\n"
"    background-color: #f4f4f4;\n"
"}"));
        centralwidget = new QWidget(ArtistWindow);
        centralwidget->setObjectName("centralwidget");
        mainVerticalLayout = new QVBoxLayout(centralwidget);
        mainVerticalLayout->setSpacing(8);
        mainVerticalLayout->setObjectName("mainVerticalLayout");
        mainVerticalLayout->setContentsMargins(15, 10, 15, 10);
        headerWidget = new QWidget(centralwidget);
        headerWidget->setObjectName("headerWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(headerWidget->sizePolicy().hasHeightForWidth());
        headerWidget->setSizePolicy(sizePolicy);
        headerWidget->setMinimumSize(QSize(0, 80));
        headerWidget->setMaximumSize(QSize(16777215, 80));
        headerWidget->setStyleSheet(QString::fromUtf8("QWidget#headerWidget {\n"
"    background-color: transparent;\n"
"}"));
        headerLayout = new QHBoxLayout(headerWidget);
        headerLayout->setSpacing(12);
        headerLayout->setObjectName("headerLayout");
        headerLayout->setContentsMargins(10, 10, 10, 10);
        profilePhotoLabel = new QLabel(headerWidget);
        profilePhotoLabel->setObjectName("profilePhotoLabel");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(profilePhotoLabel->sizePolicy().hasHeightForWidth());
        profilePhotoLabel->setSizePolicy(sizePolicy1);
        profilePhotoLabel->setMinimumSize(QSize(60, 60));
        profilePhotoLabel->setMaximumSize(QSize(60, 60));
        profilePhotoLabel->setStyleSheet(QString::fromUtf8("QLabel#profilePhotoLabel {\n"
"    background-color: #d9d9d9;\n"
"    border: 1px solid #b0b0b0;\n"
"    border-radius: 30px;\n"
"}"));
        profilePhotoLabel->setScaledContents(true);
        profilePhotoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        headerLayout->addWidget(profilePhotoLabel);

        welcomeLabel = new QLabel(headerWidget);
        welcomeLabel->setObjectName("welcomeLabel");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(welcomeLabel->sizePolicy().hasHeightForWidth());
        welcomeLabel->setSizePolicy(sizePolicy2);
        welcomeLabel->setMinimumSize(QSize(220, 35));
        welcomeLabel->setStyleSheet(QString::fromUtf8("QLabel#welcomeLabel {\n"
"    color: #242424;\n"
"    font-size: 20px;\n"
"    font-weight: 600;\n"
"    background-color: transparent;\n"
"}"));
        welcomeLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        headerLayout->addWidget(welcomeLabel);

        headerHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(headerHorizontalSpacer);


        mainVerticalLayout->addWidget(headerWidget);

        albumsFrame = new QFrame(centralwidget);
        albumsFrame->setObjectName("albumsFrame");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(albumsFrame->sizePolicy().hasHeightForWidth());
        albumsFrame->setSizePolicy(sizePolicy3);
        albumsFrame->setMinimumSize(QSize(0, 300));
        albumsFrame->setStyleSheet(QString::fromUtf8("QFrame#albumsFrame {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #888888;\n"
"    border-radius: 15px;\n"
"}"));
        albumsFrame->setFrameShape(QFrame::Shape::NoFrame);
        albumsFrame->setFrameShadow(QFrame::Shadow::Plain);
        albumsFrameLayout = new QVBoxLayout(albumsFrame);
        albumsFrameLayout->setSpacing(0);
        albumsFrameLayout->setObjectName("albumsFrameLayout");
        albumsFrameLayout->setContentsMargins(8, 8, 8, 8);
        albumsScrollArea = new QScrollArea(albumsFrame);
        albumsScrollArea->setObjectName("albumsScrollArea");
        sizePolicy3.setHeightForWidth(albumsScrollArea->sizePolicy().hasHeightForWidth());
        albumsScrollArea->setSizePolicy(sizePolicy3);
        albumsScrollArea->setStyleSheet(QString::fromUtf8("QScrollArea#albumsScrollArea {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"QScrollArea#albumsScrollArea QWidget#qt_scrollarea_viewport {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QScrollArea#albumsScrollArea QScrollBar:vertical {\n"
"    background-color: #eeeeee;\n"
"    width: 10px;\n"
"    margin: 0px;\n"
"    border: none;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QScrollArea#albumsScrollArea QScrollBar::handle:vertical {\n"
"    background-color: #b5b5b5;\n"
"    min-height: 25px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QScrollArea#albumsScrollArea QScrollBar::handle:vertical:hover {\n"
"    background-color: #999999;\n"
"}\n"
"\n"
"QScrollArea#albumsScrollArea QScrollBar::add-line:vertical,\n"
"QScrollArea#albumsScrollArea QScrollBar::sub-line:vertical {\n"
"    width: 0px;\n"
"    height: 0px;\n"
"}\n"
"\n"
"QScrollArea#albumsScrollArea QScrollBar::add-page:vertical,\n"
"QScrollArea#albumsScrollArea QScrollBar::sub-page:vertical {\n"
"    background-color:"
                        " transparent;\n"
"}"));
        albumsScrollArea->setFrameShape(QFrame::Shape::NoFrame);
        albumsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        albumsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        albumsScrollArea->setWidgetResizable(true);
        albumsContainerWidget = new QWidget();
        albumsContainerWidget->setObjectName("albumsContainerWidget");
        albumsContainerWidget->setGeometry(QRect(0, 0, 848, 432));
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(albumsContainerWidget->sizePolicy().hasHeightForWidth());
        albumsContainerWidget->setSizePolicy(sizePolicy4);
        albumsContainerWidget->setStyleSheet(QString::fromUtf8("QWidget#albumsContainerWidget {\n"
"    background-color: transparent;\n"
"}"));
        albumsContainerLayout = new QVBoxLayout(albumsContainerWidget);
        albumsContainerLayout->setSpacing(8);
        albumsContainerLayout->setObjectName("albumsContainerLayout");
        albumsContainerLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        albumsContainerLayout->setContentsMargins(10, 10, 10, 10);
        emptyAlbumsLabel = new QLabel(albumsContainerWidget);
        emptyAlbumsLabel->setObjectName("emptyAlbumsLabel");
        sizePolicy4.setHeightForWidth(emptyAlbumsLabel->sizePolicy().hasHeightForWidth());
        emptyAlbumsLabel->setSizePolicy(sizePolicy4);
        emptyAlbumsLabel->setMinimumSize(QSize(0, 70));
        emptyAlbumsLabel->setStyleSheet(QString::fromUtf8("QLabel#emptyAlbumsLabel {\n"
"    color: #777777;\n"
"    font-size: 15px;\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}"));
        emptyAlbumsLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        emptyAlbumsLabel->setWordWrap(true);

        albumsContainerLayout->addWidget(emptyAlbumsLabel);

        albumsVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        albumsContainerLayout->addItem(albumsVerticalSpacer);

        albumsScrollArea->setWidget(albumsContainerWidget);

        albumsFrameLayout->addWidget(albumsScrollArea);


        mainVerticalLayout->addWidget(albumsFrame);

        bottomBarWidget = new QWidget(centralwidget);
        bottomBarWidget->setObjectName("bottomBarWidget");
        sizePolicy.setHeightForWidth(bottomBarWidget->sizePolicy().hasHeightForWidth());
        bottomBarWidget->setSizePolicy(sizePolicy);
        bottomBarWidget->setMinimumSize(QSize(0, 70));
        bottomBarWidget->setMaximumSize(QSize(16777215, 70));
        bottomBarWidget->setStyleSheet(QString::fromUtf8("QWidget#bottomBarWidget {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QWidget#bottomBarWidget QToolButton {\n"
"    background-color: #ffffff;\n"
"    color: #303030;\n"
"    border: 1px solid #c9c9c9;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-size: 12px;\n"
"}\n"
"\n"
"QWidget#bottomBarWidget QToolButton:hover {\n"
"    background-color: #eeeeee;\n"
"    border-color: #a5a5a5;\n"
"}\n"
"\n"
"QWidget#bottomBarWidget QToolButton:pressed {\n"
"    background-color: #d8d8d8;\n"
"}\n"
"\n"
"QWidget#bottomBarWidget QToolButton:disabled {\n"
"    background-color: #f4f4f4;\n"
"    color: #aaaaaa;\n"
"    border-color: #dddddd;\n"
"}\n"
"\n"
"QToolButton#deleteAlbumButton {\n"
"    color: #b3261e;\n"
"}\n"
"\n"
"QToolButton#logoutButton {\n"
"    color: #b3261e;\n"
"}"));
        bottomBarLayout = new QHBoxLayout(bottomBarWidget);
        bottomBarLayout->setSpacing(8);
        bottomBarLayout->setObjectName("bottomBarLayout");
        bottomBarLayout->setContentsMargins(5, 5, 5, 5);
        leftBalanceWidget = new QWidget(bottomBarWidget);
        leftBalanceWidget->setObjectName("leftBalanceWidget");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(leftBalanceWidget->sizePolicy().hasHeightForWidth());
        leftBalanceWidget->setSizePolicy(sizePolicy5);
        leftBalanceWidget->setMinimumSize(QSize(70, 0));
        leftBalanceWidget->setMaximumSize(QSize(70, 16777215));

        bottomBarLayout->addWidget(leftBalanceWidget);

        leftBottomSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        bottomBarLayout->addItem(leftBottomSpacer);

        albumActionsWidget = new QWidget(bottomBarWidget);
        albumActionsWidget->setObjectName("albumActionsWidget");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(albumActionsWidget->sizePolicy().hasHeightForWidth());
        albumActionsWidget->setSizePolicy(sizePolicy6);
        albumActionsWidget->setMinimumSize(QSize(0, 52));
        albumActionsWidget->setMaximumSize(QSize(16777215, 52));
        albumActionsLayout = new QHBoxLayout(albumActionsWidget);
        albumActionsLayout->setSpacing(8);
        albumActionsLayout->setObjectName("albumActionsLayout");
        albumActionsLayout->setContentsMargins(0, 0, 0, 0);
        addAlbumButton = new QToolButton(albumActionsWidget);
        addAlbumButton->setObjectName("addAlbumButton");
        sizePolicy1.setHeightForWidth(addAlbumButton->sizePolicy().hasHeightForWidth());
        addAlbumButton->setSizePolicy(sizePolicy1);
        addAlbumButton->setMinimumSize(QSize(70, 48));
        addAlbumButton->setMaximumSize(QSize(70, 48));
        addAlbumButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        addAlbumButton->setAutoRaise(false);

        albumActionsLayout->addWidget(addAlbumButton);

        addSongButton = new QToolButton(albumActionsWidget);
        addSongButton->setObjectName("addSongButton");
        sizePolicy1.setHeightForWidth(addSongButton->sizePolicy().hasHeightForWidth());
        addSongButton->setSizePolicy(sizePolicy1);
        addSongButton->setMinimumSize(QSize(70, 48));
        addSongButton->setMaximumSize(QSize(70, 48));
        addSongButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        addSongButton->setAutoRaise(false);

        albumActionsLayout->addWidget(addSongButton);

        editAlbumButton = new QToolButton(albumActionsWidget);
        editAlbumButton->setObjectName("editAlbumButton");
        editAlbumButton->setEnabled(false);
        sizePolicy1.setHeightForWidth(editAlbumButton->sizePolicy().hasHeightForWidth());
        editAlbumButton->setSizePolicy(sizePolicy1);
        editAlbumButton->setMinimumSize(QSize(70, 48));
        editAlbumButton->setMaximumSize(QSize(70, 48));
        editAlbumButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        editAlbumButton->setAutoRaise(false);

        albumActionsLayout->addWidget(editAlbumButton);

        deleteAlbumButton = new QToolButton(albumActionsWidget);
        deleteAlbumButton->setObjectName("deleteAlbumButton");
        deleteAlbumButton->setEnabled(false);
        sizePolicy1.setHeightForWidth(deleteAlbumButton->sizePolicy().hasHeightForWidth());
        deleteAlbumButton->setSizePolicy(sizePolicy1);
        deleteAlbumButton->setMinimumSize(QSize(70, 48));
        deleteAlbumButton->setMaximumSize(QSize(70, 48));
        deleteAlbumButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        deleteAlbumButton->setAutoRaise(false);

        albumActionsLayout->addWidget(deleteAlbumButton);


        bottomBarLayout->addWidget(albumActionsWidget);

        rightBottomSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        bottomBarLayout->addItem(rightBottomSpacer);

        logoutButton = new QToolButton(bottomBarWidget);
        logoutButton->setObjectName("logoutButton");
        sizePolicy1.setHeightForWidth(logoutButton->sizePolicy().hasHeightForWidth());
        logoutButton->setSizePolicy(sizePolicy1);
        logoutButton->setMinimumSize(QSize(70, 48));
        logoutButton->setMaximumSize(QSize(70, 48));
        logoutButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        logoutButton->setAutoRaise(false);

        bottomBarLayout->addWidget(logoutButton);


        mainVerticalLayout->addWidget(bottomBarWidget);

        ArtistWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ArtistWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 22));
        ArtistWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ArtistWindow);
        statusbar->setObjectName("statusbar");
        ArtistWindow->setStatusBar(statusbar);

        retranslateUi(ArtistWindow);

        QMetaObject::connectSlotsByName(ArtistWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ArtistWindow)
    {
        ArtistWindow->setWindowTitle(QCoreApplication::translate("ArtistWindow", "Artist Dashboard", nullptr));
        profilePhotoLabel->setText(QString());
        welcomeLabel->setText(QCoreApplication::translate("ArtistWindow", "Welcome, Artist", nullptr));
        emptyAlbumsLabel->setText(QCoreApplication::translate("ArtistWindow", "No albums have been added yet.", nullptr));
#if QT_CONFIG(tooltip)
        addAlbumButton->setToolTip(QCoreApplication::translate("ArtistWindow", "Add album", nullptr));
#endif // QT_CONFIG(tooltip)
        addAlbumButton->setText(QCoreApplication::translate("ArtistWindow", "Add Album", nullptr));
#if QT_CONFIG(tooltip)
        addSongButton->setToolTip(QCoreApplication::translate("ArtistWindow", "Add song", nullptr));
#endif // QT_CONFIG(tooltip)
        addSongButton->setText(QCoreApplication::translate("ArtistWindow", "Add Song", nullptr));
#if QT_CONFIG(tooltip)
        editAlbumButton->setToolTip(QCoreApplication::translate("ArtistWindow", "Edit selected album", nullptr));
#endif // QT_CONFIG(tooltip)
        editAlbumButton->setText(QCoreApplication::translate("ArtistWindow", "Edit", nullptr));
#if QT_CONFIG(tooltip)
        deleteAlbumButton->setToolTip(QCoreApplication::translate("ArtistWindow", "Delete selected album", nullptr));
#endif // QT_CONFIG(tooltip)
        deleteAlbumButton->setText(QCoreApplication::translate("ArtistWindow", "Delete", nullptr));
#if QT_CONFIG(tooltip)
        logoutButton->setToolTip(QCoreApplication::translate("ArtistWindow", "Logout", nullptr));
#endif // QT_CONFIG(tooltip)
        logoutButton->setText(QCoreApplication::translate("ArtistWindow", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ArtistWindow: public Ui_ArtistWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARTISTWINDOW_H
