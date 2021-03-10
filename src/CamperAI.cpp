/**************************************************************************//**
 * @file
 * @brief
 *****************************************************************************/

#include "CamperAI.h"

/*************************************************************************//**
 * @author
 * @par Description: Constructor 
 * 
 ****************************************************************************/

CamperAI::CamperAI(void)
{
    // Tells the move function that we can go anywhere
}

/*************************************************************************//**
 * @author
 * @par Description: Destructor 
 *    
 ****************************************************************************/

CamperAI::~CamperAI(void)
{

}

/*************************************************************************//**
 * @author
 * @brief Decides where to move in order to camp according to the current   
 *		  position of the tank and obstacles in the map. 
 * 
 * @param[in] map - map of the field. 
 * @param[in] status - Current position coordinates and status of the tank. 
 * 
 * @returns retVal - Direction in which the tank moves.
 ****************************************************************************/

direction CamperAI::move(MapData map, PositionData status)
{
    int xPos = status.game_x;
    int yPos = status.game_y;
    int median = map.height / 2;
    int median2 = map.width / 2;
    bool UP = false, DOWN = false, LEFT = false, RIGHT = false;

    direction retVal = STAY;

    if((yPos == 0 && xPos == 0) ||
            (yPos == map.height - 1 && xPos == 0) ||
            (xPos == map.width - 1 && yPos == 0) ||
            (xPos == map.width - 1 && yPos == map.height - 1) ||
            (corner == true))
        return retVal;

    if(yPos <= median && yPos - 1 >= 0
            && (map.obstacleMap[xPos + ((yPos-1)*map.width)] == 0 ||
                map.obstacleMap[xPos + ((yPos-1)*map.width)] == 'T' ||
                map.obstacleMap[xPos + ((yPos-1)*map.width)] == 'B'))
        UP = true;

    if(yPos > median && (yPos + 1 <= map.height - 1)
            && (map.obstacleMap[xPos + ((yPos+1)*map.width)] == 0 ||
                map.obstacleMap[xPos + ((yPos+1)*map.width)] == 'T' ||
                map.obstacleMap[xPos + ((yPos+1)*map.width)] == 'B'))
        DOWN = true;

    if(xPos > median2 && (xPos + 1 <= map.width - 1)
            && (map.obstacleMap[(xPos + 1) + (yPos*map.width)] == 0 ||
                map.obstacleMap[(xPos + 1) + (yPos*map.width)] == 'T' ||
                map.obstacleMap[(xPos + 1) + (yPos*map.width)] == 'B'))
        RIGHT = true;

    if(xPos <= median2 && (xPos - 1 >= 0)
            && (map.obstacleMap[(xPos - 1) + (yPos*map.width)] == 0 ||
                map.obstacleMap[(xPos - 1) + (yPos*map.width)] == 'T' ||
                map.obstacleMap[(xPos - 1) + (yPos*map.width)] == 'B'))
        LEFT = true;

    if (!UP && !DOWN && !RIGHT && !LEFT) 
    {
        retVal = STAY;
        corner = true;
    }
    else if (UP && LEFT)
        retVal = direction::UPLEFT;
    else if (UP && RIGHT)
        retVal = direction::UPRIGHT;
    else if (UP)
        retVal = direction::UP;
    else if (DOWN && LEFT)
        retVal = direction::DOWNLEFT;
    else if (DOWN && RIGHT)
        retVal = direction::DOWNRIGHT;
    else if (DOWN)
        retVal = direction::DOWN;
    else if (LEFT)
        retVal = direction::LEFT;
    else if (RIGHT)
        retVal = direction::RIGHT;
    return retVal;
}

/*************************************************************************//**
 * @author
 * @brief Decides direction in which the tank should attack based on which
 *	  quadrant it lies in.
 * 
 * @param[in] map - Map of the field.     
 * @param[in] status - Current position coordinates and status of the tank. 
 * 
 * @returns retVal - The direction of attack.
 ****************************************************************************/

direction CamperAI::attack(MapData map, PositionData status)
{
    int yPos = status.game_y;
    int xPos = status.game_x;
    int hMedian = map.height / 2;
    int wMedian = map.width / 2;
    direction retVal;

    if(yPos >= hMedian && xPos <= wMedian)
    {
        switch (attacks[turn])
        {
        case 1:
            retVal = UPRIGHT;
            break;
        case 2:
            retVal = RIGHT;
            break;
        default:
            retVal = UP;
            break;
        }
    }

    else if(yPos < hMedian && xPos <= wMedian)
    {
        switch (attacks[turn])
        {
        case 1:
            retVal = DOWNRIGHT;
            break;
        case 2:
            retVal = RIGHT;
            break;
        default:
            retVal = DOWN;
            break;
        }
    }

    else if(yPos >= hMedian && xPos > wMedian)
    {
        switch (attacks[turn])
        {
        case 1:
            retVal = UPLEFT;
            break;
        case 2:
            retVal = LEFT;
            break;
        default:
            retVal = UP;
            break;
        }
    }

    else if(yPos < hMedian && xPos > wMedian)
    {
        switch (attacks[turn])
        {
        case 1:
            retVal = DOWNLEFT;
            break;
        case 2:
            retVal = LEFT;
            break;
        default:
            retVal = DOWN;
            break;
        }
    }

    return retVal;
}

/*************************************************************************//**
 * @author
 * @brief Sets health of the tank to the points available. 
 *  
 ****************************************************************************/

attributes CamperAI::setAttribute(int pointsAvailable, attributes baseStats)
{
    attributes retVal;

    retVal.tankHealth = pointsAvailable;

    return retVal;
}

/*************************************************************************//**
 * @author
 * @brief Randomly fills the six chances to attack with one of the three 
 *	  options available. Else turns if it exhausts its chances.  
 * 
 * @param[in] map - Map of the field.      
 * @param[in] status - Position coordinates and status of the tank.
 * 
 * @returns 1 If the tank moves. 
 * @return 2 If the tank stays and attacks.
 ****************************************************************************/

int CamperAI::spendAP(MapData map, PositionData status)
{
    if (maxAp == 0)
        maxAp = status.ap;
//Debugging map output
    
    if (maxAp == status.ap) 
    {
        turn = 0;
        for (int i = 0; i < 6; i++)
            attacks[i] = rand() % 3;
    }

    else
        turn++;

    if (move(map, status) != STAY)
        return 1;

    return 2; // Attack
}


#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new CamperAI;
    }
}
#endif
