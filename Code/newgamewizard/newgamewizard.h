#ifndef NEWGAMEWIZARD_H
#define NEWGAMEWIZARD_H

#include <QWizard>

#include "globals.h"
#include "test_db.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QComboBox;
class QRadioButton;
class QPushButton;

class NewGameWizard : public QWizard
{
    Q_OBJECT

public:
    enum {  Page_Intro,
            Page_CreatePlayer,
            Page_LoadPlayer,
            Page_RecruitUnits,
            //Page_SelectMap,
            Page_Conclusion };

    NewGameWizard(QWidget *parent = 0);

    static void setPlayerName(const QString &userName);

private:
    static QString playerName;

private slots:
    void    showHelp();
};

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel          *topLabel;
    QRadioButton    *newPlayerRadioButton;
    QRadioButton    *returningPlayerRadioButton;
};

class CreatePlayerPage : public QWizardPage
{
    Q_OBJECT

public:
    CreatePlayerPage(QWidget *parent = 0);

    int nextId() const;

private slots:
    void playerNameCreated(const QString &);

private:
    QLabel      *playerNameLabel;
    QLineEdit   *playerNameLineEdit;
};

class LoadPlayerPage : public QWizardPage
{
    Q_OBJECT

public:
    LoadPlayerPage(QWidget *parent = 0);

    int nextId() const;

private slots:
    void playerNameChanged(int);

private:
    QLabel      *playerNameLabel;
    QComboBox   *playerNameComboBox;
    Database    db;
    QStringList userNames;
};


class RecruitUnitsPage : public QWizardPage
{
    Q_OBJECT

public:
    RecruitUnitsPage(QWidget *parent = 0);

    int nextId() const;
    void test_GenerateSprites();

protected:
    //Sprite  sprites[MAX_SPRITES];

private slots:
    void nextSpriteButtonClicked();
    void prevSpriteButtonClicked();
    void recruitButtonClicked();
    void rejectButton0Clicked();
    void rejectButton1Clicked();
    void rejectButton2Clicked();
    void rejectButton3Clicked();
    void rejectButtonAnyClicked(int index);

private:
    int                     i;
    int                     spriteIndex;
    QLabel                  *spriteImage;
    QPushButton             *nextSpriteButton;
    QPushButton             *prevSpriteButton;
    QLabel                  *spriteName;
    QLabel                  *spriteAP;
    QLabel                  *spriteHP;
    QLabel                  *spriteRange;
    QLabel                  *spriteNameVal;
    QLabel                  *spriteAPVal;
    QLabel                  *spriteHPVal;
    QLabel                  *spriteRangeVal;
    QPushButton             *recruitButton;
    QList<QLabel *>         unitImageList;
    QList<QLabel *>         unitNameList;
    QList<QPushButton *>    rejectButtonList;
    bool                    isAlive[MAX_UNITS];
    Database                db;
};
/*
class SelectMapPage : public QWizardPage
{
    Q_OBJECT

public:
    SelectMapPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel  *mapLabel;
};*/

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

    //void initializePage();
    int nextId() const;
    //void setVisible(bool visible);

private slots:
    //void printButtonClicked();

private:
    QLabel *bottomLabel;
};

#endif // NEWGAMEWIZARD_H
