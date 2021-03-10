/***************************************************************************//**
 * @file game.cpp
 * @author Chezka Gaddi
 * @brief Contains all functions that maintains Game class.
 *******************************************************************************/

#include <ctime>
#include "callbacks.h"
#include "game.h"

float Drawable::xscalar = 1.0;
float Drawable::yscalar = 1.0;
int TimerEvent::idleSpeed = 750;

/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief Constructor
 * @par Description:
 * Default constructor, sets turn = 0
 *
 *******************************************************************************/
Game::Game() : turn ( 0 )
{

}

/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief Constructor
 * @par Description:
 * Constructor that sets the game mode, sets turn = 0
 *
 * @param[in] mode - type of game to be played
 *
 *******************************************************************************/
Game::Game ( gameMode mode ) : turn ( 0 )
{
    if ( gMode == 0 )
        gMode = mode;
}

/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief Destructor
 * @par Description:
 * Frees up the memory allocated to the drawables and the GameField.
 *
 *******************************************************************************/
Game::~Game()
{
    objects.clear();
    delete tankGame;
}

/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief convertGLXCoordinate
 * @par Description:
 * Converts the coordinates to GLfloat to be displayed correctly on the screen.
 *
 * @param[in] x - integer to be converted
 *
 * @return xGL - GLfloat conversion of x
 *
 *******************************************************************************/
float Game::convertGLXCoordinate ( int x )
{
    float fScaler;
    GLfloat xGL;


    // Function:fscalar = x * 4.0717 * (fieldx ^ -1.031)
    fScaler = x * 4.0717 * pow ( fieldX, -1.031 );
    xGL = -1.75 + fScaler;


    return xGL;
}

/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief convertGLYCoordinate
 * @par Description:
 * Converts the coordinates to GLfloat to be displayed correctly on the screen.
 *
 * @param[in] y - integer to be converted
 *
 * @return yGL - GLfloat conversion of y
 *
 *******************************************************************************/
float Game::convertGLYCoordinate ( int y )
{
    float fScaler;
    GLfloat yGL;

    // Formula: fscalar = y * 3.1923 * (fieldy ^ -1.08)
    fScaler =  y * 3.1923 * pow ( fieldY, -1.08 );
    yGL = 0.75 - fScaler;


    return yGL;
}

/***************************************************************************//**
 * @author Jacob Lee
 * @brief isplayable
 * @par Description:
 * Determines the end of the game by the count of the tanks on the field.
 *
 * @param[in] actorInfo - list of all the active actors
 *
 * @return boolean of whether or not more than one tank is still active
 *
 *******************************************************************************/
static bool isplayable ( const vector<ActorInfo>& actorInfo )
{
    int tankCount = 0;


    for ( auto a : actorInfo )
        tankCount += ( a.id > 0 ) ? 1 : 0;


    return ( tankCount > 1 );
}

/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief gameOver
 * @par Description:
 * Display the screen that reads game over
 *
 * @param[in] dead - vector of dead tanks?
 * @param[in] winner - vector of winning tanks?
 *
 *******************************************************************************/
