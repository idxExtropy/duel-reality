#ifndef LOADGAMEWIZARD_H
#define LOADGAMEWIZARD_H

#include <QWizard>

#include "globals.h"
#include "test_db.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QComboBox;
class QRadioButton;
class QPushButton;

class LoadGameWizard : public QWizard
{
    Q_OBJECT

public:
    enum {  Page_Intro,
            Page_LoadPlayer,
            Page_RecruitUnits,
            Page_UpgradeUnits,
            Page_SelectMode,
            Page_SelectMap,
            Page_Conclusion };

    LoadGameWizard(QWidget *parent = 0);

    static void setPlayerName(const QString &userName);
    static QString  playerName;

private slots:
    void    showHelp();
    void    finishButtonClicked();
    //void    nextButtonClicked();

private:
    Database    db;
    int         prevIdBeforeNext;
};


class IntroPageL : public QWizardPage
{
    Q_OBJECT

public:
    IntroPageL(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel          *topLabel;
    //QRadioButton    *newPlayerRadioButton;
    //QRadioButton    *returningPlayerRadioButton;
};


class LoadPlayerPageL : public QWizardPage
{
    Q_OBJECT

public:
    LoadPlayerPageL(QWidget *parent = 0);

    int nextId() const;

private slots:
    void playerNameChanged(int);

private:
    QLabel      *playerNameLabel;
    QComboBox   *playerNameComboBox;
    Database    db;
    QStringList userNames;
};


class RecruitUnitsPageL : public QWizardPage
{
    Q_OBJECT

public:
    RecruitUnitsPageL(QWidget *parent = 0);

    int nextId() const;
    void initializePage();
    //void test_GenerateSprites();

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
    //int                     i;
    int                     spriteIndex;
    QString                 spriteFileName;
    QLabel                  *spriteImage;
    QPushButton             *nextSpriteButton;
    QPushButton             *prevSpriteButton;
    QLabel                  *spriteName;
    QLabel                  *spriteAP;
    QLabel                  *spriteHP;
    QLabel                  *spriteRange;
    QLabel                  *spriteRate;
    QLabel                  *spriteNameVal;
    QLabel                  *spriteAPVal;
    QLabel                  *spriteHPVal;
    QLabel                  *spriteRangeVal;
    QLabel                  *spriteRateVal;
    QPushButton             *recruitButton;
    QList<QLabel *>         unitImageList;
    QList<QLabel *>         unitNameList;
    QList<QPushButton *>    rejectButtonList;
    bool                    isAlive[MAX_TEAM_UNITS];
    Database                db;
};

class UpgradeUnitsPageL : public QWizardPage
{
    Q_OBJECT

public:
    UpgradeUnitsPageL(QWidget *parent = 0);

    int nextId() const;
    //void initializePage();

private slots:
    //void acceptButtonClicked();
    //void upgradeButton0Clicked();
    //void upgradeButton1Clicked();
    //void upgradeButton2Clicked();
    //void upgradeButton3Clicked();
    //void upgradeButtonAnyClicked(int index);

private:
    //int                     i;
    //int                     spriteIndex;
    //QString                 spriteFileName;
    QLabel                  *selectedUnitImage;
    //QPushButton             *nextSpriteButton;
    //QPushButton             *prevSpriteButton;
    QLabel                  *selectedUnitName;
    QLabel                  *selectedUnitAP;
    QLabel                  *selectedUnitHP;
    QLabel                  *selectedUnitRange;
    QLabel                  *selectedUnitRate;
    QLabel                  *selectedUnitNameVal;
    QLabel                  *selectedUnitAPVal;
    QLabel                  *selectedUnitHPVal;
    QLabel                  *selectedUnitRangeVal;
    QLabel                  *selectedUnitRateVal;
    QPushButton             *upgradeAPButton;
    QPushButton             *upgradeHPButton;
    QPushButton             *upgradeRangeButton;
    QPushButton             *upgradeRateButton;
    QPushButton             *acceptButton;
    //QList<QLabel *>         unitImageList;
    //QList<QLabel *>         unitNameList;
    QList<QPushButton *>    selectButtonList;
    //bool                    isAlive[MAX_TEAM_UNITS];
    Database                db;
};


class SelectModePageL : public QWizardPage
{
    Q_OBJECT

public:
    SelectModePageL(QWidget *parent = 0);

    int nextId() const;

private slots:
    //void campaignModeSelected(bool);
    //void freeplayModeSelected(bool);

private:
    //QLabel          *topLabel;
    QRadioButton    *campaignModeRadioButton;
    QRadioButton    *freePlayModeRadioButton;
    Database        db;
};


class SelectMapPageL : public QWizardPage
{
    Q_OBJECT

public:
    SelectMapPageL(QWidget *parent = 0);

    int nextId() const;

private slots:
    void nextMapButtonClicked();
    void prevMapButtonClicked();
    void selectButtonClicked();
    
private:
    int         mapIndex;
    QString     mapFileName;
    QLabel      *mapImage;
    QPushButton *nextMapButton;
    QPushButton *prevMapButton;
    QLabel      *mapName;
    QLabel      *mapNameVal;
    QPushButton *selectButton;
    Database    db;
};



class ConclusionPageL : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPageL(QWidget *parent = 0);

    //void initializePage();
    int nextId() const;
    //void setVisible(bool visible);

private slots:
    //void printButtonClicked();

private:
    QLabel *bottomLabel;
};

#endif // LOADGAMEWIZARD_H
