#include <QtGui>

#include "mainwindow.h"
#include "glwidget.h"
//#include "usernamedialog.h"
#include "newgamewizard.h"
#include "mechanics.h"


// Set initial conditions of public static variables
bool MainWindow::isActiveBattle = false;
bool MainWindow::isPlayerTurn = false;

/*
Indicator::Indicator()
{
}

Indicator::~Indicator()
{
}

void Indicator::indicatorAsserted()
{
    this->update();
}


void Indicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 12, Qt::DashDotDotLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawEllipse(80, 80, 400, 240);
}
*/

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
    //createIndicators();
    createMenus();
    createToolBars();
    createStatusBar();

    // Initialize background sound
    soundBkgnd = new QSound("sounds/crazy.wav");
    soundBkgnd->setLoops(-1);
    soundBkgnd->play();

    // Initialize dialogs
    //userNameDialog = 0;
    //newgamewizard = 0;

    // Set window icon
    setWindowIcon(QIcon("icons/logo.png"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void MainWindow::createActions()
{
    actionNewGame = new QAction(tr("&New Game"), this);
    actionNewGame->setIcon(QIcon("icons/filenew.png"));
    actionNewGame->setShortcut(QKeySequence::New);
    actionNewGame->setStatusTip(tr("Start a new game"));
    actionNewGame->setEnabled(!MainWindow::isActiveBattle);
    connect(actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));

    actionLoadGame = new QAction(tr("&Load Game"), this);
    actionLoadGame->setIcon(QIcon("icons/fileopen.png"));
    actionLoadGame->setShortcut(tr("Ctrl+L"));
    actionLoadGame->setStatusTip(tr("Load a saved game"));
    actionLoadGame->setEnabled(!MainWindow::isActiveBattle);
    //connect(actionLoadGame, SIGNAL(triggered()), this, SLOT(loadGame()));

    actionSaveGame = new QAction(tr("&Save Game"), this);
    actionSaveGame->setIcon(QIcon("icons/filesave.png"));
    actionSaveGame->setShortcut(QKeySequence::Save);
    actionSaveGame->setStatusTip(tr("Save a game"));
    actionSaveGame->setEnabled(MainWindow::isActiveBattle);
    //connect(actionSaveGame, SIGNAL(triggered()), this, SLOT(saveGame()));

    actionExitGame = new QAction(tr("E&xit Game"), this);
    actionExitGame->setIcon(QIcon("icons/exit.png"));
    actionExitGame->setShortcut(tr("Ctrl+X"));
    actionExitGame->setStatusTip(tr("Exit the game"));
    actionExitGame->setEnabled(MainWindow::isActiveBattle && MainWindow::isPlayerTurn);
    connect(actionExitGame, SIGNAL(triggered()), this, SLOT(close()));

    actionAbout = new QAction(tr("&About"), this);
    //actionAbout->setShortcut();
    actionAbout->setStatusTip(tr("Provides information about the game"));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));

    actionAttack = new QAction(tr("Ctrl+A"), this);
    actionAttack->setIcon(QIcon("icons/attack.png"));
    actionAttack->setShortcut(tr("Ctrl+A"));
    actionAttack->setStatusTip(tr("Attack opponent"));
    actionAttack->setEnabled(MainWindow::isActiveBattle && MainWindow::isPlayerTurn);
    //connect(actionAttack, SIGNAL(triggered()), this, SLOT(attack()));

    actionMove = new QAction(tr("&Move"), this);
    actionMove->setIcon(QIcon("icons/rightarrow.png"));
    actionMove->setShortcut(tr("Ctrl+M"));
    actionMove->setStatusTip(tr("Move unit"));
    actionMove->setEnabled(MainWindow::isActiveBattle && MainWindow::isPlayerTurn);
    //connect(actionMove, SIGNAL(triggered()), this, SLOT(move()));

    actionEndTurn = new QAction(tr("&End Turn"), this);
    actionEndTurn->setIcon(QIcon("icons/endturn.png"));
    actionEndTurn->setShortcut(tr("Ctrl+T"));
    actionEndTurn->setStatusTip(tr("End Turn"));
    actionEndTurn->setEnabled(MainWindow::isActiveBattle && MainWindow::isPlayerTurn);
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

    actionToolBar = addToolBar(tr("&Action"));
    actionToolBar->setMovable(false);
    //actionToolBar->addWidget(turnIndicator);
    actionToolBar->addAction(actionAttack);
    actionToolBar->addAction(actionMove);
    actionToolBar->addAction(actionEndTurn);
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

        emit newGameComplete();
    }
    delete newgamewizard;
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


void MainWindow::setActiveBattleFlag()
{
    MainWindow::isActiveBattle = true;
}


void MainWindow::resetActiveBattleFlag()
{
    MainWindow::isActiveBattle = false;
}

void MainWindow::setPlayerTurnFlag()
{
    MainWindow::isPlayerTurn = true;
}

void MainWindow::resetPlayerTurnFlag()
{
    MainWindow::isPlayerTurn = false;
}
