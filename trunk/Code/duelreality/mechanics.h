#ifndef MECHANICS_H
#define MECHANICS_H
#include "globals.h"
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QString>

class Unit;
class test_db;

class mechanics : public QObject
{
Q_OBJECT
public:
    explicit mechanics(QObject *parent = 0);
    ~mechanics();
    bool isRunning() {return gamerunning;}
      void setRunnint(bool run) {gamerunning=run;}

signals:
// signalP1wins();
// signalP2wins();
// signalSwitchPlayer();
// signalMoveDone();
// signalAttackDone();
// signalError();
// startAI();


public slots:
 //void move(unit *a, int x, int y);
 //void attack(unit *a, int x int y);
 //void endTurn(int player);


private:
    void move(Unit a, int targetx, int targety);
    bool isValidMove(Unit a, int targetx, int targety);
    bool isOccupied(int x, int y);
    bool isSufficientAP(Unit a);

    int nextPlayer() {return iNextplayer;}
    void setNextPlayer(int player){iNextplayer=player;}
    Unit getUnit(int x, int y);
    Unit setFocus(int x, int y);
    //void startTurn(Unit team[4]);
    void endTurn();
    int isGameOver(Unit a[4]);
    Unit *UnitPointer;
    bool gamerunning;
    int iNextplayer;

};

#endif // MECHANICS_H
