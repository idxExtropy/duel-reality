#include "globals.h"
#include "test_db.h"
#include "glwidget.h"

//Database *db;
QList<Map>    Database::mapList;
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
    return Database::mapList[index].fileName;
}

void Database::addSprite(Sprite sprite)
{
    Database::spriteList << sprite;
}

void Database::saveMap(QString &userName, Map map)
{
    int i;

    for (i = 0; i < userList.count(); i++)
        if (userList[i].name == userName)
            userList[i].map = map;
}


int Database::spriteCount()
{
    return Database::spriteList.count();
}


QString Database::spriteName(int index) const
{
    return Database::spriteList[index].name;
}

const QPixmap Database::spritePixMap(int index) const
{
    return Database::spriteList[index].pixMap;
}

const int Database::spriteAP(int index) const
{
    return Database::spriteList[index].AP;
}

const int Database::spriteHP(int index) const
{
    return Database::spriteList[index].HP;
}

const int Database::spriteRange(int index) const
{
    return spriteList[index].range;
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
        if (Database::userList[i].name == userName)
            Database::userList[i] = user;
}


int Database::userCount()
{
    return userList.count();
}


QString Database::userName(int index) const
{
    return userList[index].name;
}


User Database::loadUser(const QString &userName)
{
    int i;

    for (i = 0; i < userList.count(); i++)
        if (userList[i].name == userName)
            return userList[i];

    return dummyUser;
}


void Database::saveUnits(QString &userName, QList<Unit> units)
{
    int i;
    int j;

    for (i = 0; i < userList.count(); i++)
    {
        if (userList[i].name == userName)
        {
            for (j = 0; j < MAX_UNITS1; j++)
                userList[i].units[j] = units[j];
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
            for (j = 0; j < MAX_UNITS1; j++)
                units << userList[i].units[j];

            return units;
        }
    }
    return dummyUnitsList;
}


void Database::generateSprites()
{
    if (Database::spriteList.count() == 0)
    {
        int i;
        //Sprite* testSprites = new Sprite[MAX_SPRITES];
        Sprite testSprites[MAX_SPRITES];

        testSprites[0].name = "Wizard";
        testSprites[0].pixMap.load("sprites/wizard.png");
        testSprites[0].AP = 8;
        testSprites[0].HP = 8;
        testSprites[0].range = 8;

        testSprites[1].name = "Monk";
        testSprites[1].pixMap.load("sprites/buddhist.png");
        testSprites[1].AP = 6;
        testSprites[1].HP = 6;
        testSprites[1].range = 6;

        testSprites[2].name = "Bard";
        testSprites[2].pixMap.load("sprites/bard.png");
        testSprites[2].AP = 4;
        testSprites[2].HP = 4;
        testSprites[2].range = 4;

        testSprites[3].name = "Desert Soldier";
        testSprites[3].pixMap.load("sprites/desertsoldier.png");
        testSprites[3].AP = 4;
        testSprites[3].HP = 6;
        testSprites[3].range = 8;

        for (i = 0; i < MAX_SPRITES; i++)
            addSprite(testSprites[i]);
    }
}


void Database::generateMaps()
{
    if (Database::mapList.count() == 0)
    {
        int         i;
        int         NUM_TEST_MAPS = 4;
        Map   testMaps[NUM_TEST_MAPS];

        testMaps[0].name = "Grass";
        testMaps[0].fileName = "backgrounds/grass.png";
        testMaps[0].cellsWide = 6;
        testMaps[0].cellsTall = 9;
        testMaps[0].gridHeight = 0.58;

        testMaps[1].name = "Beach";
        testMaps[1].fileName = "backgrounds/beach.png";
        testMaps[1].cellsWide = 6;
        testMaps[1].cellsTall = 9;
        testMaps[1].gridHeight = 0.58;

        testMaps[2].name = "Snow";
        testMaps[2].fileName = "backgrounds/snow.png";
        testMaps[2].cellsWide = 6;
        testMaps[2].cellsTall = 9;
        testMaps[2].gridHeight = 0.58;

        testMaps[3].name = "Plains";
        testMaps[3].fileName = "backgrounds/plains.png";
        testMaps[3].cellsWide = 6;
        testMaps[3].cellsTall = 9;
        testMaps[3].gridHeight = 0.58;

        for (i = 0; i < NUM_TEST_MAPS; i++)
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

        testUsers[0].units[0].status = UNIT_OK;
        testUsers[0].units[0].name = "Wizard";
        testUsers[0].units[0].pixMap.load("sprites/wizard.png");
        testUsers[0].units[0].attackPower = 2;
        testUsers[0].units[0].hitPoints = 2;
        testUsers[0].units[0].attackRange = 2;

        testUsers[0].units[1].status = NO_UNIT;
        testUsers[0].units[2].status = NO_UNIT;
        testUsers[0].units[3].status = NO_UNIT;


        testUsers[1].name = "Dick";
        testUsers[1].experiencePoints = 4;

        testUsers[1].units[0].status = UNIT_OK;
        testUsers[1].units[0].name = "Monk";
        testUsers[1].units[0].pixMap.load("sprites/buddhist.png");
        testUsers[1].units[0].attackPower = 4;
        testUsers[1].units[0].hitPoints = 4;
        testUsers[1].units[0].attackRange = 4;

        testUsers[1].units[2].status = UNIT_OK;
        testUsers[1].units[2].name = "Desert Soldier";
        testUsers[1].units[2].pixMap.load("sprites/desertsoldier.png");
        testUsers[1].units[2].attackPower = 6;
        testUsers[1].units[2].hitPoints = 6;
        testUsers[1].units[2].attackRange = 6;

        testUsers[1].units[1].status = NO_UNIT;
        testUsers[1].units[3].status = NO_UNIT;


        testUsers[2].name = "Harry";
        testUsers[2].experiencePoints = 4;

        testUsers[2].units[0].status = UNIT_OK;
        testUsers[2].units[0].name = "Bard";
        testUsers[2].units[0].pixMap.load("sprites/bard.png");
        testUsers[2].units[0].attackPower = 2;
        testUsers[2].units[0].hitPoints = 4;
        testUsers[2].units[0].attackRange = 6;

        testUsers[2].units[1].status = UNIT_OK;
        testUsers[2].units[1].name = "Wizard";
        testUsers[2].units[1].pixMap.load("sprites/wizard.png");
        testUsers[2].units[1].attackPower = 6;
        testUsers[2].units[1].hitPoints = 4;
        testUsers[2].units[1].attackRange = 2;

        testUsers[2].units[2].status = UNIT_DEAD;
        testUsers[2].units[2].name = "Monk";
        testUsers[2].units[2].pixMap.load("sprites/buddhist.png");
        testUsers[2].units[2].attackPower = 5;
        testUsers[2].units[2].hitPoints = 5;
        testUsers[2].units[2].attackRange = 5;

        testUsers[2].units[3].status = UNIT_DEAD;
        testUsers[2].units[3].name = "Priestess";
        testUsers[2].units[3].pixMap.load("sprites/priestess.png");
        testUsers[2].units[3].attackPower = 5;
        testUsers[2].units[3].hitPoints = 5;
        testUsers[2].units[3].attackRange = 5;

        for (i = 0; i < NUM_TEST_USERS; i ++)
            addUser(testUsers[i]);
    }
}
