#include <QtGui>

#include "globals.h"
#include "test_db.h"
#include "loadgamewizard.h"
#include "glwidget.h"

QString LoadGameWizard::playerName;


LoadGameWizard::LoadGameWizard(QWidget *parent)
    : QWizard(parent)
{
    // Set Load Game dialog pages
    setPage(Page_Intro, new IntroPageL);
    setPage(Page_LoadPlayer, new LoadPlayerPageL);
    setPage(Page_RecruitUnits, new RecruitUnitsPageL);
    setPage(Page_UpgradeUnits, new UpgradeUnitsPageL);
    setPage(Page_SelectMode, new SelectModePageL);
    setPage(Page_SelectMap, new SelectMapPageL);
    setPage(Page_Conclusion, new ConclusionPageL);

    // Set start page
    setStartId(Page_Intro);

    setOption(HaveHelpButton, true);

    // Connect Help slot
    connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));

    // Set window logo and title
    setWindowIcon(QIcon("icons/logo.png"));
    setWindowTitle(tr("Load Game"));

    // Check for logic execution each time next button is clicked
    //connect(button(NextButton), SIGNAL(clicked()), this, SLOT(nextButtonClicked()));
    connect(button(FinishButton), SIGNAL(clicked()), this, SLOT(finishButtonClicked()));
}

void LoadGameWizard::finishButtonClicked()
{
    db.activateUser(LoadGameWizard::playerName);
}

/*
void LoadGameWizard::nextButtonClicked()
{
    int i;

    switch (currentId())
    {
    // Before units can be recruited, create new user if non-existent
    case Page_RecruitUnits:
        for (i = 0; i < db.userCount(); i++)
        {
            // Do nothing if user exists
            if (db.userName(i) == LoadGameWizard::playerName)
                return;
        }
        // Otherwise add new user to database
        db.addUser(LoadGameWizard::playerName);
        break;
    }
}
*/

void LoadGameWizard::setPlayerName(const QString &userName)
{
    LoadGameWizard::playerName = userName;
}


void LoadGameWizard::showHelp()
{
    static QString  lastHelpMessage;
    QString         message;

    switch (currentId())
    {
    case Page_Intro:
        message = tr("Indicate if you are a returning player or a new player");
        break;
    case Page_LoadPlayer:
        message = tr("The drop-down menu is a list of all the players in the database");
        break;
    case Page_RecruitUnits:
        message = tr("From the available units, recruit up to 4 units for your team");
        break;
    case Page_UpgradeUnits:
        message = tr("Upgrade units stats using available XP");
        break;
    case Page_SelectMode:
        message = tr("In campaign mode, levels and maps are predetermined");
        break;
    case Page_SelectMap:
        message = tr("Select a desired map for freestyle mode battle");
        break;
    case Page_Conclusion:
        message = tr("The battle resumes after this");
        break;
    default:
        message = tr("This help is likely not to be of any help :-(");
    }

    if (lastHelpMessage == message)
        message = tr("That's all the help you're getting!!");

    QMessageBox::information(this, tr("Load Game Help"), message);

    lastHelpMessage = message;
}


IntroPageL::IntroPageL(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    topLabel = new QLabel(tr("This dialog takes you through the options for loading a saved game"));
    topLabel->setWordWrap(true);

    // Initialize radio buttons
    //newPlayerRadioButton = new QRadioButton(tr("N&ew Player"));
    //returningPlayerRadioButton = new QRadioButton(tr("&Returning Player"));
    //newPlayerRadioButton->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    //layout->addWidget(newPlayerRadioButton);
    //layout->addWidget(returningPlayerRadioButton);
    setLayout(layout);
}


int IntroPageL::nextId() const
{
    return LoadGameWizard::Page_LoadPlayer;
}


LoadPlayerPageL::LoadPlayerPageL(QWidget *parent)
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

    playerNameComboBox->setCurrentIndex(-1);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playerNameLabel, 0, 0);
    layout->addWidget(playerNameComboBox, 0, 1);
    setLayout(layout);

    connect(playerNameComboBox, SIGNAL(activated(int)), this, SLOT(playerNameChanged(int)));
}

void LoadPlayerPageL::playerNameChanged(int index)
{
    LoadGameWizard::setPlayerName(userNames.at(index));
}


