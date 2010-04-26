#include "mechanics.h"
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
        cout<<"old position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        if(a.vLocation==BOARDHEIGHT)
        {
        cout<< "can't move there no move made\n";
        mechanics::Move(a);
        }
        else
        {
        a.vLocation+=1;
        cout<<"new position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        a.actionPoints-=a.movementRate;
        cout<<"you have "<<a.actionPoints<<" actionpoints\n";
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
        cout<<a.name<<" ";
        cout<<"old position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        if(a.vLocation==0)
        {
        cout<< "can't move there no move made\n";
        mechanics::Move(a);
        }
        else
        {
        a.vLocation-=1;
        cout<<"new position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        a.actionPoints-=a.movementRate;
        cout<<"you have "<<a.actionPoints<<" actionpoints\n";
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
        cout<<a.name<<" ";
        cout<<"old position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        if(a.hLocation==BOARDWIDTH)
        {
                cout<< "can't move there no move made\n";
                mechanics::Move(a);
        }
        else
        {
        a.hLocation+=1;
        cout<<"new position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        a.actionPoints-=a.movementRate;
        cout<<"you have "<<a.actionPoints<<" actionpoints\n";
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
        cout<<a.name<<" ";
        cout<<"old position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        if(a.hLocation==0)
        {
        cout<< "can't move there no move made\n";
        mechanics::Move(a);
        }
        else
        {
        a.hLocation-=1;
        cout<<"new position: " <<a.hLocation<<", " <<a.vLocation<<'\n';
        a.actionPoints-=a.movementRate;
        cout<<"you have "<<a.actionPoints<<" actionpoints\n";
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
        cout<<"you have "<<unittomove.actionPoints<<" actionpoints\n";
        cout<<"you are moving: "<<unittomove.name<<" currently at " <<unittomove.hLocation<<", " <<unittomove.vLocation<<'\n';
        cout<<"pick a direction:(1-4) 1-> UP, 2->DOWN, 3-> right, 4-> LEFT:\n";
        cin>>direction;
        switch (direction)
        {
        case 1:
                {
                        mechanics::moveUP(unittomove);
                        cout<<"test: reflect new position?"<<unittomove.hLocation<<", " <<unittomove.vLocation<<'\n';
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
                        cout<<"invalid move, no temporal rifts for you! try again";
                        mechanics::Move(unittomove);
                }
        }//switch
}//Move()

/*
bool mechanics::isValidMove(jmap a, int targetx, int targety)
{
        if(isOccupied(map a, targetx,targety))
        {
                return false;
        }
        else return true;
}
*/
/*
bool mechanics::isOccupied(jmap a, int b, int c)
{
        for(int x=0; x<= BOARDWIDTH; x++)
        {
                for(int y=0; y<=BOARDHEIGHT; y++)
                {
                        if (a.mapGrid[x][y]==)
}
*/
