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
//class GLWidget;
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
    void endBattle();

signals:
 void signalP1wins();   //signal emited from isGameOVer if P1 Wins
 void signalP2wins();   //signal emited if P2 Wins
 void signalSwitchPlayer(); //signal emitted when player switches
 void signalMoveDone();     //signal emitted when move is complete
 void signalAttackDone();   //signal emitted when attack is complete
 void signalError();        //signal emitted on error
 void signalStartAI();      //signal when AI moves
 void signalBattleStart();  //signal when battle starts



public slots:
 void move(Unit *Focus);   //slot for move
 //void attack(Unit *Focus, Unit *Target);   //slot for attack
 //void endTurn(int player);            //slot


private:

    bool isValidMove(int actionpoints, int moverate, int hLoc, int vLoc,int targetx,int targety);
    bool isOccupied(int x, int y);
    bool isSufficientAP(int a, int b);
   int nextPlayer() {return iNextplayer;}
   void setNextPlayer(int player){iNextplayer=player;}
   bool isUnitAt(int x, int y, Unit *UnitRetrieved);
   //  //  Unit setFocus(int x, int y);
   //    //void startTurn(Unit team[4]);
   //    void endTurn();
    int isGameOver();
    Unit *UnitPointer;
    int targetx;
    int targety;
    bool gamerunning;
    int iNextplayer;
    bool battleRunning;
    void startAI();
    bool getGridCellSelected(int x, int y, int *ip1, int *ip2);

};

#endif // MECHANICS_H
