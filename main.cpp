#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Team Gold");
    app.setApplicationName("Duel Reality");
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}

