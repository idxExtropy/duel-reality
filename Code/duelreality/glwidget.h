#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include <string>
#include "duelreality.h"
#include "mechanics.h"
#include "mainwindow.h"
#include "test_db.h"

using namespace std;

// Constants.
static const int        DEFAULT_TRANSITION_SECONDS = 2;
static const int        TITLE_TRANSITION_SECONDS = 3;
static const int        MOVE_TRANSITION_SECONDS = 1;
static const int        ATTACK_TRANSITION_SECONDS = 1;
static const int        EFFECT_NONE = 0;
static const int        EFFECT_MOVE = 1;
static const int        EFFECT_ATTACK = 2;

class point
{
public:
    float hLoc;
    float vLoc;
};

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget();
    void LoadContent(Database db);
    void unitTest_GenerateContent();
    void unitTest_AddUnits();
    void moveUnit(int vLocPrev, int hLocPrev, int vLocNext, int hLocNext);
    void hitUnit(int vLoc, int hLoc, int damage, int vAttackerLoc, int hAttackerLoc);
    void killUnit(int vLoc, int hLoc, int vAttackerLoc, int hAttackerLoc);

    // Battle state;
    bool    isBattle;
    Map     battleMap;
    Unit    unit[MAX_MAP_UNITS];
    QString backgroundList[7];
    bool    isPending;

    // Music.
    Phonon::MediaObject *music;
    QString musicTrack;

public slots:
    void playBackgroundTrack();

private slots:
    void backgroundTrackFinished();

protected:
    // Functions.
    void initializeGL();
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);
    void resizeGL(int width, int height);
    void updateUnit(Unit unit);
    void drawGridBox(int cellFromBottom, int cellFromLeft);
    bool isGridBoxSelected(int cellFromBottom, int cellFromLeft);
    void initGrid();
    void drawHeaderInfo();
    void drawGrid();
    void drawUnits();
    void drawBackground();

    // Title screen.
    void updateTitleScreen();
    int titleIndex;

    // Content information.
    GLfloat statusWidth, fullWidth, fullHeight, cellWidth, cellHeight;
    QImage  bkImage, glBkImage;
    point   mouseClick;
    
    // Effect information.
    bool isEffect;
    int  effectType;
    int  move_vLocPrev, move_hLocPrev, move_vLocNext, move_hLocNext;
    int  attack_vLoc, attack_hLoc;
    void drawEffects();
    int  iEventCounter;
    void drawAttack();
    QString moveMask;

private:
};

#endif // GLWIDGET_H
