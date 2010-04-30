#ifndef TEST_DB_H
#define TEST_DB_H


/*---------------- C l a s s    d e c l a r a t i o n s ----------------*/

class User;


/*---------------- C l a s s    d e f i n i t i o n s ----------------*/

class Sprite
{
public:
    QString name;
    //string  name;
    //string  spriteFileName;
    QPixmap pixMap;
    int     AP;
    int     HP;
    int     range;
};


class Database
{
public:
    Database();
    ~Database();

    void generateSprites();
    void testGenerateUsers();

    void addSprite(Sprite *sprite);        // Creates user player data
    int spriteCount();                              // Returns total number of sprite data entries
    QString spriteName(int index) const;                  // Returns sprite name in entry index
    Sprite loadSprite(QString &spriteName);         // Returns sprite data for associated sprite name

    //User addUser(QString &userName);                // Creates user player data
    void addUser(QString &userName);                // Creates user player data
    int userCount();                                // Returns total number of user player data entries
    QString userName(int index) const;                    // Returns user player name in entry index
    User loadUser(QString &userName);               // Returns user player data for associate user player name
    void saveUnits(QString &userName, Unit *units); // Saves array of units in user player data
    Unit *loadUnits(QString &userName);            // Loads array of units from user player data

protected:
    QList<Sprite *> spriteList;
    QList<User *>   userList;
    QList<Unit *>   unitList;

    Sprite  *dummySprite;
    User    *dummyUser;
    Unit    *dummyUnits;
};


#endif // TEST_DB_H
