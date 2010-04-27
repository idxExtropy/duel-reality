#include <QtGui>

#include "ui_wizardpage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWizardPage page;
    page.show();

    return app.exec();
}
