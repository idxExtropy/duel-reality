#pragma once
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "unit.h"
#include "map.h"
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
	//bool isValidMove(map a, int targetx, int targety);
	//bool isOccupied(map a, int b, int c);

};

