/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Feb 19 23:26:58 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionE_xit;
    QAction *action_Load_Game;
    QAction *action_Save_Game;
    QAction *action_Load_New_Map;
    QAction *actionAdd_Friendly_Unit;
    QAction *actionAdd_Enemy_Unit;
    QAction *action_New_Game;
    QAction *actionOptions;
    QAction *actionATK;
    QAction *actionMOV;
    QAction *actionSTATUS;
    QAction *actionSummary;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menu_Map;
    QMenu *menu_Config;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(720, 540);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(720, 540));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionE_xit = new QAction(MainWindow);
        actionE_xit->setObjectName(QString::fromUtf8("actionE_xit"));
        action_Load_Game = new QAction(MainWindow);
        action_Load_Game->setObjectName(QString::fromUtf8("action_Load_Game"));
        action_Save_Game = new QAction(MainWindow);
        action_Save_Game->setObjectName(QString::fromUtf8("action_Save_Game"));
        action_Load_New_Map = new QAction(MainWindow);
        action_Load_New_Map->setObjectName(QString::fromUtf8("action_Load_New_Map"));
        actionAdd_Friendly_Unit = new QAction(MainWindow);
        actionAdd_Friendly_Unit->setObjectName(QString::fromUtf8("actionAdd_Friendly_Unit"));
        actionAdd_Enemy_Unit = new QAction(MainWindow);
        actionAdd_Enemy_Unit->setObjectName(QString::fromUtf8("actionAdd_Enemy_Unit"));
        action_New_Game = new QAction(MainWindow);
        action_New_Game->setObjectName(QString::fromUtf8("action_New_Game"));
        actionOptions = new QAction(MainWindow);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        actionATK = new QAction(MainWindow);
        actionATK->setObjectName(QString::fromUtf8("actionATK"));
        actionMOV = new QAction(MainWindow);
        actionMOV->setObjectName(QString::fromUtf8("actionMOV"));
        actionSTATUS = new QAction(MainWindow);
        actionSTATUS->setObjectName(QString::fromUtf8("actionSTATUS"));
        actionSummary = new QAction(MainWindow);
        actionSummary->setObjectName(QString::fromUtf8("actionSummary"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);

        horizontalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 720, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menu_Map = new QMenu(menuBar);
        menu_Map->setObjectName(QString::fromUtf8("menu_Map"));
        menu_Config = new QMenu(menuBar);
        menu_Config->setObjectName(QString::fromUtf8("menu_Config"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(false);
        MainWindow->addToolBar(Qt::LeftToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menu_Map->menuAction());
        menuBar->addAction(menu_Config->menuAction());
        menuFile->addAction(action_New_Game);
        menuFile->addAction(action_Save_Game);
        menuFile->addAction(action_Load_Game);
        menuFile->addSeparator();
        menuFile->addAction(actionE_xit);
        menu_Map->addAction(actionAdd_Friendly_Unit);
        menu_Map->addAction(actionAdd_Enemy_Unit);
        menu_Map->addSeparator();
        menu_Map->addAction(action_Load_New_Map);
        menu_Config->addAction(actionOptions);
        mainToolBar->addAction(actionATK);
        mainToolBar->addAction(actionMOV);
        mainToolBar->addAction(actionSTATUS);
        mainToolBar->addAction(actionSummary);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Duel Reality: 2D Tactical Combat for 16.553", 0, QApplication::UnicodeUTF8));
        actionE_xit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        action_Load_Game->setText(QApplication::translate("MainWindow", "&Load Game", 0, QApplication::UnicodeUTF8));
        action_Save_Game->setText(QApplication::translate("MainWindow", "&Save Game", 0, QApplication::UnicodeUTF8));
        action_Load_New_Map->setText(QApplication::translate("MainWindow", "&Load New Map", 0, QApplication::UnicodeUTF8));
        actionAdd_Friendly_Unit->setText(QApplication::translate("MainWindow", "Add &Friendly Unit", 0, QApplication::UnicodeUTF8));
        actionAdd_Enemy_Unit->setText(QApplication::translate("MainWindow", "Add &Enemy Unit", 0, QApplication::UnicodeUTF8));
        action_New_Game->setText(QApplication::translate("MainWindow", "&New Game", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("MainWindow", "&Options", 0, QApplication::UnicodeUTF8));
        actionATK->setText(QApplication::translate("MainWindow", "Attack", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionATK->setToolTip(QApplication::translate("MainWindow", "Attack", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionMOV->setText(QApplication::translate("MainWindow", "Move", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMOV->setToolTip(QApplication::translate("MainWindow", "Move Unit", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSTATUS->setText(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSTATUS->setToolTip(QApplication::translate("MainWindow", "Show Unit Status", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSummary->setText(QApplication::translate("MainWindow", "Summary", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSummary->setToolTip(QApplication::translate("MainWindow", "Game Summary", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Map->setTitle(QApplication::translate("MainWindow", "&Map", 0, QApplication::UnicodeUTF8));
        menu_Config->setTitle(QApplication::translate("MainWindow", "&Config", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
