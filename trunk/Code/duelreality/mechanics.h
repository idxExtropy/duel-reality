#ifndef MECHANICS_H
#define MECHANICS_H
#include "globals.h"
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QString>
#include "GLWidget.h"

class Unit;
class test_db;

class mechanics : public QObject
{
Q_OBJECT
public:
    explicit mechanics(QObject *parent = 0);
    ~mechanics();
    bool isRunning() {return gamerunning;}
    void setRunning(bool run) {gamerunning=run;}
    bool isBattle(); //{return battleRunning;}
    void setBattleRunning(bool battle); //{battleRunning = battle;}
    void startBattle();

signals:
 void signalP1wins();
 void signalP2wins();
 void signalSwitchPlayer();
 void signalMoveDone();
 void signalAttackDone();
 void signalError();
 void signalStartAI();
 void signalBattleStart();


public slots:
 void move(Unit *Focus, int x, int y);
 //void attack();
 //void endTurn(int player);


private:
//    void move(Unit a, int targetx, int targety);
//    bool isValidMove(Unit a, int targetx, int targety);
   bool isOccupied(int x, int y);
//    bool isSufficientAP(Unit a);
//
   int nextPlayer() {return iNextplayer;}
   void setNextPlayer(int player){iNextplayer=player;}
//    Unit getUnit(int x, int y, Unit *UnitRetrieved);
//  //  Unit setFocus(int x, int y);
//    //void startTurn(Unit team[4]);
//    void endTurn();
//    int isGameOver(Unit a[4]);
    Unit *UnitPointer;
    bool gamerunning;
    int iNextplayer;
    bool battleRunning;

};

#endif // MECHANICS_H
