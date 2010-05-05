#include "mechanics.h"
#define MAXTEAMS 2
#define MAXUNITS 3
#define PLAYER1 1

mechanics::mechanics(QObject *parent) :
    QObject(parent)
{
}



void mechanics::move(Unit a, int targetx, int targety)
{
    UnitPointer=new Unit;
    *UnitPointer = a;
        if(isValidMove(a, targetx, targety))
        {
         a.hLocation=targetx;
        a.vLocation=targety;
        }

}

    bool mechanics::isValidMove(Unit a, int targetx, int targety)
{
if(!mechanics::isOccupied(targetx, targety))
        {
        if (isSufficientAP(a))
        {
                if((a.vLocation==targety)||(a.hLocation==targetx))
                {
                        if(((abs(a.vLocation-targety))<=1)&&((abs(a.hLocation-targetx))<=1))
                        {
                        return true;
                        }
                }
        }
        return false;

}
}


bool mechanics::isOccupied(int x, int y)
{
        if (1)//(mapGrid[x][y].isunit)
        {
        return true;
        }
        else return false;
}

bool mechanics::isSufficientAP(Unit a)
{
        if(a.actionPoints>=a.movementRate)
        {
        return true;
        }
        else return false;
}



Unit mechanics::getUnit(int x, int y)
{
Unit Unit[4];
   if(1)//(mapGrid[x][y].isUnit)
    {
        for(int i=0;i<=MAXTEAMS;i++)
        {
                for(int j=0;j<=MAXUNITS;j++)
                {
                        if(Unit[j].team==i)
                        {
                                if((Unit[j].hLocation==x)&&(Unit[j].vLocation==y))
                                {
                                if(Unit[j].status==UNIT_OK){
                                return Unit[j];
                                }
                                }
                        }
                }
        }
    }
}

////////////////////////////////////////////
// Set's which unit that the player is moving that turn
// needs another signal slot - used at start of player 1 turn
///////////////////////////////////////////

Unit mechanics::setFocus(int x, int y)
{
    int Player=1;
        if (Player==PLAYER1)
        {
                if (1) //(mapGrid[x][y].isSelected && mapGrid[x][y].isunit)
                {
                Unit a=mechanics::getUnit(x,y);
                        if(a.team==PLAYER1&&a.status==UNIT_OK)
                        {
                        return a;
                        }
                }
        }
}

//executes when passed ENDTURN SIGNAL
//deselect focus unit?
//

void mechanics::endTurn()
{
        //mechanics::switchPlayer();
}

/////////////////////
//ready for turn
//start focus at unit[0]
//replenish actionpoints for entire team
//////////////////////////
//void mechanics::startTurn(Unit team[MAXUNITS])
//
//{
//        for(int y=0;y<=MAXUNITS; y++)
//        {
//        team[y].actionPoints=team[y].totalActionPoints;
//        }
//        team[y]=Unit[0];
//}
//




