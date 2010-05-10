#include "mechanics.h"
#define MAXTEAMS 2
#define PLAYER1 1

// Global classes.
extern GLWidget *glWidget;
MainWindow *mainwindow;

//constructor
mechanics::mechanics(QObject *parent) :
    QObject(parent)
{

}
//Destructor
mechanics::~mechanics()
{
}
//
///////////////////////////////////////////SIGNALS////////////////////////////////////////
 void mechanics::slotTestInput()
 {
     emit signalTestOutput();
 }
 void mechanics::sendBattleEnd()
 {
     emit signalBattleEnd();
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

 void mechanics::makeAIunits()
 {
QList<Unit> tempunits;
User tempUser = db.loadActiveUser();
Unit AIunits[MAX_TEAM_UNITS];
tempunits = db.loadUnits(tempUser.name);


 for (int x; x<MAX_TEAM_UNITS; x++)
    {
     AIunits[x] = tempunits[x];
    }
     for(int i=0; i<MAX_TEAM_UNITS; i++)
 {
         AIunits[i].faceLeft = true;
         AIunits[i].team = AI_UNIT;
     }
}



//////////////////////////////////////////////////////AI/////////////////////////////////////
void mechanics::handleAI()
{
    // int value=0;

    for (int i = 0; i < glWidget->battleMap.cellsTall; i++)
    {
        for (int j = 0; j < glWidget->battleMap.cellsWide; j++)
        {
            if ((glWidget->battleMap.gridCell[i][j].unit->isPending) && (glWidget->battleMap.gridCell[i][j].unit->team ==AI_UNIT) && (glWidget->battleMap.gridCell[i][j].unit->status == UNIT_OK))
            { ///START AI ROUTINE

                int range = glWidget->battleMap.gridCell[i][j].unit->attackRange;
                int power = glWidget->battleMap.gridCell[i][j].unit->attackPower;
                int attackCheckResult;
                int moverange= glWidget->battleMap.gridCell[i][j].unit->movementRange;
                attackCheckResult = mechanics::AIAttackCheck(i,j, range, power);         //from AI postion, hit anything in range
                int moveCheckResult;


                switch (attackCheckResult)
                {
                case 0:
                    // glWidget->hitUnit(targv,targh,power,i,j);
                    break;
                case 1:
                    //glWidget->killUnit(targv,targh,i,j);
                    break;
                default:
                    {
                        moveCheckResult=mechanics::AImoveCheck(i,j,moverange);
                        switch(moveCheckResult)
                        {
                            //case 0: glWidget->moveUnit(i,j,i-1,j);break;
                        case 0: if(mechanics::isValidMove(i,j,i+moverange,j))//Move UP
                            {
                                glWidget->moveUnit(i,j,i+moverange,j);
                            }
                            // case 2: glWidget->moveUnit(i,j,i-1,j);break;
                      case 1:if(mechanics::isValidMove(i,j,i-moverange,j))//Move DOWN
                            {
                              glWidget->moveUnit(i,j,i-moverange,j);
                          }
                          // case 4: glWidget->moveUnit(i,j,i-1,j);break;
                      case 2: if(mechanics::isValidMove(i,j,i,j+moverange))//Move RIGHT
                          {
                              glWidget->moveUnit(i,j,i,j+moverange);
                          }
                          //      case 6: glWidget->moveUnit(i,j,i-1,j);break;
                      case 3: if(mechanics::isValidMove(i,j,i,j-moverange))//Move LEFT
                          {
                              glWidget->moveUnit(i,j,i,j-moverange);
                          }

                      default: //DO NOTHING
                          glWidget->moveUnit(i,j,i,j);
                        break;

                         } break;
                    }
                }
            }
        }
    }
}
int mechanics::AIAttackCheck(int aiV, int aiH, int range, int power)
{
        for (int i = 0; i < glWidget->battleMap.cellsTall; i++)
        {
            for (int j = 0; j < glWidget->battleMap.cellsWide; j++)
            {
                if(mechanics::isOccupied(i,j))                                  // for all spaces, if one is occupied
                {
                    if(glWidget->battleMap.gridCell[i][j].unit->team==USER_UNIT)    //by the ENEMY
                    {
                        if(mechanics::isValidAttack(i,j,range, aiV, aiH, 2,1))      //if I can attak
                        {
                            if(power<glWidget->battleMap.gridCell[i][j].unit->hitPoints)
                                {
                                //targv=i; targh=j;
                               glWidget->hitUnit(i,j,power,aiV,aiH);
                                return 0;
                                }
                            else if (power>=glWidget->battleMap.gridCell[i][j].unit->hitPoints)
                                {
                              //  targv=i; targh=j;
                               glWidget->killUnit(i,j,aiV,aiH);
                               mechanics::checkGameEnd();

                                return 1;
                                }
                        }
                    }
                }
            }
        }
        return 2;
}

int mechanics::AImoveCheck(int aiV, int aiH, int range)
{
    static int val1=0, val2=0;
    int a, b;
    for (int i = 0; i < glWidget->battleMap.cellsTall; i++)
    {
        for (int j = 0; j < glWidget->battleMap.cellsWide; j++)
        {
            if(mechanics::isOccupied(i,j))                                  // for all spaces, if one is occupied
            {
                if(glWidget->battleMap.gridCell[i][j].unit->team==USER_UNIT)  //BY ENEMY
      //if I can't attack Enemy yet, I probably want to move toward him, but I care more if he's close
                {

                        if (aiV>i)                   //ai unitabove target
                        {
                             a=(abs(aiV-i)*-200);
                        }
                        else
                        {
                             a=(abs(aiH-i)*200); //ai unit below or on same v as target
                        }
                        if (aiH>j)                  // ai to RIGHT of target
                        {
                            b = (abs(aiH-j)*-200);
                        }
                        else                        //ai to LEFT or same H as Target
                        {
                             b = (abs(aiH-j)*200);
                        }
                        val1+=a;
                        val2+=b;
                    }

                if(glWidget->battleMap.gridCell[i][j].unit->team==USER_UNIT&&(glWidget->battleMap.gridCell[i][j].unit->hitPoints<=((glWidget->battleMap.gridCell[i][j].unit->totalHitPoints)/2)))
                {

                        if (aiV>i)                   //ai unitabove target
                        {
                             a=(abs(aiV-i)*-500);
                        }
                        else
                        {
                             a=(abs(aiH-i)*500); //ai unit below or on same v as target
                        }
                        if (aiH>j)                  // ai to RIGHT of target
                        {
                            b = (abs(aiH-j)*-500);
                        }
                        else                        //ai to LEFT or same H as Target
                        {
                             b = (abs(aiH-j)*500);
                        }
                        val1+=a;
                        val2+=b;
                    }
                  }

        if(glWidget->battleMap.gridCell[i][j].unit->team==AI_UNIT)
        {
            if (aiV>i)                   //ai unitabove target
            {
                 a=(abs(aiV-i)*100);
            }
            else
            {
                 a=(abs(aiH-i)*-100); //ai unit below or on same v as target
            }
            if (aiH>j)                  // ai to RIGHT of target
            {
                b = (abs(aiH-j)*100);
            }
            else                        //ai to LEFT or same H as Target
            {
                 b = (abs(aiH-j)*-100);
            }
            val1+=a;
            val2+=b;
        }
    }
    }
    if((abs(val1))>(abs(val2)))
    {
        if (val1>0)
        return 0;       //go UP
        if (val1<0)
        return 1;       //go DOWN
    }
    else if((abs(val1))<(abs(val2)))
    {
        if (val2>0)           //GO RIGHT
            return 2;
        if(val2<0)
            return 3;   //GO LEFT
    }
    return 4; //do NOTHING
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
            if ((glWidget->battleMap.gridCell[i][j].unit->status == UNIT_OK)&&(glWidget->battleMap.gridCell[i][j].unit->isPending))
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
if(!mechanics::isOccupied(vnext, hnext)|| ((vLoc==vnext)&&(hLoc==hnext)))
        {
           if((vLoc==vnext)||(hLoc==hnext))//no diagonal
           {
               if(vnext<=glWidget->battleMap.cellsTall-1&&vnext>=0)//6
               {
                   if(hnext<=glWidget->battleMap.cellsWide-1&&hnext>=0)//9
                   {
                     if(((abs(vLoc-vnext))<=glWidget->battleMap.gridCell[vLoc][hLoc].unit->movementRange)&&((abs(hLoc-hnext))<=glWidget->battleMap.gridCell[vLoc][hLoc].unit->movementRange))
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
    int vAttackerLoc = 0, hAttackerLoc = 0, damage = 0, range =0, atkteam=0;

    for (int i = 0; i < glWidget->battleMap.cellsTall; i++)
    {
        for (int j = 0; j < glWidget->battleMap.cellsWide; j++)
        {
            if ((glWidget->battleMap.gridCell[i][j].unit->status == UNIT_OK)&&(glWidget->battleMap.gridCell[i][j].unit->isPending))
            {
                // Get the upcoming attack power and location.
                damage = glWidget->battleMap.gridCell[i][j].unit->attackPower;
                vAttackerLoc = glWidget->battleMap.gridCell[i][j].unit->vLocation;
                hAttackerLoc = glWidget->battleMap.gridCell[i][j].unit->hLocation;
                range = glWidget->battleMap.gridCell[i][j].unit->attackRange;
                atkteam = glWidget->battleMap.gridCell[i][j].unit->team;
            }
        }
    }
    for (int i = 0; i < glWidget->battleMap.cellsTall; i++)
    {
        for (int j = 0; j < glWidget->battleMap.cellsWide; j++)
        {
            if (glWidget->battleMap.gridCell[i][j].isSelected)
            {
                if(mechanics::isValidAttack( i,j, range, vAttackerLoc, hAttackerLoc, atkteam, glWidget->battleMap.gridCell[i][j].unit->team))
                {
                  if (glWidget->battleMap.gridCell[i][j].unit->hitPoints<=glWidget->battleMap.gridCell[vAttackerLoc][hAttackerLoc].unit->attackPower)
                  {
                   glWidget->killUnit(i,j,vAttackerLoc, hAttackerLoc);

                   mechanics::checkGameEnd();
                  }
                 else glWidget->hitUnit(i,j,damage,vAttackerLoc,hAttackerLoc);
              }
            }
        }
    }
}
//Determines Whether an attack is valid
bool mechanics::isValidAttack(int targv, int targh, int atkrange, int atkrv, int  atkrh, int atkteam, int tarteam)
{
if(mechanics::isOccupied(targv, targh))
       {
        if(atkteam!=tarteam)
         {
                if(((abs(atkrv-targv))+(abs(atkrh-targh)))<=atkrange)//no diagonals
                {
                        if(((abs(atkrv-targv))<=atkrange)&&((abs(atkrh-targh))<=atkrange))
                        {
                        return (true);
                        }
                        return false;
                }
                return(false);
            }
            return(false);
        }
        return (false);
}

////////////////////////////////////////////////GAMEOVER//////////////////////////////////
bool mechanics::isGameOverP1()
{

    for(int x=0;x<glWidget->battleMap.cellsTall;x++)
    {
        for(int y=0;y<glWidget->battleMap.cellsWide;y++)
        {
            if((glWidget->battleMap.gridCell[x][y].unit->status==UNIT_OK)&&(glWidget->battleMap.gridCell[x][y].unit->team==USER_UNIT))
            {  //if there is a P1 unit alive
                return true;
            }
        }
    }
    return false;
}
bool mechanics::isGameOverP2()
{
    for(int x=0;x<glWidget->battleMap.cellsTall;x++)
    {
        for(int y=0;y<glWidget->battleMap.cellsWide;y++)
        {
            if((glWidget->battleMap.gridCell[x][y].unit->status==UNIT_OK)&&(glWidget->battleMap.gridCell[x][y].unit->team==AI_UNIT))
            {  //if there is a P1 unit alive
                return true;
            }
        }
    }
    return false;
}




///////////////////////////////////////////////////////////////////////////////////
int mechanics::endBattle(int x)
{
    return x;
}
void mechanics::checkGameEnd()
{
    bool bogey;
    bogey=mechanics::isGameOverP1();
    if (!bogey)
    {
        mechanics::sendBattleEnd();
    }
    else
    {
        bogey=mechanics::isGameOverP2();
        if (!bogey)
        {
            mechanics::sendBattleEnd();
        }
    }
}



