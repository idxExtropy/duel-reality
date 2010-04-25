#include "map.h"
#include "conio.h"
#include "player.h"
#include "unit.h"

///////////////////////////////////////////////////////////////////////////////////
//JOSH KILGORE
//
//Constructor for map - initialized grid to 0;
///////////////////////////////////////////////////////////////////////////////

map::map(void)
{
	for(int x=0; x<=BOARDHEIGHT; x++)
	{
		for (int y=0; y<=BOARDWIDTH; y++)
		{
			mapGrid[x][y] = 0;
		}
	}cout<<"Nice new map loaded for you!\n";
}

//unit player::team[4];

////////////////////////////////////////////////////////////////////////////////////////////////////
//JOSH KILGORE
// map::populate()
//
// randomly assigns starting positions for player
////keeps to left half of screen to start Player 1 //AI on other side rand() +5%10 i think.
////////////////////////////////////////////////////////////////////////////////////////////////////

void map::populate(unit team[4])
{
	cout<<"\nTo load your team press any key:\n";
	int location[5][2];
	while(!_kbhit()) rand(); //makes actually random
	for(int i=0; i<4; i++)
	{
	 location[i][0] = rand() % BOARDHEIGHT;
	 location[i][1] = rand()% BOARDWIDTH/2;  
		//need way to make sure spots not overlap!!!-putPiece()
		}
	team[0].vLocation = location[0][0];
	team[0].hLocation = location[0][1];
	cout<<team[0].name<<" is at "<<team[0].hLocation<<", " <<team[0].vLocation<<'\n';//ALWAYS LIST AS HLOV,VLOC!!!
	
	team[1].vLocation = location[1][0];
	team[1].hLocation = location[1][1];
	cout<<team[1].name<<" is at "<<team[1].hLocation<<", " <<team[1].vLocation<<'\n';

	team[2].vLocation = location[2][0];
	team[2].hLocation = location[2][1];
	cout<<team[2].name<<" is at "<<team[2].hLocation<<", " <<team[2].vLocation<<'\n';

	team[3].vLocation = location[3][0];
	team[3].hLocation = location[3][1];
	cout<<team[3].name<<" is at "<<team[3].hLocation<<", " <<team[3].vLocation<<'\n';
	  cout<<"next work on move\n";
 }
	//////////////////////////////////////////////////////////////////////////////
//
//JOSH KILGORE
////////location update: loads the current location of all units into an array
////////// to determine positioning for evaluation and validation ofo moves & attacks
//INPUTS UNITS
//OUTPUTS NONE
/////////////////////////////////////////////////////////
 void map::locationUpdate(unit team[4])
 {
	static int placearray[10][2];
	 for(int x=0; x<=3; x++)
		 {
			 if(team[x].status)
			 {
				 placearray[x][0]=team[x].hLocation;
				placearray[x][1]=team[x].vLocation;
				cout<<placearray[x][0]<<", "<< placearray[x][1]<<'\n';//for testing
			 }
		 }
 }
 

