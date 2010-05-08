#ifndef TEST_DB_H
#define TEST_DB_H


/*---------------- C l a s s    d e c l a r a t i o n s ----------------*/

class User;
class Map;
class Unit;
class QString;
class QPixmap;
//class QList;


/*---------------- C l a s s    d e f i n i t i o n s ----------------*/

class Sprite
{
public:
    QString name;
    QString fileName;
    //QPixmap pixMap;
    int     AP;
    int     HP;
    int     range;
};


class Database
{
public:
    Database();
    ~Database();

    void    generateMaps();
    void    generateSprites();
    void    testGenerateUsers();

    void    addMap(Map map);
    int     mapCount();
    QString mapName(int index) const;
    QString mapFileName(int index) const;
    
    void        addSprite(Sprite sprite);           // Creates user player data
    int         spriteCount();                      // Returns total number of sprite data entries
    QString     spriteName(int index) const;        // Returns sprite name in entry index
    QString     spriteFileName(int index) const;
    const int   spriteAP(int index) const;
    const int   spriteHP(int index) const;
    const int   spriteRange(int index) const;
    Sprite      loadSprite(QString &spriteName);    // Returns sprite data for associated sprite name


    void addUser(User user);                                // Creates user player data
    void addUser(QString &userName);
    void saveUser(QString &userName, User user);
    int userCount();                                        // Returns total number of user player data entries
    QString userName(int index) const;                      // Returns user player name in entry index
    User loadUser(const QString &userName);                 // Returns user player data for associate user player name
    void saveUnits(QString &userName, QList<Unit> units);   // Saves array of units in user player data
    QList<Unit> loadUnits(QString &userName);               // Loads array of units from user player data
    void    saveMap(QString &userName, Map map);
    Map   loadMap(QString &mapName);

private:
    static QList<Map> mapList;
    static QList<Sprite>    spriteList;
    static QList<User>      userList;
    static QList<Unit>      unitList;

    Map         dummyMap;
    Sprite      dummySprite;
    User        dummyUser;
    QList<Unit> dummyUnitsList;
};

#endif // TEST_DB_H
