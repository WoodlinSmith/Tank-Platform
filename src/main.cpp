/***************************************************************************//**
 * @file main.cpp
 *
 * @mainpage 'Capture the Flag' Tank Game
 *
 * @brief Main function for Capture the Flag
 *
 * @section Course Information
 *
 * @date Sept. 30 2018
 *
 * @par Professor: Dr Hinker
 *
 * @section Program Description
 *
 * @par Description
 *    'Capture the Flag' Tank game is built entirely with C++ using the GLUT
 *    libraries for graphics.
 *
 *    The Game is 'Battle Royale' style where AI tanks will fight until one tank
 *    remains. To create tanks for the game, users must provide a Dynamically
 *    Linked Library that inherits from the Actor class.
 *
 * @section Compile Section
 *
 * @par Build
 * @verbatim
 % make
 @endverbatim
 * @par Run
 * @verbatim
 % ./platform
@endverbatim
 *
 * @par Usage
 *
 *
 * @section To Do,  Bugs, and Mods
 *
 *
 * @par Revision History
 * @verbatim
https://gitlab.mcs.sdsmt.edu/7472586/Slackers_Platform
 @endverbatim
 ******************************************************************************/

// Includes
#include "util.h"
#include <memory>
#include <stdio.h>

// Main

int main ( int argc, char** argv )
{
    const char* dmode = "-demo";
    const char* qmode = "-quiet";
    const char* cmode = "-coverage";

    gameMode mode = ai;
    int height = 727, width = 1000;
    int counter = 1;

    //this is the start up of the game logic -at least 2 tanks need to be on the field at any given time
    while ( counter < argc )
    {
        //Getting the game mode
        if ( strcmp ( argv[counter], dmode ) == 0 && counter + 1 <= argc )
        {
            cout<<"demo mode"<<endl;
            width = 1900;
            height = 1000;
        }

        if ( strcmp ( argv[counter], qmode ) == 0 && counter + 1 <= argc )
        {
            cout<<"quiet mode"<<endl;
            mode = quiet;
        }

        if ( strcmp ( argv[counter], cmode ) == 0 && counter + 1 <= argc )
        {
            cout<<"coverage mode"<<endl;
            mode = coverage;
        }
        counter++;
    }

    initOpenGL ( argc, argv, width, height, mode );


    glutMainLoop();

    cout << "\n GAME OVER"<<endl;

    return 0;
}
