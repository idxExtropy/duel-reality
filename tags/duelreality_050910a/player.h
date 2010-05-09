#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "unit.h"
#include "map.h"

using namespace std;

class player
{

public:
        static unit team[4];
        int campaignLevel;
        int XPGained;
        int XPAvailable;
        unit getTeam();
        player(char ID[20]);
protected:
         int unitarray[4];

};
#endif // PLAYER_H
