#include <QtGui>

#include "mainwindow.h"
#include "glwidget.h"
//#include "usernamedialog.h"

 MainWindow::MainWindow()
 {
     glWidget = new GLWidget;
     setCentralWidget(glWidget);
     resize(720, 540);

     QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
     sizePolicy.setHorizontalStretch(0);
     sizePolicy.setVerticalStretch(0);
     sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
     setSizePolicy(sizePolicy);
     setMinimumSize(QSize(720, 540));

     createActions();
     createMenus();
     createToolBars();
     //createStatusBar();

     //userNameDialog = 0;

     setWindowIcon(QIcon("icons/logo.png"));
 }

 void MainWindow::closeEvent(QCloseEvent *event)
 {
     //if (maybeSave()) {
//         writeSettings();
         event->accept();
    // } else {
         //event->ignore();
    // }
 }

 void MainWindow::createActions()
 {
     actionNewGame = new QAction(tr("&New Game"), this);
     actionNewGame->setIcon(QIcon("icons/filenew.png"));
     actionNewGame->setShortcut(QKeySequence::New);
     actionNewGame->setStatusTip(tr("Start a new game"));
     //connect(actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));

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
 }

 void MainWindow::createMenus()
 {
     menuGame = menuBar()->addMenu(tr("&Game"));
     menuGame->addAction(actionNewGame);
     menuGame->addAction(actionLoadGame);
     menuGame->addAction(actionSaveGame);
     menuGame->addSeparator();
     menuGame->addAction(actionExitGame);
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
/*
 void MainWindow::createStatusBar()
 {
     statusBar()->showMessage(tr("Ready"));
 }

 void MainWindow::loadFile(const QString &fileName)
 {
     QFile file(fileName);
     if (!file.open(QFile::ReadOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Application"),
                              tr("Cannot read file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return;
     }

     QTextStream in(&file);
 #ifndef QT_NO_CURSOR
     QApplication::setOverrideCursor(Qt::WaitCursor);
 #endif
     textEdit->setPlainText(in.readAll());
 #ifndef QT_NO_CURSOR
     QApplication::restoreOverrideCursor();
 #endif

     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File loaded"), 2000);
 }

*/
