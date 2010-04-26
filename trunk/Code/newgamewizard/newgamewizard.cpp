#include <QtGui>

//#include "test_db.h"
#include "newgamewizard.h"

NewGameWizard::NewGameWizard(QWidget *parent)
    : QWizard(parent)
{
    test_GenerateSprites();

    // Set New Game dialog pages
    setPage(Page_Intro, new IntroPage);
    setPage(Page_CreatePlayer, new CreatePlayerPage);
    setPage(Page_LoadPlayer, new LoadPlayerPage);
    //setPage(Page_RecruitUnits, new RecruitUnitsPage);
    //setPage(Page_SelectMap, new SelectMapPage);
    setPage(Page_Conclusion, new ConclusionPage);

    // Set start page
    setStartId(Page_Intro);

    setOption(HaveHelpButton, true);

    // Connect Help slot
    connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));

    // Set window logo and title
    setWindowIcon(QIcon("icons/logo.png"));
    //setPixmap(QWizard::LogoPixmap, QPixmap("icons/logo.png"));
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
    /*case Page_RecruitUnits:
        message = tr("Recruit units from available sprites.");
        break;
    case Page_SelectMap:
        message = tr("Select map.");
        break;*/
    case Page_Conclusion:
        message = tr("Conclusion.");
        break;
    default:
        message = tr("This help is likely not to be of any help.");
    }

    if (lastHelpMessage == message)
        message = tr("Blah blah blah.");

    QMessageBox::information(this, tr("New Game Help"), message);

    lastHelpMessage = message;
}

void NewGameWizard::test_GenerateSprites()
{
    sprites[0].name = "Wizard";
    sprites[0].image.load("sprites/wizard.png");
    sprites[0].AP = 8;
    sprites[0].HP = 8;
    sprites[0].range = 8;

    sprites[1].name = "Monk";
    sprites[1].image.load("sprites/buddhist.png");
    sprites[1].AP = 6;
    sprites[1].HP = 6;
    sprites[1].range = 6;

    sprites[2].name = "Bard";
    sprites[2].image.load("sprites/bard.png");
    sprites[2].AP = 4;
    sprites[2].HP = 4;
    sprites[2].range = 4;

    sprites[3].name = "Desert Soldier";
    sprites[3].image.load("sprites/desertsoldier.png");
    sprites[3].AP = 4;
    sprites[3].HP = 4;
    sprites[3].range = 4;
}


IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    topLabel = new QLabel(tr("This dialog takes you through the options for a new game."));
    topLabel->setWordWrap(true);

    // Initialize radio buttons
    newPlayerRadioButton = new QRadioButton(tr("N&ew Player"));
    returningPlayerRadioButton = new QRadioButton(tr("&Returning Player"));
    newPlayerRadioButton->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addWidget(newPlayerRadioButton);
    layout->addWidget(returningPlayerRadioButton);
    setLayout(layout);
}


int IntroPage::nextId() const
{
    if (returningPlayerRadioButton->isChecked())
        return NewGameWizard::Page_LoadPlayer;
    else
        return NewGameWizard::Page_CreatePlayer;
}

CreatePlayerPage::CreatePlayerPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Create Player"));
    setSubTitle(tr("Enter new player name."));

    playerNameLabel = new QLabel(tr("&Player Name:"));
    playerNameLineEdit = new QLineEdit;
    playerNameLabel->setBuddy(playerNameLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playerNameLabel, 0, 0);
    layout->addWidget(playerNameLineEdit, 0, 1);
    //layout->addWidget(playerNameLabel, 1, 0);
    //layout->addWidget(playerNameLineEdit, 1, 1);
    setLayout(layout);
}

int CreatePlayerPage::nextId() const
{
    //return NewGameWizard::Page_RecruitUnits;
    return NewGameWizard::Page_Conclusion;
}

LoadPlayerPage::LoadPlayerPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Load Player."));
    setSubTitle(tr("Select player name from drop down menu."));

    playerNameLabel = new QLabel(tr("&Player Name:"));

    playerNameComboBox = new QComboBox;
    playerNameComboBox->addItem(tr("Blah1"));
    playerNameComboBox->addItem(tr("Blah2"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playerNameLabel, 0, 0);
    layout->addWidget(playerNameComboBox, 0, 1);
    setLayout(layout);
}

int LoadPlayerPage::nextId() const
{
    //return NewGameWizard::Page_RecruitUnits;
    return NewGameWizard::Page_Conclusion;
}

void RecruitUnitsPage::nextSpritePushButtonClicked()
{
    spriteIndex = (spriteIndex + 1) % MAX_SPRITES;
}


void RecruitUnitsPage::prevSpritePushButtonClicked()
{
    spriteIndex = (spriteIndex + MAX_SPRITES - 1) % MAX_SPRITES;
    spriteLabel->setPixmap();
}


ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Completion"));
    //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    bottomLabel = new QLabel;
    bottomLabel = new QLabel(tr("You have completed the New Game options."));
    bottomLabel->setWordWrap(true);

    //agreeCheckBox = new QCheckBox(tr("I agree to the terms of the license"));

    //registerField("conclusion.agree*", agreeCheckBox);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(bottomLabel);
    //layout->addWidget(agreeCheckBox);
    setLayout(layout);
}

int ConclusionPage::nextId() const
{
    return -1;
}
