#include "StdAfx.h"
#include "unit.h"

unit::unit(int type)
{
    if (type==1) //soldier
        {
        name = "soldier";
        unitType=1;
        team=1;
        vLocation = 0;
        hLocation =0;
        hitPoints = 20;
        totalHitPoints=20;
        actionPoints=10;
        totalActionPoints=10;
        movementRate = 3;
        attackRange = 1;
        attackPower=3;
        unitWorth= 100;
        status=0;

  //     image.load("sprites/desertsoldier.png");
     //   mask_image.load("sprites/mask_desertsoldier.png");
        }
      else  if (type==2) //wizard
          {
          name = "wizard";
          unitType=1;
          team=1;
          vLocation = 0;
          hLocation =0;
          hitPoints = 20;
          totalHitPoints=20;
          actionPoints=10;
          totalActionPoints=10;
          movementRate = 3;
          attackRange = 1;
          attackPower=3;
          unitWorth= 100;
          status=0;
       //     image.load("sprites/wizard.png");
       //     mask_image.load("sprites/mask_wizard.png");
        }
   else  if (type==3) //monk
      {
       name = "monk";
       unitType=1;
       team=1;
       vLocation = 0;
       hLocation =0;
       hitPoints = 20;
       totalHitPoints=20;
       actionPoints=10;
       totalActionPoints=10;
       movementRate = 3;
       attackRange = 1;
       attackPower=3;
       unitWorth= 100;
       status=0;
               //   image.load("sprites/buddhist.png");
               //   mask_image.load("sprites/mask_buddhist.png");
              }
}


