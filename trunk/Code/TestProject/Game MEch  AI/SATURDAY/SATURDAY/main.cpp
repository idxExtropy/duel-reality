//#include "stdafx.h"
#define BOARDHEIGHT 7
#define BOARDWIDTH 10
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "player.h"
#include "unit.h"
#include "map.h"
#include "mechanics.h"

using namespace std;
unit team[4];

int main()
{	
	
	char ID[20];
	cout<< "WELCOME TO DUEL REALITY\n"
		"Enter player name: ";
	cin>> ID;
	/////////////////////////////////////////////for (int j = 0;j<=MAXPLAYERS; J++) 
	///////////////////////////////////////////////if(!strcmp(ID, knownplayers[MAXPLAYERS])
    player newPlayer(ID);
	
	 unit a = newPlayer.getTeam();
	 unit b = newPlayer.getTeam();
	 unit c = newPlayer.getTeam();
	 unit d = newPlayer.getTeam();
	 static unit team[4] = {a,b,c,d};
	cout<<"\n Congratulations, "<< ID<<", your team is as follows: "<<team[0].name<<" "<<team[1].name<<" "<<team[2].name<<" "<<team[3].name<<'\n';

	map newMap;
	newMap.populate(team);
	mechanics thisGame;
	thisGame.Move(team[0]);
	newMap.locationUpdate(team);

for(;;);
return 0;
}