int LoadPlayerPageL::nextId() const
{
    return LoadGameWizard::Page_RecruitUnits;
}


RecruitUnitsPageL::RecruitUnitsPageL(QWidget *parent)
    : QWizardPage(parent)
{
    int i;

    // Initialize isAlive flag
    for (i = 0; i < MAX_TEAM_UNITS; i++)
        isAlive[i] = false;

    spriteIndex = 0;
    spriteFileName = db.spriteFileName(0);

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
    spriteImage->setPixmap(spriteFileName);
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

    spriteName = new QLabel(tr("Name:"), spriteBox);
    spriteName->setObjectName(QString::fromUtf8("spriteName"));
    spriteStatsLayout->addWidget(spriteName, 0, 0, 1, 1);
    
    spriteNameVal = new QLabel(spriteBox);
    spriteNameVal->setObjectName(QString::fromUtf8("spriteNameVal"));
    spriteNameVal->setText(db.spriteName(0));
    spriteStatsLayout->addWidget(spriteNameVal, 0, 1, 1, 1);

    spriteAP = new QLabel(tr("AP:"), spriteBox);
    spriteAP->setObjectName(QString::fromUtf8("spriteAP"));
    spriteStatsLayout->addWidget(spriteAP, 1, 0, 1, 1);
    
    spriteAPVal = new QLabel(spriteBox);
    spriteAPVal->setObjectName(QString::fromUtf8("spriteAPVal"));
    spriteAPVal->setText(QString::number(db.spriteAP(0)));
    spriteStatsLayout->addWidget(spriteAPVal, 1, 1, 1, 1);

    spriteHP = new QLabel(tr("HP:"), spriteBox);
    spriteHP->setObjectName(QString::fromUtf8("spriteHP"));
    spriteStatsLayout->addWidget(spriteHP, 2, 0, 1, 1);
    
    spriteHPVal = new QLabel(spriteBox);
    spriteHPVal->setObjectName(QString::fromUtf8("spriteHPVal"));
    spriteHPVal->setText(QString::number(db.spriteHP(0)));
    spriteStatsLayout->addWidget(spriteHPVal, 2, 1, 1, 1);

    spriteRange = new QLabel(tr("Range:"), spriteBox);
    spriteRange->setObjectName(QString::fromUtf8("spriteRange"));
    spriteStatsLayout->addWidget(spriteRange, 3, 0, 1, 1);

    spriteRangeVal = new QLabel(spriteBox);
    spriteRangeVal->setObjectName(QString::fromUtf8("spriteRangeVal"));
    spriteRangeVal->setText(QString::number(db.spriteRange(0)));
    spriteStatsLayout->addWidget(spriteRangeVal, 3, 1, 1, 1);
    //leftMidLayout->addLayout(spriteStatsLayout);

    spriteRate = new QLabel(tr("Rate:"), spriteBox);
    spriteRate->setObjectName(QString::fromUtf8("spriteRate"));
    spriteStatsLayout->addWidget(spriteRate, 4, 0, 1, 1);

    spriteRateVal = new QLabel(spriteBox);
    spriteRateVal->setObjectName(QString::fromUtf8("spriteRateVal"));
    spriteRateVal->setText(QString::number(db.spriteRate(0)));
    spriteStatsLayout->addWidget(spriteRateVal, 4, 1, 1, 1);
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

    //QList<Unit> units = db.loadUnits(LoadGameWizard::playerName);

    // Iteratively fill Player Units section
    for (i = 0; i < MAX_TEAM_UNITS; i++)
    {
        QHBoxLayout *rightUnitLayout = new QHBoxLayout();
        
        QLabel *unitImage = new QLabel(unitsBox);
        
        unitImage->setMaximumSize(QSize(41, 41));
        unitImage->setMinimumSize(QSize(41, 41));
        //if (units[i].status)
            //unitImage->setPixmap(QPixmap(units[i].imageFileName));
        //else
            unitImage->setPixmap(QPixmap(QString::fromUtf8("sprites/blank.PNG")));
        unitImage->setScaledContents(true);
        rightUnitLayout->addWidget(unitImage);

        QVBoxLayout *unitRejectLayout = new QVBoxLayout;
        
        QLabel *unitName = new QLabel(tr("Unit"), unitsBox);
        
        unitRejectLayout->addWidget(unitName);

        QPushButton *rejectButton = new QPushButton(tr("Reject"), unitsBox);
        
        unitRejectLayout->addWidget(rejectButton);
        rightUnitLayout->addLayout(unitRejectLayout);
        unitBoxLayout->addLayout(rightUnitLayout, i, 0, 1, 1);

        unitImageList << unitImage;
        unitNameList << unitName;
        rejectButtonList << rejectButton;
    }

    mainLayout->addWidget(unitsBox);
    setLayout(mainLayout);
    
    connect(nextSpriteButton, SIGNAL(clicked()), this, SLOT(nextSpriteButtonClicked()));
    connect(prevSpriteButton, SIGNAL(clicked()), this, SLOT(prevSpriteButtonClicked()));
    connect(recruitButton, SIGNAL(clicked()), this, SLOT(recruitButtonClicked()));
    connect(rejectButtonList[0], SIGNAL(clicked()), this, SLOT(rejectButton0Clicked()));
    connect(rejectButtonList[1], SIGNAL(clicked()), this, SLOT(rejectButton1Clicked()));
    connect(rejectButtonList[2], SIGNAL(clicked()), this, SLOT(rejectButton2Clicked()));
    connect(rejectButtonList[3], SIGNAL(clicked()), this, SLOT(rejectButton3Clicked()));
}

