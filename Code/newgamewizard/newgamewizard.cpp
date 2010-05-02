#include <QtGui>

#include "globals.h"
#include "test_db.h"
#include "newgamewizard.h"

QString NewGameWizard::playerName;
//User    NewGameWizard::tempUser;

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

    connect(button(NextButton), SIGNAL(clicked()), this, SLOT(nextButtonClicked()));
}

void NewGameWizard::nextButtonClicked()
{
    int i;

    switch (currentId())
    {
    // Creater new user if non-existent
    case Page_RecruitUnits:
        for (i = 0; i < db.userCount(); i++)
        {
            if (db.userName(i) == NewGameWizard::playerName)
                return;
        }
        db.addUser(NewGameWizard::playerName);
        break;
    }
}


void NewGameWizard::setPlayerName(const QString &userName)
{
    NewGameWizard::playerName = userName;
}


void NewGameWizard::showHelp()
{
    static QString  lastHelpMessage;
    QString         message;

    switch (currentId())
    {
    case Page_Intro:
        message = tr("Indicate if you are a returning player or a new player");
        break;
    case Page_CreatePlayer:
        message = tr("The player name will be associated with the games you save");
        break;
    case Page_LoadPlayer:
        message = tr("The drop-down menu is a list of all the players in the database");
        break;
    case Page_RecruitUnits:
        message = tr("From the available units, recruit up to 4 units for your team");
        break;
    /*case Page_SelectMap:
        message = tr("Select a desired battle map");
        break;*/
    case Page_Conclusion:
        message = tr("The battle resumes after this");
        break;
    default:
        message = tr("This help is likely not to be of any help :-(");
    }

    if (lastHelpMessage == message)
        message = tr("That's all the help you're getting!!");

    QMessageBox::information(this, tr("New Game Help"), message);

    lastHelpMessage = message;
}


IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    topLabel = new QLabel(tr("This dialog takes you through the options for a new game"));
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
    setSubTitle(tr("Type a new player name"));

    playerNameLabel = new QLabel(tr("&Player Name:"));
    playerNameLineEdit = new QLineEdit;
    playerNameLabel->setBuddy(playerNameLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playerNameLabel, 0, 0);
    layout->addWidget(playerNameLineEdit, 0, 1);
    //layout->addWidget(playerNameLabel, 1, 0);
    //layout->addWidget(playerNameLineEdit, 1, 1);
    setLayout(layout);

    registerField("player.name*", playerNameLineEdit);
    //connect(playerNameLineEdit, SIGNAL(textChanged(QString &)), this, SLOT(playerNameCreated(QString &)));
    connect(playerNameLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(playerNameCreated(const QString &)));
    //connect(QWizard::NextButton, SIGNAL(clicked()), this, SLOT(nextButtonClicked()));
    //connect(NewGameWizard::button(NewGameWizard::NextButton), SIGNAL(clicked()), this, SLOT(nextButtonClicked()));
}

void CreatePlayerPage::nextButtonClicked()
{

}

void CreatePlayerPage::playerNameCreated(const QString &userName)
//void CreatePlayerPage::playerNameCreated(QString &userName)
{
    //db.addUser(userName);
    //NewGameWizard::tempUser = db.loadUser(userName);
    NewGameWizard::setPlayerName(playerNameLineEdit->text());
    //db.addUser(userName);
}

int CreatePlayerPage::nextId() const
{
    //return NewGameWizard::Page_RecruitUnits;
    return NewGameWizard::Page_RecruitUnits;
}

LoadPlayerPage::LoadPlayerPage(QWidget *parent)
    : QWizardPage(parent)
{
    int i;

    setTitle(tr("Load Player."));
    setSubTitle(tr("Select player name from drop-down menu"));

    playerNameLabel = new QLabel(tr("Player Name:"));

    playerNameComboBox = new QComboBox;

    for (i = 0; i < db.userCount(); i++)
        userNames << db.userName(i);

    userNames.sort();

    for (i = 0; i < userNames.count(); i++)
        playerNameComboBox->addItem(userNames.at(i));

    //playerNameComboBox->addItem(tr("Blah1"));
    //playerNameComboBox->addItem(tr("Blah2"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playerNameLabel, 0, 0);
    layout->addWidget(playerNameComboBox, 0, 1);
    setLayout(layout);

    connect(playerNameComboBox, SIGNAL(activated(int)), this, SLOT(playerNameChanged(int)));
    connect(playerNameComboBox, SIGNAL(activated(int)), this, SLOT(playerNameChanged2(int)));
}

