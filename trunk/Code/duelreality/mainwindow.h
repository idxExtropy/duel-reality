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
    void isBattleMode(bool);        // True if game is in battle mode; false otherwise
    void isGameCfgMode(bool);       // True if game is in config mode; false otherwise
    void isUserTurn(bool);          // True is user's turn; false otherwise

public slots:
    void onBattleStart();   // Disables game config user interactions
    void onBattleEnd();     // Disables battle interactions
    void onUserTurn();      // Enables user turn interactions

private slots:
    void newGame();     // Calls New Game dialogs
    void about();       // Calls About Game dialogs
    //void loadGame();    // Calls Load Game dialogs
    //bool exitGame();    // Exits game
    //bool saveGame();    // Calls Save Game dialog    
    void endTurnClicked();  // Disables user turn interactions

private:
    void createActions();   // Creates actions
    void createMenus();     // Creates menus
    void createToolBars();  // Creates toolbars
    void createStatusBar(); // Creates status bars

    // Test methods
    void createTestTools();

    // Modules from other team members
    QWidget     *centralWidget;
    //Mechnics    *mechanics;
    //Database    *db;

    // Action sounds
    QSound  *soundBkgnd;        // Played when not in battle
    QSound  *soundBattleStart;  // Played at start of battle

    // Action items
    QAction     *actionNewGame;     // Triggered to start new game
    QAction     *actionLoadGame;    // Triggered to load new game
    QAction     *actionSaveGame;    // Triggered to save game
    QAction     *actionExitGame;    // Triggered to exit game
    QAction     *turnIndicator;     // Indicates player turn (not implemented as an action)
    QAction     *actionAttack;      // Triggered to attack opponent
    QAction     *actionMove;        // Triggered to move unit
    QAction     *actionAbout;       // Triggered to open About dialog
    QAction     *actionEndTurn;     // Triggered to end user turn

    // Menu items
    QMenu       *menuGame;      // Game menu
    QMenu       *menuAction;    // Action menu
    QMenu       *menuHelp;      // Help menu

    // Toolbar items
    QToolBar    *gameToolBar;   // Game toolbar
    QToolBar    *actionToolBar; // Action toolbar

    // Test Members
    QToolBar    *testToolBar;
    QAction     *actionTestSignalBattleStart;
    QAction     *actionTestSignalUserTurnStart;
    QAction     *actionTestSignalBattleEnd;
};

#endif // MAINWINDOW_H
