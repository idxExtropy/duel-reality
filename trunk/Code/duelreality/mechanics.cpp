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
//////////////////////////////////////////////////////MOVE///////////////////////////////////////
//Move Function, from Slot Move
void mechanics::move(Unit *UnitPointer)
{

        if(isValidMove(UnitPointer->actionPoints, UnitPointer->movementRate, UnitPointer->hLocation, UnitPointer->vLocation, targetx, targety))
        {
        UnitPointer->hLocation=targetx;
        UnitPointer->vLocation=targety;
        UnitPointer->actionPoints-=UnitPointer->movementRate;
        }
}

//Determines Whether a move is valid
bool mechanics::isValidMove(int actionpoints, int moverate, int hLoc, int vLoc,int targetx,int targety)
{
if(!mechanics::isOccupied(targetx, targety))
        {
        if (isSufficientAP(actionpoints, moverate))
        {
                if((vLoc==targety)||(hLoc==targetx))
                {
                        if(((abs(vLoc-targety))<=1)&&((abs(hLoc-targetx))<=1))
                        {
                        return (true);
                        }
                }
                return(false);
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

//Returns whether Unit has enough Action Points to Move/act
bool mechanics::isSufficientAP(int a, int b)
{
        if(a>=b)
        {
        return true;
        }
        else return false;
}
////////////////////////////////////////////////ATTACK////////////////////////////////////////////////
//void mechanics::attack(Unit *UnitPointer, int x, int y)
//{
//    Unit a = *UnitPointer;
//    Unit *Target = mechanics::getUnit(x,y);
//
//        if(isValidAttack(a,Target))
//        {
//        Target.hitPoints-=a.attackPower;
//        if(Target.hitPoints<=0)
//          {
//          Target.status= UNIT_DEAD;
//            }
//        mechanics::isGameOver;
//        }
//
//}
////Determines Whether a move is valid
//bool mechanics::isValidMove(Unit a, Unit *Target)
//{
////if(mechanics::isOccupied(Target.hLocation, Target.vLocation))
//      //  {
//        if (isSufficientAP(a))
//        {
//                if((a.vLocation==Target.hLocation)||(a.hLocation==Target.vLocation))
//                {
//                        if(((abs(a.vLocation-Target.vLocation))<=a.attackRange)&&((abs(a.hLocation-Target.hLocation))<=a.attackRange))
//                        {
//                        return (true);
//                        }
//                }
//                return(false);
//        }
//        return (false);

//}
//return (false);
///*
//Unit mechanics::getUnit(int x, int y)
//{
//    //  if(mechanics::isOccupied(x,y))
//     //  {
//         for(int i=0;i<=MAXTEAMS;i++)
//         {
//           for(int j=0;j<=MAX_TEAM_UNITS;j++)
//            {
//             if(a[j].team==i)
//             {
//}
//         }}}*/

bool mechanics::isUnitAt(int x, int y, Unit *UnitRetrieved)
{
   Unit a=*UnitRetrieved;
 //  if(mechanics::isOccupied(x,y))
  //  {
       // for(int i=0;i<=MAXTEAMS;i++)
        //{
          //      for(int j=0;j<=MAX_TEAM_UNITS;j++)
          //      {
            //            if(a[j].team==i)
              //          {
                                if((a.hLocation==x)&&(a.vLocation==y))
                                {
                                    if(a.status==UNIT_OK)
                                    {
                                     return (true);
                                    }
                                }
                                return (false);
                      //  }
                //return (false);
                //}
        //}
   // }
  // return (false);
}
/////////////////////////////////////////////////////////////FOCUS////////////////////
//////////////////////////////////////////////
//// Set's which unit that the player is moving that turn
//// needs another signal slot - used at start of player 1 turn
/////////////////////////////////////////////
//
////Unit mechanics::setFocus(int x, int y)
////{
////    int Player=1;
////    Unit *a;
////    if (Player==PLAYER1)
////    {
////            if (1) //(mapGrid[x][y].isSelected && mapGrid[x][y].isunit)
////            {
////                *a=&mechanics::getUnit(x,y, a);
////                if(a.team==PLAYER1&&a.status==UNIT_OK)
////                {
////                    return (a);
////                }
////            }
////    }
////    return (a);
////}
//finds which gridCell is selected, passes coordinates to targetx & target y
bool mechanics::getGridCellSelected(int x, int y, int *ip1, int *ip2) //2D array of pointers of type gridBox
{
    ip1 = &targetx;
    ip2 = &targety;
        for(int x=0;x<=glWidget->battleMap.cellsTall;x++)
        {
         for(int y=0;y<=glWidget->battleMap.cellsWide;y++)
         {
                if(glWidget->battleMap.gridCell[x][y].isSelected)
                {
                        *ip1=x;
                        *ip1=y;
                        return (true);

                }
               return (false);
         }
        }return (false);
}
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
///////////////////////
////ready for turn
////start focus at unit[0]
////replenish actionpoints for entire team
////////////////////////////
////void mechanics::startTurn(Unit team[MAXUNITS])
////
////{
////        for(int y=0;y<=MAXUNITS; y++)
////        {
////        team[y].actionPoints=team[y].totalActionPoints;
////        }
////        team[y]=Unit[0];
////}
////
//
////////////////////////////////////////////////GAMEOVER//////////////////////////////////
//int mechanics::isGameOver()
//{
//    int deadcount=0;
//    for(int i=0;i<=MAXTEAMS;i++)
//    {
//        for (int j=0;j<=MAX_TEAM_UNITS;j++)
//        {
//            if (bob.units[j].team==1)
//            {
//                if(Player::units[j].status==UNIT_DEAD)
//                {
//                    deadcount++;
//                }
//                if (deadcount ==4)
//                {
                    //emit SignalP2Win()
//                  mechanics::EndBattle();
//              return 2;
//                }
//            }
//
//            if (Player::units[j].team==2)
//            {
//                if(Player::units[j].status==UNIT_DEAD)
//                {
//                    deadcount++;
//                }
//                if (deadcount ==4)
//                {    //emit SignalP1Win()
//                return 1;
//                }
//            }
//            else
//                deadcount=0;
//                return 0;
//        }
//    }
//    return 0;
//}
////////////////////////////////////////////////////AI/////////////////////////////////////
 void mechanics::startAI()
{

    //AI myAI;
   //bool result = myAI.getmove(px,py);
     // if(result){move(Unit *UnitPointer,int x, int y);
     //mechanics::isGameOver();

}
