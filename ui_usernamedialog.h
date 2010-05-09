/********************************************************************************
** Form generated from reading UI file 'usernamedialog.ui'
**
** Created: Sun Apr 18 07:54:28 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERNAMEDIALOG_H
#define UI_USERNAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserNameDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *newUserBox;
    QCheckBox *returningUserBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *continueButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *UserNameDialog)
    {
        if (UserNameDialog->objectName().isEmpty())
            UserNameDialog->setObjectName(QString::fromUtf8("UserNameDialog"));
        UserNameDialog->resize(211, 102);
        verticalLayout_3 = new QVBoxLayout(UserNameDialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(UserNameDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(UserNameDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        newUserBox = new QCheckBox(UserNameDialog);
        newUserBox->setObjectName(QString::fromUtf8("newUserBox"));
        newUserBox->setEnabled(true);
        newUserBox->setCheckable(true);

        verticalLayout->addWidget(newUserBox);

        returningUserBox = new QCheckBox(UserNameDialog);
        returningUserBox->setObjectName(QString::fromUtf8("returningUserBox"));

        verticalLayout->addWidget(returningUserBox);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        continueButton = new QPushButton(UserNameDialog);
        continueButton->setObjectName(QString::fromUtf8("continueButton"));
        continueButton->setEnabled(false);
        continueButton->setDefault(true);

        verticalLayout_2->addWidget(continueButton);

        cancelButton = new QPushButton(UserNameDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        verticalLayout_2->addWidget(cancelButton);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(lineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(UserNameDialog);

        QMetaObject::connectSlotsByName(UserNameDialog);
    } // setupUi

    void retranslateUi(QWidget *UserNameDialog)
    {
        UserNameDialog->setWindowTitle(QApplication::translate("UserNameDialog", "Enter User Name", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UserNameDialog", "&User Name", 0, QApplication::UnicodeUTF8));
        newUserBox->setText(QApplication::translate("UserNameDialog", "&New User", 0, QApplication::UnicodeUTF8));
        returningUserBox->setText(QApplication::translate("UserNameDialog", "&Returning User", 0, QApplication::UnicodeUTF8));
        continueButton->setText(QApplication::translate("UserNameDialog", "&Continue", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("UserNameDialog", "C&ancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UserNameDialog: public Ui_UserNameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERNAMEDIALOG_H
