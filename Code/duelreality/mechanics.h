#ifndef MECHANICS_H
#define MECHANICS_H

#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "unit.h"
#include "jmap.h"
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
        //bool isValidMove(jmap a, int targetx, int targety);
        //bool isOccupied(jmap a, int b, int c);

};


#endif // MECHANICS_H