void Game::gameOver ( vector<ActorInfo> dead, vector<ActorInfo> winner )
{

    const char* str;
    static int runCount = 0;
    int count, winDex;
    int i, l;
    int timer_pause = TimerEvent::idleSpeed * 133;
    float k;
    float color[] = {1.0f, 1.0f, 1.0f};
    float j = -0.7f;

    bool flag = false;
    csv tankOutput;
    tankData tempTank;

    string scoreDetails[4] = { "Place:", "Player Number:", "Kills:", "Hits:" };
    string fileScoreDetails[10] = {"Player", "Place", "Kills", "Shots", "Hits", "AP", "Radar", "MaxHealth",
                                   "RemainingHealth", "MaxAmmo"
                                  };
    string s;
    if ( runCount == 0 )
    {
        for ( i = 0; i < 10; i++ )
            tankOutput.addColumn ( fileScoreDetails[i] );

        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glLoadIdentity();
        glEnable ( GL_TEXTURE_2D );

        glPushMatrix();
        glTranslatef ( 0.0f, 0.0f, -5.0f );
        glBindTexture ( GL_TEXTURE_2D, gameTex[5] );
        glBegin ( GL_QUADS );
        glTexCoord2f ( 0.0f, 0.0f );
        glVertex3f ( -0.8f, -0.3f,  1.0f );
        glTexCoord2f ( 1.0f, 0.0f );
        glVertex3f ( 0.8f, -0.3f,  1.0f );
        glTexCoord2f ( 1.0f, 1.0f );
        glVertex3f ( 0.8f,  0.8f,  1.0f );
        glTexCoord2f ( 0.0f, 1.0f );
        glVertex3f ( -0.8f,  0.8f,  1.0f );
        glEnd();
        glPopMatrix();

        glDisable ( GL_TEXTURE_2D );


        glPushMatrix();
        glTranslatef ( 0.0f, 0.0f, -5.0f );
        glColor3fv ( color );


        if ( winner.size() != 0 )
        {
            count = 1;
            winDex = 0;
            k = -0.5;

            for ( i = 0; i < 4; i++ )
            {
                glRasterPos3f ( j, -0.3f, 2.0f );
                str = scoreDetails[i].c_str();

                while ( *str )
                {
                    glutBitmapCharacter ( GLUT_BITMAP_9_BY_15, *str );
                    str++;
                }

                if ( !flag )
                {
                    j += 0.3;
                    flag = true;
                }

                else
                {
                    j += 0.7;
                    flag = false;
                }
            }


            while ( winner[winDex].name == "default\n" && ( unsigned ) winDex < winner.size() )
                winDex++;


            str = "1st";
            glRasterPos3f ( -0.7f, k, 2.0f );

            while ( *str )
            {
                glutBitmapCharacter ( GLUT_BITMAP_9_BY_15, *str );
                str++;
            }


            str = winner[winDex].name.c_str();
            glRasterPos3f ( -0.4f, k, 2.0f );

            while ( *str )
            {
                glutBitmapCharacter ( GLUT_BITMAP_9_BY_15, *str );
                str++;
            }


            str = to_string ( winner[winDex].kills ).c_str();
            glRasterPos3f ( 0.3f, k, 2.0f );

            while ( *str )
            {
                glutBitmapCharacter ( GLUT_BITMAP_9_BY_15, *str );
                str++;
            }


            str = to_string ( winner[winDex].hits ).c_str();
            glRasterPos3f ( 0.6f, k, 2.0f );

            while ( *str )
            {
                glutBitmapCharacter ( GLUT_BITMAP_9_BY_15, *str );
                str++;
            }


            k += -0.1f;
            count++;

            tempTank.player = winner[winDex].name;
            tempTank.place = 1;
            tempTank.kills = winner[winDex].kills;
            tempTank.shots = winner[winDex].shots;
            tempTank.hits = winner[winDex].hits;
            tempTank.AP = winner[winDex].AP;
            tempTank.radar = winner[winDex].radar;
            tempTank.maxHealth = winner[winDex].max_health;
            tempTank.remainingHealth = winner[winDex].health;
            tempTank.maxAmmo = winner[winDex].max_ammo;
            tankOutput.addRow ( tempTank );

            for ( l = dead.size() - 1; l >= 0; l-- )
            {
                if ( count == 2 )
                    str = "2nd";
                else if ( count == 3 )
                    str = "3rd";
                else
                {
                    s = to_string ( count );
                    s += "th";
                    str = s.c_str();  //use char const* as target type
                }


                glRasterPos3f ( -0.7f, k, 2.0f );


                while ( *str )
                {
                    glutBitmapCharacter ( GLUT_BITMAP_9_BY_15, *str );
                    str++;
                }


                str = dead[l].name.c_str();
                glRasterPos3f ( -0.4f, k, 2.0f );

                while ( *str )
                {
                    glutBitmapCharacter ( GLUT_BITMAP_9_BY_15, *str );
                    str++;
                }


                str = to_string ( dead[l].kills ).c_str();
                glRasterPos3f ( 0.3f, k, 2.0f );

                while ( *str )
                {
                    glutBitmapCharacter ( GLUT_BITMAP_9_BY_15, *str );
                    str++;
                }


                str = to_string ( dead[l].hits ).c_str();
                glRasterPos3f ( 0.6f, k, 2.0f );

                while ( *str )
                {
                    glutBitmapCharacter ( GLUT_BITMAP_9_BY_15, *str );
                    str++;
                }


                k += -0.1f;


                tempTank.player = dead[l].name;
                tempTank.place = count;
                tempTank.kills = dead[l].kills;
                tempTank.shots = dead[l].shots;
                tempTank.hits = dead[l].hits;
                tempTank.AP = dead[l].AP;
                tempTank.radar = dead[l].radar;
                tempTank.maxHealth = dead[l].max_health;
                tempTank.remainingHealth = dead[l].health;
                tempTank.maxAmmo = dead[l].max_ammo;
                tankOutput.addRow ( tempTank );

                count++;
            }
        }

        else
        {
            cout << "Draw game" << endl;
            glRasterPos3f ( -0.05f, -0.3f, 2.0f );
            s = "DRAW";
            str = s.c_str();


            while ( *str )
            {
                glutBitmapCharacter ( GLUT_BITMAP_9_BY_15, *str );
                str++;
            }


            for ( l = dead.size() - 1; l >= 0; l-- )
            {
                tempTank.player = dead[l].name;
                tempTank.place = 1;
                tempTank.kills = dead[l].kills;
                tempTank.shots = dead[l].shots;
                tempTank.hits = dead[l].hits;
                tempTank.AP = dead[l].AP;
                tempTank.radar = dead[l].radar;
                tempTank.maxHealth = dead[l].max_health;
                tempTank.remainingHealth = dead[l].health;
                tempTank.maxAmmo = dead[l].max_ammo;
                tankOutput.addRow ( tempTank );
            }
        }

        tankOutput.outputCSV();

        //Note- Early screen closing might be caused by this
        timer_pause >= 0 ? usleep ( timer_pause ) : usleep ( 0 );

        glutSwapBuffers();

        timer_pause = TimerEvent::idleSpeed * 533;
        timer_pause >= 0 ? usleep ( timer_pause ) : usleep ( 0 );
       
        runCount++;
    }
}

