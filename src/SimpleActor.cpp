#include "SimpleActor.h"

/**
 * @author David Donahue
 * @par Description:
 * returns the direction selected at construction
 *
 * @param[in] map - MapData with the current game map
 * @param[in] status - information about the current actor including position and ID
 */
direction SimpleActor::move(MapData map, PositionData status)
{
    return dir;
}

/**
 * @author David Donahue
 * @par Description:
 * Attacks 0,0 with the damage set at construction
 *
 * @param[in] map - MapData with the current game map
 * @param[in] status - information about the current actor including position and ID
 */
direction SimpleActor::attack(MapData map, PositionData status)
{
    return atk;
}

/**
 * @author David Donahue
 * @par Description:
 * Default constructor, sets default move to up and attack to 0,0
 */
SimpleActor::SimpleActor()
{
    atk=STAY;
    dir=UP;
}

/**
 * @author David Donahue
 * @par Description:
 * Constructor with desired direction and damage to attack 0,0 with
 *
 * @param[in] mv : the desired default move
 * @param[in] d : the desired attack direction
 */
SimpleActor::SimpleActor(direction mv, direction d)
{
    atk=d;
    dir=mv;
}

/**
 * @author David Donahue
 * @par Description:
 * Set the desired point and damage to return on attack()
 *
 * @param[in] x - x coordinate to attack
 * @param[in] y - y coordinate to attack
 * @param[in] d - damage of the projectile
 */
void SimpleActor::setAttack(direction d)
{
    atk = d;
}

/**
 * @author David Donahue
 * @par Description:
 * Set the desired direction to move on the next turn
 *
 * @param[in] d - direction to move
 */
void SimpleActor::setMove(direction d)
{
    dir = d;
}

/**
 * @author Youki Lewis
 * @par Description:
 * Sets the attributes for the tanks decided by the AI
 *
 * @parm[in] pointsAvailable - available points for distribution
 */
attributes SimpleActor::setAttribute(int pointsAvailable, attributes baseStats)
{
    attributes tankAttributes;
    int basicDistribution = pointsAvailable / 4;

    tankAttributes.tankHealth = basicDistribution;
    tankAttributes.tankDamage = basicDistribution;
    tankAttributes.tankAP = basicDistribution;
    tankAttributes.tankShots = basicDistribution;

    return tankAttributes;
}

int SimpleActor::spendAP(MapData map, PositionData status)
{
    return (status.ap > 1) ? 1 : 2;
}

#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new SimpleActor;
    }
}
#endif
