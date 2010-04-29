#ifndef MECHANICS_H
#define MECHANICS_H

#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "unit.h"
#include "jmap.h"
#include "glwidget.h"
//#include "player.h"

class mechanics
{
public:
        mechanics();
        ~mechanics(void);
        void moveUP(unit a);
        void moveDOWN(unit a);
        void moveLEFT(unit a);
        void moveRIGHT(unit a);
        void Move(unit unittomove);
      //  void initiate();
        bool isValidMove(unit a, int targetx, int targety);
        bool isOccupied(int b, int c);
        void attack(unit a, unit target);
        bool isValidAttack(unit a, unit target);
        //bool isGameOver()
        //unit upgradeUnit(unit)
        bool isSufficientAP (int AP, int moveRate);
};


#endif // MECHANICS_H
