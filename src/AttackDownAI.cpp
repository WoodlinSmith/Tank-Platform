#include "AttackDownAI.h"
/*******************************************************************//**
 * @file
 *
 * @brief Description:
 * The source code for the Attack Down AI tank.
 *
 **********************************************************************/

/*******************************************************************//**
 * @author Jon McKee
 *
 * @par Description:
 * This is the constructor for the AttackDownAI
 *
 **********************************************************************/
AttackDownAI::AttackDownAI ( void )
{
    // Tells the move function that we can go anywhere
}

/*******************************************************************//**
 * @author Jon McKee
 *
 * @par Description:
 * This is the deconstructor for the AttackDownAI
 *
 **********************************************************************/
AttackDownAI::~AttackDownAI ( void )
{

}

/*******************************************************************//**
 * @author Jon McKee
 *
 * @par Description:
 * This is the move function for the AttackDownAI.  The AttackDownAI
 * does not move, so this function always returns stay.
 *
 **********************************************************************/
direction AttackDownAI::move ( MapData map, PositionData status )
{
    direction retval = STAY;
    return retval;
}

/*******************************************************************//**
 * @author Jon McKee
 *
 * @par Description:
 * This is the attack function for the AttackDownAI.  It only returns DOWN
 *
 **********************************************************************/
direction AttackDownAI::attack ( MapData map, PositionData status )
{
    direction retval;
    retval = DOWN;

    return retval;
}

/*******************************************************************//**
 * @author Jon McKee
 *
 * @par Description:
 * This is the setAttributes for the AttackDownAI.  It currently only
 * adds to the AP of the tank.
 *
 **********************************************************************/
attributes AttackDownAI::setAttribute ( int pointsAvailable, attributes baseStats )
{
    attributes retval;
    retval.tankAP = pointsAvailable;

    return retval;
}

/*******************************************************************//**
 * @author Jon McKee
 *
 * @par Description:
 * This is the spendAP function for the AttackDownAI.  It only returns a
 * 2 for attack.
 *
 **********************************************************************/
int AttackDownAI::spendAP ( MapData map, PositionData status )
{
    return 2; // Attack
}


#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor* maker()
    {
        return new AttackDownAI;
    }
}
#endif
