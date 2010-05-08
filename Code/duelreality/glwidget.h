#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include <string>
#include "globals.h"
#include "mechanics.h"
#include "mainwindow.h"

using namespace std;

// Constants.
static const int titleTransitionSeconds = 3;

class point
{
public:
    float hLoc;
    float vLoc;
};

class GLWidget : public QGLWidget
{
public:
    GLWidget();
    void    unitTest_GenerateContent();
    bool    isBattle;
    Map     battleMap;
    Unit    unit[MAX_MAP_UNITS];
    QString backgroundList[7];
    Phonon::MediaObject *music;

protected:
    // Functions.
    void initializeGL();
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);
    void resizeGL(int width, int height);
    bool updateUnit(Unit unit);
    bool drawGridBox(int cellFromBottom, int cellFromLeft);
    bool isGridBoxSelected(int cellFromBottom, int cellFromLeft);
    void initGrid();
    void setBackgroundTrack(QString trackFileName);
    int iEventCounter;

    // Title screen.
    void updateTitleScreen();
    int titleIndex;

    // Content information.
    GLfloat statusWidth, fullWidth, fullHeight, cellWidth, cellHeight;
    QImage  bkImage, glBkImage;
    point   mouseClick;
    
    // Effect information.
    bool isPending;
    int selectedBorder;

private:
};

#endif // GLWIDGET_H