void LoadPlayerPage::playerNameChanged(int index)
{
    //NewGameWizard::tempUser = db.loadUser(userNames.at(index));
    NewGameWizard::setPlayerName(userNames.at(index));
}


void LoadPlayerPage::playerNameChanged2(int index)
{
    //NewGameWizard::tempUser = db.loadUser(userNames.at(index));
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

    //test_GenerateSprites();

    // Initialize test database
    //db = new Database;
    //Database db;

    setTitle(tr("Recruit Units"));
    setSubTitle(tr("Recruit units for battle"));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QGroupBox *spriteBox = new QGroupBox(tr("&Available Units"));
    spriteBox->setObjectName(QString::fromUtf8("spriteBox"));
    
    QGridLayout *spriteBoxLayout = new QGridLayout(spriteBox);
    spriteBoxLayout->setObjectName(QString::fromUtf8("spriteBoxLayout"));

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->setObjectName(QString::fromUtf8("leftLayout"));
    
    QHBoxLayout *leftTopLayout = new QHBoxLayout;
    leftTopLayout->setObjectName(QString::fromUtf8("leftTopLayout"));

    prevSpriteButton = new QPushButton(tr("<<"), spriteBox);
    prevSpriteButton->setObjectName(QString::fromUtf8("prevSpriteButton"));
    prevSpriteButton->setMaximumSize(QSize(31, 23));
    leftTopLayout->addWidget(prevSpriteButton);

    spriteImage = new QLabel(spriteBox);
    spriteImage->setObjectName(QString::fromUtf8("spriteImage"));
    spriteImage->setMinimumSize(QSize(71, 101));
    spriteImage->setMaximumSize(QSize(71, 101));
    spriteImage->setPixmap(db.spritePixMap(0));
    spriteImage->setScaledContents(true);
    leftTopLayout->addWidget(spriteImage);

    nextSpriteButton = new QPushButton(tr(">>"), spriteBox);
    nextSpriteButton->setObjectName(QString::fromUtf8("nextSpriteButton"));
    nextSpriteButton->setMaximumSize(QSize(31, 23));
    leftTopLayout->addWidget(nextSpriteButton);
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
    spriteName = new QLabel(tr("Name:"), spriteBox);
    spriteName->setObjectName(QString::fromUtf8("spriteName"));
    spriteStatsLayout->addWidget(spriteName, 0, 0, 1, 1);
    
    //spriteNameValue = new QLabel(this);
    spriteNameVal = new QLabel(spriteBox);
    spriteNameVal->setObjectName(QString::fromUtf8("spriteNameVal"));
    spriteNameVal->setText(db.spriteName(0));
    spriteStatsLayout->addWidget(spriteNameVal, 0, 1, 1, 1);

    //spriteAP = new QLabel(tr("AP:"));
    spriteAP = new QLabel(tr("AP:"), spriteBox);
    spriteAP->setObjectName(QString::fromUtf8("spriteAP"));
    spriteStatsLayout->addWidget(spriteAP, 1, 0, 1, 1);
    
    //spriteAPValue = new QLabel(this);
    spriteAPVal = new QLabel(spriteBox);
    spriteAPVal->setObjectName(QString::fromUtf8("spriteAPVal"));
    spriteAPVal->setText(QString::number(db.spriteAP(0)));
    spriteStatsLayout->addWidget(spriteAPVal, 1, 1, 1, 1);

    //spriteHP = new QLabel(tr("HP:"));
    spriteHP = new QLabel(tr("HP:"), spriteBox);
    spriteHP->setObjectName(QString::fromUtf8("spriteHP"));
    spriteStatsLayout->addWidget(spriteHP, 2, 0, 1, 1);
    
    //spriteHPValue = new QLabel(this);
    spriteHPVal = new QLabel(spriteBox);
    spriteHPVal->setObjectName(QString::fromUtf8("spriteHPVal"));
    spriteHPVal->setText(QString::number(db.spriteHP(0)));
    spriteStatsLayout->addWidget(spriteHPVal, 2, 1, 1, 1);

    //spriteRange = new QLabel(tr("Range:"));
    spriteRange = new QLabel(tr("Range:"), spriteBox);
    spriteRange->setObjectName(QString::fromUtf8("spriteRange"));
    spriteStatsLayout->addWidget(spriteRange, 3, 0, 1, 1);

    //spriteRangeValue = new QLabel(this);
    spriteRangeVal = new QLabel(spriteBox);
    spriteRangeVal->setObjectName(QString::fromUtf8("spriteRangeVal"));
    spriteRangeVal->setText(QString::number(db.spriteRange(0)));
    spriteStatsLayout->addWidget(spriteRangeVal, 3, 1, 1, 1);
    leftMidLayout->addLayout(spriteStatsLayout);

    QSpacerItem *hRightSpacerSpriteStats = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    leftMidLayout->addItem(hRightSpacerSpriteStats);
    leftLayout->addLayout(leftMidLayout);

    QHBoxLayout *leftBotLayout = new QHBoxLayout;
    leftBotLayout->setObjectName(QString::fromUtf8("leftBotLayout"));

    QSpacerItem *hLeftSpacerRecruit = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    leftBotLayout->addItem(hLeftSpacerRecruit);

    recruitButton = new QPushButton(tr("&Recruit"), spriteBox);
    recruitButton->setObjectName(QString::fromUtf8("recruitButton"));
    leftBotLayout->addWidget(recruitButton);

    QSpacerItem *hRightSpacerRecruit = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    leftBotLayout->addItem(hRightSpacerRecruit);
    leftLayout->addLayout(leftBotLayout);
    spriteBoxLayout->addLayout(leftLayout, 0, 0, 1, 1);
    mainLayout->addWidget(spriteBox);

    QGroupBox *unitsBox = new QGroupBox(tr("&Player Units"));
    unitsBox->setObjectName(QString::fromUtf8("unitsBox"));
    
    QGridLayout *unitBoxLayout = new QGridLayout(unitsBox);
    unitBoxLayout->setObjectName(QString::fromUtf8("unitBoxLayout"));

    //QVBoxLayout *rightLayout = new QVBoxLayout;

    for (i = 0; i < MAX_UNITS; i++)
    {
        QHBoxLayout *rightUnitLayout = new QHBoxLayout();
        //rightUnitLayout->setObjectName(QString::fromUtf8("rightUnitLayout1"));
        QLabel *unitImage = new QLabel(unitsBox);
        //unitImage->setObjectName(QString::fromUtf8("unitImage1"));
        unitImage->setMaximumSize(QSize(41, 41));
        unitImage->setMinimumSize(QSize(41, 41));
        unitImage->setPixmap(QPixmap(QString::fromUtf8("sprites/blank.PNG")));
        unitImage->setScaledContents(true);
        rightUnitLayout->addWidget(unitImage);

        QVBoxLayout *unitRejectLayout = new QVBoxLayout;
        //unitRejectLayout->setObjectName(QString::fromUtf8("unitRejectLayout1"));
        QLabel *unitName = new QLabel(tr("Unit"), unitsBox);
        //unitName->setObjectName(QString::fromUtf8("unitName1"));
        unitRejectLayout->addWidget(unitName);

        QPushButton *rejectButton = new QPushButton(tr("Reject"), unitsBox);
        //rejectPushButton->setObjectName(QString::fromUtf8("rejectPushButton"));
        unitRejectLayout->addWidget(rejectButton);
        rightUnitLayout->addLayout(unitRejectLayout);
        unitBoxLayout->addLayout(rightUnitLayout, i, 0, 1, 1);

        unitImageList << unitImage;
        unitNameList << unitName;
        rejectButtonList << rejectButton;
    }

    mainLayout->addWidget(unitsBox);
    setLayout(mainLayout);

    //i = 0;
    
    connect(nextSpriteButton, SIGNAL(clicked()), this, SLOT(nextSpriteButtonClicked()));
    connect(prevSpriteButton, SIGNAL(clicked()), this, SLOT(prevSpriteButtonClicked()));
    connect(recruitButton, SIGNAL(clicked()), this, SLOT(recruitButtonClicked()));
    connect(rejectButtonList[0], SIGNAL(clicked()), this, SLOT(rejectButton0Clicked()));
    connect(rejectButtonList[1], SIGNAL(clicked()), this, SLOT(rejectButton1Clicked()));
    connect(rejectButtonList[2], SIGNAL(clicked()), this, SLOT(rejectButton2Clicked()));
    connect(rejectButtonList[3], SIGNAL(clicked()), this, SLOT(rejectButton3Clicked()));
}

