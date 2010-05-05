#ifndef MECHANICS_H
#define MECHANICS_H
#include "globals.h"
#include <QObject>

class Unit;

class mechanics : public QObject
{
Q_OBJECT
public:
    explicit mechanics(QObject *parent = 0);

signals:

public slots:
 //void move();
 //void attack();
 //void endTurn();

private:
    void move(Unit a, int targetx, int targety);
    bool isValidMove(Unit a, int targetx, int targety);
    bool isOccupied(int x, int y);
    bool isSufficientAP(Unit a);
    Unit getUnit(int x, int y);
    Unit setFocus(int x, int y);
    //void startTurn(Unit team[4]);
    void endTurn();

    Unit *UnitPointer;

};

#endif // MECHANICS_H
