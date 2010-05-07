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
class QPainter;

/*
class Indicator : public QWidget
{
    Q_OBJECT

public:
    Indicator();
    ~Indicator();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void indicatorAsserted();
};
*/

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
    void setActiveBattleFlag();
    void resetActiveBattleFlag();
    void setPlayerTurnFlag();
    void resetPlayerTurnFlag();

private:
    void createActions();
    //void createIndicators();
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
    QAction      *turnIndicator;
    QAction     *actionAttack;
    QAction     *actionMove;
    QAction     *actionAbout;
    QAction     *actionEndTurn;

    QWidget     *centralWidget;
    QMenu       *menuGame;
    QMenu       *menuHelp;
    QToolBar    *gameToolBar;
    QToolBar    *actionToolBar;
};

#endif // MAINWINDOW_H
