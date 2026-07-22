/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLineEdit *usernameLineEdit;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *nameLineEdit;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QLineEdit *passwordLineEdit;
    QHBoxLayout *horizontalLayout;
    QRadioButton *artistRadioButton;
    QRadioButton *listenerRadioButton;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QTextEdit *bioTextEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *submitRegisterButton;
    QPushButton *backButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(942, 668);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName("gridLayout");
        verticalSpacer = new QSpacerItem(20, 21, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 21, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        widget = new QWidget(Dialog);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(500, 450));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setSpacing(30);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(20, 20, 20, 20);
        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout_5->addWidget(label);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        usernameLineEdit = new QLineEdit(widget);
        usernameLineEdit->setObjectName("usernameLineEdit");
        QFont font;
        font.setPointSize(10);
        usernameLineEdit->setFont(font);

        verticalLayout_2->addWidget(usernameLineEdit);


        verticalLayout_5->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        nameLineEdit = new QLineEdit(widget);
        nameLineEdit->setObjectName("nameLineEdit");
        nameLineEdit->setFont(font);

        verticalLayout->addWidget(nameLineEdit);


        verticalLayout_5->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);

        passwordLineEdit = new QLineEdit(widget);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setFont(font);
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout_3->addWidget(passwordLineEdit);


        verticalLayout_5->addLayout(verticalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        artistRadioButton = new QRadioButton(widget);
        artistRadioButton->setObjectName("artistRadioButton");

        horizontalLayout->addWidget(artistRadioButton);

        listenerRadioButton = new QRadioButton(widget);
        listenerRadioButton->setObjectName("listenerRadioButton");

        horizontalLayout->addWidget(listenerRadioButton);


        verticalLayout_5->addLayout(horizontalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");

        verticalLayout_4->addWidget(label_5);

        bioTextEdit = new QTextEdit(widget);
        bioTextEdit->setObjectName("bioTextEdit");
        bioTextEdit->setFont(font);

        verticalLayout_4->addWidget(bioTextEdit);


        verticalLayout_5->addLayout(verticalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(100);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        submitRegisterButton = new QPushButton(widget);
        submitRegisterButton->setObjectName("submitRegisterButton");

        horizontalLayout_2->addWidget(submitRegisterButton);

        backButton = new QPushButton(widget);
        backButton->setObjectName("backButton");

        horizontalLayout_2->addWidget(backButton);


        verticalLayout_5->addLayout(horizontalLayout_2);


        gridLayout->addWidget(widget, 1, 1, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:16pt;\">Start exploring the world of music</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:10pt;\">User Name</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:10pt;\">Name</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:10pt;\">Password</span></p></body></html>", nullptr));
        artistRadioButton->setText(QCoreApplication::translate("Dialog", "Artist", nullptr));
        listenerRadioButton->setText(QCoreApplication::translate("Dialog", "Listener", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:10pt;\">Biography</span></p></body></html>", nullptr));
        submitRegisterButton->setText(QCoreApplication::translate("Dialog", "Register", nullptr));
        backButton->setText(QCoreApplication::translate("Dialog", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