/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief executeTurn
 * @par Description:
 * While the game is still playable, execute a turn from each of the tanks,
 * otherwise return back to main and destroy the GUI.
 *
 *******************************************************************************/
void Game::executeTurn()
{
    if ( tankGame->getTurnCount() == maxTurns )
    {
        //Finding Early Winner
        vector<ActorInfo>* actors = tankGame->getActorsPointer();
        int actorId = 0;
        int currMaxHealth = 0;
        bool tie = false;


        for ( auto a : *actors ) //clear out non tanks
            if ( a.id < 0 )
                a.health = 0;


        tankGame->cull();  //remove the old tanks


        for ( auto a : *actors )
        {
            if ( a.health > currMaxHealth )
            {
                actorId = a.id;
                tie = false;
                currMaxHealth = a.health;
            }

            else if ( a.health == currMaxHealth )
                tie = true;
        }


        if ( tie == true ) //Clear all tanks if tie.  Return to draw screen.
            for ( auto& a : * actors )
                a.health = 0;

        else if ( tie == false ) //No tie, kill off all tanks
            for ( auto& a : *actors )
                if ( a.id != actorId )
                    a.health = 0;

        tankGame->turnCount++;
        tankGame->cull(); //Let game play one more turn and quit itself
    }

    else if ( isplayable ( tankGame->getActorsConst() ) ) //Keep playing
        tankGame->nextTurn();

    else   //If maxturns is not hit, and no longer playable print results
    {
        gameOver ( tankGame->getDeceased(), tankGame->getActors() );
        if ( gMode == coverage )
            glutLeaveMainLoop();
    }
}

/***************************************************************************//**
 * @author David Donahue
 * @brief displayWrapper
 * @par Description:
 * Wrapper to display() that acts as the GameField display callback

 * @param[in] map - The map
 * @param[in] actors - vector of tanks?
 * @param[in] turnCount - count of Turns.
 *
 *******************************************************************************/
void displayWrapper ( MapData map, vector<ActorInfo> actors, int turnCount )
{
    display();
}

/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief initGameState
 * @par Description:
 * Initialize the main GameField and all the Drawables needed to start the game.
   Reads settings from the file "config.txt"
 *
 *******************************************************************************/
