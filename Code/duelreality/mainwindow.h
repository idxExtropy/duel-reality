#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtOpenGL>


// Forward declarations
class QAction;
class QMenu;
//class UserNameDialog;
class GLWidget;
class NewGameWizard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    static bool isActiveBattle;
    static bool isPlayerTurn;

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void    newGameComplete();

private slots:
    void newGame();
    void about();
    //void loadGame();
    //bool exitGame();
    //bool saveGame();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    GLWidget *glWidget;
    //UserNameDialog *userNameDialog;
    //NewGameWizard   *newgamewizard;

    QSound  *soundBkgnd;
    QSound  *soundBattleStart;

    // Actions and associated menus & toolbars
    QAction     *actionNewGame;
    QAction     *actionLoadGame;
    QAction     *actionSaveGame;
    QAction     *actionExitGame;
    QAction     *actionAttack;
    QAction     *actionMove;
    QAction     *actionAbout;
    QWidget     *centralWidget;
    QMenu       *menuGame;
    QMenu       *menuHelp;
    QToolBar    *gameToolBar;
    QToolBar    *actionToolBar;
};

#endif // MAINWINDOW_H
