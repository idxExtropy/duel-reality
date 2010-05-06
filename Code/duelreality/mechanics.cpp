#include "mechanics.h"
#define MAXTEAMS 2
#define PLAYER1 1


mechanics::mechanics(QObject *parent) :
    QObject(parent)
{
}

mechanics::~mechanics()
{
}

/////returns whether a battle is active
bool mechanics::isBattle()
 {
     return battleRunning;
 }

////////sets whether a battle is running

void mechanics::setBattleRunning(bool battle)
{
    battleRunning = battle;
}

void mechanics::startBattle()
{
    setBattleRunning(true);
            emit signalBattleStart();
}


//
//void mechanics::move(Unit a, int targetx, int targety)
//{
//    UnitPointer=new Unit;
//    *UnitPointer = a;
//        if(isValidMove(a, targetx, targety))
//        {
//         a.hLocation=targetx;
//        a.vLocation=targety;
//        }
//
//}
//
//bool mechanics::isValidMove(Unit a, int targetx, int targety)
//{
//if(!mechanics::isOccupied(targetx, targety))
//        {
//        if (isSufficientAP(a))
//        {
//                if((a.vLocation==targety)||(a.hLocation==targetx))
//                {
//                        if(((abs(a.vLocation-targety))<=1)&&((abs(a.hLocation-targetx))<=1))
//                        {
//                        return (true);
//                        }
//                }
//                return(false);
//        }
//        return (false);
//
//}
//return (false);
//}
//
//
//bool mechanics::isOccupied(int x, int y)
//{
//
//        if (mapGrid[x][y].isunit)
//        {
//        return (true);
//        }
//        else return false;
//}
//
//bool mechanics::isSufficientAP(Unit a)
//{
//        if(a.actionPoints>=a.movementRate)
//        {
//        return true;
//        }
//        else return false;
//}
//
//
//
//Unit mechanics::getUnit(int x, int y, Unit *UnitRetreived)
//{
//   Unit Unit[4];
//   if(1)//(mapGrid[x][y].isUnit)
//    {
//        for(int i=0;i<=MAXTEAMS;i++)
//        {
//                for(int j=0;j<=MAX_TEAM_UNITS;j++)
//                {
//                        if(Unit[j].team==i)
//                        {
//                                if((Unit[j].hLocation==x)&&(Unit[j].vLocation==y))
//                                {
//                                if(Unit[j].status==UNIT_OK){
//                                return Unit[j];
//                                }
//                                }
//                        }
//                }
//        }
//    }
//   return Unit[0];
//}
//
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
//
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
//
//int mechanics::isGameOver(Unit a[4])
//{
//    int deadcount=0;
//    for(int i=0;i<=MAXTEAMS;i++)
//    {
//        for (int j=0;j<=MAX_TEAM_UNITS;j++)
//        {
//            if (a[j].team==1)
//            {
//                if(a[j].status==UNIT_DEAD)
//                {
//                    deadcount++;
//                }
//                if (deadcount ==4)
//                {    //emit SignalP2Win()
//              return 2;
//                }
//            }
//
//            if (a[j].team==2)
//            {
//                if(a[j].status==UNIT_DEAD)
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
//
//
//        }
//    }
//    return 0;
//}
//
