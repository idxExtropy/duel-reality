#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtOpenGL>

//#include "glwidget.h"

class QAction;
//class QMenuBar;
class QMenu;
class GLWidget;
//class UserNameDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    //void newGame();
    //void loadGame();
    //bool exitGame();
    //bool saveGame();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    //void createStatusBar();

    GLWidget *glWidget;
    //UserNameDialog *userNameDialog;

    QAction *actionNewGame;
    QAction *actionLoadGame;
    QAction *actionSaveGame;
    QAction *actionExitGame;
    QAction *actionAttack;
    QAction *actionMove;
    QWidget *centralWidget;
    //QHBoxLayout *horizontalLayout_2;
    //QHBoxLayout *horizontalLayout;
    //QMenuBar *menuBar;
    QMenu *menuGame;
    QToolBar *gameToolBar;
    QToolBar *actionToolBar;
    //QStatusBar *statusBar;
};

#endif // MAINWINDOW_H
