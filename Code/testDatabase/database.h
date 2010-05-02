#ifndef DATABASE_H
#define DATABASE_H


#include <QDialog>

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

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
    bool addPlayer (QString playerName);   //add new player, if it is existed return false; if not, return true
    QString spriteName(int index) const;   // Returns sprite name in entry index
    const QPixmap spritePixMap(int index) const;  //return QPixmap handle
    const int spriteAP(int index) const;
    const int spriteHP(int index) const;
    const int spriteRange(int index) const;
    Sprite loadSprite(QString spriteName);
    QString userName(int index) const;  // Returns user player name in entry index

private:
    QString tableName;
};



#endif // DATABASE_H
