#include "mechanics.h"
#include "player.h"

#define BOARDHEIGHT 7
#define BOARDWIDTH 10

mechanics::mechanics()
{
        cout<<"loading mechanics\n\n";
}

mechanics::~mechanics(void)
{
}
//////////////////////////////////////////////////////////////////////////////
//
//JOSH KILGORE
////////MOVEUP: MOVES UNIT UP 1 SPACE VERTICALLY
//INPUTS UNIT A:
//OUTPUTS NONE
/////////////////////////////////////////////////////////
void mechanics::moveUP(unit a)
{
        cout<<a.name<<" ";
     //   cout<<"old position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        if(a.vLocation==BOARDHEIGHT)
        {
     //   cout<< "can't move there no move made\n";
        mechanics::Move(a);
        }
        else
        {
        a.vLocation+=1;
     //   cout<<"new position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        a.actionPoints-=a.movementRate;
     //   cout<<"you have "<<a.actionPoints<<" actionpoints\n";
        }

}

//////////////////////////////////////////////////////////////////////////////
//
//JOSH KILGORE
////////MOVEUP: MOVES UNIT DOWN 1 SPACE VERTICALLY
//INPUTS UNIT A:
//OUTPUTS NONE
/////////////////////////////////////////////////////////
void mechanics::moveDOWN(unit a)
{
  //      cout<<a.name<<" ";
 //       cout<<"old position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        if(a.vLocation==0)
        {
//        cout<< "can't move there no move made\n";
        mechanics::Move(a);
        }
        else
        {
        a.vLocation-=1;
 //       cout<<"new position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        a.actionPoints-=a.movementRate;
//        cout<<"you have "<<a.actionPoints<<" actionpoints\n";
        }

}
//////////////////////////////////////////////////////////////////////////////
//
//JOSH KILGORE
////////MOVEUP: MOVES UNIT RIGHT 1 SPACE
//INPUTS UNIT A:
//OUTPUTS NONE
/////////////////////////////////////////////////////////


void mechanics::moveRIGHT(unit a)
{
   //     cout<<a.name<<" ";
   //     cout<<"old position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        if(a.hLocation==BOARDWIDTH)
        {
  //              cout<< "can't move there no move made\n";
                mechanics::Move(a);
        }
        else
        {
        a.hLocation+=1;
  //      cout<<"new position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        a.actionPoints-=a.movementRate;
  //      cout<<"you have "<<a.actionPoints<<" actionpoints\n";
        }

}

//////////////////////////////////////////////////////////////////////////////
//
//JOSH KILGORE
////////MOVEUP: MOVES UNIT LEFT 1 SPACE VERTICALLY
//INPUTS UNIT A:
//OUTPUTS NONE
/////////////////////////////////////////////////////////
void mechanics::moveLEFT(unit a)
{
   //     cout<<a.name<<" ";
   //     cout<<"old position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        if(a.hLocation==0)
        {
 //       cout<< "can't move there no move made\n";
        mechanics::Move(a);
        }
        else
        {
        a.hLocation-=1;
//        cout<<"new position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        a.actionPoints-=a.movementRate;
 //       cout<<"you have "<<a.actionPoints<<" actionpoints\n";
        }

}
/////////////////////////////////////////////////////////////////////////////
//
//JOSH KILGORE
//MOVE
// DEPENDING ON USER CHOICE, MOVES UNIT IN A DIRECTION
//INPUTS: UNITTOMOVE
//OUTPUT NONE:
///////////////////////////////////////////////////////////////////////////////

void mechanics:: Move(unit unittomove)
{
        int direction;
   //     cout<<"you have "<<unittomove.actionPoints<<" actionpoints\n";
   //     cout<<"you are moving: "<<unittomove.name<<" currently at " <<unittomove.hLocation<<", " <<unittomove.vLocation<<'\n';
  //      cout<<"pick a direction:(1-4) 1-> UP, 2->DOWN, 3-> right, 4-> LEFT:\n";
        cin>>direction;
        switch (direction)
        {
        case 1:
                {
                        mechanics::moveUP(unittomove);
      //                  cout<<"test: reflect new position?"<<unittomove.hLocation<<", " <<unittomove.vLocation<<'\n';
                        break;
                }
        case 2:
                {
                        mechanics::moveDOWN(unittomove);
                        break;
                }
        case 3:
                {
                        mechanics::moveRIGHT(unittomove);
                        break;
                }
        case 4:
                {
                        mechanics::moveLEFT(unittomove);
                        break;
                }
        default:
                {
    //                    cout<<"invalid move, no temporal rifts for you! try again";
                        mechanics::Move(unittomove);
                }
        }//switch
}//Move()


/////////////////////////////////////////////////////////////////////////////
//
//JOSH KILGORE
//mechanics::isValidMove
// Determines if target x,y is a valid move from current x,y
//Requires 4 checks: istarget square occupied? is there sufficient AP? is the move diagonal? is the move within range?
//INPUTS: X Y location///make UNIT?
//OUTPUT T/F
///////////////////////////////////////////////////////////////////////////////
bool mechanics::isValidMove(unit a, int targetx, int targety)
{
   // if(mechanics::isOccupied(targetx,targety))
     //   {
            if(isSufficientAP(a.actionPoints, a.movementRate))
            {
                if((a.vLocation==targety)||(a.hLocation==targetx))  //NO DIAGONALS
                {
                    if((abs(a.vLocation-targety)<=1)&&(abs(a.hLocation-targetx)<=1))  //WITHIN RANGE - FOR RIGHT NOW SET TO 1
                    {
                        return true;
                    }
                }

    //    }
        }
            return false;
 }
/*
/////////////////////////////////////////////////////////////////////////////
//
//JOSH KILGORE
//mechanics::isOccupied()
// Determines if a gridbox is occupied
//INPUTS: X Y location
//OUTPUT T/F
///////////////////////////////////////////////////////////////////////////////
bool mechanics::isOccupied(int x, int y)
{
   if (mapGrid[x][y].isUnit)
    {
       return true;
    }
   else return false;
}

*/

void mechanics::attack(unit a, unit target)
{
    if(a.team!=target.team)
    {
         if(isSufficientAP(a.actionPoints, a.movementRate))
         {
           if(isValidAttack(a,target))
        {
            target.hitPoints-=a.attackPower;
            a.actionPoints-=a.movementRate;

        }
    }
    }
}

bool mechanics::isValidAttack(unit a, unit target)
{


        if((a.vLocation==target.vLocation)||(a.hLocation==target.hLocation))  //NO DIAGONALS
        {
            if((abs(a.vLocation-target.vLocation)<=a.attackRange)&&(abs(a.hLocation-target.hLocation)<=a.attackRange))  //WITHIN RANGE
            {
                return true;
            }
        }
    return false;
}
/*
void mechanics::initiate()
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

        jmap newMap;
        newMap.populate(team);
        mechanics thisGame;
        thisGame.Move(team[0]);
        newMap.locationUpdate(team);


}
*/
/////////////////////////////////////////////////////////////////////////////
//
//JOSH KILGORE
//mechanics::isSufficientAP
// Tests if there are sufficient Action Points to do a desired action
//INPUTS: unit's Action Points, Movement Rate
//OUTPUT T/F
///////////////////////////////////////////////////////////////////////////////
bool mechanics::isSufficientAP(int AP, int moveRate)
{
    if(AP>=moveRate)
    {
        return true;
    }
    else return false;              //SUFFICIENT ACTION POINTS
}
