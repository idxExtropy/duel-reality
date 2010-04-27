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
    i = 0;
    spriteIndex = 0;

    test_GenerateSprites();

    setTitle(tr("Recruit Units"));
    setSubTitle(tr("Recruit player units."));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QGroupBox *spriteBox = new QGroupBox;
    spriteBox->setObjectName(QString::fromUtf8("spriteBox"));
    
    QGridLayout *spriteBoxLayout = new QGridLayout(spriteBox);
    spriteBoxLayout->setObjectName(QString::fromUtf8("spriteBoxLayout"));

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->setObjectName(QString::fromUtf8("leftLayout"));
    
    QHBoxLayout *leftTopLayout = new QHBoxLayout;
    leftTopLayout->setObjectName(QString::fromUtf8("leftTopLayout"));

    prevSpritePushButton = new QPushButton(spriteBox);
    prevSpritePushButton->setObjectName(QString::fromUtf8("prevSpritePushButton"));
    prevSpritePushButton->setMaximumSize(QSize(31, 23));
    leftTopLayout->addWidget(prevSpritePushButton);

    spriteImage = new QLabel(spriteBox);
    spriteImage->setObjectName(QString::fromUtf8("spriteImage"));
    spriteImage->setMaximumSize(QSize(71, 101));
    //spriteImage->setPixmap(QPixmap(QString::fromUtf8("debug/sprites/desertsoldier.png")));
    spriteImage->setScaledContents(true);
    leftTopLayout->addWidget(spriteImage);

    nextSpritePushButton = new QPushButton(spriteBox);
    nextSpritePushButton->setObjectName(QString::fromUtf8("nextSpritePushButton"));
    nextSpritePushButton->setMaximumSize(QSize(31, 23));
    leftTopLayout->addWidget(nextSpritePushButton);
    leftLayout->addLayout(leftTopLayout);

    QHBoxLayout *leftMidLayout = new QHBoxLayout;
    leftMidLayout->setObjectName(QString::fromUtf8("leftMidLayout"));
    QSpacerItem *hLeftSpacerSpriteStats = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    leftMidLayout->addItem(hLeftSpacerSpriteStats);

    QGridLayout *spriteStatsLayout = new QGridLayout;
    spriteStatsLayout->setObjectName(QString::fromUtf8("spriteStatsLayout"));

    //spriteLabel = new QLabel(this);
    //spriteLabel->setGeometry(QRect(335, 140, 51, 111));
    //spriteLabel->setPixmap(sprites[0].pixMap);

    //spriteName = new QLabel(tr("Name:"));
    spriteName = new QLabel(spriteBox);
    spriteName->setObjectName(QString::fromUtf8("spriteName"));
    spriteStatsLayout->addWidget(spriteName, 0, 0, 1, 1);
    
    //spriteNameValue = new QLabel(this);
    spriteNameVal = new QLabel(spriteBox);
    spriteNameVal->setObjectName(QString::fromUtf8("spriteNameVal"));
    spriteNameVal->setText(sprites[0].name);
    spriteStatsLayout->addWidget(spriteNameVal, 0, 1, 1, 1);

    spriteAP = new QLabel(tr("AP:"));
    spriteAPValue = new QLabel(this);
    spriteAPValue->setText(QString::number(sprites[0].AP));

    spriteHP = new QLabel(tr("HP:"));
    spriteHPValue = new QLabel(this);
    spriteHPValue->setText(QString::number(sprites[0].HP));

    spriteRange = new QLabel(tr("Range:"));
    spriteRangeValue = new QLabel(this);
    spriteRangeValue->setText(QString::number(sprites[0].range));

    
    
    recruitPushButton = new QPushButton(tr("&Recruit"), this);
    recruitPushButton->setObjectName(QString::fromUtf8("recruitPushButton"));

    QGridLayout *statsLayout = new QGridLayout;
    statsLayout->setObjectName(QString::fromUtf8("statsLayout"));
    statsLayout->addWidget(spriteName, 0, 0);
    statsLayout->addWidget(spriteNameValue, 0, 1);
    statsLayout->addWidget(spriteAP, 1, 0);
    statsLayout->addWidget(spriteAPValue, 1, 1);
    statsLayout->addWidget(spriteHP, 2, 0);
    statsLayout->addWidget(spriteHPValue, 2, 1);
    statsLayout->addWidget(spriteRange, 3, 0);
    statsLayout->addWidget(spriteRangeValue, 3, 1);

    QHBoxLayout *leftMidRightLayout = new QHBoxLayout;
    leftMidRightLayout->addLayout(statsLayout);
    leftMidRightLayout->addStretch();

    

    //QGridLayout *spriteLayout = new QGridLayout;
    QHBoxLayout *spriteLayout = new QHBoxLayout;
    spriteLayout->setSpacing(6);
    spriteLayout->setObjectName(QString::fromUtf8("spriteLayout"));
    //spriteLayout->addWidget(prevSpritePushButton, 0, 0, 1, 1);
    spriteLayout->addWidget(prevSpritePushButton);
    //spriteLayout->addWidget(spriteLabel, 0, 1, 1, 1);
    spriteLayout->addWidget(spriteLabel);
    //spriteLayout->addWidget(nextSpritePushButton, 0, 2, 1, 1);
    spriteLayout->addWidget(nextSpritePushButton);
    spriteLayout->addStretch();

    QSpacerItem *hSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *hSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    QHBoxLayout *midLeftLayout = new QHBoxLayout;
    midLeftLayout->setSpacing(6);
    midLeftLayout->setObjectName(QString::fromUtf8("midLeftLayout"));
    midLeftLayout->addItem(hSpacer_1);
    midLeftLayout->addWidget(recruitPushButton);
    midLeftLayout->addItem(hSpacer_2);
    midLeftLayout->addStretch();

    QVBoxLayout *topLeftLayout = new QVBoxLayout;
    topLeftLayout->addLayout(spriteLayout);
    topLeftLayout->addLayout(midLeftLayout);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->setSpacing(6);
    leftLayout->setContentsMargins(11, 11, 11, 11);
    leftLayout->setObjectName(QString::fromUtf8("leftLayout"));
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->addLayout(topLeftLayout);
    //leftLayout->addLayout(spriteLayout);
    //leftLayout->addLayout(midLeftLayout);
    leftLayout->addLayout(leftMidRightLayout);
    leftLayout->addStretch();

    QVBoxLayout *rightLayout = new QVBoxLayout;

    for (i = 0; i < MAX_UNITS; i++)
    {
        QFrame *frame = new QFrame(this);
        //frame->setGeometry(QRect(290, 100, 69, 124));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        QGridLayout *gridLayout = new QGridLayout(frame);

        QLabel *unitLabel = new QLabel(frame);
        unitLabel->setPixmap(QPixmap(QString::fromUtf8("sprites/blank.png")));
        unitLabel->setScaledContents(true);
        unitsLabel << unitLabel;
        gridLayout->addWidget(unitsLabel[i], 0, 0, 1, 1);
        //QPushButton *blah = new QPushButton;
        //unitLabel->setGeometry(QRect(335, 140, 51, 111));
        rightLayout->addWidget(frame);
        //rightLayout->addWidget(blah);
        //unitsLabel << unitLabel;
    }

    i = 0;

    
    
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    connect(nextSpritePushButton, SIGNAL(clicked()), this, SLOT(nextSpritePushButtonClicked()));
    connect(prevSpritePushButton, SIGNAL(clicked()), this, SLOT(prevSpritePushButtonClicked()));
    connect(recruitPushButton, SIGNAL(clicked()), this, SLOT(recruitPushButtonClicked()));

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

void RecruitUnitsPage::recruitPushButtonClicked()
{
    if (i < MAX_UNITS)
    {
        unitsLabel[i]->setPixmap(*(spriteLabel->pixmap()));;
        i++;
    }

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
