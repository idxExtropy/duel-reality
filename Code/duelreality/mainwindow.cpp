#include <QtGui>

#include "mainwindow.h"
#include "glwidget.h"
#include "newgamewizard.h"
#include "loadgamewizard.h"
#include "mechanics.h"

// Global classes.
GLWidget *glWidget;
mechanics *mech;

MainWindow::MainWindow()
{
    // Set central widget
    glWidget = new GLWidget;
    setCentralWidget(glWidget);
    resize(720, 540);

    // Manage window size
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    setMinimumSize(QSize(720, 540));

    // Create actions, menus, toolbars and status bars
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    // Create test actions & toolbars
    createTestTools();

    emit isBattleMode(false);
    emit isGameCfgMode(true);
    emit isUserTurn(false);

    // Play main theme.
    glWidget->music = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("sounds/MainTheme.mp3"));
    glWidget->music->play();

    // Set window icon
    setWindowIcon(QIcon("icons/logo.png"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}


void MainWindow::createTestTools()
{
    actionTestSignalBattleStart = new QAction(tr("&Battle Start Test Signal"), this);
    actionTestSignalBattleStart->setIcon(QIcon("icons/basketball.png"));
    connect(actionTestSignalBattleStart, SIGNAL(triggered()), this, SLOT(onBattleStart()));

    actionTestSignalBattleEnd = new QAction(tr("&Battle End Test Signal"), this);
    actionTestSignalBattleEnd->setIcon(QIcon("icons/skullandbones.png"));
    connect(actionTestSignalBattleEnd, SIGNAL(triggered()), this, SLOT(onBattleEnd()));

    actionTestSignalUserTurnStart = new QAction(tr("&User Turn Test Signal"), this);
    actionTestSignalUserTurnStart->setIcon(QIcon("icons/babyboy.png"));
    connect(actionTestSignalUserTurnStart, SIGNAL(triggered()), this, SLOT(onUserTurn()));

    testToolBar = addToolBar(tr("&Test"));
    testToolBar->setMovable(false);
    testToolBar->addAction(actionTestSignalBattleStart);
    testToolBar->addAction(actionTestSignalBattleEnd);
    testToolBar->addAction(actionTestSignalUserTurnStart);
}


void MainWindow::createActions()
{
    actionNewGame = new QAction(tr("&New Game"), this);
    actionNewGame->setIcon(QIcon("icons/filenew.png"));
    actionNewGame->setShortcut(QKeySequence::New);
    actionNewGame->setStatusTip(tr("Start a new game"));
    connect(this, SIGNAL(isGameCfgMode(bool)), actionNewGame, SLOT(setEnabled(bool)));
    connect(actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));

    actionLoadGame = new QAction(tr("&Load Game"), this);
    actionLoadGame->setIcon(QIcon("icons/fileopen.png"));
    actionLoadGame->setShortcut(tr("Ctrl+L"));
    actionLoadGame->setStatusTip(tr("Load a saved game"));
    connect(this, SIGNAL(isGameCfgMode(bool)), actionLoadGame, SLOT(setEnabled(bool)));
    connect(actionLoadGame, SIGNAL(triggered()), this, SLOT(loadGame()));

    actionSaveGame = new QAction(tr("&Save Game"), this);
    actionSaveGame->setIcon(QIcon("icons/filesave.png"));
    actionSaveGame->setShortcut(QKeySequence::Save);
    actionSaveGame->setStatusTip(tr("Save a game"));
    connect(this, SIGNAL(isBattleMode(bool)), actionSaveGame, SLOT(setEnabled(bool)));
    //connect(actionSaveGame, SIGNAL(triggered()), this, SLOT(saveGame()));

    actionExitGame = new QAction(tr("E&xit Game"), this);
    actionExitGame->setIcon(QIcon("icons/exit.png"));
    actionExitGame->setShortcut(tr("Ctrl+X"));
    actionExitGame->setStatusTip(tr("Exit the game"));
    connect(actionExitGame, SIGNAL(triggered()), this, SLOT(close()));

    actionAbout = new QAction(tr("&About"), this);
    actionAbout->setStatusTip(tr("Provides information about the game"));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));

    turnIndicator = new QAction(tr("&Turn Signal"), this);
    turnIndicator->setIcon(QIcon("icons/redcircle.png"));
    turnIndicator->setStatusTip(tr("Computer's turn to play"));

    actionAttack = new QAction(tr("&Attack"), this);
    actionAttack->setIcon(QIcon("icons/attack.png"));
    actionAttack->setShortcut(tr("Ctrl+A"));
    actionAttack->setStatusTip(tr("Attack opponent"));
    connect(this, SIGNAL(isBattleMode(bool)), actionAttack, SLOT(setEnabled(bool)));
    //connect(actionAttack, SIGNAL(triggered()), this, SLOT(attack()));

    actionMove = new QAction(tr("&Move"), this);
    actionMove->setIcon(QIcon("icons/rightarrow.png"));
    actionMove->setShortcut(tr("Ctrl+M"));
    actionMove->setStatusTip(tr("Move unit"));
    connect(this, SIGNAL(isBattleMode(bool)), actionMove, SLOT(setEnabled(bool)));
    connect(actionMove, SIGNAL(triggered()), this, SIGNAL(move()));
