#include "glwidget.h"

// Global classes.
extern mechanics *mech;

/*******************************************************
* GLWidget()
*
* Description: Constructor which initializes the OpenGL
* widget and starts the graphics update timer.
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
    isEffect = false;
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

    // Connect music slot.
    musicTrack = TITLE_AUDIO_TRACK;
    music = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(musicTrack));
    connect(music, SIGNAL(finished()), SLOT(backgroundTrackFinished()));

    // Start the graphics display timer.
    startTimer( GL_TIMER_INTERVAL );
}

/*******************************************************
* LoadContent()
*
* Description: Loads the battle map content passed from
* the user interface (with some hard coded).
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::LoadContent(Database db)
{
    // Get the active user.
    User myUser =  db.loadActiveUser();

    // Get the selected level (battle map).
    int levelMapIndex = myUser.level;
    battleMap.imageFileName = db.mapFileName(levelMapIndex);
    battleMap.audioFileName = "sounds/Battle_02.mp3";
    battleMap.cellsTall = 6;
    battleMap.cellsWide = 9;
    battleMap.gridHeight = 0.58;

    // Add units.
    unitTest_AddUnits();

    for (int i = 0; i < 4; i++)
    {
        // Get unit images from UI selection.
        unit[i].imageFileName = myUser.units[i].imageFileName;

        QStringList splitString = unit[i].imageFileName.split("/");
        QString maskFileName;
        maskFileName.append(splitString[0]);
        maskFileName.append("/mask_");
        maskFileName.append(splitString[1]);

        unit[i].maskFileName = maskFileName;
        unit[i].name = myUser.units[i].name;

        // Load the actual sprite images.
        unit[i].image.load(unit[i].imageFileName);
        unit[i].mask_image.load(unit[i].maskFileName);
        unit[i].faceLeft = false;

        // Load data (if it makes sense).
        unit[i].movementRange = myUser.units[i].movementRange;
    }

    // Load a background image.
    bkImage.load(battleMap.imageFileName);
    bkImage = bkImage.scaled(GLWidget::width(), GLWidget::height(), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    glBkImage = QGLWidget::convertToGLFormat(bkImage);

    // Initialize the grid.
    initGrid();

    musicTrack = battleMap.audioFileName;
    playBackgroundTrack();

    // Start the battle.
    isBattle = true;

    // Ensure proper graphics scaling.
    resizeGL(GLWidget::width(), GLWidget::height());
}

/*******************************************************
* unitTest_AddUnits()
*
* Description: Create 8 "dummy" units.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::unitTest_AddUnits()
{
    // Create a new unit (for gl debug purposes).
    unit[0].actionTime = 10;
    unit[0].actionRate=450;
    unit[0].hitPoints = 100;
    unit[0].totalHitPoints = 100;
    unit[0].status = UNIT_OK;
    unit[0].vLocation = 1;
    unit[0].hLocation = 2;
    unit[0].attackPower = 12;
    unit[0].attackRange = 2;
    unit[0].faceLeft = false;
    unit[0].movementRange = 2;
    unit[0].team = USER_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[1].actionTime = 10;
    unit[1].actionRate = 500;
    unit[1].hitPoints = 100;
    unit[1].totalHitPoints = 100;
    unit[1].status =UNIT_OK;
    unit[1].vLocation = 2;
    unit[1].hLocation = 1;
    unit[1].attackPower = 16;
    unit[1].attackRange = 2;
    unit[1].faceLeft = false;
    unit[1].movementRange = 1;
    unit[1].team = USER_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[2].actionTime = 60;
    unit[2].actionRate =400;
    unit[2].hitPoints = 80;
    unit[2].totalHitPoints = 80;
    unit[2].status =UNIT_OK;
    unit[2].vLocation = 3;
    unit[2].hLocation = 2;
    unit[2].attackPower = 15;
    unit[2].attackRange = 1;
    unit[2].faceLeft = false;
    unit[2].movementRange = 4;
    unit[2].team = USER_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[3].actionTime = 40;
    unit[3].actionRate = 400;
    unit[3].hitPoints = 60;
    unit[3].totalHitPoints = 60;
    unit[3].status =UNIT_OK;
    unit[3].vLocation = 2;
    unit[3].hLocation = 2;
    unit[3].attackPower = 12;
    unit[3].attackRange = 3;
    unit[3].faceLeft = false;
    unit[3].movementRange = 2;
    unit[3].team = USER_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[4].name = "Berserker";
    unit[4].actionTime = 40;
    unit[4].actionRate = 300;
    unit[4].hitPoints = 90;
    unit[4].totalHitPoints = 90;
    unit[4].imageFileName = "sprites/berserker.png";
    unit[4].image.load("sprites/berserker.png");
    unit[4].mask_image.load("sprites/mask_berserker.png");
    unit[4].status =UNIT_OK;
    unit[4].vLocation = 3;
    unit[4].hLocation = 5;
    unit[4].attackPower = 10;
    unit[4].attackRange = 1;
    unit[4].faceLeft = true;
    unit[4].movementRange = 2;
    unit[4].team = AI_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[5].name = "Valkyrie";
    unit[5].actionTime = 40;
    unit[5].actionRate = 500;
    unit[5].hitPoints = 70;
    unit[5].totalHitPoints = 70;
    unit[5].imageFileName = "sprites/valkyrie.png";
    unit[5].image.load("sprites/valkyrie.png");
    unit[5].mask_image.load("sprites/mask_valkyrie.png");
    unit[5].status =UNIT_OK;
    unit[5].vLocation = 4;
    unit[5].hLocation = 7;
    unit[5].attackPower = 14;
    unit[5].attackRange = 1;
    unit[5].faceLeft = true;
    unit[5].movementRange = 1;
    unit[5].team = AI_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[6].name = "Knight";
    unit[6].actionTime = 40;
    unit[6].actionRate = 500;
    unit[6].hitPoints = 70;
    unit[6].totalHitPoints = 70;
    unit[6].imageFileName = "sprites/knight.png";
    unit[6].image.load("sprites/knight.png");
    unit[6].mask_image.load("sprites/mask_knight.png");
    unit[6].status =UNIT_OK;
    unit[6].vLocation = 1;
    unit[6].hLocation = 5;
    unit[6].attackPower = 8;
    unit[6].attackRange = 2;
    unit[6].faceLeft = true;
    unit[6].movementRange = 4;
    unit[6].team = AI_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[7].name = "Bard";
    unit[7].actionTime = 40;
    unit[7].actionRate = 400;
    unit[7].hitPoints = 60;
    unit[7].totalHitPoints = 60;
    unit[7].imageFileName = "sprites/bard.png";
    unit[7].image.load("sprites/bard.png");
    unit[7].mask_image.load("sprites/mask_bard.png");
    unit[7].status =UNIT_OK;
    unit[7].vLocation = 4;
    unit[7].hLocation = 8;
    unit[7].attackPower = 13;
    unit[7].attackRange = 3;
    unit[7].faceLeft = true;
    unit[7].movementRange = 2;
    unit[7].team = AI_UNIT;

    for (int i = 0; i < MAX_MAP_UNITS; i++)
    {
        // No units are pending to start.
        unit[i].isPending = false;
    }

    for (int i = 8; i < MAX_MAP_UNITS; i++)
    {
        // Tell OpenGL whether or not the unit exists.
        unit[i].status = NO_UNIT;
    }
}

/*******************************************************
* unitTest_GenerateContent()
*
* Description: Loads hard coded battle map content for
* unit testing.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::unitTest_GenerateContent()
{
    // Select a battle map.
    battleMap.imageFileName = "backgrounds/plains.png";
    battleMap.audioFileName = "sounds/Battle_02.mp3";
    battleMap.cellsTall = 6;
    battleMap.cellsWide = 9;
    battleMap.gridHeight = 0.58;

    // Create a new unit (for gl debug purposes).
    unit[0].name = "Knight";
    unit[0].actionTime = 10;
    unit[0].actionRate=450;
    unit[0].hitPoints = 100;
    unit[0].totalHitPoints = 100;
    unit[0].image.load("sprites/knight.png");
    unit[0].mask_image.load("sprites/mask_knight.png");
    unit[0].status = UNIT_OK;
    unit[0].vLocation = 1;
    unit[0].hLocation = 2;
    unit[0].attackPower = 12;
    unit[0].attackRange = 2;
    unit[0].faceLeft = false;
    unit[0].movementRange = 2;
    unit[0].team =USER_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[1].name = "Crusader";
    unit[1].actionTime = 10;
    unit[1].actionRate = 500;
    unit[1].hitPoints = 100;
    unit[1].totalHitPoints = 100;
    unit[1].image.load("sprites/crusader.png");
    unit[1].mask_image.load("sprites/mask_crusader.png");
    unit[1].status =UNIT_OK;
    unit[1].vLocation = 2;
    unit[1].hLocation = 1;
    unit[1].attackPower = 16;
    unit[1].attackRange = 2;
    unit[1].faceLeft = false;
    unit[1].movementRange = 1;
    unit[1].team =USER_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[2].name = "Thai Boxer";
    unit[2].actionTime = 60;
    unit[2].actionRate =400;
    unit[2].hitPoints = 80;
    unit[2].totalHitPoints = 80;
    unit[2].image.load("sprites/thaiboxer.png");
    unit[2].mask_image.load("sprites/mask_thaiboxer.png");
    unit[2].status =UNIT_OK;
    unit[2].vLocation = 3;
    unit[2].hLocation = 2;
    unit[2].attackPower = 15;
    unit[2].attackRange = 1;
    unit[2].faceLeft = false;
    unit[2].movementRange = 4;
    unit[2].team =USER_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[3].name = "Assassin";
    unit[3].actionTime = 40;
    unit[3].actionRate = 400;
    unit[3].hitPoints = 60;
    unit[3].totalHitPoints = 60;
    unit[3].image.load("sprites/assassin.png");
    unit[3].mask_image.load("sprites/mask_assassin.png");
    unit[3].status =UNIT_OK;
    unit[3].vLocation = 1;
    unit[3].hLocation = 5;
    unit[3].attackPower = 12;
    unit[3].attackRange = 3;
    unit[3].faceLeft = false;
    unit[3].movementRange = 2;
    unit[3].team =USER_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[4].name = "Berserker";
    unit[4].actionTime = 40;
    unit[4].actionRate = 300;
    unit[4].hitPoints = 90;
    unit[4].totalHitPoints = 90;
    unit[4].image.load("sprites/berserker.png");
    unit[4].mask_image.load("sprites/mask_berserker.png");
    unit[4].status =UNIT_OK;
    unit[4].vLocation = 3;
    unit[4].hLocation = 5;
    unit[4].attackPower = 10;
    unit[4].attackRange = 1;
    unit[4].faceLeft = true;
    unit[4].movementRange = 2;
    unit[4].team =AI_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[5].name = "Valkyrie";
    unit[5].actionTime = 40;
    unit[5].actionRate = 500;
    unit[5].hitPoints = 70;
    unit[5].totalHitPoints = 70;
    unit[5].image.load("sprites/valkyrie.png");
    unit[5].mask_image.load("sprites/mask_valkyrie.png");
    unit[5].status =UNIT_OK;
    unit[5].vLocation = 4;
    unit[5].hLocation = 7;
    unit[5].attackPower = 14;
    unit[5].attackRange = 1;
    unit[5].faceLeft = true;
    unit[5].movementRange = 1;
    unit[5].team =AI_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[6].name = "Valkyrie";
    unit[6].actionTime = 40;
    unit[6].actionRate = 500;
    unit[6].hitPoints = 70;
    unit[6].totalHitPoints = 70;
    unit[6].image.load("sprites/valkyrie.png");
    unit[6].mask_image.load("sprites/mask_valkyrie.png");
    unit[6].status =UNIT_OK;
    unit[6].vLocation = 2;
    unit[6].hLocation = 2;
    unit[6].attackPower = 8;
    unit[6].attackRange = 2;
    unit[6].faceLeft = true;
    unit[6].movementRange = 4;
    unit[6].team =AI_UNIT;

    // Create a new unit (for gl debug purposes).
    unit[7].name = "Bard";
    unit[7].actionTime = 40;
    unit[7].actionRate = 400;
    unit[7].hitPoints = 60;
    unit[7].totalHitPoints = 60;
    unit[7].image.load("sprites/bard.png");
    unit[7].mask_image.load("sprites/mask_bard.png");
    unit[7].status =UNIT_OK;
    unit[7].vLocation = 4;
    unit[7].hLocation = 8;
    unit[7].attackPower = 13;
    unit[7].attackRange = 3;
    unit[7].faceLeft = true;
    unit[7].movementRange = 2;
    unit[7].team =AI_UNIT;

    // Load a background image (debug).
    bkImage.load(battleMap.imageFileName);
    bkImage = bkImage.scaled(GLWidget::width(), GLWidget::height(), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    glBkImage = QGLWidget::convertToGLFormat(bkImage);

    // Initialize the grid.
    initGrid();

    musicTrack = battleMap.audioFileName;
    playBackgroundTrack();

    // Start the battle.
    isBattle = true;

    // Ensure proper graphics scaling.
    resizeGL(GLWidget::width(), GLWidget::height());
}

/*******************************************************
* playBackgroundTrack()
*
* Description: Plays the currently selected background
* track.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::playBackgroundTrack()
{
    // Play current track.
    music->stop();
    music->setCurrentSource(Phonon::MediaSource(musicTrack));
    music->play();
}

/*******************************************************
* backgroundTrackFinished()
*
* Description: Restarts the currently selected
* background track when it is completed.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::backgroundTrackFinished()
{
    // Restart current track.
    playBackgroundTrack();
}

/*******************************************************
* updateTitleScreen()
*
* Description: Toggles through various battle map
* backgrounds and displays a "Duel Reality" logo across
* the top.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::updateTitleScreen()
{
    // Clear the display.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    int ticksPerSecond = 1000 / GL_TIMER_INTERVAL;

    if (iEventCounter / ticksPerSecond >= TITLE_TRANSITION_SECONDS)
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
    
    // Draw title screen header.
    glColor4f( 0.2f, 0.2f, 0.2f, 0.9f );
    glBegin (GL_QUADS);
        glVertex3f (0, GLWidget::height() - 20, 0.0);
        glVertex3f (GLWidget::width(), GLWidget::height() - 20, 0.0);
        glVertex3f (GLWidget::width(), GLWidget::height() - 20 - 110, 0.0);
        glVertex3f (0, GLWidget::height() - 20 - 110, 0.0);
    glEnd();

    qglColor(Qt::white);
    int vLoc = GLWidget::height() - 80;

    // Unit name.
    QFont nameFont = GLWidget::font();
    nameFont.setBold(true);
    nameFont.setPointSize(24);
    renderText (GLWidget::width() - 250, vLoc, 0.0, "Duel Reality", nameFont);
    vLoc -= 15;

    // Update event counter.
    iEventCounter++;
}

/*******************************************************
* initializeGL()
*
* Description: Initializes the OpenGL widget by setting
* various color, shading, and blending options.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
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

/*******************************************************
* initGrid()
*
* Description: Initializes the various battle map grid
* cells with correct data.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
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

/*******************************************************
* paintGL()
*
* Description: The primary painting function for the
* OpenGL widget.  Everything is drawn here at the
* specified update rate.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::paintGL()
{
    // Handle title screen.
    if (!isBattle)
    {
        updateTitleScreen();
        return;
    }

    // Capture pending status.
    if (!isPending && !isEffect)
    {
        for (int i = 0; i < MAX_MAP_UNITS; i++)
        {
            // Update the action time (unitTest).
            if (unit[i].actionTime >= 100 && unit[i].status==UNIT_OK) //the dead shall not move :o
            {
                if (unit[i].team == USER_UNIT)
                {
                    // Play 'ready' sound.
                    QSound *soundBkgnd = new QSound("sounds/blip.wav");
                    soundBkgnd->play();
                }

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

    // Clear the background.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw items.
    drawBackground();
    drawGrid();
    drawUnits();
    drawHeaderInfo();

    if (isEffect)
    {
        drawEffects();
    }
}

/*******************************************************
* drawEffects()
*
* Description: Case statement to time and handle the
* special effects.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::drawEffects()
{
    int ticksPerSecond = 1000 / GL_TIMER_INTERVAL;

    switch(effectType)
    {
    case EFFECT_NONE:
        if (iEventCounter / ticksPerSecond >= DEFAULT_TRANSITION_SECONDS)
        {
            isEffect = false;
        }
        break;
    case EFFECT_MOVE:
        if (iEventCounter / ticksPerSecond >= MOVE_TRANSITION_SECONDS)
        {
            isEffect = false;

            for (int i = 0; i < MAX_MAP_UNITS; i++)
            {
                if(unit[i].status != NO_UNIT)
                {
                    QStringList splitString = unit[i].imageFileName.split("/");
                    QString maskFileName;
                    maskFileName.append(splitString[0]);
                    maskFileName.append("/mask_");
                    maskFileName.append(splitString[1]);

                    unit[i].mask_image.load(maskFileName);
                    unit[i].maskFileName = maskFileName;
                }
            }
        }
        break;
    case EFFECT_ATTACK:
        if (iEventCounter / ticksPerSecond >= ATTACK_TRANSITION_SECONDS)
        {
            isEffect = false;
        }
        else
        {
            drawAttack();
        }
        break;
    }

    // Update event counter.
    iEventCounter++;
}

/*******************************************************
* drawAttack()
*
* Description: Handles and draws the special effect for
* the attack function.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::drawAttack()
{
    QImage mask_image, image;

    mask_image.load("effects/mask_wisp.png");
    image.load("effects/wisp.png");

    // Dynamically define the height and width of the sprite.
    float widthRatio = (float)image.width() / (float)image.height();
    int spriteHeight = cellHeight * 1.5 + 1;
    int spriteWidth = cellHeight * 1.5 * widthRatio;

    // Dynamically define the OpenGL location of the sprite.
    int bottomEdge = attack_vLoc * cellHeight + spriteHeight/6;
    int leftEdge = attack_hLoc * cellWidth + (cellWidth / 2) - (spriteWidth / 2);

    glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );
    glBlendFunc( GL_DST_COLOR,GL_ZERO );

    glEnable(GL_TEXTURE_2D);

    GLuint textureMask = bindTexture( mask_image, GL_TEXTURE_2D );

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

    glBlendFunc(GL_ONE, GL_ONE);
    GLuint textureValue = bindTexture( image, GL_TEXTURE_2D );

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

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_TEXTURE_2D);

    // Free memory.
    glDeleteTextures( 1, &textureMask );
    glDeleteTextures( 1, &textureValue );
}

/*******************************************************
* drawBackground()
*
* Description: Draws the static background.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::drawBackground()
{
    glDrawPixels(glBkImage.width(), glBkImage.height(), GL_RGBA, GL_UNSIGNED_BYTE, glBkImage.bits());
}

/*******************************************************
* drawUnits()
*
* Description: Draws the units themselves within the
* correct battle map grid cell.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::drawUnits()
{
    for (int i = battleMap.cellsTall - 1; i >= 0; i--)
    {
        for (int j = 0; j < battleMap.cellsWide; j++)
        {
            for (int k = 0; k < MAX_MAP_UNITS; k++)
            {
                if (unit[k].status != NO_UNIT)
                {
                    if (i == unit[k].vLocation && j == unit[k].hLocation)
                    {
                        battleMap.gridCell[i][j].unit = &unit[k];
                        battleMap.gridCell[i][j].isUnit = true;

                        // Draw the units.
                        updateUnit(unit[k]);
                    }
                }
            }
        }
    }
}

/*******************************************************
* drawGrid()
*
* Description: Loop to draw all the various grid boxes.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::drawGrid()
{
    for (int i = 0; i < battleMap.cellsTall; i++)
    {
        for (int j = 0; j < battleMap.cellsWide; j++)
        {
            // Draw the grid.
            drawGridBox(i, j);
        }
    }
}

/*******************************************************
* drawHeaderInfo()
*
* Description: Paints the selected and pending unit info
* to the header region of the battle map.
*
* Inputs: none
*
* Outputs: none
*
* Return: none
*******************************************************/
void GLWidget::drawHeaderInfo()
{
    for (int i = 0; i < battleMap.cellsTall; i++)
    {
        for (int j = 0; j < battleMap.cellsWide; j++)
        {
            if (battleMap.gridCell[i][j].unit->status != NO_UNIT)
            {
                if (battleMap.gridCell[i][j].unit->isPending)
                {
                    // Draw information header.
                    glColor4f( 0.2f, 0.2f, 0.2f, 0.9f );
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
                    renderText (30, vLoc, 0.0, battleMap.gridCell[i][j].unit->name, nameFont);
                    vLoc -= 15;

                    // Unit hit points.
                    itoa(battleMap.gridCell[i][j].unit->hitPoints, tmpString, 10);
                    displayString = "Health: ";
                    displayString.append(tmpString);
                    displayString.append(" / ");
                    itoa(battleMap.gridCell[i][j].unit->totalHitPoints, tmpString, 10);
                    displayString.append(tmpString);
                    renderText (30, vLoc, 0.0, displayString.c_str());
                    vLoc -= 15;

                    // Unit attack power.
                    itoa(battleMap.gridCell[i][j].unit->attackPower, tmpString, 10);
                    displayString = "Attack Power: ";
                    displayString.append(tmpString);
                    renderText (30, vLoc, 0.0, displayString.c_str());
                    vLoc -= 15;

                    // Unit attack range.
                    itoa(battleMap.gridCell[i][j].unit->attackRange, tmpString, 10);
                    displayString = "Attack Range: ";
                    displayString.append(tmpString);
                    renderText (30, vLoc, 0.0, displayString.c_str());
                    vLoc -= 15;

                    // Unit movement rate.
                    itoa(battleMap.gridCell[i][j].unit->movementRange, tmpString, 10);
                    displayString = "Movement Rate: ";
                    displayString.append(tmpString);
                    renderText (30, vLoc, 0.0, displayString.c_str());
                    vLoc -= 15;

                    // Unit action time.
                    itoa(battleMap.gridCell[i][j].unit->actionTime, tmpString, 10);
                    displayString = "Action Time: ";
                    displayString.append(tmpString);
                    displayString.append("%");
                    renderText (30, vLoc, 0.0, displayString.c_str());
                    vLoc -= 15;
                }
            }

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
                displayString = "Health: ";
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
                itoa(battleMap.gridCell[i][j].unit->movementRange, tmpString, 10);
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

/*******************************************************
* isGridBoxSelected()
*
* Description: Return whether or not a grid cell is
* selected.
*
* Inputs: Coordinates of the grid cell in question.
*
* Outputs: none.
*
* Return: True = Cell Selected
*         False = Cell not selected
*******************************************************/
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

/*******************************************************
* drawGridBox()
*
* Description: Draws an individual grid cell.
*
* Inputs: Coordinates of the grid cell to be drawn.
*
* Outputs: none.
*
* Return: none.
*******************************************************/
void GLWidget::drawGridBox(int i, int j)
{
    // Find out whether or not the current grid is selected.
    bool isHighlighted = false;
    battleMap.gridCell[i][j].isSelected = isGridBoxSelected(i, j);

    // Cell border style.
    int padding = 3;
    if (battleMap.gridCell[i][j].isSelected || battleMap.gridCell[i][j].unit->isPending)
    {
       if (battleMap.gridCell[i][j].isSelected)
        {
            glColor4f( 0.4f, 0.0f, 0.0f, 0.7f );
        }
        else if(battleMap.gridCell[i][j].unit->isPending)
        {
            glColor4f( 0.2f, 0.2f, 0.2f, 0.7f );
        }
        isHighlighted = true;
    }
    else
    {
        glLineWidth( 1 );
        glColor4f( 0.4f, 0.4f, 0.4f, 1.0f );
        isHighlighted = false;
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

    if (isHighlighted == true)
    {
        glBegin(GL_QUADS);
            // Bottom left.
            glVertex3f (blLoc.hLoc, blLoc.vLoc, 0.0);

            // Bottom right.
            glVertex3f (brLoc.hLoc, brLoc.vLoc, 0.0);

            // Top right.
            glVertex3f (urLoc.hLoc, urLoc.vLoc, 0.0);

            // Top left.
            glVertex3f (ulLoc.hLoc, ulLoc.vLoc, 0.0);

            glRotatef(5, 1.0, 0.0, 0.0);
        glEnd();
    }

    glRotatef(5, 1.0, 0.0, 0.0);
}

/*******************************************************
* updateUnit()
*
* Description: Draws an individual unit.
*
* Inputs: Unit to be drawn.
*
* Outputs: none.
*
* Return: none.
*******************************************************/
void GLWidget::updateUnit(Unit myUnit)
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

    // Draw the sprite facing right.
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

    // Draw the sprite facing left.
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
    glColor3f(0.0f, 0.6f, 0.0f);
    if (myUnit.team == AI_UNIT)
    {
        glColor3f(0.6f, 0.0f, 0.0f);
    }
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
}

/*******************************************************
* resizeGL()
*
* Description: Handles the UI resize event.
*
* Inputs: New dimensions of the OpenGL Widget.
*
* Outputs: none.
*
* Return: none.
*******************************************************/
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

/*******************************************************
* timerEvent()
*
* Description: Repaints the OpenGL widget whenever the
* timer triggers.
*
* Inputs: The event itself (unused).
*
* Outputs: none.
*
* Return: none.
*******************************************************/
void GLWidget::timerEvent(QTimerEvent *event)
{
    // Redraw the graphics window.
    updateGL();
}

/*******************************************************
* mousePressEvent()
*
* Description: Capture the mouse coordinates when a
* click event occurs on the OpenGL widget.
*
* Inputs: The event (used to capture coordinates).
*
* Outputs: none.
*
* Return: none.
*******************************************************/
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if (isBattle)
    {
        // Proces mouse events for rotate/move inside 3D scene
        mouseClick.hLoc = event->x();
        mouseClick.vLoc = (fullHeight / battleMap.gridHeight) - event->y();
    }
}

/*******************************************************
* moveUnit()
*
* Description: Handles the "move unit" event triggered
* by the UI and managed by the mechanics modules.
*
* Inputs: Previous and new grid coordinates.
*
* Outputs: none.
*
* Return: none.
*******************************************************/
void GLWidget::moveUnit(int vLocPrev, int hLocPrev, int vLocNext, int hLocNext)
{
    iEventCounter = 0;
    isEffect = true;
    effectType = EFFECT_MOVE;
    isPending = false;

    move_vLocNext = vLocNext;
    move_hLocNext = hLocNext;

    // Update the new cell.
    battleMap.gridCell[move_vLocNext][move_hLocNext].unit = battleMap.gridCell[vLocPrev][hLocPrev].unit;
    battleMap.gridCell[move_vLocNext][move_hLocNext].unit->vLocation = vLocNext;
    battleMap.gridCell[move_vLocNext][move_hLocNext].unit->hLocation = hLocNext;
    battleMap.gridCell[move_vLocNext][move_hLocNext].unit->isPending = false;
    battleMap.gridCell[move_vLocNext][move_hLocNext].unit->actionTime = 0;
    battleMap.gridCell[move_vLocNext][move_hLocNext].isUnit = true;

    // Clear the old cell.
    battleMap.gridCell[vLocPrev][hLocPrev].unit = new Unit;
    battleMap.gridCell[vLocPrev][hLocPrev].isUnit = false;
    battleMap.gridCell[vLocPrev][hLocPrev].unit->vLocation = -1;
    battleMap.gridCell[vLocPrev][hLocPrev].unit->hLocation = -1;
    battleMap.gridCell[vLocPrev][hLocPrev].unit->isPending = false;

    // Remove mask temporarily.
    moveMask = battleMap.gridCell[move_vLocNext][move_hLocNext].unit->maskFileName;
    battleMap.gridCell[move_vLocNext][move_hLocNext].unit->mask_image.load("sprites/white.png");

    // Play 'move' sound.
    QSound *soundBkgnd = new QSound("sounds/Action_Move.wav");
    soundBkgnd->play();
}

/*******************************************************
* hitUnit()
*
* Description: Handles the "hit unit" event triggered
* by the UI and managed by the mechanics modules.
*
* Inputs: Attacker and victim coordinates as well as
* the damage to be done.
*
* Outputs: none.
*
* Return: none.
*******************************************************/
void GLWidget::hitUnit(int vLocation, int hLocation, int damage, int vAttackerLoc, int hAttackerLoc)
{
    iEventCounter = 0;
    isEffect = true;
    effectType = EFFECT_ATTACK;
    isPending = false;

    attack_vLoc = vLocation;
    attack_hLoc = hLocation;

    battleMap.gridCell[attack_vLoc][attack_hLoc].unit->hitPoints -= damage;

    battleMap.gridCell[vAttackerLoc][hAttackerLoc].unit->isPending = false;
    battleMap.gridCell[vAttackerLoc][hAttackerLoc].unit->actionTime = 0;

    // Play 'hit' sound.
    QSound *soundBkgnd = new QSound("sounds/Action_Hit.wav");
    soundBkgnd->play();
}

/*******************************************************
* hitUnit()
*
* Description: Handles the "kill unit" event triggered
* by the UI and managed by the mechanics modules.
*
* Inputs: Attacker and victim coordinates.
*
* Outputs: none.
*
* Return: none.
*******************************************************/
void GLWidget::killUnit(int vLocation, int hLocation, int vAttackerLoc, int hAttackerLoc)
{
    iEventCounter = 0;
    isEffect = true;
    effectType = EFFECT_ATTACK;
    isPending = false;

    attack_vLoc = vLocation;
    attack_hLoc = hLocation;

    battleMap.gridCell[attack_vLoc][attack_hLoc].unit->status = NO_UNIT;

    battleMap.gridCell[vAttackerLoc][hAttackerLoc].unit->isPending = false;
    battleMap.gridCell[vAttackerLoc][hAttackerLoc].unit->actionTime = 0;

    // Clear the old cell.
    battleMap.gridCell[attack_vLoc][attack_hLoc].unit = new Unit;
    battleMap.gridCell[attack_vLoc][attack_hLoc].isUnit = false;
    battleMap.gridCell[attack_vLoc][attack_hLoc].unit->vLocation = -1;
    battleMap.gridCell[attack_vLoc][attack_hLoc].unit->hLocation = -1;
    battleMap.gridCell[attack_vLoc][attack_hLoc].unit->isPending = false;

    // Play 'hit' sound.
    QSound *soundBkgnd = new QSound("sounds/Action_Hit.wav");
    soundBkgnd->play();
}
