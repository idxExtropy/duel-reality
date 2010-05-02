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
    QString tableSprites="sprites";
    QString tablePlayers="players";

    QString playerName="Ye";

 //  bool t= gamedata.addPlayer(playerName);
    QString name;
    name=gamedata.userName(3);
    qDebug() << name;

 //   int ap;
 //   ap=gamedata.spriteRange(3);
 //   qDebug() << ap;

 //   Sprite sprite;
 //   sprite = gamedata.loadSprite("Bard");
 //   qDebug() << sprite.AP;

 //   int numPlayers=gamedata.userCount();
 //   qDebug()<<numPlayers;




    gamedata.show(tableSprites);
//    gamedata.show(tablePlayers);

    return 0;
}
