#include <QApplication>
#include "database.h"
#include <qDebug>

//! [0]
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Database gamedata;
    if (!gamedata.connection())
        return 1;
    QString tableSprite="sprite";
    QString tableUser="user";
    QString saveName="save";
    QString num="3";
    saveName.append(num);

    QString userName="Yue";

    //bool t= gamedata.addUser(userName);
    //QString name;
    //name=gamedata.userName(3);
    //qDebug() << saveName;

 //   int ap;
 //   ap=gamedata.spriteRange(3);
 //   qDebug() << ap;

 //   Sprite sprite;
 //   sprite = gamedata.loadSprite("Bard");
 //   qDebug() << sprite.AP;

 //   int numPlayers=gamedata.userCount();
 //   qDebug()<<numPlayers;


    // ***************saveUnits() test***************
    /*QList<Unit> u;

    Unit units[2];
    units[0].status = UNIT_OK;
    units[0].name = "Wizard";
    units[0].imageFileName = "sprites/wizard.png";
    units[0].attackPower = 7;
    units[0].hitPoints = 2;
    units[0].attackRange = 3;
    units[0].team = USER_UNIT;
    units[0].vLocation = 2;
    units[0].hLocation = 2;
    units[0].faceLeft = false;
    units[0].movementRange = 4;
    units[0].actionRate = 1;
    units[0].actionTime = 1;
    units[0].maskFileName = "sprites/mask_wizard.png";
    units[0].totalHitPoints = 2;
    units[0].unitWorth = 7;

    units[1].status = UNIT_OK;
    units[1].name = "Wizard";
    units[1].imageFileName = "sprites/wizard.png";
    units[1].attackPower = 7;
    units[1].hitPoints = 2;
    units[1].attackRange = 3;
    units[1].team = USER_UNIT;
    units[1].vLocation = 3;
    units[1].hLocation = 2;
    units[1].faceLeft = false;
    units[1].movementRange = 4;
    units[1].actionRate = 1;
    units[1].actionTime = 1;
    units[1].maskFileName = "sprites/mask_wizard.png";
    units[1].totalHitPoints = 2;
    units[1].unitWorth = 7;

    u<<units[0]<<units[1];


    gamedata.saveUnits(userName, u);*/


    // ***************loadUnits() test***************

    /*QList<Unit> load;
    load = gamedata.loadUnits(userName);
    qDebug() << load[0].vLocation;
    qDebug() << load[1].vLocation;*/


    // ***************loadUser() test***************
    /*User user = gamedata.loadUser(userName);
    qDebug() << user.experiencePoints;*/

    // ***************saveLevel() test***************
    /*gamedata.saveLevel(userName, 2);*/

    // ***************saveXP() test***************
    /*gamedata.saveXP(userName, 2);*/

    // ***************loadXP() test***************
    /*qDebug()<<gamedata.loadXP(userName);*/

    // ***************saveUser() test***************
    /*User user;
    user.experiencePoints = 1;
    user.isActive = 0;
    user.level =7;
    gamedata.saveUser(userName, user);*/

    // ***************addUser(User user) test***************
    /*User user;
    user.experiencePoints = 9;
    user.isActive = 0;
    user.level = 3;
    user.name = "UML";
    gamedata.addUser(user);*/

    // ***************activateUser() test***************
    //gamedata.activateUser(userName);

    // ***************deactivateUser() test***************
    /*gamedata.deactivateUser(userName);*/

    // ***************loadActiveUser() test***************
    /*User user;
    user = gamedata.loadActiveUser();
    qDebug() << user.name;*/

    // ***************spriteFileName() test***************
    //qDebug()<<gamedata.spriteFileName(12);

    // ***************spriteAttackPower() test***************
    //qDebug()<<gamedata.spriteAttackPower(1);

    gamedata.show(tableSprite);

    return 0;
}
