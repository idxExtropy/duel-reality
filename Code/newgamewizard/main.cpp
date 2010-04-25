#include <QtGui/QApplication>
//#include "mainwindow.h"

#include "newgamewizard.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //MainWindow w;
    //w.show();

    NewGameWizard   wizard;
    wizard.show();

    return app.exec();
}
