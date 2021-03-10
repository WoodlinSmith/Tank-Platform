/***************************************************************************//**
* @file util.cpp
* @author Chezka Gaddi
* @brief Contains all functions manage event creations.
*******************************************************************************/
#include "util.h"


/***************************************************************************//**
* @author Chezka Gaddi
* @brief utilityCentral
*
* Creates the game manager and manages events to their associated functions
*******************************************************************************/
void utilityCentral ( gameMode mode, Event* event )
{
    static gameMode gMode = none;
    if ( gMode == none )
    {
        if ( mode == none )
            gMode = ai;
        else
            gMode = mode;
    }
    static Game gameloop ( gMode );

    event->doAction ( gameloop );

    delete event;
}

/***************************************************************************//**
* @author Chezka Gaddi
* @brief initOpenGL
*
* Initialize glut callback functions, set the display mode, create a window.
*
* @param[in] argc - number of command line arguments
* @param[in] argc - pointer to the list of command line arguments
* @param[in] wCols - width of the window
* @param[in] wRows - height of the window
* @param[in] mode - game mode
*******************************************************************************/
void initOpenGL ( int argc, char** argv, int wCols, int wRows, gameMode mode )
{
    glutInit ( &argc, argv );

    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

    glutSetOption ( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION );

    glutInitWindowSize ( wCols, wRows );

    glutInitWindowPosition ( 10, 10 );

    glutCreateWindow ( "Tank Topple" );

    glutSetIconTitle ( "images/icon.png" );

    glutDisplayFunc ( display );

    glShadeModel ( GL_SMOOTH );

    glutReshapeFunc ( reshape );

    glutKeyboardFunc ( keyboard );

    glutTimerFunc ( 750, ticktock, 750 );

    glutCloseFunc ( onClose );

    glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

    glClearDepth ( 1.0f );

    glEnable ( GL_DEPTH_TEST );

    glDepthFunc ( GL_LEQUAL );

    glHint ( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    utilityCentral ( mode, new InitEvent ( wCols, wRows ) );
}
