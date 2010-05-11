#include "duelreality.h"
#include "test_db.h"
#include "glwidget.h"

QList<Map>          Database::mapList;
QList<Sprite>       Database::spriteList;
QList<User>         Database::userList;
QList<Unit>         Database::unitList;

Database::Database()
{
    generateMaps();
    generateSprites();
    testGenerateUsers();
}

Database::~Database()
{
    ;
}

void Database::addMap(Map map)
{
    Database::mapList << map;
}


Map Database::loadMap(QString &mapName)
{
    int i;

    for (i = 0; i < mapList.count(); i++)
        if (mapList[i].name == mapName)
            return mapList[i];

    return dummyMap;
}

int Database::mapCount()
{
    return Database::mapList.count();
}


QString Database::mapName(int index) const
{
    return Database::mapList[index].name;
}

QString Database::mapFileName(int index) const
{
    return Database::mapList[index].imageFileName;
}

void Database::addSprite(Sprite sprite)
{
    Database::spriteList << sprite;
}

/*
void Database::saveMap(QString &userName, Map map)
{
    int i;

    for (i = 0; i < userList.count(); i++)
        if (userList[i].name == userName)
            userList[i].map = map;
}


void Database::saveGameMode(QString &userName, int gameMode)
{
    int i;

    for (i = 0; i < userList.count(); i++)
        if (userList[i].name == userName)
            userList[i].gameMode = gameMode;
}
*/

void Database::saveXP(QString &userName, int xp)
{
    int i;

    for (i = 0; i < userList.count(); i++)
    {
        if (userList[i].name == userName)
        {
            userList[i].experiencePoints = xp;
            return;
        }
    }
}

void Database::saveLevel(QString &userName, int level)
{
    int i;

    for (i = 0; i < userList.count(); i++)
    {
        if (userList[i].name == userName)
        {
            userList[i].level = level;
            return;
        }
    }
}


int Database::spriteCount()
{
    return Database::spriteList.count();
}


QString Database::spriteName(int index) const
{
    return Database::spriteList[index].name;
}

QString Database::spriteFileName(int index) const
{
    return Database::spriteList[index].imageFileName;
}

/*
const QPixmap Database::spritePixMap(int index) const
{
    return Database::spriteList[index].pixMap;
}
*/

const int Database::spriteAttackPower(int index) const
{
    return Database::spriteList[index].attackPower;
}

const int Database::spriteHitPoints(int index) const
{
    return Database::spriteList[index].hitPoints;
}

const int Database::spriteAttackRange(int index) const
{
    return spriteList[index].attackRange;
}


const int Database::spriteRate(int index) const
{
    return spriteList[index].rate;
}


Sprite Database::loadSprite(QString &spriteName)
{
    int i;

    for (i = 0; i < spriteList.count(); i++)
        if (spriteList[i].name == spriteName)
            return spriteList[i];

    return dummySprite;
}


void Database::addUser(QString &userName)
{
    User newUser;
    
    newUser.name = userName;
    newUser.level = 0;
    newUser.experiencePoints = 0;
    newUser.isActive = false;
    Database::userList << newUser;
}


void Database::addUser(User user)
{
    Database::userList << user;
}


void Database::saveUser(QString &userName, User user)
{
    int i;

    for (i = 0; i < userList.count(); i++)
    {
        if (Database::userList[i].name == userName)
        {
            Database::userList[i] = user;
            return;
        }
    }
}

void Database::activateUser(QString &userName)
{
    int i;

    for (i = 0; i < userList.count(); i++)
    {
        if (Database::userList[i].name == userName)
        {
            Database::userList[i].isActive = true;
            return;
        }
    }
}


void Database::deactivateUser(QString &userName)
{
    int i;

    for (i = 0; i < userList.count(); i++)
    {
        if (Database::userList[i].name == userName)
        {
            Database::userList[i].isActive = false;
            return;
        }
    }
}


int Database::userCount()
{
    return userList.count();
}


QString Database::userName(int index) const
{
    return userList[index].name;
}

User Database::loadActiveUser()
{
    int i;

    for (i = 0; i < userList.count(); i++)
        if (userList[i].isActive == true)
            return userList[i];

    return dummyUser;
}

User Database::loadUser(const QString &userName)
{
    int i;

    for (i = 0; i < userList.count(); i++)
        if (userList[i].name == userName)
            return userList[i];

    return dummyUser;
}



int Database::loadXP(QString &userName) const
{
    int i;

    for (i = 0; i < userList.count(); i++)
        if (userList[i].name == userName)
            return userList[i].experiencePoints;

    return 0;
}
/*
int Database::loadGameMode(QString &userName) const
{
    int i;

    for (i = 0; i < userList.count(); i++)
        if (userList[i].name == userName)
            return userList[i].gameMode;

    return 0;
}
*/

