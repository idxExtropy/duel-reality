#ifndef TEST_DB_H
#define TEST_DB_H


/*---------------- C l a s s    d e c l a r a t i o n s ----------------*/

class User


/*---------------- C l a s s    d e f i n i t i o n s ----------------*/

class Sprite
{
public:
    //QString name;
    string  name;
    string  spriteFileName;
    //QPixmap pixMap;
    int     AP;
    int     HP;
    int     range;
};


/*---------------- F u n c t i o n    P r o t o t y p e s ----------------*/

int GetSpriteCount(void);           // Returns total number of sprite data entries
string GetSpriteName(int index);    // Returns sprite name in entry index
Sprite GetSpriteData(string name);  // Returns sprite data for associated sprite name

User CreateUserData(string name);   // Creates user player data
int GetUserCount(void);             // Returns total number of user player data entries
string GetUserName(int index);      // Returns user player name in entry index
User GetUserData(string name);      // Returns user player data for associate user player name


#endif // TEST_DB_H
