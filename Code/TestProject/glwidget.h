#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>

static const int NO_UNIT = 0;
static const int UNIT_DEAD = 1;
static const int UNIT_OK = 2;
static const int MAX_UNITS = 10;
static const int TIMER_INTERVAL = 100;

class characterUnit
{
public:
    QImage  image;
    QImage  mask_image;
    int     xLocation;
    int     yLocation;
    int     hitPoints;
    int     totalHitPoints;
    float   actionTime;
    int     actionRate;
    int     movementRate;
    int     attackRange;
    int     attackPower;
    int     status;
    bool    selected;
    bool    leftTeam;
};

class GLWidget : public QGLWidget
{
public:
    GLWidget();

    float rotX, rotY, rotZ; //i want access these variable so public
    void resizeGL(int width, int height);
    bool drawUnit(characterUnit unit);
    short int col;
protected:
    void initializeGL();
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);

    characterUnit   unit[MAX_UNITS];
    GLfloat statusWidth, fullWidth, fullHeight, cellWidth, cellHeight;
    QImage bkImage, glBkImage;
    int cellCount;
private:


};

#endif // GLWIDGET_H
