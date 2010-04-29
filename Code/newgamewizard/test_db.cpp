#include "globals.h"
#include "test_db.h"


Sprite  testSprites[4];
User    testUsers[3];
Unit    testUnits[3];


void TestGenerateSprites(void)
{
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
}


void TestGenerateUsers(void)
{
    testUsers[0].playerName = "Tom";
    testUsers[0].experiencePoints = 2;
    testUsers[0].units[0].status = UNIT_OK;

    units[0].name = "Wizard";
    units[0].attackPower = 2;
    units[0].hitPoints = 2;
    units[0].attackRange = 2;
    SaveUserUnits(units[0].name, &units);
    
    /*testUsers[0].units[0].name = "Wizard";
    testUsers[0].units[0].attackPower = 2;
    testUsers[0].units[0].hitPoints = 2;
    testUsers[0].units[0].attackRange = 2;*/
    
    testUsers[1].playerName = "Dick";
    testUsers[1].experiencePoints = 4;
    testUsers[1].units[0].status = UNIT_OK;
    testUsers[1].units[0].name = "Monk";
    testUsers[1].units[0].attackPower = 4;
    testUsers[1].units[0].hitPoints = 4;
    testUsers[1].units[0].attackRange = 4;
    testUsers[1].units[2].status = UNIT_OK;
    testUsers[1].units[2].name = "Desert Soldier";
    testUsers[1].units[2].attackPower = 6;
    testUsers[1].units[2].hitPoints = 6;
    testUsers[1].units[2].attackRange = 6;

    testUsers[2].playerName = "Harry";
    testUsers[2].experiencePoints = 4;
    testUsers[2].units[0].status = UNIT_OK;
    testUsers[2].units[0].name = "Bard";
    testUsers[2].units[0].attackPower = 2;
    testUsers[2].units[0].hitPoints = 4;
    testUsers[2].units[0].attackRange = 6;
    testUsers[2].units[1].status = UNIT_OK;
    testUsers[2].units[1].name = "Wizard";
    testUsers[2].units[1].attackPower = 6;
    testUsers[2].units[1].hitPoints = 4;
    testUsers[2].units[1].attackRange = 2;    
    testUsers[2].units[0].status = UNIT_DEAD;
}


int GetSpriteCount(void)
{
    return 4;
}

string GetSpriteName(int index)
{
    return testSprites[index].name;
}


Sprite GetSpriteData(string name)
{
    int i;
    
    for (i = 0; i < 4; i++)
        if (testSprites[i].name == name)
            return testSprites[i];
}


User CreateUserData(string name)
{
    User user;

    user.playerName = name;
    return user;
}


int GetUserCount(void)
{
    return 3;
}


string GetUserName(int index)
{
    return testUsers[index].playerName;
}


User GetUserData(string name)
{
    int i;
    
    for (i = 0; i < 3; i++)
        if (testUsers[i].name == name)
            return testUsers[i];
}
