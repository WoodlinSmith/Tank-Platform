/*! \file */
#include "ProjectileActor.h"


/**************************************************************************//**
 * @author Brad Peterson
 *
 * @par Description
 * Basic Constructor
 *
******************************************************************************/
ProjectileActor::ProjectileActor()
{

}


/**************************************************************************//**
 * @author Brad Peterson
 *
 * @par Description
 * This constructor will set the member values of ProjectileActor to passed in
 * values.
 *
******************************************************************************/
ProjectileActor::ProjectileActor ( direction d ) : dir ( d )
{

}


/**************************************************************************//**
 * @author Brad Peterson
 *
 * @par Description:
 *
******************************************************************************/
direction ProjectileActor::move ( MapData map, PositionData status )
{
    return dir;
}


/**************************************************************************//**
 * @author Brad Peterson
 *
 * @par Description
 * This function returns STAY for the direction the tank will move when it 
 * attacks.
 *
 * @param[in] map - the data for our current gamefield dimensions
 * @param[in[ status - the data containing actor position
 *
 * @returns STAY - enumerator to STAY in same position.
******************************************************************************/
direction ProjectileActor::attack ( MapData map, PositionData status )
{
    return STAY;
}


/**************************************************************************//**
 * @author Brad Peterson
 *
 * @par Description
 * Returns attributes of projectile
 *
 * @returns projAttributes - attributes of projectile
 *
******************************************************************************/
attributes ProjectileActor::setAttribute ( int pointsAvailable, attributes baseStats )
{
	// Projectiles have attributes, similar to tanks.
    attributes projAttributes;
    return projAttributes;
}


/**
 * @author David Donahue
 * @par Description
 * Returns decision to (0) end turn, (1) move, or (2) attack
 */
int ProjectileActor::spendAP ( MapData map, PositionData status )
{
	// AI do not spend AP, so returns 1.
	// Players would need to spend AP, so this function will be necessary when 
	// that functionality is added.
    return 1;
}
