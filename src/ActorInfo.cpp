/**************************************************************************//**
* @file
*
* @brief The source code for the ActorInfo class
*
******************************************************************************/

#include "ActorInfo.h"

/*******************************************************************//**
 * @author David Donahue
 *
 * @par Description:
 * This is the overload function for '==' operator.
 *
 **********************************************************************/

bool operator==(const ActorInfo& lhs, const ActorInfo& rhs)
{
    return (lhs.act_p == rhs.act_p && lhs.health == rhs.health && 
    		lhs.damage == rhs.damage &&lhs.x == rhs.x && lhs.y == rhs.y && 
    		lhs.id == rhs.id && lhs.range == rhs.range && 
    		lhs.hits == rhs.hits && lhs.shots == rhs.shots);
}