void Game::initGameState()
{


    int x = 0, y = 0, i = 0; //Temp Holders
    int attributePoints = 0;
    //Game Setting defaults
    int aiSpeed = 750, width = 15, height = 9, maxT = 200, hPad = 0, wPad = 0;
    //Tank Defaults
    int damage = 1, health = 3, range = 4, radar = 4, ap = 1, ammo = 6;

    bool taken;
    bool isQuiet = false;

    ifstream fin ( "config.txt" );
    ofstream fout;

    string configLine, id, args, name;

    Obstacles* tempOb = nullptr;
    Drawable* temp = nullptr;
    attributes baseStats;

    pair<int, int> coordPair, padCoordPair;

    //Location vectors
    vector<pair<int, int>> obstacleLocations, treeLocations, rockLocations,
           bushLocations, tankLocations, waterLocations, specialLocations;

    //Image vectors for custom images
    vector<string> tankImages, gameImages, treeImages, rockImages,
           bushImages, waterImages, AINames;

    vector<Actor*> startActorPointers;
    vector<ActorInfo> startActors;

    // Check if quiet mode.
    if ( gMode == quiet )
        isQuiet = true;

    cout << "Game::Loading config.txt\n";

    //Seed random for random obstacle selection
    srand ( time ( 0 ) );

    // Load game field
    constants.push_back ( new GameFieldDrawable );

    if ( !fin )
        createConfig();

    fout.open ( "results.txt", ios::out | ios::in | ios::app );

    if ( !fout )
        cout << "UNABLE OPEN RESULTS FILE (results.txt).  Game will play but results will not be saved.\n";



    while ( !fin.eof() )
    {
        getline ( fin, configLine );

        if ( configLine[0] != '#' ) //Ignore comment lines
        {
            if ( configLine == "MAP" )
            {
                if ( height < 9 )
                {
                    hPad = ( 9 - height ) / 2;
                    height = 9;
                }

                if ( width < 15 )
                {
                    wPad = ( 15 - width ) / 2;
                    width = 15;
                }

                for ( y = 0; y < hPad; y++ )
                    for ( x = 0; x < width; x++ )
                        obstacleLocations.push_back ( pair<int, int> ( x, y ) );


                for ( ; y < height - hPad; y++ )
                {
                    getline ( fin, configLine );


                    for ( x = 0; x < width; x++ )
                    {
                        coordPair = pair<int, int> ( x, y );

                        if ( ( unsigned ) x >= configLine.size() + wPad )
                            obstacleLocations.push_back ( coordPair );

                        else if ( x < wPad )
                            obstacleLocations.push_back ( coordPair );

                        else
                        {
                            switch ( configLine[x - wPad] )
                            {
                                case 'B':
                                case 'b':
                                    bushLocations.push_back ( coordPair );
                                    break;

                                case 'R':
                                case 'r':
                                    rockLocations.push_back ( coordPair );
                                    break;

                                case 'T':
                                case 't':
                                    treeLocations.push_back ( coordPair );
                                    break;

                                case 'W':
                                case 'w':
                                    waterLocations.push_back ( coordPair );
                                    break;

                                case 'C':
                                case 'c':
                                    specialLocations.push_back ( coordPair );
                                    break;

                                case 'X':
                                case 'x':
                                case ' ':
                                    break;

                                default:
                                    obstacleLocations.push_back ( coordPair );
                                    break;
                            }
                        }
                    }
                }


                for ( ; y < height; y++ )
                    for ( x = 0; x < width; x++ )
                        obstacleLocations.push_back ( pair<int, int> ( x, y ) );
            }

            else
            {
                i = configLine.find ( ' ' ); //index of first space
                id = configLine.substr ( 0, i ); //Separate Identifier and Args
                args = configLine.substr ( i + 1 );


                //AI settings
                if ( id == "AI" ) //AI to load
                    loadAI ( isQuiet, AINames, args, tankLocations,
                             tankImages, wPad, hPad );

                //PI WILL CHANGE SPEED STUFF, DO NOT REFACTOR
                else if ( id == "AI_SPEED" )
                {
                    stringstream ( args ) >> aiSpeed;

                    if ( aiSpeed > 1500 )
                        aiSpeed = 1500;

                    else if ( aiSpeed < 1 )
                        aiSpeed = 1;

                    TimerEvent::idleSpeed = aiSpeed;
                    idleSpeed = aiSpeed;
                }

                else if ( id == "ANIMATION_SPEED" )
                {
                    stringstream ( args ) >> aniSpeed;

                    if ( aniSpeed > 30 )
                        aniSpeed = 30;

                    else if ( aniSpeed < 0 )
                        aniSpeed = 0;
                }

                else if ( id == "TANK_SPEED" )
                {
                    stringstream ( args ) >> tankSpeed;

                    if ( tankSpeed > 800 )
                        tankSpeed = 800;

                    else if ( tankSpeed < 0 )
                        tankSpeed = 0;
                }

                else if ( id == "BULLET_SPEED" )
                {
                    stringstream ( args ) >> bulletSpeed;

                    if ( bulletSpeed > 100 )
                        bulletSpeed = 100;

                    else if ( bulletSpeed < 0 )
                        bulletSpeed = 0;
                }

                //field params
                setFieldParams ( id, args, width, height, maxT, gameImages );

                if ( id == "DISABLEGUI" )
                    ui = false;

                loadObstacleLocations ( id, args, width, height, tankLocations,
                                        obstacleLocations,
                                        treeLocations, rockLocations, bushLocations, specialLocations,
                                        waterLocations, taken, isQuiet );

                loadImages ( id, args, gameImages, treeImages, rockImages, waterImages,
                             bushImages );

                //Tank params
                setTankParams ( id, args, damage, health, ap, radar, range, attributePoints,
                                ammo, width );
            }
        }
    }

    Drawable::xscalar = ( 3.75 / width ) / .32;
    Drawable::yscalar = Drawable::xscalar;

    fieldX = width;
    fieldY = height;

    glEnable ( GL_TEXTURE_2D );

    if ( !LoadGLTextures ( tankImages, gameImages, treeImages, rockImages,
                           bushImages, waterImages ) )
        if ( !isQuiet )
            cout << "Failed to open image(s).\n" << endl;

    glDisable ( GL_TEXTURE_2D );

    startActorPointers = dynamicTankLoader ( AINames );

    for ( i = 0; ( unsigned ) i < startActorPointers.size(); ++i )
        if ( tankLocations[i].first < width && tankLocations[i].first >= 0
                && tankLocations[i].second < height && tankLocations[i].second >= 0 )
        {
            startActors.push_back ( ActorInfo ( startActorPointers[i],
                                                health, damage, tankLocations[i].first,
                                                tankLocations[i].second, i + 1, ap, range,
                                                0, radar, ammo, AINames[i] ) );
        }


    tankGame = new GameField ( width, height, startActors, displayWrapper,
                               this );

    baseStats.tankHealth = health;
    baseStats.tankDamage = damage;
    baseStats.tankAP = ap;
    baseStats.tankAmmo = ammo;
    baseStats.tankRadar = radar;
    baseStats.tankRange = range;

    tankGame->setSPECIAL ( attributePoints, baseStats );

    // Add obstacles to the gamefield
    addGenericObstacles ( tankGame, obstacleLocations, tankLocations, tempOb );
    addCrates ( tankGame, specialLocations, tankLocations, temp );
    addTrees ( tankGame, treeLocations, tempOb );
    addRocks ( tankGame, tankLocations, rockLocations, tempOb );
    addBushes ( tankGame, bushLocations, tempOb );
    addWater ( tankGame, tankLocations, waterLocations, temp );


    if ( gMode == coverage )
    {
        cout << "Turning on coverage mode." << endl;
        idleSpeed = 1;
        aniSpeed = 1;
        tankSpeed = 1;
        bulletSpeed = 1;
    }
}

