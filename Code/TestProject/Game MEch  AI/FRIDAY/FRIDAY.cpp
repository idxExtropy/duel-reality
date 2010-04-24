#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "unit.h"
#include "map.h"

using namespace std;

class player{
	
public:
	
	player(char ID[20]);
	int campaignLevel;
	int XPGained;
	int XPAvailable;
	void getTeam();
	void maketeam();
protected:
	int unitarray[4];
	
};

player::player(char ID[20])
{
	cout<<"\n HI there "<<ID << '\n';
	campaignLevel = 0;
	XPGained=0;
	XPAvailable=0;
	cout<<"campaign level= " <<campaignLevel<<'\n';
	cout<<"Total XP= " <<XPGained<<'\n';
	cout<<"Xp available to spend= " <<XPAvailable<<'\n';
}
void player::getTeam()
{
int type;


	cout<<"\n It's time to make your team:\n";
	for (int x=0; x<=3; x++)
	{
	 cout	<< "choose your unit types by entering (1-3), \nyou have " <<4-x<< " left to choose >>";
	 cin >> type;
	 switch (type)
	 {
	 case 1:
        {
        cout<< "unit " << x+1<< " is a soldier\n\n";
       unitarray[x]=1;
        break;
        }
	 case 2:
        {
        cout<< "unit " << x+1 << " is a wizard\n\n";
       unitarray[x]=2;
        break;
        }
	 case 3:
        {
        cout<< "unit " << x+1 << " is a monk\n\n";
        unitarray[x]=3;
        break;
        }
	 default:
        {
        cout<< "invalid number, you get a soldier\n\n";
        unitarray[x]=1;
        break;
        }
	  }//switch
    }//for
}//getTeam
void player::maketeam()
{	
	
    cout<<"\n making the team\n";
		unit a(unitarray[0]);
		unit b(unitarray[1]);
		unit c(unitarray[2]);
		unit d(unitarray[3]);
		unit team[4] ={a,b,c,d};
		for(int j=0; j<=3; j++)
		{
		cout<<"unit "<<j+1<<" is a "<<team[j].name<<'\n';
		}
		cout<<"kick-ass now let's fight\n";

		for(;;);
}


int main()
{	
	
	char ID[20];
	cout<< "WELCOME TO DUEL REALITY\nEnter player name: ";
	cin>> ID;
	/////////////////////////////////////////////for (int j = 0;j<=MAXPLAYERS; J++) 
	///////////////////////////////////////////////if(!strcmp(ID, knownplayers[MAXPLAYERS])
    player newPlayer(ID);
	newPlayer.getTeam();
	newPlayer.maketeam();
	map newMap();

//for(;;);
return 0;
}