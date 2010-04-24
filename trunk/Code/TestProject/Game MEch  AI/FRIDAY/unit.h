#pragma once

#include <string>


using namespace std;

class unit
{
  //  Q_OBJECT
public:
	string name;
   // bool    faceLeft;
    int     unitType;
    int     team;   //which team unit is on
    int     vLocation;  //y
    int     hLocation;  //x
    int     hitPoints;
    int     totalHitPoints;
    int     actionPoints;
    int     totalActionPoints;
    int     movementRate;   //cost for movement
    int     attackRange;
    int     attackPower;
    int     unitWorth;
    int     status;         //alive?
  //  QImage  image;
   // QImage  mask_image;
    unit(int type);

protected:
  //  static unit myteam[4];
};

