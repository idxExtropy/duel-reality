#include <QtGui>

#include "mainwindow.h"
#include "glwidget.h"
#include "usernamedialog.h"

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

    // Initialize background sound
    soundBkgnd = new QSound("sounds/crazy.wav");
    soundBkgnd->setLoops(-1);
    soundBkgnd->play();

    // Initialize dialogs
    userNameDialog = 0;

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
    connect(actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));

    actionLoadGame = new QAction(tr("&Load Game"), this);
    actionLoadGame->setIcon(QIcon("icons/fileopen.png"));
    actionLoadGame->setShortcut(tr("Ctrl+L"));
    actionLoadGame->setStatusTip(tr("Load a saved game"));
    //connect(actionLoadGame, SIGNAL(triggered()), this, SLOT(loadGame()));

    actionSaveGame = new QAction(tr("&Save Game"), this);
    actionSaveGame->setIcon(QIcon("icons/filesave.png"));
    actionSaveGame->setShortcut(QKeySequence::Save);
    actionSaveGame->setStatusTip(tr("Save a game"));
    //connect(actionSaveGame, SIGNAL(triggered()), this, SLOT(saveGame()));

    actionExitGame = new QAction(tr("E&xit Game"), this);
    actionExitGame->setIcon(QIcon("icons/exit.png"));
    actionExitGame->setShortcut(tr("Ctrl+X"));
    actionExitGame->setStatusTip(tr("Exit the game"));
    connect(actionExitGame, SIGNAL(triggered()), this, SLOT(close()));

    actionAttack = new QAction(tr("Ctrl+A"), this);
    actionAttack->setIcon(QIcon("icons/attack.png"));
    actionAttack->setShortcut(tr("Attack"));
    actionAttack->setStatusTip(tr("Attack opponent"));
    //connect(actionAttack, SIGNAL(triggered()), this, SLOT(attack()));

    actionMove = new QAction(tr("&Move"), this);
    actionMove->setShortcut(tr("Ctrl+M"));
    actionMove->setStatusTip(tr("Move unit"));
    //connect(actionMove, SIGNAL(triggered()), this, SLOT(move()));

    actionAbout = new QAction(tr("&About"), this);
    //actionAbout->setShortcut();
    actionAbout->setStatusTip(tr("Provides information about the game"));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
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
    actionToolBar->addAction(actionAttack);
    actionToolBar->addAction(actionMove);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::newGame()
{
    if (!userNameDialog)
    {
        userNameDialog = new UserNameDialog(this);
        //connect(userNameDialog, SIGNAL(sendUserName()), )
    }

    userNameDialog->show();
    userNameDialog->raise();
    userNameDialog->activateWindow();
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
