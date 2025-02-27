#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include <string>

using namespace std;

static const int NO_UNIT = 0;
static const int UNIT_DEAD = 1;
static const int UNIT_OK = 2;
static const int MAX_UNITS = 10;
static const int TIMER_INTERVAL = 100;
static const int MAX_GRID_DIMENSION = 100;

class battleMap
{
public:
    string  mapFilename;
    int     cellsWide;
    int     cellsTall;
    float   gridHeight; // Ratio of grid to header.
};

class characterUnit
{
public:
    string  name;
    bool    faceLeft;
    int     vLocation;
    int     hLocation;
    int     hitPoints;
    int     totalHitPoints;
    float   actionTime;
    int     actionRate;
    int     movementRate;
    int     attackRange;
    int     attackPower;
    int     status;
    QImage  image;
    QImage  mask_image;
};

class gridBox
{
public:
    bool isUnit;
    characterUnit unit;

    bool isSelected;
    float cellWidth;
    float cellHeight;
    float leftEdge;
    float bottomEdge;
};

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
    void unitTest_GenerateContent();

protected:
    void initializeGL();
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);
    void resizeGL(int width, int height);
    bool updateUnit(characterUnit unit);
    bool drawGridBox(int cellFromBottom, int cellFromLeft);
    bool isGridBoxSelected(int cellFromBottom, int cellFromLeft);
    void initGrid();

    // Content data.
    characterUnit   unit[MAX_UNITS];
    battleMap       map;
    GLfloat statusWidth, fullWidth, fullHeight, cellWidth, cellHeight;
    QImage bkImage, glBkImage;
    point mouseClick;
    gridBox mapGrid[MAX_GRID_DIMENSION][MAX_GRID_DIMENSION];

    // Effect values.
    int selectedBorder;

private:
};

#endif // GLWIDGET_H
