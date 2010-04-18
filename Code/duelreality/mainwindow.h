#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtOpenGL>


// Forward declarations
class QAction;
class QMenu;
class UserNameDialog;
class GLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newGame();
    //void loadGame();
    //bool exitGame();
    //bool saveGame();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    GLWidget *glWidget;
    UserNameDialog *userNameDialog;

    // Actions and associated menus & toolbars
    QAction *actionNewGame;
    QAction *actionLoadGame;
    QAction *actionSaveGame;
    QAction *actionExitGame;
    QAction *actionAttack;
    QAction *actionMove;
    QWidget *centralWidget;
    QMenu *menuGame;
    QToolBar *gameToolBar;
    QToolBar *actionToolBar;
};

#endif // MAINWINDOW_H
