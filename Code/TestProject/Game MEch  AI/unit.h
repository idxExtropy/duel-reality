///////////////////////////////////////////////////////////////////////////////
// UNIT_H
////JOSH KILGORE
////  APRIL 17 2010
//// UNIT CLASS
//// CREATES UNIT CLASS WITH ATTRIBUTES COMMON TO ALL UNITS
///////////////////////////////////////////////////////////////



#ifndef UNIT_H
#define UNIT_H
#include <string>
//#include <QGLWidget>

using namespace std;
class Unit
{
  //  Q_OBJECT
public:
    string  name;
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
    Unit(int type);

protected:
    static Unit myunit;
};


#endif // UNIT_H