/***************************************************************************//**
 * @author Jon McKee
 * @brief createConfig
 * @par Description:
 * Creates new config file
 *
 *******************************************************************************/
void Game::createConfig()
{
    ofstream fout;

    cout << "FAILED TO LOAD CONFIG FILE\n";
    cout << "Attempting to generate config file...\n";

    fout.open ( "config.txt", ios::out | ios::in | ios::app );

    if ( !fout )
    {
        cout << "Unable to generate new config file.\n";
        exit ( 1 );
    }

    writeConfig ( fout );

    fout.close();

    cout << "   ...done.\n";
    cout << "Please add tanks to the new config.txt"
         << " and re-run the platform.\n";
}

/***************************************************************************//**
 * @author Team?
 * @brief closeDown
 * @par Description:
 * Prints out debugging info.
 *
 *******************************************************************************/
void Game::closeDown()
{
    cout << "Game::Closing game, cleaning up memory\n";
}

/***************************************************************************//**
 * @author Team?
 * @brief earlyOut
 * @par Description:
 * Allows exiting the game during playback with the ESC, Q, or q input
 *
 *******************************************************************************/
void Game::earlyOut()
{
    glutLeaveMainLoop();
}


void Game::addGenericObstacles ( GameField* playField,
                                 vector<pair<int, int>> obsLoc, vector<pair<int, int>> tankLoc,
                                 Obstacles* tempObj )
{
    bool taken = false;
    for ( auto o : obsLoc )
    {

        taken = false;
        for ( auto tank : tankLoc )
            if ( tank.first == o.first && tank.second == o.second )
                taken = true;

        if ( taken == false )
        {
            playField->addObstacle ( o.first, o.second );
            tempObj = new Obstacles ( 50, convertGLXCoordinate ( o.first ),
                                      convertGLYCoordinate ( o.second ), o.first, o.second );
            constants.push_back ( tempObj );
        }
    }
}

