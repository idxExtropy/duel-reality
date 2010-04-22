//////JOSH KILGORE
//////APRIL 17 2010
/////// PLAYER CLASS - CREATES ARRAY OF UNITS PLAYED IN BOARD, STORES UPGRADED UNITS
/////////KEEPS TRACK OF CAMPAIGN LEVEL, XP EARNED AND XP AVAILABLE TO SPEND



#ifndef PLAYER_H
#define PLAYER_H
#include "unit.h"
//#include"savedUnit.h"

class Player
{
public:
    Player();
    int playerID;               //player id - for identifying individual player
    static Unit team[4];         // 1 of 4 units on board
    static savedUnit saved_units[100];       //saved unit upgrades
    int campaignLevel;          //game level 1-7
    int experienceGained;       //total experience gained by player
    int experienceAvailable;    //xp to spend
    void makeTeam();

};

#endif // PLAYER_H
