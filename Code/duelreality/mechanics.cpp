#include "mechanics.h"
#define MAXTEAMS 2
#define PLAYER1 1

// Global classes.
extern GLWidget *glWidget;

//constructor
mechanics::mechanics(QObject *parent) :
    QObject(parent)
{

}
//Destructor
mechanics::~mechanics()
{
}

void mechanics::handleAI()
{
    for (int i = 0; i < glWidget->battleMap.cellsTall; i++)
    {
        for (int j = 0; j < glWidget->battleMap.cellsWide; j++)
        {
            if ((glWidget->battleMap.gridCell[i][j].unit->isPending) && (glWidget->battleMap.gridCell[i][j].unit->team == AI_UNIT))
            {
                // Dummy movement for now...
                if(mechanics::isValidMove(i,j,i+1,j))//Move UP
                {
                glWidget->moveUnit(i,j,i+1,j);
                 }
                else glWidget->moveUnit(i,j,i-1,j);
//                 else if(mechanics::isValidMove(i,j,i,j+1))//MOVE LEFT
//                 {
//                 glWidget->moveUnit(i,j,i,j+1);
//                 }
//                 else if(mechanics::isValidMove(i,j,i-1,j))//MOVE Down
//                 {
//                 glWidget->moveUnit(i,j,i-1,j);
//                 }
//                 else if(mechanics::isValidMove(i,j,i,j-1))//MOVE Right
//                 {
//                 glWidget->moveUnit(i,j,i,j-1);
//                 }
            }
        }
    }
}






///////////////////////////////////////////////////BATTLE ACTIVE///////////////////////////
//Returns whether a battle is active
bool mechanics::isBattle()
 {
     return battleRunning;
 }

//Allows game to set condition of whether a battle is running
void mechanics::setBattleRunning(bool battle)
{
    battleRunning = battle;
}

//Called at Start of a Battle
void mechanics::startBattle()
{
    setBattleRunning(true);
    emit signalBattleStart();
}

void mechanics::endBattle()
{
    setBattleRunning(false);
}

//////////////////////////////////////////////////////MOVE///////////////////////////////////////
// loads selected square into lext location V&H
void mechanics::moveUnit()
{
    int vLocNext = 0, hLocNext = 0;
    for (int i = 0; i < glWidget->battleMap.cellsTall; i++)
    {
        for (int j = 0; j < glWidget->battleMap.cellsWide; j++)
        {
            if (glWidget->battleMap.gridCell[i][j].isSelected)
            {
                vLocNext = i;
                hLocNext = j;
            }
        }
    }

    for (int i = 0; i < glWidget->battleMap.cellsTall; i++)
    {
        for (int j = 0; j < glWidget->battleMap.cellsWide; j++)
        {
            if (glWidget->battleMap.gridCell[i][j].unit->isPending)
            {
                if(mechanics::isValidMove(i,j,vLocNext,hLocNext))
                {
                glWidget->moveUnit(i,j,vLocNext,hLocNext);       //moves from pending to selected!!!
                }
                return;
            }
        }
    }
}

//Determines Whether a move is valid
bool mechanics::isValidMove(int vLoc, int hLoc,int vnext,int hnext)
{
if(!mechanics::isOccupied(hnext, vnext))
        {
           if((vLoc==vnext)||(hLoc==hnext))//no diagonal
           {
               if(vnext<=glWidget->battleMap.cellsTall-1&&vnext>=0)//6
               {
                   if(hnext<=glWidget->battleMap.cellsWide-1&&hnext>=0)//9
                   {
                     if(((abs(vLoc-vnext))<=glWidget->battleMap.gridCell[vLoc][hLoc].unit->movementRate)&&((abs(hLoc-hnext))<=glWidget->battleMap.gridCell[vLoc][hLoc].unit->movementRate))
                     {
                     return (true);
                     }
                   return (false);
                   }
               return (false);
               }
          return (false);
          }
    return (false);
    }
return (false);
}
//Determines if a space is occupied
bool mechanics::isOccupied(int x, int y)  ///DOUBLECHECK
{

    if (glWidget->battleMap.gridCell[x][y].isUnit)
        {
        return (true);
        }
       else return false;
}


