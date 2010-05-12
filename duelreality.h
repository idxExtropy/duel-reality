#ifndef GLOBALS_H
#define GLOBALS_H

/*---------------- I n c l u d e s ----------------*/
#include <QList>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <Phonon/MediaObject>

#include <iostream>
using std::cout;

#include <string>
using std::string;


/*---------------- C o n s t a n t    d e f i n i t i o n s ----------------*/

static const int        MAX_LEVELS = 7;
static const int        MAX_TEAM_UNITS = 4;      // Maximum number of units per player
static const int        MAX_MAPS = 7;      // Maximum number maps
static const int        MAX_SPRITES = 12;      // Maximum number maps
static const int        NO_UNIT = 0;        // Unit status (unit doesn't exist)
static const int        UNIT_DEAD = 1;      // Unit status (unit is dead)
static const int        UNIT_OK = 2;        // Unit status (unit is alive)
static const int        USER_UNIT = 1;      // Indicates unit is associated with user
static const int        AI_UNIT = 2;        // Indicates unit is associated with AI
static const int        MAX_MAP_UNITS = 10;
static const int        GL_TIMER_INTERVAL = 100;
static const int        MAX_GRID_DIMENSION = 20;
static const int        CAMPAIGN_MODE = 1;
static const int        FREEPLAY_MODE = 2;
static const QString    TITLE_AUDIO_TRACK = "sounds/MainTheme.mp3";

/*---------------- C l a s s    d e c l a r a t i o n s ----------------*/


/*---------------- C l a s s    d e f i n i t i o n s ----------------*/

class Sprite
{
public:
    QString name;
    QString imageFileName;
    QString maskFileName;
    QImage  image;
    QImage  mask_image;
    //QPixmap pixMap;
    int     attackPower;
    int     hitPoints;
    int     attackRange;
    int     actionRate;
    int     actionTime;
    int     movementRange;
    int     rate;
};


class Unit
{
public:
    QString name;               // Unit name
    bool    faceLeft;           // Unit orientation
    int     vLocation;          // Unit vertical location
    int     hLocation;          // Unit horizontal location
    int     hitPoints;          // Unit hit points
    int     totalHitPoints;     // Total unit hit points
    float   actionTime;
    int     actionRate;
    int     movementRange;
    int     attackRange;
    int     attackPower;
    int     status;             // Unit status
    QString imageFileName;
    QString maskFileName;
    //QPixmap pixMap;
    QImage  image;              // Associated unit image
    QImage  mask_image;         // Associate unit mask image
    int     team;               // Unit's associated team
    //int     actionPoints;
    int     unitWorth;          // Amount of XP awarded for killing unit
    int     isPending;
};

class gridBox
{
public:
    Unit *unit;
    bool isUnit;
    bool isSelected;
    float cellWidth;
    float cellHeight;
    float leftEdge;
    float bottomEdge;
};

class Map
{
public:
    QString name;
    QString imageFileName;
    QString audioFileName;
    int     cellsWide;
    int     cellsTall;
    float   gridHeight; // Ratio of grid to header.

    gridBox  gridCell[MAX_GRID_DIMENSION][MAX_GRID_DIMENSION];
};

class Player
{
public:
    Unit   units[MAX_TEAM_UNITS];   // Player units
};


class User : public Player
{
public:
    QString name;               // Player name
    int     experiencePoints;   // Player experience points
    bool    isActive;           // True if player is selected for battle
    //int     gameMode;
    //Map     map;
    int     level;
};


class AI : public Player
{
public:
    QString name;               // Player name
};


#endif // GLOBALS_H
