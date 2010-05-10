#include <QtGui>

#include "globals.h"
#include "test_db.h"
#include "newgamewizard.h"
#include "glwidget.h"

QString NewGameWizard::playerName;

NewGameWizard::NewGameWizard(QWidget *parent)
    : QWizard(parent)
{
    // Set New Game dialog pages
    setPage(Page_Intro, new IntroPage);
    setPage(Page_CreatePlayer, new CreatePlayerPage);
    setPage(Page_LoadPlayer, new LoadPlayerPage);
    setPage(Page_RecruitUnits, new RecruitUnitsPage);
    setPage(Page_SelectMode, new SelectModePage);
    setPage(Page_SelectMap, new SelectMapPage);
    setPage(Page_Conclusion, new ConclusionPage);

    // Set start page
    setStartId(Page_Intro);

    setOption(HaveHelpButton, true);

    // Connect Help slot
    connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));

    // Set window logo and title
    setWindowIcon(QIcon("icons/logo.png"));
    setWindowTitle(tr("New Game"));

    // Check for logic execution each time next button is clicked
    connect(button(NextButton), SIGNAL(clicked()), this, SLOT(nextButtonClicked()));
    connect(button(FinishButton), SIGNAL(clicked()), this, SLOT(finishButtonClicked()));
}

void NewGameWizard::finishButtonClicked()
{
    db.activateUser(NewGameWizard::playerName);
}

void NewGameWizard::nextButtonClicked()
{
    int i;

    switch (currentId())
    {
    // Before units are recruited, create new user if non-existent
    case Page_RecruitUnits:
        for (i = 0; i < db.userCount(); i++)
        {
            // Do nothing if user exists
            if (db.userName(i) == NewGameWizard::playerName)
                return;
        }
        // Otherwise add new user to database
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

    // Organize into layouts
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
    // Set titles
    setTitle(tr("Create Player"));
    setSubTitle(tr("Type a new player name"));

    playerNameLabel = new QLabel(tr("&Player Name:"));
    playerNameLineEdit = new QLineEdit;
    playerNameLabel->setBuddy(playerNameLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playerNameLabel, 0, 0);
    layout->addWidget(playerNameLineEdit, 0, 1);
    setLayout(layout);

    // Enable next button only if user name is entered
    registerField("player.name*", playerNameLineEdit);

    connect(playerNameLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(playerNameCreated(const QString &)));
}


void CreatePlayerPage::playerNameCreated(const QString &userName)
{
    NewGameWizard::setPlayerName(playerNameLineEdit->text());
}


int CreatePlayerPage::nextId() const
{
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

    // Get user name from database and sort
    for (i = 0; i < db.userCount(); i++)
        userNames << db.userName(i);

    userNames.sort();

    // Inset names in combo box and initialize combox box index
    for (i = 0; i < userNames.count(); i++)
        playerNameComboBox->addItem(userNames.at(i));

    playerNameComboBox->setCurrentIndex(-1);

    // Organize layouts
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playerNameLabel, 0, 0);
    layout->addWidget(playerNameComboBox, 0, 1);
    setLayout(layout);

    connect(playerNameComboBox, SIGNAL(activated(int)), this, SLOT(playerNameChanged(int)));
}


void LoadPlayerPage::playerNameChanged(int index)
{
    NewGameWizard::setPlayerName(userNames.at(index));
}


int LoadPlayerPage::nextId() const
{
    return NewGameWizard::Page_RecruitUnits;
}


