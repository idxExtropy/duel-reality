#ifndef MECHANICS_H
#define MECHANICS_H
#include "duelreality.h"
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QString>
#include "GLWidget.h"
#include "test_db.h"

class Unit;
class test_db;
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
void signalTestOutput();
void signalBattleEnd();
 void signalPlayerLost();

public slots:
void slotTestInput();
private:
   int targetx;
   int targety;
    bool isValidMove(int vloc, int hloc,int vnext,int hnext);
    bool isValidAttack(int targv, int targh, int atkrange, int atkrv, int  atkrh, int atkteam, int tarteam);
    bool isOccupied(int x, int y);
    bool isGameOverP1();
    bool isGameOverP2();
    void populate();
    void checkGameEnd();
    Unit *FocusUnit;
    bool gamerunning;
    bool battleRunning;
    int AIcheckboard(int, int, int);
    int AIAttackCheck(int a, int b, int c, int power);
    int AImoveCheck(int aiV, int aiH, int range);
    void makeAIunits();
    void sendBattleEnd();
    void sendPlayerLost();
    Database db;
};

#endif // MECHANICS_H
