#ifndef GLOBALS_H
#define GLOBALS_H


#include <string>
using std::string;

static const int    MAX_SPRITES = 4;
static const int    MAX_UNITS = 4;


class QImage;


class characterUnit
{
public:
    bool    isAlive;
    string  name;
    bool    faceLeft;
    int     vLocation;
    int     hLocation;
    int     hitPoints;
    int     totalHitPoints;
    float   actionTime;
    int     actionRate;
    int     movementRate;
    int     attackRange;
    int     attackPower;
    int     status;
    QImage  image;
    QImage  mask_image;
};


class Player
{
public:
    characterUnit   units[MAX_UNITS];
};


class User : public Player
{
public:
    string  playerName;
    int     experiencePoints;
};


#endif // GLOBALS_H
