/***************************************************************************//**
* @file PongAI.cpp
* @brief Basic AI to play the game; simply moves back and forth around midpoint
* @author Chezka Gaddi 
* *****************************************************************************/

#include "PongAI.h"

/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Holds last move performed by the AI
*******************************************************************************/
PongAI::PongAI( void )
    :LastDir( STAY )
{
    // Tells the move function that we can go anywhere
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief Default Constructor, needed to satisfy compiler
*
*******************************************************************************/
PongAI::~PongAI( void )
{
    // Intentionally Left Empty
}

/***************************************************************************//**
* @author Chezka Gaddi
* @brief controls the movement of the PongAI's tank
*
* Move down to bottom of map, move back up to top, repeat
*
* @param MapData map of the field, including all obstacles
* @param PositionData contains the coordinates of this tank as well as ammo, etc
*******************************************************************************/
direction PongAI::move( MapData map, PositionData status )
{
    int yPos = status.game_y;


    direction retval = DOWN;
    if( yPos == 0 )
        retval = DOWN;
    else if( yPos == map.height - 1 )
        retval = UP;
    else if( LastDir == UP )
        retval = UP;
    else if( LastDir == DOWN )
        retval = DOWN;

    LastDir = retval;

    return retval;

}

/***************************************************************************//**
* @author Chezka Gaddi
* @brief Controls the PongAI's Attack function
*
* Checks if tank is on the left or right half of the map,
*  shoots to the opposite side of the map (straight left or right)
* @param MapData map of the field, including all obstacles
* @param PositionData contains the coordinates of this tank as well as ammo, etc
*******************************************************************************/
direction PongAI::attack( MapData map, PositionData status )
{
    int xPos = status.game_x;
    int median = map.width / 2;
    direction retval;

    if( xPos >= median )
        retval = LEFT;
    else
        retval = RIGHT;

    return retval;
}

/***************************************************************************//**
* @author Chezka Gaddi
* @brief reads in the remaining action points this tank has to use
*
* @param pointsAvailable passes in the number of action points this tank has
* @param attributes passes in the struct that stores the tanks attributes
* (health, damage, action points, shots, ammo, etc)
*******************************************************************************/
attributes PongAI::setAttribute( int pointsAvailable, attributes baseStats )
{
    attributes retval;

    retval.tankAP = pointsAvailable;

    return retval;
}

/***************************************************************************//**
* @author Chezka Gaddi
* @brief attacks only if one action point remains, otherwise moves
*
* @param MapData map of the field, including all obstacles
* @param PositionData contains the coordinates of this tank as well as ammo, etc
*******************************************************************************/
int PongAI::spendAP( MapData map, PositionData status )
{
    if( status.ap == 1 )
        return 2; // Attack
    else
        return 1; // Move
}



#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker( )
    {
        return new PongAI;
    }
}
#endif