void RecruitUnitsPageL::initializePage()
{
    int i;
    QList<Unit> units = db.loadUnits(LoadGameWizard::playerName);

    for (i = 0; i < MAX_TEAM_UNITS; i++)
    {
        if (units[i].status)
        {
            unitImageList[i]->setPixmap(units[i].imageFileName);
            unitNameList[i]->setText(units[i].name);
            isAlive[i] = true;
        }
    }
}

void RecruitUnitsPageL::nextSpriteButtonClicked()
{
    spriteIndex = (spriteIndex + 1) % MAX_SPRITES;
    spriteFileName = db.spriteFileName(spriteIndex);

    spriteImage->setPixmap(spriteFileName);
    spriteNameVal->setText(db.spriteName(spriteIndex));
    spriteAPVal->setText(QString::number(db.spriteAP(spriteIndex)));
    spriteHPVal->setText(QString::number(db.spriteHP(spriteIndex)));
    spriteRangeVal->setText(QString::number(db.spriteRange(spriteIndex)));
    spriteRateVal->setText(QString::number(db.spriteRate(spriteIndex)));
}


void RecruitUnitsPageL::prevSpriteButtonClicked()
{
    spriteIndex = (spriteIndex + MAX_SPRITES - 1) % MAX_SPRITES;
    spriteFileName = db.spriteFileName(spriteIndex);

    spriteImage->setPixmap(spriteFileName);
    spriteNameVal->setText(db.spriteName(spriteIndex));
    spriteAPVal->setText(QString::number(db.spriteAP(spriteIndex)));
    spriteHPVal->setText(QString::number(db.spriteHP(spriteIndex)));
    spriteRangeVal->setText(QString::number(db.spriteRange(spriteIndex)));
    spriteRateVal->setText(QString::number(db.spriteRate(spriteIndex)));
}


void RecruitUnitsPageL::recruitButtonClicked()
{
    int i;

    // Check if there is an available unit slot and fill it with current sprite
    for (i = 0; i < MAX_TEAM_UNITS; i++)
    {
        if (!isAlive[i])
        {
            // Fill open slot in Player Units section
            //unitImageList[i]->setPixmap(*(spriteImage->pixmap()));
            unitImageList[i]->setPixmap(spriteFileName);
            unitNameList[i]->setText(spriteNameVal->text());
            isAlive[i] = true;

            // Get copy of units from database and update it
            QList<Unit> tempUnits = db.loadUnits(LoadGameWizard::playerName);

            tempUnits[i].name = spriteNameVal->text();
            tempUnits[i].imageFileName = spriteFileName;
            tempUnits[i].attackPower = spriteAPVal->text().toInt();
            tempUnits[i].hitPoints = spriteHPVal->text().toInt();
            tempUnits[i].status = UNIT_OK;

            db.saveUnits(LoadGameWizard::playerName, tempUnits);

            return;
            //break;
        }
    }
}

