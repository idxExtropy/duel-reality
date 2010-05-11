#ifndef DATABASE_H
#define DATABASE_H


#include <QDialog>

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <qDebug>

#include "globals.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QPushButton;
class QSqlTableModel;
QT_END_NAMESPACE

//! [0]
class TableEditor : public QDialog     // Used for displaying/testing my database table
{
    Q_OBJECT

public:
    TableEditor(const QString &tableName, QWidget *parent = 0);

private slots:
    void submit();

private:
    QPushButton *submitButton;
    QPushButton *revertButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QSqlTableModel *model;
};
//! [0]


class Database     //My database class
{

public:
    Database();
    bool connection ();    //QT connection to the database file
    int show(QString &tableName);   //display the database table
    int userCount();  // Returns total number of user player data entries
    bool addUser(User user);
    bool addUser (QString userName);   //add new player, if it is existed return false; if not, return true
    void activateUser(QString &userName);
    void deactivateUser(QString &userName);
    User loadActiveUser();
    QString spriteName(int index) const;   // Returns sprite name in entry index

    QString spriteFileName(int index) const;
    const int spriteAttackPower(int index) const;
    const int spriteHitPoints(int index) const;
    const int spriteAttackRange(int index) const;
    const int spriteMovementRange(int index) const;
    const int spriteRate(int index) const;
    const int spriteActionRate(int index) const;
    const float spriteActionTime(int index) const;
    Sprite loadSprite(QString spriteName);
    QString userName(int index) const;  // Returns user player name in entry index

    void saveUser(QString &userName, User user);

    void saveXP(QString &userName, int xp);
    int loadXP(QString &userName) const;
    void saveLevel(QString &userName, int level);

    void saveUnits(QString userName, QList<Unit> units);
    QList<Unit> loadUnits(QString userName);               // Loads array of units from user player data
    User loadUser(const QString &userName);                 // Returns user player data for associate user player name

private:
    QString tableName;
};



#endif // DATABASE_H