////////////////////////////////////////////////ATTACK////////////////////////////////////////////////
void mechanics::attackUnit()
{
    int vAttackerLoc = 0, hAttackerLoc = 0, damage = 0, range =0;

    for (int i = 0; i < glWidget->battleMap.cellsTall; i++)
    {
        for (int j = 0; j < glWidget->battleMap.cellsWide; j++)
        {
            if (glWidget->battleMap.gridCell[i][j].unit->isPending)
            {
                // Get the upcoming attack power and location.
                damage = glWidget->battleMap.gridCell[i][j].unit->attackPower;
                vAttackerLoc = glWidget->battleMap.gridCell[i][j].unit->vLocation;
                hAttackerLoc = glWidget->battleMap.gridCell[i][j].unit->hLocation;
                range = glWidget->battleMap.gridCell[i][j].unit->attackRange;
            }
        }
    }
    for (int i = 0; i < glWidget->battleMap.cellsTall; i++)
    {
        for (int j = 0; j < glWidget->battleMap.cellsWide; j++)
        {
            if (glWidget->battleMap.gridCell[i][j].isSelected)
            {
           //     if(mechanics::isValidAttack( i,j, range, vAttackerLoc, hAttackerLoc))
            //    {
                  if (glWidget->battleMap.gridCell[i][j].unit->hitPoints<=glWidget->battleMap.gridCell[vAttackerLoc][hAttackerLoc].unit->attackPower)
                  {
                   glWidget->killUnit(i,j,vAttackerLoc, hAttackerLoc);
                  }
                 else glWidget->hitUnit(i,j,damage,vAttackerLoc,hAttackerLoc);
          //    }
            }
        }
    }
}
//Determines Whether an attack is valid
bool mechanics::isValidAttack(int targv, int targh, int atkrange, int atkrv, int  atkrh)
{
if(mechanics::isOccupied(targh, targv))
       {
                if((atkrv==targv)||(atkrh==targh))//no diagonals
                {
                        if(((abs(atkrv-targv))<=atkrange)&&((abs(atkrh-targh))<=atkrange))
                        {
                        return (true);
                        }
                        return false;
                }
                return(false);

        }
        return (false);
}
///*
//// if there is a unit with isPending=true, loads FocusUnit pointer to address of that unit - called by move/attack
//bool mechanics::getPending()
//{
//    for(int x=0;x<=glWidget->battleMap.cellsTall;x++)
//    {
//        for(int y=0;y<=glWidget->battleMap.cellsWide;y++)
//        {
//          if(glWidget->battleMap.gridCell[x][y].unit->isPending)
//          {
//          FocusUnit=glWidget->battleMap.gridCell[x][y].unit;
//          return true;
//          }
//          return (false);
//        }
//    }return (false);
//}
//
//Unit *mechanics::getUnit(int x, int y)
//     {
//        return glWidget->battleMap.gridCell[y][x].unit;    //vLoc, HLoc order in glwidget.cpp
//     }

/////////////////////////////////////////////////////////////FOCUS////////////////////

//// Set's which unit that the player is moving that turn
//// needs another signal slot - used at start of player 1 turn
/////////////////////////////////////////////
//
//finds which gridCell is selected, passes coordinates to targetx & target y
//bool mechanics::getGridCellSelected() //2D array of pointers of type gridBox
//{
//    int *ip1 = &targetx;
//    int *ip2 = &targety;
//        for(int x=0;x<=glWidget->battleMap.cellsTall;x++)
//        {
//         for(int y=0;y<=glWidget->battleMap.cellsWide;y++)
//         {
//                if(glWidget->battleMap.gridCell[x][y].isSelected)
//                {
//                        *ip1=x;
//                        *ip2=y;
//                        return (true);
//
//                }
//               return (false);
//         }
//        }return (false);
//}
//////////////////////////////////////////////////TURNS//////////////////////////////////////////////
////executes when passed ENDTURN SIGNAL
////deselect focus unit?
////
//
//void mechanics::endTurn()
//{
//        //mechanics::switchPlayer();
//}
//

////
//
////////////////////////////////////////////////GAMEOVER//////////////////////////////////
bool mechanics::isGameOver()
{
    int deadcount=0;
    for(int x=0;x<=glWidget->battleMap.cellsTall;x++)
    {
     for(int y=0;y<=glWidget->battleMap.cellsWide;y++)
     {
           if(glWidget->battleMap.gridCell[x][y].unit->status==UNIT_DEAD&&glWidget->battleMap.gridCell[x][y].unit->team==USER_UNIT)
           {
                    deadcount++;
                if (deadcount ==4)
                {
                    emit SignalP2Win();
                  //mechanics::EndBattle();
                    return true;
                }
            }

            if (glWidget->battleMap.gridCell[x][y].unit->status==UNIT_DEAD&&glWidget->battleMap.gridCell[x][y].unit->team==AI_UNIT)
            {
                    deadcount++;
                if (deadcount ==4)
                 {
                 emit SignalP1Win();
                 //mechanics::EndBattle();
                 return true;
                 }
            }
            else
                deadcount=0;
                return false;
        }
    }
    return false;
}
//////////////////////////////////////////////////////AI/////////////////////////////////////
// void mechanics::startAI()
//{
//
//    //AI myAI;
//   //bool result = myAI.getmove(px,py);
//     // if(result){move(Unit *UnitPointer,int x, int y);
//     //mechanics::isGameOver();
//
//}