void Game::addCrates ( GameField* playField, vector<pair<int, int>> specLoc,
                       vector<pair<int, int>>tankLoc, Drawable* tempObj )
{
    bool taken = false;
    for ( auto c : specLoc )
    {
        taken = false;

        for ( auto tank : tankLoc )
            if ( tank.first == c.first && tank.second == c.second )
                taken = true;

        if ( taken == false )
        {
            tankGame->addObstacle ( c.first, c.second, 'C' );
            tempObj = new Crate ( convertGLXCoordinate ( c.first ),
                                  convertGLYCoordinate ( c.second ), c.first, c.second );
            specials.push_back ( tempObj );
        }
    }

}

void Game::addTrees ( GameField* playField, vector<pair<int, int>> treeLoc,
                      Obstacles* tempObj )
{
    for ( auto t : treeLoc )
    {
        playField->addObstacle ( t.first, t.second, 'T' );
        tempObj = new Obstacles ( 0, convertGLXCoordinate ( t.first ),
                                  convertGLYCoordinate ( t.second ), t.first, t.second );
        trees.push_back ( tempObj );
    }
}



void Game::addRocks ( GameField* playField, vector<pair<int, int>> tankLoc,
                      vector<pair<int, int>> rockLoc, Obstacles* tempObj )
{
    bool taken = false;
    for ( auto r : rockLoc )
    {
        taken = false;

        for ( auto tank : tankLoc )
            if ( tank.first == r.first && tank.second == r.second )
                taken = true;

        if ( taken == false )
        {
            playField->addObstacle ( r.first, r.second, 'R' ); //No driving over rocks
            tempObj = new Obstacles ( 1, convertGLXCoordinate ( r.first ),
                                      convertGLYCoordinate ( r.second ), r.first, r.second );
            rocks.push_back ( tempObj );
        }
    }
}



void Game::addBushes ( GameField* playField, vector<pair<int, int>> bushLoc,
                       Obstacles* tempObj )
{
    for ( auto b : bushLoc )
    {
        playField->addObstacle ( b.first, b.second, 'B' );
        tempObj = new Obstacles ( 2, convertGLXCoordinate ( b.first ),
                                  convertGLYCoordinate ( b.second ), b.first, b.second );
        bushes.push_back ( tempObj );
    }
}


void Game::addWater ( GameField* playField, vector<pair<int, int>> tankLoc,
                      vector<pair<int, int>> watLoc, Drawable* temp )
{
    bool taken = false;
    for ( auto w : watLoc )
    {
        taken = false;

        for ( auto tank : tankLoc )
            if ( tank.first == w.first && tank.second == w.second )
                taken = true;

        if ( taken == false )
        {
            playField->addObstacle ( w.first, w.second, 'W' );
            temp = new Obstacles ( 3, convertGLXCoordinate ( w.first ),
                                   convertGLYCoordinate ( w.second ), w.first, w.second );
            waters.push_back ( temp );
        }
    }
}
