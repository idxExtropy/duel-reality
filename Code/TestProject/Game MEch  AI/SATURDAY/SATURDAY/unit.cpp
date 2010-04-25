//#include "stdafx.h"
#include "unit.h"

unit::unit()
{
	     name = "zero";
        unitType=0;
        team=0;
        vLocation = 0;
        hLocation =0;
        hitPoints = 0;
        totalHitPoints=0;
        actionPoints=0;
        totalActionPoints=0;
        movementRate = 0;
        attackRange = 0;
        attackPower=0;
        unitWorth=0;
        status=0;
}
unit::unit(int type)
{
	switch (type)
	{
    case 1: //soldier
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
        status=1;

  //     image.load("sprites/desertsoldier.png");
     //   mask_image.load("sprites/mask_desertsoldier.png");
		break;
        }
	case 2: //wizard
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
          status=1;

       //     image.load("sprites/wizard.png");
       //     mask_image.load("sprites/mask_wizard.png");
       break;
		  }
	case 3: //monk
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
       status=1;
               //   image.load("sprites/buddhist.png");
               //   mask_image.load("sprites/mask_buddhist.png");
         break;  
	  }
	default:
		{cout<<"ERROR";
		break;}

}//switch
}

