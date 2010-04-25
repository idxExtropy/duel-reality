#ifndef NEWGAMEWIZARD_H
#define NEWGAMEWIZARD_H

#include <QWizard>

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
            //Page_RecruitUnits,
            //Page_SelectMap,
            Page_Conclusion };

    NewGameWizard(QWidget *parent = 0);

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

private:
    QLabel      *playerNameLabel;
    QComboBox   *playerNameComboBox;
};

/*
class RecruitUnitsPage : public QWizardPage
{
    Q_OBJECT

public:
    RecruitUnitsPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel      *spriteLabel;
    QPushButton *nextSpritePushButton;
    QPushButton *prevSpritePushButton;
    QLabel      *spriteName;
    QLabel      *spriteAP;
    QLabel      *spriteHP;
    QLabel      *spriteRange;
    QLabel      *spriteNameValue;
    QLabel      *spriteAPValue;
    QLabel      *spriteHPValue;
    QLabel      *spriteRangeValue;
    QPushButton *recruitPushButton;
    QLabel      *unitLabel;
};

class SelectMapPage : public QWizardPage
{
    Q_OBJECT

public:
    SelectMapPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel  *mapLabel;
};
*/

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
    //QCheckBox *agreeCheckBox;
};

#endif // NEWGAMEWIZARD_H
