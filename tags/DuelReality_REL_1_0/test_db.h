#ifndef TEST_DB_H
#define TEST_DB_H


/*---------------- C l a s s    d e c l a r a t i o n s ----------------*/

class User;
class Map;
class Unit;
class QString;
class QImage;
class QPixmap;
class Sprite;
class AI;

/*---------------- C l a s s    d e f i n i t i o n s ----------------*/

class Database
{
public:
    Database();
    ~Database();

    void    generateMaps();         // Generates maps at program start
    void    generateSprites();      // Generates sprites at program start
    void    testGenerateUsers();    // Geneates existing users at program start

    void    addMap(Map map);                // Adds map to database
    int     mapCount();                     // Returns total number of map entries
    QString mapName(int index) const;       // Returns name of map (useful for listing in a database)
    QString mapFileName(int index) const;   // Returns image file name of map (useful for listing in a database)
    Map     loadMap(QString &mapName);      // Loads map
    
    void        addSprite(Sprite sprite);           // Creates user player data
    int         spriteCount();                      // Returns total number of sprite data entries
    QString     spriteName(int index) const;        // Returns sprite name in entry index
    QString     spriteFileName(int index) const;    // Returns file name of sprite
    const int   spriteAttackPower(int index) const; // Returns sprite's attack power
    const int   spriteHitPoints(int index) const;   // Returns spite's hit points
    const int   spriteAttackRange(int index) const; // Returns sprite's attack range
    const int   spriteRate(int index) const;        // Returns sprites attack rate
    Sprite      loadSprite(QString &spriteName);    // Returns sprite data for associated sprite name

    void    saveGameData(QString &userName);        // INCOMPLETE. Saves all game data

    void        addUser(User user);                 // Creates user player data
    void        addUser(QString &userName);         // Creates user player data
    void        activateUser(QString &userName);    // Sets isActive user member
    void        deactivateUser(QString &userName);  // Resets isActive user member
    User        loadActiveUser();                   // Loads data for user with isActive member set
    QList<Unit> loadActiveUserUnits();              // Loads units of active user
    
    void    saveUser(QString &userName, User user); // Overwrites user player data
    User    loadUser(const QString &userName);      // Loads user data
    QString userName(int index) const;              // Loads user name from database (useful for listing names in for loop)

    AI          loadAI();                           // Loads AI data
    void        saveAI(AI aiPlayer);                // Overwrites AI data
    QList<Unit> loadAIUnits();                      // Loads AI units
    void        saveAIUnits(QList<Unit> units);     // Saves AI units
    
    int     userCount();                                // Returns total number of user player data entries
    void    saveXP(QString &userName, int xp);          // Saves user XP
    int     loadXP(QString &userName) const;            // Loads user XP
    void    saveLevel(QString &userName, int level);    // Saves user level

    void        saveUnits(QString &userName, QList<Unit> units);    // Saves array of units in user player data
    QList<Unit> loadUnits(QString &userName);                       // Loads array of units from user player data

private:
    static QList<Map> mapList;
    static QList<Sprite>    spriteList;
    static QList<User>      userList;
    static QList<Unit>      unitList;
    static AI               ai;

    Map         dummyMap;
    Sprite      dummySprite;
    User        dummyUser;
    QList<Unit> dummyUnitsList;
};

#endif // TEST_DB_H
