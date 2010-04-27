/********************************************************************************
** Form generated from reading UI file 'wizardpage.ui'
**
** Created: Tue Apr 27 15:42:25 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIZARDPAGE_H
#define UI_WIZARDPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_WizardPage
{
public:
    QWidget *widget;
    QWidget *widget1;
    QHBoxLayout *mainLayout;
    QGroupBox *spriteBox;
    QGridLayout *spriteBoxLayout;
    QVBoxLayout *leftLayout;
    QHBoxLayout *leftTopLayout;
    QPushButton *prevSpritePushButton;
    QLabel *spriteImage;
    QPushButton *nextSpritePushButton;
    QHBoxLayout *leftMidLayout;
    QSpacerItem *hLeftSpacerSpriteStats;
    QGridLayout *spriteStatsLayout;
    QLabel *spriteName;
    QLabel *spriteNameVal;
    QLabel *spriteAP;
    QLabel *spriteAPVal;
    QLabel *spriteHP;
    QLabel *spriteHPVal;
    QLabel *spriteRange;
    QLabel *spriteRangeVal;
    QSpacerItem *hRightSpacerSpriteStats;
    QHBoxLayout *leftBotLayout;
    QSpacerItem *hLeftSpacerRecruit;
    QPushButton *recruitPushButton;
    QSpacerItem *hRightSpacerRecruit;
    QGroupBox *unitsBox;
    QGridLayout *unitBoxLayout;
    QHBoxLayout *rightUnitLayout1;
    QLabel *unitImage1;
    QVBoxLayout *unitRejectLayout1;
    QLabel *unitName1;
    QPushButton *rejectButton1;
    QHBoxLayout *rightUnitLayout2;
    QLabel *unitImage2;
    QVBoxLayout *unitRejectLayout2;
    QLabel *unitName2;
    QPushButton *rejectButton2;
    QHBoxLayout *rightUnitLayout3;
    QLabel *unitImage3;
    QVBoxLayout *unitRejectLayout3;
    QLabel *unitName3;
    QPushButton *rejectButton3;
    QHBoxLayout *rightUnitLayout4;
    QLabel *unitImage4;
    QVBoxLayout *unitRejectLayout4;
    QLabel *unitName4;
    QPushButton *rejectButton4;

    void setupUi(QWizardPage *WizardPage)
    {
        if (WizardPage->objectName().isEmpty())
            WizardPage->setObjectName(QString::fromUtf8("WizardPage"));
        WizardPage->resize(400, 300);
        widget = new QWidget(WizardPage);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 250, 381, 41));
        widget1 = new QWidget(WizardPage);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(30, 0, 322, 251));
        mainLayout = new QHBoxLayout(widget1);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        spriteBox = new QGroupBox(widget1);
        spriteBox->setObjectName(QString::fromUtf8("spriteBox"));
        spriteBoxLayout = new QGridLayout(spriteBox);
        spriteBoxLayout->setObjectName(QString::fromUtf8("spriteBoxLayout"));
        leftLayout = new QVBoxLayout();
        leftLayout->setObjectName(QString::fromUtf8("leftLayout"));
        leftTopLayout = new QHBoxLayout();
        leftTopLayout->setObjectName(QString::fromUtf8("leftTopLayout"));
        prevSpritePushButton = new QPushButton(spriteBox);
        prevSpritePushButton->setObjectName(QString::fromUtf8("prevSpritePushButton"));
        prevSpritePushButton->setMaximumSize(QSize(31, 23));

        leftTopLayout->addWidget(prevSpritePushButton);

        spriteImage = new QLabel(spriteBox);
        spriteImage->setObjectName(QString::fromUtf8("spriteImage"));
        spriteImage->setMaximumSize(QSize(71, 101));
        spriteImage->setPixmap(QPixmap(QString::fromUtf8("debug/sprites/desertsoldier.png")));
        spriteImage->setScaledContents(true);

        leftTopLayout->addWidget(spriteImage);

        nextSpritePushButton = new QPushButton(spriteBox);
        nextSpritePushButton->setObjectName(QString::fromUtf8("nextSpritePushButton"));
        nextSpritePushButton->setMaximumSize(QSize(31, 23));

        leftTopLayout->addWidget(nextSpritePushButton);


        leftLayout->addLayout(leftTopLayout);

        leftMidLayout = new QHBoxLayout();
        leftMidLayout->setObjectName(QString::fromUtf8("leftMidLayout"));
        hLeftSpacerSpriteStats = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        leftMidLayout->addItem(hLeftSpacerSpriteStats);

        spriteStatsLayout = new QGridLayout();
        spriteStatsLayout->setObjectName(QString::fromUtf8("spriteStatsLayout"));
        spriteName = new QLabel(spriteBox);
        spriteName->setObjectName(QString::fromUtf8("spriteName"));

        spriteStatsLayout->addWidget(spriteName, 0, 0, 1, 1);

        spriteNameVal = new QLabel(spriteBox);
        spriteNameVal->setObjectName(QString::fromUtf8("spriteNameVal"));

        spriteStatsLayout->addWidget(spriteNameVal, 0, 1, 1, 1);

        spriteAP = new QLabel(spriteBox);
        spriteAP->setObjectName(QString::fromUtf8("spriteAP"));

        spriteStatsLayout->addWidget(spriteAP, 1, 0, 1, 1);

        spriteAPVal = new QLabel(spriteBox);
        spriteAPVal->setObjectName(QString::fromUtf8("spriteAPVal"));

        spriteStatsLayout->addWidget(spriteAPVal, 1, 1, 1, 1);

        spriteHP = new QLabel(spriteBox);
        spriteHP->setObjectName(QString::fromUtf8("spriteHP"));

        spriteStatsLayout->addWidget(spriteHP, 2, 0, 1, 1);

        spriteHPVal = new QLabel(spriteBox);
        spriteHPVal->setObjectName(QString::fromUtf8("spriteHPVal"));

        spriteStatsLayout->addWidget(spriteHPVal, 2, 1, 1, 1);

        spriteRange = new QLabel(spriteBox);
        spriteRange->setObjectName(QString::fromUtf8("spriteRange"));

        spriteStatsLayout->addWidget(spriteRange, 3, 0, 1, 1);

        spriteRangeVal = new QLabel(spriteBox);
        spriteRangeVal->setObjectName(QString::fromUtf8("spriteRangeVal"));

        spriteStatsLayout->addWidget(spriteRangeVal, 3, 1, 1, 1);


        leftMidLayout->addLayout(spriteStatsLayout);

        hRightSpacerSpriteStats = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        leftMidLayout->addItem(hRightSpacerSpriteStats);


        leftLayout->addLayout(leftMidLayout);

        leftBotLayout = new QHBoxLayout();
        leftBotLayout->setObjectName(QString::fromUtf8("leftBotLayout"));
        hLeftSpacerRecruit = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        leftBotLayout->addItem(hLeftSpacerRecruit);

        recruitPushButton = new QPushButton(spriteBox);
        recruitPushButton->setObjectName(QString::fromUtf8("recruitPushButton"));

        leftBotLayout->addWidget(recruitPushButton);

        hRightSpacerRecruit = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        leftBotLayout->addItem(hRightSpacerRecruit);


        leftLayout->addLayout(leftBotLayout);


        spriteBoxLayout->addLayout(leftLayout, 0, 0, 1, 1);


        mainLayout->addWidget(spriteBox);

        unitsBox = new QGroupBox(widget1);
        unitsBox->setObjectName(QString::fromUtf8("unitsBox"));
        unitBoxLayout = new QGridLayout(unitsBox);
        unitBoxLayout->setObjectName(QString::fromUtf8("unitBoxLayout"));
        rightUnitLayout1 = new QHBoxLayout();
        rightUnitLayout1->setObjectName(QString::fromUtf8("rightUnitLayout1"));
        unitImage1 = new QLabel(unitsBox);
        unitImage1->setObjectName(QString::fromUtf8("unitImage1"));
        unitImage1->setMaximumSize(QSize(41, 41));
        unitImage1->setPixmap(QPixmap(QString::fromUtf8("debug/sprites/blank.PNG")));
        unitImage1->setScaledContents(true);

        rightUnitLayout1->addWidget(unitImage1);

        unitRejectLayout1 = new QVBoxLayout();
        unitRejectLayout1->setObjectName(QString::fromUtf8("unitRejectLayout1"));
        unitName1 = new QLabel(unitsBox);
        unitName1->setObjectName(QString::fromUtf8("unitName1"));

        unitRejectLayout1->addWidget(unitName1);

        rejectButton1 = new QPushButton(unitsBox);
        rejectButton1->setObjectName(QString::fromUtf8("rejectButton1"));

        unitRejectLayout1->addWidget(rejectButton1);


        rightUnitLayout1->addLayout(unitRejectLayout1);


        unitBoxLayout->addLayout(rightUnitLayout1, 0, 0, 1, 1);

        rightUnitLayout2 = new QHBoxLayout();
        rightUnitLayout2->setObjectName(QString::fromUtf8("rightUnitLayout2"));
        unitImage2 = new QLabel(unitsBox);
        unitImage2->setObjectName(QString::fromUtf8("unitImage2"));
        unitImage2->setMaximumSize(QSize(41, 41));
        unitImage2->setPixmap(QPixmap(QString::fromUtf8("debug/sprites/blank.PNG")));
        unitImage2->setScaledContents(true);

        rightUnitLayout2->addWidget(unitImage2);

        unitRejectLayout2 = new QVBoxLayout();
        unitRejectLayout2->setObjectName(QString::fromUtf8("unitRejectLayout2"));
        unitName2 = new QLabel(unitsBox);
        unitName2->setObjectName(QString::fromUtf8("unitName2"));

        unitRejectLayout2->addWidget(unitName2);

        rejectButton2 = new QPushButton(unitsBox);
        rejectButton2->setObjectName(QString::fromUtf8("rejectButton2"));

        unitRejectLayout2->addWidget(rejectButton2);


        rightUnitLayout2->addLayout(unitRejectLayout2);


        unitBoxLayout->addLayout(rightUnitLayout2, 1, 0, 1, 1);

        rightUnitLayout3 = new QHBoxLayout();
        rightUnitLayout3->setObjectName(QString::fromUtf8("rightUnitLayout3"));
        unitImage3 = new QLabel(unitsBox);
        unitImage3->setObjectName(QString::fromUtf8("unitImage3"));
        unitImage3->setMaximumSize(QSize(41, 41));
        unitImage3->setPixmap(QPixmap(QString::fromUtf8("debug/sprites/blank.PNG")));
        unitImage3->setScaledContents(true);

        rightUnitLayout3->addWidget(unitImage3);

        unitRejectLayout3 = new QVBoxLayout();
        unitRejectLayout3->setObjectName(QString::fromUtf8("unitRejectLayout3"));
        unitName3 = new QLabel(unitsBox);
        unitName3->setObjectName(QString::fromUtf8("unitName3"));

        unitRejectLayout3->addWidget(unitName3);

        rejectButton3 = new QPushButton(unitsBox);
        rejectButton3->setObjectName(QString::fromUtf8("rejectButton3"));

        unitRejectLayout3->addWidget(rejectButton3);


        rightUnitLayout3->addLayout(unitRejectLayout3);


        unitBoxLayout->addLayout(rightUnitLayout3, 2, 0, 1, 1);

        rightUnitLayout4 = new QHBoxLayout();
        rightUnitLayout4->setObjectName(QString::fromUtf8("rightUnitLayout4"));
        unitImage4 = new QLabel(unitsBox);
        unitImage4->setObjectName(QString::fromUtf8("unitImage4"));
        unitImage4->setMaximumSize(QSize(41, 41));
        unitImage4->setPixmap(QPixmap(QString::fromUtf8("debug/sprites/blank.PNG")));
        unitImage4->setScaledContents(true);

        rightUnitLayout4->addWidget(unitImage4);

        unitRejectLayout4 = new QVBoxLayout();
        unitRejectLayout4->setObjectName(QString::fromUtf8("unitRejectLayout4"));
        unitName4 = new QLabel(unitsBox);
        unitName4->setObjectName(QString::fromUtf8("unitName4"));

        unitRejectLayout4->addWidget(unitName4);

        rejectButton4 = new QPushButton(unitsBox);
        rejectButton4->setObjectName(QString::fromUtf8("rejectButton4"));

        unitRejectLayout4->addWidget(rejectButton4);


        rightUnitLayout4->addLayout(unitRejectLayout4);


        unitBoxLayout->addLayout(rightUnitLayout4, 3, 0, 1, 1);


        mainLayout->addWidget(unitsBox);


        retranslateUi(WizardPage);

        QMetaObject::connectSlotsByName(WizardPage);
    } // setupUi

    void retranslateUi(QWizardPage *WizardPage)
    {
        WizardPage->setWindowTitle(QApplication::translate("WizardPage", "WizardPage", 0, QApplication::UnicodeUTF8));
        spriteBox->setTitle(QApplication::translate("WizardPage", "&Available Units", 0, QApplication::UnicodeUTF8));
        prevSpritePushButton->setText(QApplication::translate("WizardPage", "<<", 0, QApplication::UnicodeUTF8));
        spriteImage->setText(QString());
        nextSpritePushButton->setText(QApplication::translate("WizardPage", ">>", 0, QApplication::UnicodeUTF8));
        spriteName->setText(QApplication::translate("WizardPage", "Name:", 0, QApplication::UnicodeUTF8));
        spriteNameVal->setText(QApplication::translate("WizardPage", "NameVal", 0, QApplication::UnicodeUTF8));
        spriteAP->setText(QApplication::translate("WizardPage", "AP:", 0, QApplication::UnicodeUTF8));
        spriteAPVal->setText(QApplication::translate("WizardPage", "APVal", 0, QApplication::UnicodeUTF8));
        spriteHP->setText(QApplication::translate("WizardPage", "HP:", 0, QApplication::UnicodeUTF8));
        spriteHPVal->setText(QApplication::translate("WizardPage", "HPVal", 0, QApplication::UnicodeUTF8));
        spriteRange->setText(QApplication::translate("WizardPage", "Range:", 0, QApplication::UnicodeUTF8));
        spriteRangeVal->setText(QApplication::translate("WizardPage", "RangeVal", 0, QApplication::UnicodeUTF8));
        recruitPushButton->setText(QApplication::translate("WizardPage", "Recruit", 0, QApplication::UnicodeUTF8));
        unitsBox->setTitle(QApplication::translate("WizardPage", "&Player Units", 0, QApplication::UnicodeUTF8));
        unitImage1->setText(QString());
        unitName1->setText(QApplication::translate("WizardPage", "Unit 1", 0, QApplication::UnicodeUTF8));
        rejectButton1->setText(QApplication::translate("WizardPage", "Reject", 0, QApplication::UnicodeUTF8));
        unitImage2->setText(QString());
        unitName2->setText(QApplication::translate("WizardPage", "Unit 2", 0, QApplication::UnicodeUTF8));
        rejectButton2->setText(QApplication::translate("WizardPage", "Reject", 0, QApplication::UnicodeUTF8));
        unitImage3->setText(QString());
        unitName3->setText(QApplication::translate("WizardPage", "Unit 3", 0, QApplication::UnicodeUTF8));
        rejectButton3->setText(QApplication::translate("WizardPage", "Reject", 0, QApplication::UnicodeUTF8));
        unitImage4->setText(QString());
        unitName4->setText(QApplication::translate("WizardPage", "Unit 4", 0, QApplication::UnicodeUTF8));
        rejectButton4->setText(QApplication::translate("WizardPage", "Reject", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WizardPage: public Ui_WizardPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIZARDPAGE_H