void RecruitUnitsPageL::rejectButton0Clicked()
{
    rejectButtonAnyClicked(0);
}

void RecruitUnitsPageL::rejectButton1Clicked()
{
    rejectButtonAnyClicked(1);
}

void RecruitUnitsPageL::rejectButton2Clicked()
{
    rejectButtonAnyClicked(2);
}

void RecruitUnitsPageL::rejectButton3Clicked()
{
    rejectButtonAnyClicked(3);
}

void RecruitUnitsPageL::rejectButtonAnyClicked(int index)
{
    if (isAlive[index])
    {
        unitImageList[index]->setPixmap(QPixmap(QString::fromUtf8("sprites/blank.PNG")));
        unitNameList[index]->setText("Unit");
        isAlive[index] = false;

        // Get copy of units from database and update it
        QList<Unit> tempUnits = db.loadUnits(LoadGameWizard::playerName);

        //tempUnits[i].pixMap.operator =((*(spriteImage->pixmap())));
        //tempUnits[i].image.operator =((spriteImage->pixmap()->toImage()));
        //tempUnits[i].name = spriteNameVal->text();
        tempUnits[index].status = NO_UNIT;

        db.saveUnits(LoadGameWizard::playerName, tempUnits);
    }
}


int RecruitUnitsPageL::nextId() const
{
    return LoadGameWizard::Page_UpgradeUnits;
}


UpgradeUnitsPageL::UpgradeUnitsPageL(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Upgrade Units"));
    setSubTitle(tr("Upgrade your units"));

    //QVBoxLayout *layout = new QVBoxLayout;
    //layout->addWidget(topLabel);
    //layout->addWidget(campaignModeRadioButton);
    //layout->addWidget(freePlayModeRadioButton);
    //setLayout(layout);
}


int UpgradeUnitsPageL::nextId() const
{
    return LoadGameWizard::Page_SelectMap;
}


SelectModePageL::SelectModePageL(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Game Mode"));
    setSubTitle(tr("Select the game mode"));

    // Initialize radio buttons
    campaignModeRadioButton = new QRadioButton(tr("&Campaign Mode"));
    freePlayModeRadioButton = new QRadioButton(tr("&Free Play Mode"));
    campaignModeRadioButton->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    //layout->addWidget(topLabel);
    layout->addWidget(campaignModeRadioButton);
    layout->addWidget(freePlayModeRadioButton);
    setLayout(layout);
}


int SelectModePageL::nextId() const
{
    if (freePlayModeRadioButton->isChecked())
        return LoadGameWizard::Page_SelectMap;
    else
        return LoadGameWizard::Page_Conclusion;
}

