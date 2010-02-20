#include "glwidget.h"

GLWidget::GLWidget()
{
    startTimer( 11 ); //64-65fps
    rotX = rotY = rotZ = 0.f;
    col = 0;
}

void GLWidget::initializeGL()
{
    // Load the sprites.
    unitTeamA[0].load("../sprites/desertsoldier_right.bmp");
    unitTeamB[0].load("../sprites/desertsoldier_left.bmp");

    // Resize the sprites (hard coded).
    unitTeamA[0] = unitTeamA[0].scaled(GLWidget::width()/10 * 0.7, GLWidget::height()/10, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    glUnitTeamA[0] = QGLWidget::convertToGLFormat(unitTeamA[0]);

    glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
    glClearColor(0.0f, 0.2f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);							// Depth Buffer Setup
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);				// Set Line Antialiasing
    glEnable(GL_BLEND);                                                 // Enable Blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Type Of Blending To Use
    glEnable(GL_TEXTURE_2D);
    return;								// Initialization Went OK
}

void GLWidget::paintGL()
{
    int cellCount = 10;

    GLfloat fullWidth = GLWidget::width();
    GLfloat fullHeight = GLWidget::height();

    GLfloat statusWidth = (fullWidth / cellCount) * 0.15f;

    //draw scene here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw unit 1 for team A.
    glDrawPixels(unitTeamA[0].width(), unitTeamA[0].height(), GL_RGBA, GL_UNSIGNED_BYTE, glUnitTeamA[0].bits());

    // Show unit 1's health.
    glColor3f(0.8f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f( unitTeamA[0].width(),                unitTeamA[0].height(), 0.0f );	// Left And Up 1 Unit (Top Left)
        glVertex3f( unitTeamA[0].width() + statusWidth,  unitTeamA[0].height(), 0.0f );	// Right And Up 1 Unit (Top Right)
        glVertex3f( unitTeamA[0].width() + statusWidth,  0.0f, 0.0f );	// Right And Down One Unit (Bottom Right)
        glVertex3f( unitTeamA[0].width(),                0.0f, 0.0f );	// Left And Down One Unit (Bottom Left)
    glEnd();

    // Show unit 1's action points.
    glColor3f(0.0f, 0.0f, 0.8f);
    glBegin(GL_QUADS);
        glVertex3f( unitTeamA[0].width() + statusWidth,      unitTeamA[0].height(), 0.0f );	// Left And Up 1 Unit (Top Left)
        glVertex3f( unitTeamA[0].width() + (2*statusWidth),  unitTeamA[0].height(), 0.0f );	// Right And Up 1 Unit (Top Right)
        glVertex3f( unitTeamA[0].width() + (2*statusWidth),  0.0f, 0.0f );	// Right And Down One Unit (Bottom Right)
        glVertex3f( unitTeamA[0].width() + statusWidth,      0.0f, 0.0f );	// Left And Down One Unit (Bottom Left)
    glEnd();

    // Make the grid lines white.
    qglColor(Qt::white);

    // Draw the grid lines.
    glBegin(GL_LINES);
    for (int i = 1; i <= cellCount + 2; i++)
    {
        // Vertical lines.
        glVertex3f(fullWidth/cellCount * i, 0.0f, 0.0f); // Origin of the line.
        glVertex3f(fullWidth/cellCount * i , fullHeight, 0.0f); // Ending point of the line.
    }
    for (int i = 1; i <= 12; i++)
    {
        // Horizontal lines.
        glVertex3f(0.0f, fullHeight/cellCount * i, 0.0f); // Origin of the line.
        glVertex3f(fullWidth, fullHeight/cellCount * i, 0.0f); // Ending point of the line.
    }
    glEnd( );

    // Write some text.
    qglColor(Qt::cyan);
    renderText(330, 310, 0.0, "Tom text!");
}

void GLWidget::resizeGL(int width, int height)
{
    // Never divide by zero.
    if (height==0)
    {
        height=1;
    }

    // Setup the new viewport.
    glViewport (0, 0, width, height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width,0,height,-1,1);
    glMatrixMode (GL_MODELVIEW);    						// Reset The Modelview Matrix
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
  //proces mouse events for rotate/move inside 3D scene
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // Process mouse stuff...
}

void GLWidget::timerEvent(QTimerEvent *event)
{
    updateGL();
}