void Database::saveUnits(QString &userName, QList<Unit> units)
{
    int i;
    int j;

    for (i = 0; i < userList.count(); i++)
    {
        if (userList[i].name == userName)
        {
            for (j = 0; j < MAX_TEAM_UNITS; j++)
                userList[i].units[j] = units[j];

            return;
        }
    }
}


QList<Unit> Database::loadUnits(QString &userName)
{
    int i;
    int j;
    QList<Unit> units;

    for (i = 0; i < userList.count(); i++)
    {
        if (userList[i].name == userName)
        {
            for (j = 0; j < MAX_TEAM_UNITS; j++)
                units << userList[i].units[j];

            return units;
        }
    }
    return dummyUnitsList;
}

void Database::saveGameData(QString &userName)
{

}

void Database::generateSprites()
{
    if (Database::spriteList.count() == 0)
    {
        int     i;
        Sprite  testSprites[MAX_SPRITES];

        testSprites[0].name = "Wizard";
        testSprites[0].imageFileName = "sprites/wizard.png";
        testSprites[0].maskFileName = "sprites/mask_wizard.png";
        testSprites[0].attackPower = 8;
        testSprites[0].attackRange = 4;
        testSprites[0].hitPoints = 6;
        //testSprites[0].totalHitPoints = 6;
        testSprites[0].actionRate = 4;
        testSprites[0].actionTime = 4;
        testSprites[0].movementRange = 4;
        testSprites[0].rate = 2;

        testSprites[1].name = "Monk";
        testSprites[1].imageFileName = "sprites/buddhist.png";
        testSprites[1].maskFileName = "sprites/mask_buddhist.png";
        testSprites[1].attackPower = 1;
        testSprites[1].attackRange = 2;
        testSprites[1].hitPoints = 3;
        //testSprites[1].totalHitPoints = 4;
        testSprites[1].actionRate = 5;
        testSprites[1].actionTime = 6;
        testSprites[1].movementRange = 7;
        testSprites[1].rate = 8;

        testSprites[2].name = "Bard";
        testSprites[2].imageFileName = "sprites/bard.png";
        testSprites[2].maskFileName = "sprites/mask_bard.png";
        testSprites[2].attackPower = 2;
        testSprites[2].attackRange = 2;
        testSprites[2].hitPoints = 2;
        //testSprites[2].totalHitPoints = 2;
        testSprites[2].actionRate = 4;
        testSprites[2].actionTime = 4;
        testSprites[2].movementRange = 4;
        testSprites[2].rate = 4;

        testSprites[3].name = "Desert Soldier";
        testSprites[3].imageFileName = "sprites/desertsoldier.png";
        testSprites[3].maskFileName = "sprites/mask_desertsoldier.png";
        testSprites[3].attackPower = 4;
        testSprites[3].attackRange = 4;
        testSprites[3].hitPoints = 4;
        //testSprites[3].totalHitPoints = 4;
        testSprites[3].actionRate = 6;
        testSprites[3].actionTime = 6;
        testSprites[3].movementRange = 6;
        testSprites[3].rate = 6;

        testSprites[4].name = "Valkyrie";
        testSprites[4].imageFileName = "sprites/valkyrie.png";
        testSprites[4].maskFileName = "sprites/mask_valkyrie.png";
        testSprites[4].attackPower = 4;
        testSprites[4].attackRange = 4;
        testSprites[4].hitPoints = 4;
        //testSprites[3].totalHitPoints = 4;
        testSprites[4].actionRate = 6;
        testSprites[4].actionTime = 6;
        testSprites[4].movementRange = 6;
        testSprites[4].rate = 6;

        testSprites[5].name = "Thai Boxer";
        testSprites[5].imageFileName = "sprites/thaiboxer.png";
        testSprites[5].maskFileName = "sprites/mask_thaiboxer.png";
        testSprites[5].attackPower = 4;
        testSprites[5].attackRange = 4;
        testSprites[5].hitPoints = 4;
        //testSprites[3].totalHitPoints = 4;
        testSprites[5].actionRate = 6;
        testSprites[5].actionTime = 6;
        testSprites[5].movementRange = 6;
        testSprites[5].rate = 6;        

        testSprites[6].name = "Merchant";
        testSprites[6].imageFileName = "sprites/merchant.png";
        testSprites[6].maskFileName = "sprites/mask_merchant.png";
        testSprites[6].attackPower = 4;
        testSprites[6].attackRange = 4;
        testSprites[6].hitPoints = 4;
        //testSprites[3].totalHitPoints = 4;
        testSprites[6].actionRate = 6;
        testSprites[6].actionTime = 6;
        testSprites[6].movementRange = 6;
        testSprites[6].rate = 6;

        testSprites[7].name = "Knight";
        testSprites[7].imageFileName = "sprites/knight.png";
        testSprites[7].maskFileName = "sprites/mask_knight.png";
        testSprites[7].attackPower = 4;
        testSprites[7].attackRange = 4;
        testSprites[7].hitPoints = 4;
        //testSprites[3].totalHitPoints = 4;
        testSprites[7].actionRate = 6;
        testSprites[7].actionTime = 6;
        testSprites[7].movementRange = 6;
        testSprites[7].rate = 6;        

        testSprites[8].name = "Crusader";
        testSprites[8].imageFileName = "sprites/crusader.png";
        testSprites[8].maskFileName = "sprites/mask_crusader.png";
        testSprites[8].attackPower = 4;
        testSprites[8].attackRange = 4;
        testSprites[8].hitPoints = 4;
        //testSprites[3].totalHitPoints = 4;
        testSprites[8].actionRate = 6;
        testSprites[8].actionTime = 6;
        testSprites[8].movementRange = 6;
        testSprites[8].rate = 6;

        testSprites[9].name = "Criminal";
        testSprites[9].imageFileName = "sprites/criminal.png";
        testSprites[9].maskFileName = "sprites/mask_criminal.png";
        testSprites[9].attackPower = 4;
        testSprites[9].attackRange = 4;
        testSprites[9].hitPoints = 4;
        //testSprites[3].totalHitPoints = 4;
        testSprites[9].actionRate = 6;
        testSprites[9].actionTime = 6;
        testSprites[9].movementRange = 6;
        testSprites[9].rate = 6;

        testSprites[10].name = "Assassin";
        testSprites[10].imageFileName = "sprites/assassin.png";
        testSprites[10].maskFileName = "sprites/mask_assassin.png";
        testSprites[10].attackPower = 4;
        testSprites[10].attackRange = 4;
        testSprites[10].hitPoints = 4;
        //testSprites[3].totalHitPoints = 4;
        testSprites[10].actionRate = 6;
        testSprites[10].actionTime = 6;
        testSprites[10].movementRange = 6;
        testSprites[10].rate = 6;

        testSprites[11].name = "Berserker";
        testSprites[11].imageFileName = "sprites/berserker.png";
        testSprites[11].maskFileName = "sprites/mask_berserker.png";
        testSprites[11].attackPower = 4;
        testSprites[11].attackRange = 4;
        testSprites[11].hitPoints = 4;
        //testSprites[3].totalHitPoints = 4;
        testSprites[11].actionRate = 6;
        testSprites[11].actionTime = 6;
        testSprites[11].movementRange = 6;
        testSprites[11].rate = 6;
        
        for (i = 0; i < MAX_SPRITES; i++)
            addSprite(testSprites[i]);
    }
}


