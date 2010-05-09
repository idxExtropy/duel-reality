#ifndef SMAP_H
#define SMAP_H

#define BOARDHEIGHT 7
#define BOARDWIDTH 10
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "unit.h"
//#include "player.h"

using namespace std;

class smap
{
public:
        int mapGrid[BOARDHEIGHT][BOARDWIDTH];
        smap();
        void populate(unit team[4]);
        void locationUpdate(unit team[4]);

};
#endif // SMAP_H
