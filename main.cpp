#include <QtGui/QApplication>

#include "newgamewizard.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    NewGameWizard   wizard;
    wizard.show();

    return app.exec();
}