void Database::generateMaps()
{
    if (Database::mapList.count() == 0)
    {
        int i;
        Map testMaps[MAX_MAPS];

        testMaps[0].name = "Grass";
        testMaps[0].imageFileName = "backgrounds/grass.png";
        testMaps[0].audioFileName = "sounds/Battle_01.mp3";
        testMaps[0].cellsWide = 6;
        testMaps[0].cellsTall = 9;
        testMaps[0].gridHeight = 0.58;

        testMaps[1].name = "Beach";
        testMaps[1].imageFileName = "backgrounds/beach.png";
        testMaps[1].audioFileName = "sounds/Battle_02.mp3";
        testMaps[1].cellsWide = 6;
        testMaps[1].cellsTall = 9;
        testMaps[1].gridHeight = 0.58;

        testMaps[2].name = "Snow";
        testMaps[2].imageFileName = "backgrounds/snow.png";
        testMaps[2].audioFileName = "sounds/Battle_03.mp3";
        testMaps[2].cellsWide = 6;
        testMaps[2].cellsTall = 9;
        testMaps[2].gridHeight = 0.58;

        testMaps[3].name = "Plains";
        testMaps[3].imageFileName = "backgrounds/plains.png";
        testMaps[3].audioFileName = "sounds/Battle_04.mp3";
        testMaps[3].cellsWide = 6;
        testMaps[3].cellsTall = 9;
        testMaps[3].gridHeight = 0.58;

        testMaps[4].name = "Beach";
        testMaps[4].imageFileName = "backgrounds/beach2.png";
        testMaps[4].audioFileName = "sounds/Battle_01.mp3";
        testMaps[4].cellsWide = 6;
        testMaps[4].cellsTall = 9;
        testMaps[4].gridHeight = 0.58;

        testMaps[5].name = "Night Town";
        testMaps[5].imageFileName = "backgrounds/townnight.png";
        testMaps[5].audioFileName = "sounds/Battle_02.mp3";
        testMaps[5].cellsWide = 6;
        testMaps[5].cellsTall = 9;
        testMaps[5].gridHeight = 0.58;

        testMaps[6].name = "Night Grass";
        testMaps[6].imageFileName = "backgrounds/grassnight.png";
        testMaps[6].audioFileName = "sounds/Battle_03.mp3";
        testMaps[6].cellsWide = 6;
        testMaps[6].cellsTall = 9;
        testMaps[6].gridHeight = 0.58;

        for (i = 0; i < MAX_MAPS; i++)
            addMap(testMaps[i]);
    }
}


