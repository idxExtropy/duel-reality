#include <QtGui>

//#include "test_db.h"
#include "newgamewizard.h"

NewGameWizard::NewGameWizard(QWidget *parent)
    : QWizard(parent)
{
    // Set New Game dialog pages
    setPage(Page_Intro, new IntroPage);
    setPage(Page_CreatePlayer, new CreatePlayerPage);
    setPage(Page_LoadPlayer, new LoadPlayerPage);
    setPage(Page_RecruitUnits, new RecruitUnitsPage);
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
    return NewGameWizard::Page_RecruitUnits;
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
    return NewGameWizard::Page_RecruitUnits;
}

RecruitUnitsPage::RecruitUnitsPage(QWidget *parent)
    : QWizardPage(parent)
{
    spriteIndex = 0;

    test_GenerateSprites();

    setTitle(tr("Recruit Units"));
    setSubTitle(tr("Recruit player units."));

    spriteLabel = new QLabel(this);
    spriteLabel->setGeometry(QRect(335, 140, 51, 111));
    spriteLabel->setPixmap(sprites[0].pixMap);
    //spriteLabel->setMask(sprites[0].pixMap.mask());

    spriteName = new QLabel(tr("Name:"));
    spriteNameValue = new QLabel(this);
    spriteNameValue->setText(sprites[0].name);

    spriteAP = new QLabel(tr("AP:"));
    spriteAPValue = new QLabel(this);
    spriteAPValue->setText(QString::number(sprites[0].AP));

    spriteHP = new QLabel(tr("HP:"));
    spriteHPValue = new QLabel(this);
    spriteHPValue->setText(QString::number(sprites[0].HP));

    spriteRange = new QLabel(tr("Range:"));
    spriteRangeValue = new QLabel(this);
    spriteRangeValue->setText(QString::number(sprites[0].range));

    nextSpritePushButton = new QPushButton(tr("&Next"), this);
    prevSpritePushButton = new QPushButton(tr("&Previous"), this);

    QGridLayout *statsLayout = new QGridLayout;
    statsLayout->addWidget(spriteName, 0, 0);
    statsLayout->addWidget(spriteNameValue, 0, 1);
    statsLayout->addWidget(spriteAP, 1, 0);
    statsLayout->addWidget(spriteAPValue, 1, 1);
    statsLayout->addWidget(spriteHP, 2, 0);
    statsLayout->addWidget(spriteHPValue, 2, 1);
    statsLayout->addWidget(spriteRange, 3, 0);
    statsLayout->addWidget(spriteRangeValue, 3, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(prevSpritePushButton);
    buttonsLayout->addWidget(nextSpritePushButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(spriteLabel);
    layout->addLayout(statsLayout);
    layout->addLayout(buttonsLayout);
    setLayout(layout);

    connect(nextSpritePushButton, SIGNAL(clicked()), this, SLOT(nextSpritePushButtonClicked()));
    connect(prevSpritePushButton, SIGNAL(clicked()), this, SLOT(prevSpritePushButtonClicked()));

    //recruitPushButton = new QPushButton(this);
}

void RecruitUnitsPage::test_GenerateSprites()
{
    sprites[0].name = "Wizard";
    sprites[0].pixMap.load("sprites/wizard.png");
    sprites[0].AP = 8;
    sprites[0].HP = 8;
    sprites[0].range = 8;

    sprites[1].name = "Monk";
    sprites[1].pixMap.load("sprites/buddhist.png");
    sprites[1].AP = 6;
    sprites[1].HP = 6;
    sprites[1].range = 6;

    sprites[2].name = "Bard";
    sprites[2].pixMap.load("sprites/bard.png");
    sprites[2].AP = 4;
    sprites[2].HP = 4;
    sprites[2].range = 4;

    sprites[3].name = "Desert Soldier";
    sprites[3].pixMap.load("sprites/desertsoldier.png");
    sprites[3].AP = 4;
    sprites[3].HP = 4;
    sprites[3].range = 4;
}


void RecruitUnitsPage::nextSpritePushButtonClicked()
{
    spriteIndex = (spriteIndex + 1) % MAX_SPRITES;

    spriteLabel->setPixmap(sprites[spriteIndex].pixMap);
    spriteNameValue->setText(sprites[spriteIndex].name);
    spriteAPValue->setText(QString::number(sprites[spriteIndex].AP));
    spriteHPValue->setText(QString::number(sprites[spriteIndex].HP));
    spriteRangeValue->setText(QString::number(sprites[spriteIndex].range));
}


void RecruitUnitsPage::prevSpritePushButtonClicked()
{
    spriteIndex = (spriteIndex + MAX_SPRITES - 1) % MAX_SPRITES;
    //spriteLabel->setPixmap();
    spriteLabel->setPixmap(sprites[spriteIndex].pixMap);
    spriteNameValue->setText(sprites[spriteIndex].name);
    spriteAPValue->setText(QString::number(sprites[spriteIndex].AP));
    spriteHPValue->setText(QString::number(sprites[spriteIndex].HP));
    spriteRangeValue->setText(QString::number(sprites[spriteIndex].range));
}


int RecruitUnitsPage::nextId() const
{
    //return NewGameWizard::Page_RecruitUnits;
    return NewGameWizard::Page_Conclusion;
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
