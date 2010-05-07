#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtOpenGL>


// Forward declarations
class QAction;
class QMenu;
class GLWidget;
class NewGameWizard;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void signalGameCfgComplete();   // Indicates new game or load game dialog is complete
    void signalUserTurnEnd();       // Indicates that user has ended turn

private slots:
    void newGame();     // Calls New Game dialogs
    void about();       // Calls About Game dialogs
    //void loadGame();    // Calls Load Game dialogs
    //bool exitGame();    // Exits game
    //bool saveGame();    // Calls Save Game dialog
    //void setActiveBattleFlag();
    //void resetActiveBattleFlag();
    //void setPlayerTurnFlag();
    //void resetPlayerTurnFlag();

    void onBattleStart();   // Disables game config user interactions
    void onBattleEnd();     // Disables battle interactions
    void onUserTurn();      // Enables user turn interactions

private:
    void createActions();   // Creates actions
    void createMenus();     // Creates menus
    void createToolBars();  // Creates toolbars
    void createStatusBar(); // Creates status bars

    // Modules from other team members
    QWidget     *centralWidget;
    //Mechnics *mechanics;
    //Database *db;

    QSound  *soundBkgnd;
    QSound  *soundBattleStart;

    // Action items
    QAction     *actionNewGame;
    QAction     *actionLoadGame;
    QAction     *actionSaveGame;
    QAction     *actionExitGame;
    QAction     *turnIndicator;
    QAction     *actionAttack;
    QAction     *actionMove;
    QAction     *actionAbout;
    QAction     *actionEndTurn;

    // Menu items
    QMenu       *menuGame;      // Game menu
    QMenu       *menuAction;    // Action menu
    QMenu       *menuHelp;      // Help menu

    // Toolbar items
    QToolBar    *gameToolBar;   // Game toolbar
    QToolBar    *actionToolBar; // Action toolbar
};

#endif // MAINWINDOW_H