connect(this, SIGNAL(signalmove()), mech, SLOT(move()));
    actionEndTurn = new QAction(tr("&End Turn"), this);
    actionEndTurn->setIcon(QIcon("icons/endturn.png"));
    actionEndTurn->setShortcut(tr("Ctrl+T"));
    actionEndTurn->setStatusTip(tr("End Turn"));
    connect(this, SIGNAL(isBattleMode(bool)), actionEndTurn, SLOT(setEnabled(bool)));
    connect(actionEndTurn, SIGNAL(triggered()), this, SLOT(endTurnClicked()));
}

void MainWindow::onBattleStart()
{
    glWidget->unitTest_GenerateContent(); //unitTest
    emit isBattleMode(true);
    emit isGameCfgMode(false);
}


void MainWindow::onBattleEnd()
{
    emit isBattleMode(false);
    emit isGameCfgMode(true);
}


void MainWindow::onUserTurn()
{
    turnIndicator->setStatusTip(tr("Your turn to play"));
    turnIndicator->setIcon(QIcon("icons/greencircle.png"));
    emit isUserTurn(true);
}


void MainWindow::endTurnClicked()
{
    turnIndicator->setStatusTip(tr("Computer's turn to play"));
    turnIndicator->setIcon(QIcon("icons/redcircle.png"));
    emit isUserTurn(false);
    emit signalUserTurnEnd();
}

void MainWindow::createMenus()
{
    menuGame = menuBar()->addMenu(tr("&Game"));
    menuGame->addAction(actionNewGame);
    menuGame->addAction(actionLoadGame);
    menuGame->addAction(actionSaveGame);
    menuGame->addSeparator();
    menuGame->addAction(actionExitGame);

    menuHelp = menuBar()->addMenu(tr("&Help"));
    menuHelp->addAction(actionAbout);
}

void MainWindow::createToolBars()
{
    gameToolBar = addToolBar(tr("&Game"));
    gameToolBar->setMovable(false);
    gameToolBar->addAction(actionNewGame);
    gameToolBar->addAction(actionLoadGame);
    gameToolBar->addAction(actionSaveGame);
    gameToolBar->addSeparator();

    actionToolBar = addToolBar(tr("&Action"));
    actionToolBar->setMovable(false);
    actionToolBar->addAction(turnIndicator);
    actionToolBar->addAction(actionAttack);
    actionToolBar->addAction(actionMove);
    actionToolBar->addAction(actionEndTurn);
    actionToolBar->addSeparator();
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::newGame()
{
    NewGameWizard *newgamewizard = new NewGameWizard(this);

    if (newgamewizard->exec())
    {
        soundBkgnd->stop();

        soundBattleStart = new QSound("sounds/trumpet.wav");
        soundBattleStart->play();

        emit signalGameCfgComplete();
    }
    delete newgamewizard;
}

void MainWindow::loadGame()
{
    LoadGameWizard *loadgamewizard = new LoadGameWizard(this);

    if (loadgamewizard->exec())
    {
        soundBkgnd->stop();

        soundBattleStart = new QSound("sounds/trumpet.wav");
        soundBattleStart->play();

        emit signalGameCfgComplete();
    }
    delete loadgamewizard;
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Duel Reality"),
                       tr("<h2>Duel Reality 1.0</h2>"
                          "<p>Copyright &copy; 2010 Team Gold Inc."
                          "<p>Duel Reality is a turn-based strategy game. "
                          "It is a design project for the "
                          "Software Engineering course, 16.553, "
                          "at University of Massachusetss, Lowell."));
}
