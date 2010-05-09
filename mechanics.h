#ifndef MECHANICS_H
#define MECHANICS_H
#include "globals.h"
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QString>
#include "GLWidget.h"
#include "test_db.h"

class Unit;
class test_db;
//class GLWidget;
class MainWindow;
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
    void handleAI();
    void moveUnit();
    void attackUnit();
    int endBattle(int x);

signals:
 void SignalP1Win();   //signal emited from isGameOVer if P1 Wins
 void SignalP2Win();   //signal emited if P2 Wins
 void SignalSwitchPlayer(); //signal emitted when player switches
 void SignalMoveDone();     //signal emitted when move is complete
 void SignalAttackDone();   //signal emitted when attack is complete
 void SignalError();        //signal emitted on error
 void SignalStartAI();      //signal when AI moves
 void signalBattleStart();  //signal when battle starts



public slots:

private:
   int targetx;
   int targety;
    bool isValidMove(int vloc, int hloc,int vnext,int hnext);
    bool isValidAttack(int targv, int targh, int atkrange, int atkrv, int  atkrh, int atkteam, int tarteam);
    bool isOccupied(int x, int y);

 //  int nextPlayer() {return iNextplayer;}
  // void setNextPlayer(int player){iNextplayer=player;}
 //  bool isUnitAt(int x, int y, Unit *UnitRetrieved);
   //    void endTurn();
    int isGameOver();
    void checkGameEnd();
    Unit *FocusUnit;
    bool gamerunning;
  //  int iNextplayer;
    bool battleRunning;
//    void startAI();
  //  bool getGridCellSelected();
   // bool getPending();
  //  Unit *getUnit(int x, int y);
    int AIcheckboard(int, int, int);
};

#endif // MECHANICS_H