SelectMapPageL::SelectMapPageL(QWidget *parent)
    : QWizardPage(parent)
{
    mapIndex = 0;

    setTitle(tr("Select Map"));
    setSubTitle(tr("Select desired battle map"));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QGroupBox *mapBox = new QGroupBox(tr("&Available Maps"));
    mapBox->setObjectName(QString::fromUtf8("mapBox"));
    
    QGridLayout *mapBoxLayout = new QGridLayout(mapBox);
    mapBoxLayout->setObjectName(QString::fromUtf8("mapBoxLayout"));

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->setObjectName(QString::fromUtf8("leftLayout"));
    
    QHBoxLayout *leftTopLayout = new QHBoxLayout;
    leftTopLayout->setObjectName(QString::fromUtf8("leftTopLayout"));

    prevMapButton = new QPushButton(tr("<<"), mapBox);
    prevMapButton->setObjectName(QString::fromUtf8("prevMapButton"));
    prevMapButton->setMaximumSize(QSize(31, 23));
    leftTopLayout->addWidget(prevMapButton);

    mapFileName = db.mapFileName(0);

    mapImage = new QLabel(mapBox);
    mapImage->setObjectName(QString::fromUtf8("mapImage"));
    mapImage->setMinimumSize(QSize(191, 101));
    mapImage->setMaximumSize(QSize(191, 101));
    mapImage->setPixmap(db.mapFileName(0));
    mapImage->setScaledContents(true);
    leftTopLayout->addWidget(mapImage);

    nextMapButton = new QPushButton(tr(">>"), mapBox);
    nextMapButton->setObjectName(QString::fromUtf8("nextMapButton"));
    nextMapButton->setMaximumSize(QSize(31, 23));
    leftTopLayout->addWidget(nextMapButton);
    leftLayout->addLayout(leftTopLayout);

    QHBoxLayout *leftMidLayout = new QHBoxLayout;
    leftMidLayout->setObjectName(QString::fromUtf8("leftMidLayout"));
    
    QSpacerItem *hLeftSpacerMapStats = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    leftMidLayout->addItem(hLeftSpacerMapStats);

    QGridLayout *mapStatsLayout = new QGridLayout;
    mapStatsLayout->setObjectName(QString::fromUtf8("mapStatsLayout"));

    mapName = new QLabel(tr("Name:"), mapBox);
    mapName->setObjectName(QString::fromUtf8("mapName"));
    mapStatsLayout->addWidget(mapName, 0, 0, 1, 1);
    
    mapNameVal = new QLabel(mapBox);
    mapNameVal->setObjectName(QString::fromUtf8("mapNameVal"));
    mapNameVal->setText(db.mapName(0));
    mapStatsLayout->addWidget(mapNameVal, 0, 1, 1, 1);
    leftMidLayout->addLayout(mapStatsLayout);

    QSpacerItem *hRightSpacerMapStats = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    leftMidLayout->addItem(hRightSpacerMapStats);
    leftLayout->addLayout(leftMidLayout);

    QHBoxLayout *leftBotLayout = new QHBoxLayout;
    leftBotLayout->setObjectName(QString::fromUtf8("leftBotLayout"));

    QSpacerItem *hLeftSpacerSelect = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    leftBotLayout->addItem(hLeftSpacerSelect);

    selectButton = new QPushButton(tr("&Select"), mapBox);
    selectButton->setObjectName(QString::fromUtf8("selectButton"));
    leftBotLayout->addWidget(selectButton);

    QSpacerItem *hRightSpacerSelect = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    leftBotLayout->addItem(hRightSpacerSelect);
    leftLayout->addLayout(leftBotLayout);
    mapBoxLayout->addLayout(leftLayout, 0, 0, 1, 1);
    mainLayout->addWidget(mapBox);
    setLayout(mainLayout);

    connect(nextMapButton, SIGNAL(clicked()), this, SLOT(nextMapButtonClicked()));
    connect(prevMapButton, SIGNAL(clicked()), this, SLOT(prevMapButtonClicked()));
    connect(selectButton, SIGNAL(clicked()), this, SLOT(selectButtonClicked()));
}

void SelectMapPageL::nextMapButtonClicked()
{
    mapIndex = (mapIndex + 1) % db.mapCount();

    mapFileName = db.mapFileName(mapIndex);

    mapImage->setPixmap(QPixmap(db.mapFileName(mapIndex)));
    mapNameVal->setText(db.mapName(mapIndex));
}


void SelectMapPageL::prevMapButtonClicked()
{
    mapIndex = (mapIndex + db.mapCount() - 1) % db.mapCount();

    mapFileName = db.mapFileName(mapIndex);

    mapImage->setPixmap(QPixmap(db.mapFileName(mapIndex)));
    mapNameVal->setText(db.mapName(mapIndex));
}


void SelectMapPageL::selectButtonClicked()
{
    //Map map;

    //map.imageFileName = mapFileName;
    db.saveLevel(LoadGameWizard::playerName, mapIndex);
    //db.saveMap(LoadGameWizard::playerName, map);
}


int SelectMapPageL::nextId() const
{
    return LoadGameWizard::Page_Conclusion;
}


ConclusionPageL::ConclusionPageL(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Completion"));
    //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    bottomLabel = new QLabel;
    bottomLabel = new QLabel(tr("You have completed the Load Game options"));
    bottomLabel->setWordWrap(true);

    //agreeCheckBox = new QCheckBox(tr("I agree to the terms of the license"));

    //registerField("conclusion.agree*", agreeCheckBox);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(bottomLabel);
    //layout->addWidget(agreeCheckBox);
    setLayout(layout);
}


int ConclusionPageL::nextId() const
{
    return -1;
}
