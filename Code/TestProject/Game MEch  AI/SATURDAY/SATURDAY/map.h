#pragma once
#define BOARDHEIGHT 7
#define BOARDWIDTH 10
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "unit.h"
//#include "player.h"

using namespace std;

class map
{
public:
	int mapGrid[BOARDHEIGHT][BOARDWIDTH];
	map();
	void populate(unit team[4]);
	void locationUpdate(unit team[4]);

};
