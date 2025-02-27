#include "glwidget.h"

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	GLWidget()
//	Description:	Class constructor.
//	Modified:	03/02/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
GLWidget::GLWidget()
{
    selectedBorder = 1;
    startTimer( TIMER_INTERVAL );
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	unitTest_GenerateContent()
//	Description:	Add content for unit testing.
//	Modified:	03/02/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
void GLWidget::unitTest_GenerateContent()
{
    // Select a battle map.
    map.mapFilename = "backgrounds/grassnight.png";
    map.cellsTall = 7;
    map.cellsWide = 9;
    map.gridHeight = 0.55;

    // Create a new unit (for gl debug purposes).
    unit[0].name = "Wizard";
    unit[0].actionTime = 10;
    unit[0].actionRate = 150;
    unit[0].hitPoints = 80;
    unit[0].totalHitPoints = 100;
    unit[0].image.load("sprites/wizard.png");
    unit[0].mask_image.load("sprites/mask_wizard.png");
    unit[0].status = UNIT_OK;
    unit[0].vLocation = 1;
    unit[0].hLocation = 1;
    unit[0].faceLeft = false;

    // Create a new unit (for gl debug purposes).
    unit[1].name = "Monk";
    unit[1].actionTime = 10;
    unit[1].actionRate = 200;
    unit[1].hitPoints = 40;
    unit[1].totalHitPoints = 100;
    unit[1].image.load("sprites/buddhist.png");
    unit[1].mask_image.load("sprites/mask_buddhist.png");
    unit[1].status = UNIT_OK;
    unit[1].vLocation = 0;
    unit[1].hLocation = 1;
    unit[1].faceLeft = false;

    // Create a new unit (for gl debug purposes).
    unit[2].name = "Bard";
    unit[2].actionTime = 40;
    unit[2].actionRate = 100;
    unit[2].hitPoints = 10;
    unit[2].totalHitPoints = 100;
    unit[2].image.load("sprites/bard.png");
    unit[2].mask_image.load("sprites/mask_bard.png");
    unit[2].status = UNIT_OK;
    unit[2].vLocation = 2;
    unit[2].hLocation = 2;
    unit[2].faceLeft = false;

    // Create a new unit (for gl debug purposes).
    unit[3].name = "Desert Soldier";
    unit[3].actionTime = 40;
    unit[3].actionRate = 100;
    unit[3].hitPoints = 10;
    unit[3].totalHitPoints = 100;
    unit[3].image.load("sprites/desertsoldier.png");
    unit[3].mask_image.load("sprites/mask_desertsoldier.png");
    unit[3].status = UNIT_OK;
    unit[3].vLocation = 3;
    unit[3].hLocation = 5;
    unit[3].faceLeft = true;

    // Create a new unit (for gl debug purposes).
    unit[4].name = "Merchant";
    unit[4].actionTime = 40;
    unit[4].actionRate = 100;
    unit[4].hitPoints = 10;
    unit[4].totalHitPoints = 100;
    unit[4].image.load("sprites/merchant.png");
    unit[4].mask_image.load("sprites/mask_merchant.png");
    unit[4].status = UNIT_OK;
    unit[4].vLocation = 2;
    unit[4].hLocation = 5;
    unit[4].faceLeft = true;

    // Create a new unit (for gl debug purposes).
    unit[5].name = "Priestess";
    unit[5].actionTime = 40;
    unit[5].actionRate = 100;
    unit[5].hitPoints = 10;
    unit[5].totalHitPoints = 100;
    unit[5].image.load("sprites/priestess.png");
    unit[5].mask_image.load("sprites/mask_priestess.png");
    unit[5].status = UNIT_OK;
    unit[5].vLocation = 1;
    unit[5].hLocation = 6;
    unit[5].faceLeft = true;

    for (int i = 6; i < MAX_UNITS; i++)
    {
        // Tell OpenGL whether or not the unit exists.
        unit[i].status = NO_UNIT;
    }
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	initializeGL()
//	Description:	Initialize the OpenGL widget.
//	Modified:	03/02/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
void GLWidget::initializeGL()
{
    unitTest_GenerateContent();

    initGrid();

    // Load a background image (debug).
    bkImage.load(map.mapFilename.c_str());
    bkImage = bkImage.scaled(GLWidget::width(), GLWidget::height(), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    glBkImage = QGLWidget::convertToGLFormat(bkImage);

    // Setup OpenGL values for appropriate graphics.
    glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);							// Depth Buffer Setup
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);				// Set Line Antialiasing
    glEnable(GL_BLEND);                                                 // Enable Blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Type Of Blending To Use

    return;
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	initGrid()
//	Description:
//	Modified:	04/09/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
void GLWidget::initGrid()
{
    for (int i = 0; i < MAX_GRID_DIMENSION; i++)
    {
        for (int j = 0; j < MAX_GRID_DIMENSION; j++)
        {
            mapGrid[i][j].isUnit = false;
            mapGrid[i][j].isSelected = false;

            mapGrid[i][j].cellWidth = fullWidth / map.cellsWide;
            mapGrid[i][j].cellHeight = fullHeight / map.cellsTall;
            mapGrid[i][j].bottomEdge = i * cellHeight;
            mapGrid[i][j].leftEdge = j * cellWidth;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	paintGL()
//	Description:	Paint the OpenGL widget (run on a timer).
//	Modified:	03/02/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw the background.
    glDrawPixels(glBkImage.width(), glBkImage.height(), GL_RGBA, GL_UNSIGNED_BYTE, glBkImage.bits());
    
    for (int i = 0; i < map.cellsTall; i++)
    {
        for (int j = 0; j < map.cellsWide; j++)
        {
            // Draw the grid.
            drawGridBox(i, j);

            // Assume no unit at the beginning.
            mapGrid[i][j].isUnit = false;
        }
    }

    for (int i = 0; i < MAX_UNITS; i++)
    {
        // Draw the units.
        updateUnit(unit[i]);

        mapGrid[unit[i].vLocation][unit[i].hLocation].unit = unit[i];
        mapGrid[unit[i].vLocation][unit[i].hLocation].isUnit = true;

        // Update the action time (unitTest).
        if (unit[i].actionTime >= 100)
        {
            unit[i].actionTime = 0;
        }
        unit[i].actionTime += 0.005 * unit[i].actionRate;
    }

    for (int i = 0; i < map.cellsTall; i++)
    {
        for (int j = 0; j < map.cellsWide; j++)
        {
            if (mapGrid[i][j].isSelected && mapGrid[i][j].isUnit)
            {
                // Draw information header.
                glColor4f( 0.0f, 0.0f, 0.0f, 0.8f );
                glBegin (GL_QUADS);
                    glVertex3f (15, GLWidget::height() - 20, 0.0);
                    glVertex3f (15 + 250, GLWidget::height() - 20, 0.0);
                    glVertex3f (15 + 250, GLWidget::height() - 20 - 100, 0.0);
                    glVertex3f (15, GLWidget::height() - 20 - 100, 0.0);
                glEnd();

                qglColor(Qt::white);
                char *tmpString = (char*)malloc(256);
                string displayString = "";
                int vLoc = GLWidget::height() - 40;

                // Unit name.
                QFont nameFont = GLWidget::font();
                nameFont.setBold(true);
                renderText(30, vLoc, 0.0, mapGrid[i][j].unit.name.c_str(), nameFont);
                vLoc -= 15;

                // Unit hit points.
                itoa(mapGrid[i][j].unit.hitPoints, tmpString, 10);
                displayString = "Hit Points: ";
                displayString.append(tmpString);
                renderText(30, vLoc, 0.0, displayString.c_str());
                vLoc -= 15;

                // Unit attack power.
                itoa(mapGrid[i][j].unit.attackPower, tmpString, 10);
                displayString = "Attack Power: ";
                displayString.append(tmpString);
                renderText(30, vLoc, 0.0, displayString.c_str());
                vLoc -= 15;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	isGridBoxSelected()
//	Description:	Draw the requested grid box.
//                      Call this fuction in a loop to get full grid.
//                      If 'isSelected' is true, the box is red.
//	Modified:	03/02/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
bool GLWidget::isGridBoxSelected(int i, int j)
{
    if (mouseClick.hLoc > mapGrid[i][j].leftEdge && mouseClick.hLoc < mapGrid[i][j].leftEdge + cellWidth)
    {
        if (mouseClick.vLoc > mapGrid[i][j].bottomEdge && mouseClick.vLoc < mapGrid[i][j].bottomEdge + cellHeight)
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
    else
    {
        return (false);
    }
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	drawGridBox()
//	Description:	Draw the requested grid box.
//                      Call this fuction in a loop to get full grid.
//                      If 'isSelected' is true, the box is red.
//	Modified:	03/02/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
bool GLWidget::drawGridBox(int i, int j)
{
    // Find out whether or not the current grid is selected.
    mapGrid[i][j].isSelected = isGridBoxSelected(i, j);

    // Cell border style.
    int padding = 3;
    if (mapGrid[i][j].isSelected)
    {
        if( selectedBorder == 2 )   selectedBorder = 1;
        else                        selectedBorder = 2;
        glLineWidth(selectedBorder);
        glColor4f( 0.4f, 0.0f, 0.0f, 0.8f );
    }
    else
    {
        glLineWidth( 1 );
        glColor4f( 0.4f, 0.4f, 0.4f, 0.8f );
    }

    // Define corner locations (without perspective).
    point ulLoc, urLoc, blLoc, brLoc;
    blLoc.hLoc = mapGrid[i][j].leftEdge + padding;
    blLoc.vLoc = mapGrid[i][j].bottomEdge + padding;
    brLoc.hLoc = mapGrid[i][j].leftEdge + cellWidth - padding;
    brLoc.vLoc = mapGrid[i][j].bottomEdge + padding;
    ulLoc.hLoc = mapGrid[i][j].leftEdge + padding;
    ulLoc.vLoc = mapGrid[i][j].bottomEdge + cellHeight - padding;
    urLoc.hLoc = mapGrid[i][j].leftEdge + cellWidth - padding;
    urLoc.vLoc = mapGrid[i][j].bottomEdge + cellHeight - padding;

    glRotatef(-5, 1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        // Left line.
        glVertex3f(blLoc.hLoc, blLoc.vLoc, 0.0f);
        glVertex3f(ulLoc.hLoc, ulLoc.vLoc, 0.0f);

        // Top line.
        glVertex3f(ulLoc.hLoc, ulLoc.vLoc, 0.0f);
        glVertex3f(urLoc.hLoc, urLoc.vLoc, 0.0f);

        // Right line.
        glVertex3f(brLoc.hLoc, brLoc.vLoc, 0.0f);
        glVertex3f(urLoc.hLoc, urLoc.vLoc, 0.0f);

        // Bottom line.
        glVertex3f(blLoc.hLoc, blLoc.vLoc, 0.0f);
        glVertex3f(brLoc.hLoc, brLoc.vLoc, 0.0f);
    glEnd();
    glRotatef(5, 1.0, 0.0, 0.0);

    return (true);
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	updateUnit()
//	Description:	Update the requested Unit in the OpenGL widget.
//	Modified:	03/02/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
bool GLWidget::updateUnit(characterUnit myUnit)
{
    if (myUnit.status == NO_UNIT)
    {
        return (false);
    }

    // Calculate the action and hit point bars as a percentage.
    float actionTime = (float)myUnit.actionTime / (float)100;
    float hitPoints = (float)myUnit.hitPoints / (float)myUnit.totalHitPoints;

    // Dynamically define the height and width of the sprite.
    float widthRatio = (float)myUnit.image.width() / (float)myUnit.image.height();
    int spriteHeight = cellHeight * 1.5 + 1;
    int spriteWidth = cellHeight * 1.5 * widthRatio;

    // Dynamically define the OpenGL location of the sprite.
    int bottomEdge = myUnit.vLocation * cellHeight + spriteHeight/6;
    int leftEdge = myUnit.hLocation * cellWidth + (cellWidth / 2) - (spriteWidth / 2);
    int rightEdge = leftEdge + spriteWidth;

    glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );
    glBlendFunc( GL_DST_COLOR,GL_ZERO );

    glEnable(GL_TEXTURE_2D);
    GLuint textureMask = bindTexture( myUnit.mask_image, GL_TEXTURE_2D );

    // Draw the sprite facing left or right.
    if (myUnit.faceLeft)
    {
        glBegin (GL_QUADS);
            // Bottom left.
            glTexCoord2f (0.0, 0.0);
            glVertex3f (leftEdge, bottomEdge, 0.0);

            // Bottom right.
            glTexCoord2f (1.0, 0.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge, 0.0);

            // Top right.
            glTexCoord2f (1.0, 1.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge + spriteHeight, 0.0);

            // Top left.
            glTexCoord2f (0.0, 1.0);
            glVertex3f (leftEdge, bottomEdge + spriteHeight, 0.0);
        glEnd();
    }
    else
    {
        glBegin (GL_QUADS);
            // Bottom left.
            glTexCoord2f (1.0, 0.0);
            glVertex3f (leftEdge, bottomEdge, 0.0);

            // Bottom right.
            glTexCoord2f (0.0, 0.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge, 0.0);

            // Top right.
            glTexCoord2f (0.0, 1.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge + spriteHeight, 0.0);

            // Top left.
            glTexCoord2f (1.0, 1.0);
            glVertex3f (leftEdge, bottomEdge + spriteHeight, 0.0);
        glEnd ();
    }

    glBlendFunc(GL_ONE, GL_ONE);
    GLuint textureValue = bindTexture( myUnit.image, GL_TEXTURE_2D );

    // Draw the sprite facing left or right.
    if (myUnit.faceLeft)
    {
        glBegin (GL_QUADS);
            // Bottom left.
            glTexCoord2f (0.0, 0.0);
            glVertex3f (leftEdge, bottomEdge, 0.0);

            // Bottom right.
            glTexCoord2f (1.0, 0.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge, 0.0);

            // Top right.
            glTexCoord2f (1.0, 1.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge + spriteHeight, 0.0);

            // Top left.
            glTexCoord2f (0.0, 1.0);
            glVertex3f (leftEdge, bottomEdge + spriteHeight, 0.0);
        glEnd ();
    }
    else
    {
        glBegin(GL_QUADS);
            // Bottom left.
            glTexCoord2f (1.0, 0.0);
            glVertex3f (leftEdge, bottomEdge, 0.0);

            // Bottom right.
            glTexCoord2f (0.0, 0.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge, 0.0);

            // Top right.
            glTexCoord2f (0.0, 1.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge + spriteHeight, 0.0);

            // Top left.
            glTexCoord2f (1.0, 1.0);
            glVertex3f (leftEdge, bottomEdge + spriteHeight, 0.0);
        glEnd();
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_TEXTURE_2D);

    // Free memory.
    glDeleteTextures( 1, &textureMask );
    glDeleteTextures( 1, &textureValue );

    // Show unit's health.
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex3f( leftEdge - statusWidth, bottomEdge + cellHeight/2, 0.0f );
        glVertex3f( leftEdge, bottomEdge + cellHeight/2, 0.0f );
        glVertex3f( leftEdge,  bottomEdge, 0.0f );
        glVertex3f( leftEdge - statusWidth, bottomEdge, 0.0f );
    glEnd();
    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f( leftEdge - statusWidth, bottomEdge + cellHeight/2 * hitPoints, 0.0f );
        glVertex3f( leftEdge, bottomEdge + cellHeight/2 * hitPoints, 0.0f );
        glVertex3f( leftEdge,  bottomEdge, 0.0f );
        glVertex3f( leftEdge - statusWidth, bottomEdge, 0.0f );
    glEnd();

    // Show unit's action points.
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex3f( rightEdge, bottomEdge + cellHeight/2, 0.0f );	// Top Left
        glVertex3f( rightEdge + statusWidth, bottomEdge + cellHeight/2, 0.0f );	//Top Right
        glVertex3f( rightEdge + statusWidth, bottomEdge, 0.0f );	// Bottom Right
        glVertex3f( rightEdge, bottomEdge, 0.0f );	// Bottom Left
    glEnd();
    glColor3f(0.0f, 0.0f, 0.6f);
    glBegin(GL_QUADS);
        glVertex3f( rightEdge, bottomEdge + cellHeight/2 * actionTime, 0.0f );	// Top Left
        glVertex3f( rightEdge + statusWidth, bottomEdge + cellHeight/2 * actionTime, 0.0f );	//Top Right
        glVertex3f( rightEdge + statusWidth, bottomEdge, 0.0f );	// Bottom Right
        glVertex3f( rightEdge, bottomEdge, 0.0f );	// Bottom Left
    glEnd();

    return (true);
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	resizeGL()
//	Description:	Adjust drawing element dimensions on window resize.
//	Modified:	03/02/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
void GLWidget::resizeGL(int width, int height)
{
    // Never divide by zero.
    if (height == 0)
    {
        height=1;
    }

    // (Re)Calculate the OpenGL object dimensions.
    fullWidth = width;
    fullHeight = height * map.gridHeight;
    statusWidth = (fullWidth / map.cellsWide) * 0.1f;
    cellWidth = fullWidth / map.cellsWide;
    cellHeight = fullHeight / map.cellsTall;

    mouseClick.hLoc = 0;
    mouseClick.vLoc = 0;

    // Reset grid locations and dimensions.
    initGrid();
    
    // Setup the 2d perspective.
    glViewport(0, 0, width, height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1000, 1000);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    updateGL();

    // Reload and resize the background image.
    bkImage.load(map.mapFilename.c_str());
    bkImage = bkImage.scaled(GLWidget::width(), GLWidget::height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    glBkImage = QGLWidget::convertToGLFormat(bkImage);
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	timerEvent()
//	Description:	Redraw the OpenGl widget whenever the timer triggers.
//	Modified:	03/02/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
void GLWidget::timerEvent(QTimerEvent *event)
{
    updateGL();
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	mousePressEvent()
//	Description:	Capture a user mouse click.
//	Modified:	04/09/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    // Proces mouse events for rotate/move inside 3D scene
    mouseClick.hLoc = event->x();
    mouseClick.vLoc = (fullHeight / map.gridHeight) - event->y();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // Process mouse stuff...
}
