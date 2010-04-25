#include <QtGui>

#include "newgamewizard.h"

NewGameWizard::NewGameWizard(QWidget *parent)
    : QWizard(parent)
{
    // Set New Game dialog pages
    setPage(Page_Intro, new IntroPage);
    setPage(Page_CreatePlayer, new CreatePlayerPage);
    setPage(Page_LoadPlayer, new LoadPlayerPage);
    setPage(Page_RecruitUnits, new RecruitUnitsPage);
    setPage(Page_SelectMap, new SelectMapPage);

    // Set start page
    setStartId(Page_Intro);

    setOption(HaveHelpButton, true);

    // Connect Help slot
    connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));

    // Set window logo and title
    setPixmap(QWizard::LogoPixmap, QPixmap("icons/logo.png"));
    setWindowTitle(tr("New Game"));
}

void NewGameWizard::showHelp()
{
    static QString  lastHelpMessage;
    QString         message;

    switch (currentId())
    {
    case Page_Intro:
        message = tr("Select if you are a returning player or a new player.");
        break;
    case Page_CreatePlayer:
        message = tr("Create a new player name.");
        break;
    case Page_LoadPlayer:
        message = tr("Select from existing player names.");
        break;
    case Page_RecruitUnits:
        message = tr("Recruit units from available sprites.");
        break;
    case Page_SelectMap:
        message = tr("Select map.");
        break;
    default:
        message = tr("This help is likely not to be of any help.");
    }

    if (lastHelpMessage == message)
        message = tr("Blah blah blah.");

    QMessageBox::information(this, tr("New Game Help"), message);

    lastHelpMessage = message;
}


IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    topLabel = new QLabel(tr("This wizard will help you register your copy of "
                             "<i>Super Product One</i>&trade; or start "
                             "evaluating the product."));
    topLabel->setWordWrap(true);

    //registerRadioButton = new QRadioButton(tr("&Register your copy"));
    //evaluateRadioButton = new QRadioButton(tr("&Evaluate the product for 30 "
                                              "days"));
    //registerRadioButton->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addWidget(registerRadioButton);
    layout->addWidget(evaluateRadioButton);
    setLayout(layout);
}