void Database::testGenerateUsers()
{
    if (Database::userList.count() == 0)
    {
        int     i;
        int     NUM_TEST_USERS = 3;
        User    testUsers[NUM_TEST_USERS];

        testUsers[0].name = "Tom";
        testUsers[0].experiencePoints = 2;
        testUsers[0].isActive = false;
        testUsers[0].level = 2;

        testUsers[0].units[0].status = UNIT_OK;
        testUsers[0].units[0].name = "Wizard";
        testUsers[0].units[0].imageFileName = "sprites/wizard.png";
        testUsers[0].units[0].image.load("sprites/wizard.png");
        testUsers[0].units[0].attackPower = 1;
        testUsers[0].units[0].hitPoints = 2;
        testUsers[0].units[0].attackRange = 3;
        testUsers[0].units[0].team = USER_UNIT;
        testUsers[0].units[0].vLocation = 1;
        testUsers[0].units[0].hLocation = 2;
        testUsers[0].units[0].faceLeft = false;
        testUsers[0].units[0].movementRange = 4;
        testUsers[0].units[0].actionRate = 1;
        testUsers[0].units[0].actionTime = 1;
        testUsers[0].units[0].maskFileName = "sprites/mask_wizard.png";
        testUsers[0].units[0].mask_image.load("sprites/mask_wizard.png");
        testUsers[0].units[0].totalHitPoints = 2;
        

        testUsers[0].units[1].status = NO_UNIT;
        testUsers[0].units[2].status = NO_UNIT;
        testUsers[0].units[3].status = NO_UNIT;

        testUsers[1].name = "Dick";
        testUsers[1].experiencePoints = 4;
        testUsers[1].isActive = false;
        testUsers[1].level = 1;

        testUsers[1].units[0].status = UNIT_OK;
        testUsers[1].units[0].name = "Monk";
        testUsers[1].units[0].imageFileName = "sprites/buddhist.png";
        testUsers[1].units[0].image.load("sprites/buddhist.png");
        testUsers[1].units[0].attackPower = 4;
        testUsers[1].units[0].hitPoints = 3;
        testUsers[1].units[0].attackRange = 2;
        testUsers[1].units[0].team = USER_UNIT;
        testUsers[1].units[0].vLocation = 2;
        testUsers[1].units[0].hLocation = 1;
        testUsers[1].units[0].faceLeft = false;
        testUsers[1].units[0].movementRange = 4;
        testUsers[1].units[0].actionRate = 1;
        testUsers[1].units[0].actionTime = 1;
        testUsers[1].units[0].maskFileName = "sprites/mask_buddhist.png";
        testUsers[1].units[0].mask_image.load("sprites/mask_buddhist.png");
        testUsers[1].units[0].totalHitPoints = 3;

        testUsers[1].units[1].status = NO_UNIT;

        testUsers[1].units[2].status = UNIT_OK;
        testUsers[1].units[2].name = "Desert Soldier";
        testUsers[1].units[2].imageFileName = "sprites/desertsoldier.png";
        testUsers[1].units[2].image.load("sprites/desertsoldier.png");
        testUsers[1].units[2].attackPower = 2;
        testUsers[1].units[2].hitPoints = 4;
        testUsers[1].units[2].attackRange = 6;
        testUsers[1].units[2].team = USER_UNIT;
        testUsers[1].units[2].vLocation = 3;
        testUsers[1].units[2].hLocation = 2;
        testUsers[1].units[2].faceLeft = false;
        testUsers[1].units[2].movementRange = 4;
        testUsers[1].units[2].actionRate = 1;
        testUsers[1].units[2].actionTime = 1;
        testUsers[1].units[2].maskFileName = "sprites/mask_desertsoldier.png";
        testUsers[1].units[2].mask_image.load("sprites/mask_desertsoldier.png");
        testUsers[1].units[0].totalHitPoints = 4;

        testUsers[1].units[3].status = NO_UNIT;


        testUsers[2].name = "Harry";
        testUsers[2].experiencePoints = 4;
        testUsers[2].isActive = false;
        testUsers[2].level = 6;

        testUsers[2].units[0].status = UNIT_OK;
        testUsers[2].units[0].name = "Bard";
        testUsers[2].units[0].imageFileName = "sprites/bard.png";
        testUsers[2].units[0].image.load("sprites/bard.png");
        testUsers[2].units[0].attackPower = 10;
        testUsers[2].units[0].hitPoints = 9;
        testUsers[2].units[0].attackRange = 8;
        testUsers[2].units[0].team = USER_UNIT;
        testUsers[2].units[0].vLocation = 3;
        testUsers[2].units[0].hLocation = 5;
        testUsers[2].units[0].faceLeft = false;
        testUsers[2].units[0].movementRange = 4;
        testUsers[2].units[0].actionRate = 1;
        testUsers[2].units[0].actionTime = 1;
        testUsers[2].units[0].maskFileName = "sprites/mask_bard.png";
        testUsers[2].units[0].mask_image.load("sprites/mask_bard.png");
        testUsers[2].units[0].totalHitPoints = 3;

        testUsers[2].units[1].status = UNIT_OK;
        testUsers[2].units[1].name = "Wizard";
        testUsers[2].units[1].imageFileName = "sprites/wizard.png";
        testUsers[2].units[1].image.load("sprites/wizard.png");
        testUsers[2].units[1].attackPower = 2;
        testUsers[2].units[1].hitPoints = 3;
        testUsers[2].units[1].attackRange = 4;
        testUsers[2].units[1].team = USER_UNIT;
        testUsers[2].units[1].vLocation = 1;
        testUsers[2].units[1].hLocation = 5;
        testUsers[2].units[1].faceLeft = false;
        testUsers[2].units[1].movementRange = 4;
        testUsers[2].units[1].actionRate = 1;
        testUsers[2].units[1].actionTime = 1;
        testUsers[2].units[1].maskFileName = "sprites/mask_wizard.png";
        testUsers[2].units[1].mask_image.load("sprites/mask_wizard.png");
        testUsers[2].units[1].totalHitPoints = 3;

        testUsers[2].units[2].status = UNIT_DEAD;
        testUsers[2].units[2].name = "Monk";
        testUsers[2].units[2].imageFileName = "sprites/buddhist.png";
        testUsers[2].units[2].image.load("sprites/buddhist.png");
        testUsers[2].units[2].attackPower = 1;
        testUsers[2].units[2].hitPoints = 3;
        testUsers[2].units[2].attackRange = 5;
        testUsers[2].units[2].team = USER_UNIT;
        testUsers[2].units[2].vLocation = 4;
        testUsers[2].units[2].hLocation = 7;
        testUsers[2].units[2].faceLeft = false;
        testUsers[2].units[2].movementRange = 4;
        testUsers[2].units[2].actionRate = 1;
        testUsers[2].units[2].actionTime = 1;
        testUsers[2].units[2].maskFileName = "sprites/mask_buddhist.png";
        testUsers[2].units[2].mask_image.load("sprites/mask_buddhist.png");
        testUsers[2].units[2].totalHitPoints = 3;

        testUsers[2].units[3].status = UNIT_DEAD;
        testUsers[2].units[3].name = "Priestess";
        testUsers[2].units[3].imageFileName = "sprites/priestess.png";
        testUsers[2].units[3].image.load("sprites/priestess.png");
        testUsers[2].units[3].attackPower = 3;
        testUsers[2].units[3].hitPoints = 6;
        testUsers[2].units[3].attackRange = 9;
        testUsers[2].units[3].movementRange = 12;
        testUsers[2].units[3].team = USER_UNIT;
        testUsers[2].units[3].vLocation = 2;
        testUsers[2].units[3].hLocation = 6;
        testUsers[2].units[3].faceLeft = false;
        testUsers[2].units[3].movementRange = 4;
        testUsers[2].units[3].actionRate = 1;
        testUsers[2].units[3].actionTime = 1;
        testUsers[2].units[3].maskFileName = "sprites/mask_priestess.png";
        testUsers[2].units[3].mask_image.load("sprites/mask_priestess.png");
        testUsers[2].units[3].totalHitPoints = 6;

        for (i = 0; i < NUM_TEST_USERS; i ++)
            addUser(testUsers[i]);
    }
}
