
#include "player.h"
#include "unit.h"

player::player(char ID[20])
{
	cout<<"\nHI there "<<ID << '\n';
	campaignLevel = 0;
	XPGained=0;
	XPAvailable=0;
	cout<<"\nYour Stats:\nCampaign level= "<<campaignLevel<<'\n';
	cout<<"Total XP= " <<XPGained<<'\n';
	cout<<"Xp available to spend= " <<XPAvailable<<'\n'<<'\n';
}


unit player::getTeam()
 {
	int type;
	//cout<<"\n It's time to make your team:\n";
	//for (int x=0; x<=3; x++)
	//{
	 cout	<< "choose your unit types by entering (1-3), \n"
	"1: soldier\n"
	"2:wizard\n"
	"3:monk\n";
	//"you have " <<4-x<< " left to choose >>";
	 cin >> type;
	 switch (type)
	 {
	 case 1:
        {
        cout<< "you have found a corageous Soldier\n\n";
       return unit(1);
        break;
        }
	 case 2:
        {
        cout<< "you have recruited a mighty Wizard\n\n";
       return unit(2);
        break;
        }
	 case 3:
        {
        cout<< "You have enlisted the aid of a venerable Monk\n\n";
        return unit(3);
        break;
        }
	 default:
        {
        cout<< "invalid number, you can't follow directions,\nand therefore get a Soldier to learn from\n\n";
       return unit(1);
        break;
        }
	  }//switch
   // }//for	
}//getTeam


