#include "glwidget.h"

// Global classes.
extern mechanics *mech;

/*******************************************************
* GLWidget()
*
* Description: Initializes the OpenGL widget and starts
* the graphics update timer.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
GLWidget::GLWidget()
{
    // Initialize some variables.
    isPending = false;
    isBattle = false;
    selectedBorder = 1;
    titleIndex = 0;
    iEventCounter = 0;

    // Set strings for the title screen slide show.
    backgroundList[0] = "backgrounds/beach.png";
    backgroundList[1] = "backgrounds/beach2.png";
    backgroundList[2] = "backgrounds/grass.png";
    backgroundList[3] = "backgrounds/grassnight.png";
    backgroundList[4] = "backgrounds/plains.png";
    backgroundList[5] = "backgrounds/snow.png";
    backgroundList[6] = "backgrounds/townnight.png";

    // Start the graphics display timer.
    startTimer( GL_TIMER_INTERVAL );
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	unitTest_GenerateContent()
//	Description:	Add content for unit testing.
//	Modified:	03/02/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
void GLWidget::updateTitleScreen()
{
    // Clear the display.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (iEventCounter > GL_TIMER_INTERVAL / (10 / titleTransitionSeconds))
    {
        // Next title image.
        titleIndex++;
        iEventCounter = 0;

        if (titleIndex > 6)
        {
            titleIndex = 0;
        }

        // Change image if necessary.
        bkImage.load(backgroundList[titleIndex]);
        bkImage = bkImage.scaled(GLWidget::width(), GLWidget::height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
        glBkImage = QGLWidget::convertToGLFormat(bkImage);
    }

    // Draw the background.
    glDrawPixels(glBkImage.width(), glBkImage.height(), GL_RGBA, GL_UNSIGNED_BYTE, glBkImage.bits());
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
    battleMap.imageFileName = "backgrounds/plains.png";
    battleMap.audioFileName = "sounds/Battle_01.mp3";
    battleMap.cellsTall = 6;
    battleMap.cellsWide = 9;
    battleMap.gridHeight = 0.58;

    // Create a new unit (for gl debug purposes).
    unit[0].name = "Knight";
    unit[0].actionTime = 10;
    unit[0].actionRate = 150;
    unit[0].hitPoints = 80;
    unit[0].totalHitPoints = 100;
    unit[0].image.load("sprites/knight.png");
    unit[0].mask_image.load("sprites/mask_knight.png");
    unit[0].status = UNIT_OK;
    unit[0].vLocation = 1;
    unit[0].hLocation = 2;
    unit[0].attackPower = 8;
    unit[0].attackRange = 3;
    unit[0].faceLeft = false;
    unit[0].movementRate = 1;
    unit[0].team = USER_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[1].name = "Crusader";
    unit[1].actionTime = 10;
    unit[1].actionRate = 200;
    unit[1].hitPoints = 67;
    unit[1].totalHitPoints = 100;
    unit[1].image.load("sprites/crusader.png");
    unit[1].mask_image.load("sprites/mask_crusader.png");
    unit[1].status = UNIT_OK;
    unit[1].vLocation = 2;
    unit[1].hLocation = 1;
    unit[1].attackPower = 8;
    unit[1].attackRange = 3;
    unit[1].faceLeft = false;
    unit[1].movementRate = 2;
    unit[1].team = USER_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[2].name = "Thai Boxer";
    unit[2].actionTime = 60;
    unit[2].actionRate = 200;
    unit[2].hitPoints = 10;
    unit[2].totalHitPoints = 100;
    unit[2].image.load("sprites/thaiboxer.png");
    unit[2].mask_image.load("sprites/mask_thaiboxer.png");
    unit[2].status = UNIT_OK;
    unit[2].vLocation = 3;
    unit[2].hLocation = 2;
    unit[2].attackPower = 8;
    unit[2].attackRange = 3;
    unit[2].faceLeft = false;
    unit[2].movementRate = 1;
    unit[1].team = USER_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[3].name = "Assassin";
    unit[3].actionTime = 40;
    unit[3].actionRate = 101;
    unit[3].hitPoints = 30;
    unit[3].totalHitPoints = 100;
    unit[3].image.load("sprites/assassin.png");
    unit[3].mask_image.load("sprites/mask_assassin.png");
    unit[3].status = UNIT_OK;
    unit[3].vLocation = 3;
    unit[3].hLocation = 5;
    unit[3].attackPower = 8;
    unit[3].attackRange = 3;
    unit[3].faceLeft = true;
    unit[3].movementRate = 2;
    unit[3].team = AI_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[4].name = "Berserker";
    unit[4].actionTime = 40;
    unit[4].actionRate = 102;
    unit[4].hitPoints = 22;
    unit[4].totalHitPoints = 100;
    unit[4].image.load("sprites/berserker.png");
    unit[4].mask_image.load("sprites/mask_berserker.png");
    unit[4].status = UNIT_OK;
    unit[4].vLocation = 1;
    unit[4].hLocation = 5;
    unit[4].attackPower = 8;
    unit[4].attackRange = 3;
    unit[4].faceLeft = true;
    unit[4].movementRate = 2;
    unit[4].team = AI_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[5].name = "Valkyrie";
    unit[5].actionTime = 40;
    unit[5].actionRate = 103;
    unit[5].hitPoints = 10;
    unit[5].totalHitPoints = 100;
    unit[5].image.load("sprites/valkyrie.png");
    unit[5].mask_image.load("sprites/mask_valkyrie.png");
    unit[5].status = UNIT_OK;
    unit[5].vLocation = 4;
    unit[5].hLocation = 7;
    unit[5].attackPower = 8;
    unit[5].attackRange = 3;
    unit[5].faceLeft = true;
    unit[5].movementRate = 1;
    unit[5].team = AI_UNIT;

    for (int i = 0; i < MAX_MAP_UNITS; i++)
    {
        // No units are pending to start.
        unit[i].isPending = false;
    }

    for (int i = 6; i < MAX_MAP_UNITS; i++)
    {
        // Tell OpenGL whether or not the unit exists.
        unit[i].status = NO_UNIT;
    }

    // Load a background image (debug).
    bkImage.load(battleMap.imageFileName);
    bkImage = bkImage.scaled(GLWidget::width(), GLWidget::height(), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    glBkImage = QGLWidget::convertToGLFormat(bkImage);

    // Initialize the grid.
    initGrid();

    setBackgroundTrack(battleMap.audioFileName);

    // Start the battle.
    isBattle = true;

    // Ensure proper graphics scaling.
    resizeGL(GLWidget::width(), GLWidget::height());
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	initializeGL()
//	Description:	Initialize the OpenGL widget.
//	Modified:	03/02/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
void GLWidget::initializeGL()
{
    // Setup OpenGL values for appropriate graphics.
    glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);							// Depth Buffer Setup
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);				// Set Line Antialiasing
    glEnable(GL_BLEND);                                                 // Enable Blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Type Of Blending To Use
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
            battleMap.gridCell[i][j].unit = new Unit;
            battleMap.gridCell[i][j].unit->status = NO_UNIT;
            battleMap.gridCell[i][j].unit->isPending = false;
            battleMap.gridCell[i][j].isUnit = false;
            battleMap.gridCell[i][j].isSelected = false;

            battleMap.gridCell[i][j].cellWidth = fullWidth / battleMap.cellsWide;
            battleMap.gridCell[i][j].cellHeight = fullHeight / battleMap.cellsTall;
            battleMap.gridCell[i][j].bottomEdge = i * cellHeight;
            battleMap.gridCell[i][j].leftEdge = j * cellWidth;
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
    if (!isBattle)
    {
        updateTitleScreen();
        return;
    }

    if (!isPending)
    {
        for (int i = 0; i < MAX_MAP_UNITS; i++)
        {
            // Update the action time (unitTest).
            if (unit[i].actionTime >= 100)
            {
                // Play 'ready' sound.
                QSound *soundBkgnd = new QSound("sounds/blip.wav");
                soundBkgnd->play();

                // The unit is ready to go, so pause the game.
                battleMap.gridCell[unit[i].vLocation][unit[i].hLocation].unit->isPending = true;
                isPending = true;

                // Tell mechanics to handle AI.
                mech->handleAI();
                break;
            }
            unit[i].actionTime += 0.005 * unit[i].actionRate;
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw the background.
    glDrawPixels(glBkImage.width(), glBkImage.height(), GL_RGBA, GL_UNSIGNED_BYTE, glBkImage.bits());
    
    for (int i = 0; i < battleMap.cellsTall; i++)
    {
        for (int j = 0; j < battleMap.cellsWide; j++)
        {
            // Draw the grid.
            drawGridBox(i, j);

            // Assume no unit at the beginning.
            battleMap.gridCell[i][j].isUnit = false;
        }
    }

    for (int i = 0; i < MAX_MAP_UNITS; i++)
    {
        if (unit[i].status != NO_UNIT)
        {
            // Make sure the map is up to date.
            battleMap.gridCell[unit[i].vLocation][unit[i].hLocation].unit = &unit[i];
            battleMap.gridCell[unit[i].vLocation][unit[i].hLocation].isUnit = true;

            // Draw the units.
            updateUnit(unit[i]);

            if (unit[i].isPending)
            {
                // Draw information header.
                glColor4f( 0.0f, 0.0f, 0.2f, 0.9f );
                glBegin (GL_QUADS);
                    glVertex3f (15, GLWidget::height() - 20, 0.0);
                    glVertex3f (15 + 250, GLWidget::height() - 20, 0.0);
                    glVertex3f (15 + 250, GLWidget::height() - 20 - 110, 0.0);
                    glVertex3f (15, GLWidget::height() - 20 - 110, 0.0);
                glEnd();

                qglColor(Qt::white);
                char *tmpString = (char*)malloc(256);
                string displayString = "";
                int vLoc = GLWidget::height() - 40;

                // Unit name.
                QFont nameFont = GLWidget::font();
                nameFont.setBold(true);
                renderText (30, vLoc, 0.0, unit[i].name, nameFont);
                vLoc -= 15;

                // Unit hit points.
                itoa(unit[i].hitPoints, tmpString, 10);
                displayString = "Hit Points: ";
                displayString.append(tmpString);
                displayString.append(" / ");
                itoa(unit[i].totalHitPoints, tmpString, 10);
                displayString.append(tmpString);
                renderText (30, vLoc, 0.0, displayString.c_str());
                vLoc -= 15;

                // Unit attack power.
                itoa(unit[i].attackPower, tmpString, 10);
                displayString = "Attack Power: ";
                displayString.append(tmpString);
                renderText (30, vLoc, 0.0, displayString.c_str());
                vLoc -= 15;

                // Unit attack range.
                itoa(unit[i].attackRange, tmpString, 10);
                displayString = "Attack Range: ";
                displayString.append(tmpString);
                renderText (30, vLoc, 0.0, displayString.c_str());
                vLoc -= 15;

                // Unit movement rate.
                itoa(unit[i].movementRate, tmpString, 10);
                displayString = "Movement Rate: ";
                displayString.append(tmpString);
                renderText (30, vLoc, 0.0, displayString.c_str());
                vLoc -= 15;

                // Unit action time.
                itoa(unit[i].actionTime, tmpString, 10);
                displayString = "Action Time: ";
                displayString.append(tmpString);
                displayString.append("%");
                renderText (30, vLoc, 0.0, displayString.c_str());
                vLoc -= 15;
            }
        }
    }

    for (int i = 0; i < battleMap.cellsTall; i++)
    {
        for (int j = 0; j < battleMap.cellsWide; j++)
        {
            if (battleMap.gridCell[i][j].isSelected && battleMap.gridCell[i][j].isUnit)
            {
                // Draw information header.
                glColor4f( 0.2f, 0.0f, 0.0f, 0.9f );
                glBegin (GL_QUADS);
                    glVertex3f (GLWidget::width() - 265, GLWidget::height() - 20, 0.0);
                    glVertex3f (GLWidget::width() - 15, GLWidget::height() - 20, 0.0);
                    glVertex3f (GLWidget::width() - 15, GLWidget::height() - 20 - 110, 0.0);
                    glVertex3f (GLWidget::width() - 265, GLWidget::height() - 20 - 110, 0.0);
                glEnd();

                qglColor(Qt::white);
                char *tmpString = (char*)malloc(256);
                string displayString = "";
                int vLoc = GLWidget::height() - 40;

                // Unit name.
                QFont nameFont = GLWidget::font();
                nameFont.setBold(true);
                renderText (GLWidget::width() - 250, vLoc, 0.0, battleMap.gridCell[i][j].unit->name, nameFont);
                vLoc -= 15;

                // Unit hit points.
                itoa(battleMap.gridCell[i][j].unit->hitPoints, tmpString, 10);
                displayString = "Hit Points: ";
                displayString.append(tmpString);
                displayString.append(" / ");
                itoa(battleMap.gridCell[i][j].unit->totalHitPoints, tmpString, 10);
                displayString.append(tmpString);
                renderText (GLWidget::width() - 250, vLoc, 0.0, displayString.c_str());
                vLoc -= 15;

                // Unit attack power.
                itoa(battleMap.gridCell[i][j].unit->attackPower, tmpString, 10);
                displayString = "Attack Power: ";
                displayString.append(tmpString);
                renderText (GLWidget::width() - 250, vLoc, 0.0, displayString.c_str());
                vLoc -= 15;

                // Unit attack range.
                itoa(battleMap.gridCell[i][j].unit->attackRange, tmpString, 10);
                displayString = "Attack Range: ";
                displayString.append(tmpString);
                renderText (GLWidget::width() - 250, vLoc, 0.0, displayString.c_str());
                vLoc -= 15;

                // Unit movement rate.
                itoa(battleMap.gridCell[i][j].unit->movementRate, tmpString, 10);
                displayString = "Movement Rate: ";
                displayString.append(tmpString);
                renderText (GLWidget::width() - 250, vLoc, 0.0, displayString.c_str());
                vLoc -= 15;

                // Unit action time.
                itoa(battleMap.gridCell[i][j].unit->actionTime, tmpString, 10);
                displayString = "Action Time: ";
                displayString.append(tmpString);
                displayString.append("%");
                renderText (GLWidget::width() - 250, vLoc, 0.0, displayString.c_str());
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
    if (mouseClick.hLoc > battleMap.gridCell[i][j].leftEdge && mouseClick.hLoc < battleMap.gridCell[i][j].leftEdge + cellWidth)
    {
        if (mouseClick.vLoc > battleMap.gridCell[i][j].bottomEdge && mouseClick.vLoc < battleMap.gridCell[i][j].bottomEdge + cellHeight)
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
    battleMap.gridCell[i][j].isSelected = isGridBoxSelected(i, j);

    // Cell border style.
    int padding = 3;
    if (battleMap.gridCell[i][j].isSelected)
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

    if (battleMap.gridCell[i][j].unit->status != NO_UNIT)
    {
        if (battleMap.gridCell[i][j].unit->isPending)
        {
            glColor4f( 0.0f, 0.0f, 0.4f, 0.8f );
        }
    }

    // Define corner locations (without perspective).
    point ulLoc, urLoc, blLoc, brLoc;
    blLoc.hLoc = battleMap.gridCell[i][j].leftEdge + padding;
    blLoc.vLoc = battleMap.gridCell[i][j].bottomEdge + padding;
    brLoc.hLoc = battleMap.gridCell[i][j].leftEdge + cellWidth - padding;
    brLoc.vLoc = battleMap.gridCell[i][j].bottomEdge + padding;
    ulLoc.hLoc = battleMap.gridCell[i][j].leftEdge + padding;
    ulLoc.vLoc = battleMap.gridCell[i][j].bottomEdge + cellHeight - padding;
    urLoc.hLoc = battleMap.gridCell[i][j].leftEdge + cellWidth - padding;
    urLoc.vLoc = battleMap.gridCell[i][j].bottomEdge + cellHeight - padding;

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
bool GLWidget::updateUnit(Unit myUnit)
{
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
    fullHeight = height * battleMap.gridHeight;
    statusWidth = (fullWidth / battleMap.cellsWide) * 0.05f;
    cellWidth = fullWidth / battleMap.cellsWide;
    cellHeight = fullHeight / battleMap.cellsTall;

    mouseClick.hLoc = 0;
    mouseClick.vLoc = 0;

    if (!isBattle)
    {
        // Setup the 2d perspective.
        glViewport(0, 0, width, height);
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, 0, height, -1000, 1000);

        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity();

        updateGL();

        // Reload and resize the background image.
        bkImage.load(backgroundList[titleIndex]);
        bkImage = bkImage.scaled(GLWidget::width(), GLWidget::height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
        glBkImage = QGLWidget::convertToGLFormat(bkImage);
    }
    else
    {
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
        bkImage.load(battleMap.imageFileName);
        bkImage = bkImage.scaled(GLWidget::width(), GLWidget::height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
        glBkImage = QGLWidget::convertToGLFormat(bkImage);
    }
}

///////////////////////////////////////////////////////////////////////////////
//	Function Name:	timerEvent()
//	Description:	Redraw the OpenGl widget whenever the timer triggers.
//	Modified:	03/02/2010
//	Author:		Tom Calloway
///////////////////////////////////////////////////////////////////////////////
void GLWidget::timerEvent(QTimerEvent *event)
{
    // Update event counter.
    iEventCounter++;

    // Redraw the graphics window.
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
    if (isBattle)
    {
        // Proces mouse events for rotate/move inside 3D scene
        mouseClick.hLoc = event->x();
        mouseClick.vLoc = (fullHeight / battleMap.gridHeight) - event->y();
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // Process mouse stuff...
}

void GLWidget::setBackgroundTrack(QString trackFileName)
{
    music->stop();
    music = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(trackFileName));
    music->play();
}

void GLWidget::moveUnit(int vLocPrev, int hLocPrev, int vLocNext, int hLocNext)
{
    battleMap.gridCell[vLocPrev][hLocPrev].unit->vLocation = vLocNext;
    battleMap.gridCell[vLocPrev][hLocPrev].unit->hLocation = hLocNext;

    battleMap.gridCell[vLocPrev][hLocPrev].unit->isPending = false;
    battleMap.gridCell[vLocPrev][hLocPrev].unit->actionTime = 0;
    isPending = false;
}

void GLWidget::hitUnit(int vLocation, int hLocation, int damage, int vAttackerLoc, int hAttackerLoc)
{
    battleMap.gridCell[vLocation][hLocation].unit->hitPoints -= damage;

    battleMap.gridCell[vAttackerLoc][hAttackerLoc].unit->isPending = false;
    battleMap.gridCell[vAttackerLoc][hAttackerLoc].unit->actionTime = 0;
    isPending = false;
}

void GLWidget::killUnit(int vLocation, int hLocation, int vAttackerLoc, int hAttackerLoc)
{
    battleMap.gridCell[vLocation][hLocation].unit->status = NO_UNIT;

    battleMap.gridCell[vAttackerLoc][hAttackerLoc].unit->isPending = false;
    battleMap.gridCell[vAttackerLoc][hAttackerLoc].unit->actionTime = 0;
    isPending = false;
}