RecruitUnitsPage::RecruitUnitsPage(QWidget *parent)
    : QWizardPage(parent)
{
    int i;

    // Initialize variables
    for (i = 0; i < MAX_TEAM_UNITS; i++)
        isAlive[i] = false;

    spriteIndex = 0;
    spriteFileName = db.spriteFileName(0);

    // Set titles
    setTitle(tr("Recruit Units"));
    setSubTitle(tr("Recruit units for battle"));

    // Create layouts and boxes
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

    spriteAttackPower = new QLabel(tr("AP:"), spriteBox);
    spriteAttackPower->setObjectName(QString::fromUtf8("spriteAttackPower"));
    spriteStatsLayout->addWidget(spriteAttackPower, 1, 0, 1, 1);
    
    spriteAttackPowerVal = new QLabel(spriteBox);
    spriteAttackPowerVal->setObjectName(QString::fromUtf8("spriteAttackPowerVal"));
    spriteAttackPowerVal->setText(QString::number(db.spriteAttackPower(0)));
    spriteStatsLayout->addWidget(spriteAttackPowerVal, 1, 1, 1, 1);

    spriteHitPoints = new QLabel(tr("HP:"), spriteBox);
    spriteHitPoints->setObjectName(QString::fromUtf8("spriteHitPoints"));
    spriteStatsLayout->addWidget(spriteHitPoints, 2, 0, 1, 1);
    
    spriteHitPointsVal = new QLabel(spriteBox);
    spriteHitPointsVal->setObjectName(QString::fromUtf8("spriteHitPointsVal"));
    spriteHitPointsVal->setText(QString::number(db.spriteHitPoints(0)));
    spriteStatsLayout->addWidget(spriteHitPointsVal, 2, 1, 1, 1);

    spriteAttackRange = new QLabel(tr("Range:"), spriteBox);
    spriteAttackRange->setObjectName(QString::fromUtf8("spriteAttackRange"));
    spriteStatsLayout->addWidget(spriteAttackRange, 3, 0, 1, 1);

    spriteAttackRangeVal = new QLabel(spriteBox);
    spriteAttackRangeVal->setObjectName(QString::fromUtf8("spriteAttackRangeVal"));
    spriteAttackRangeVal->setText(QString::number(db.spriteAttackRange(0)));
    spriteStatsLayout->addWidget(spriteAttackRangeVal, 3, 1, 1, 1);
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

    // Iteratively fill Player Units section
    for (i = 0; i < MAX_TEAM_UNITS; i++)
    {
        QHBoxLayout *rightUnitLayout = new QHBoxLayout();
        
        QLabel *unitImage = new QLabel(unitsBox);
        
        unitImage->setMaximumSize(QSize(41, 41));
        unitImage->setMinimumSize(QSize(41, 41));
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


void RecruitUnitsPage::nextSpriteButtonClicked()
{
    spriteIndex = (spriteIndex + 1) % NUM_TEST_SPRITES;
    spriteFileName = db.spriteFileName(spriteIndex);

    spriteImage->setPixmap(spriteFileName);
    spriteNameVal->setText(db.spriteName(spriteIndex));
    spriteAttackPowerVal->setText(QString::number(db.spriteAttackPower(spriteIndex)));
    spriteHitPointsVal->setText(QString::number(db.spriteHitPoints(spriteIndex)));
    spriteAttackRangeVal->setText(QString::number(db.spriteAttackRange(spriteIndex)));
    spriteRateVal->setText(QString::number(db.spriteRate(spriteIndex)));
}


void RecruitUnitsPage::prevSpriteButtonClicked()
{
    spriteIndex = (spriteIndex + NUM_TEST_SPRITES - 1) % NUM_TEST_SPRITES;
    spriteFileName = db.spriteFileName(spriteIndex);

    spriteImage->setPixmap(spriteFileName);
    spriteNameVal->setText(db.spriteName(spriteIndex));
    spriteAttackPowerVal->setText(QString::number(db.spriteAttackPower(spriteIndex)));
    spriteHitPointsVal->setText(QString::number(db.spriteHitPoints(spriteIndex)));
    spriteAttackRangeVal->setText(QString::number(db.spriteAttackRange(spriteIndex)));
    spriteRateVal->setText(QString::number(db.spriteRate(spriteIndex)));
}


void RecruitUnitsPage::recruitButtonClicked()
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
            QList<Unit> tempUnits = db.loadUnits(NewGameWizard::playerName);

            tempUnits[i].name = spriteNameVal->text();
            tempUnits[i].imageFileName = spriteFileName;
            tempUnits[i].attackPower = spriteAttackPowerVal->text().toInt();
            tempUnits[i].hitPoints = spriteHitPointsVal->text().toInt();
            tempUnits[i].attackRange = spriteAttackRangeVal->text().toInt();
            tempUnits[i].movementRange = spriteRateVal->text().toInt();
            tempUnits[i].status = UNIT_OK;

            db.saveUnits(NewGameWizard::playerName, tempUnits);

            return;
            //break;
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

        // Get copy of units from database and update it
        QList<Unit> tempUnits = db.loadUnits(NewGameWizard::playerName);

        //tempUnits[i].pixMap.operator =((*(spriteImage->pixmap())));
        //tempUnits[i].image.operator =((spriteImage->pixmap()->toImage()));
        //tempUnits[i].name = spriteNameVal->text();
        tempUnits[index].status = NO_UNIT;

        db.saveUnits(NewGameWizard::playerName, tempUnits);
    }
}


int RecruitUnitsPage::nextId() const
{
    return NewGameWizard::Page_SelectMode;
}


SelectModePage::SelectModePage(QWidget *parent)
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


int SelectModePage::nextId() const
{  
    if (freePlayModeRadioButton->isChecked())
        return NewGameWizard::Page_SelectMap;
    else
        return NewGameWizard::Page_Conclusion;
}


SelectMapPage::SelectMapPage(QWidget *parent)
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

void SelectMapPage::nextMapButtonClicked()
{
    mapIndex = (mapIndex + 1) % db.mapCount();

    mapFileName = db.mapFileName(mapIndex);

    mapImage->setPixmap(QPixmap(db.mapFileName(mapIndex)));
    mapNameVal->setText(db.mapName(mapIndex));
}


void SelectMapPage::prevMapButtonClicked()
{
    mapIndex = (mapIndex + db.mapCount() - 1) % db.mapCount();

    mapFileName = db.mapFileName(mapIndex);

    mapImage->setPixmap(QPixmap(db.mapFileName(mapIndex)));
    mapNameVal->setText(db.mapName(mapIndex));
}


void SelectMapPage::selectButtonClicked()
{
    //Map map;

    //map.imageFileName = mapFileName;
    db.saveLevel(NewGameWizard::playerName, mapIndex);
    //db.saveMap(NewGameWizard::playerName, map);
}


int SelectMapPage::nextId() const
{
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