/*void RecruitUnitsPage::test_GenerateSprites()
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
*/

void RecruitUnitsPage::nextSpriteButtonClicked()
{
    spriteIndex = (spriteIndex + 1) % MAX_SPRITES;

    spriteImage->setPixmap(db.spritePixMap(spriteIndex));
    spriteNameVal->setText(db.spriteName(spriteIndex));
    spriteAPVal->setText(QString::number(db.spriteAP(spriteIndex)));
    spriteHPVal->setText(QString::number(db.spriteHP(spriteIndex)));
    spriteRangeVal->setText(QString::number(db.spriteRange(spriteIndex)));
}


void RecruitUnitsPage::prevSpriteButtonClicked()
{
    spriteIndex = (spriteIndex + MAX_SPRITES - 1) % MAX_SPRITES;

    spriteImage->setPixmap(db.spritePixMap(spriteIndex));
    spriteNameVal->setText(db.spriteName(spriteIndex));
    spriteAPVal->setText(QString::number(db.spriteAP(spriteIndex)));
    spriteHPVal->setText(QString::number(db.spriteHP(spriteIndex)));
    spriteRangeVal->setText(QString::number(db.spriteRange(spriteIndex)));
}

void RecruitUnitsPage::recruitButtonClicked()
{
    for (i = 0; i < MAX_UNITS; i++)
    {
        if (!isAlive[i])
        {
            QList<Unit> tempUnits = db.loadUnits(NewGameWizard::playerName);
            
            unitImageList[i]->setPixmap(*(spriteImage->pixmap()));
            unitNameList[i]->setText(spriteNameVal->text());
            isAlive[i] = true;

            //NewGameWizard::tempUser.units[i].pixMap.load((*(spriteImage->pixmap())));
            tempUnits[i].pixMap.operator =((*(spriteImage->pixmap())));
            //NewGameWizard::tempUser.units[i].image.load((*(spriteImage->pixmap())));
            tempUnits[i].image.operator =((spriteImage->pixmap()->toImage()));
            tempUnits[i].name = spriteNameVal->text();
            tempUnits[i].status = UNIT_OK;

            db.saveUnits(NewGameWizard::playerName, tempUnits);

            break;
        }
    }
}

void RecruitUnitsPage::rejectButton0Clicked()
{
    rejectButtonAnyClicked(0);
}

void RecruitUnitsPage::rejectButton1Clicked()
{
    rejectButtonAnyClicked(1);
}

void RecruitUnitsPage::rejectButton2Clicked()
{
    rejectButtonAnyClicked(2);
}

void RecruitUnitsPage::rejectButton3Clicked()
{
    rejectButtonAnyClicked(3);
}

void RecruitUnitsPage::rejectButtonAnyClicked(int index)
{
    if (isAlive[index])
    {
        unitImageList[index]->setPixmap(QPixmap(QString::fromUtf8("sprites/blank.PNG")));
        unitNameList[index]->setText("Unit");
        isAlive[index] = false;
/*
        NewGameWizard::tempUser.units[index].pixMap.load(QString::fromUtf8("sprites/blank.PNG"));
        NewGameWizard::tempUser.units[index].name = "Unit";
        NewGameWizard::tempUser.units[index].status = UNIT_OK;NewGameWizard::tempUser.units[i].status = NO_UNIT;*/
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
    bottomLabel = new QLabel(tr("You have completed the New Game options"));
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
