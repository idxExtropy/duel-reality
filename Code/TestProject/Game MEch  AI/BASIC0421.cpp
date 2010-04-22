// BASIC0421.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "unit.h"
#include "stdio.h"
#include "iostream"

using namespace std;

void main()
{
char playerID[20];
int type;
int team[3];


cout<<"enter player name >>";
cin>> playerID;


cout<<"Hi " << playerID<< "!!!\n\n";

for (int x=0; x<=3; x++)
{
cout	<< "choose your unit types by entering (1-3), \nyou have " <<4-x<< " left to choose >>";

cin >> type;
 switch (type)
 {
  case 1:
        {
        cout<< "unit " << x+1<< " is a soldier\n\n";
        team[x] = 1;
		break;
		}
  case 2:
        {
        cout<< "unit " << x+1 << " is an archer\n\n";
		team[x] = 2;
        break;
        }

  case 3:
        {
        cout<< "unit " << x+1 << " is a monk\n\n";
		team[x]=3;
       break;
        }
  default:
        {
        cout<< "invalid number, you get a soldier\n\n";
        team[x]=1;
		break;
        }
 }//switch
}//for
		


	cout<< " great now what????";
	for(int j=0; j<=3; j++)
	{ cout<< team[j] <<" ";}

	
for(;;);
}//main
