#ifndef __ATTACKDOWN_AI_H
#define __ATTACKDOWN_AI_H

/*******************************************************************//**
 * @file
 *
 * @brief Description:
 * The function prototypes for the Attack Down AI tank.
 *
 **********************************************************************/

#include "Actor.h"
#include "direction.h"
#include <cmath>

/*! @class AttackDownAI
    @brief description
    This class outlines the function prototypes for the AttackDownAI class.
*/
class AttackDownAI : public Actor
{
    public:
        // The Overwritten Move function.
        virtual direction move ( MapData map, PositionData status ); /*!< Overwritten version of the move function */

        // The Overwritten attack function.
        virtual direction attack ( MapData map, PositionData status ); /*!< Overwritten version of the attack function */

        // The Overwritten set attribute  function.
        virtual attributes setAttribute ( int pointsAvailable, attributes baseStats ); /*< Overwritten version of the setAttribute function */

        // The Overwritten spendAP  function.
        virtual int spendAP ( MapData map, PositionData status ); /*< Overwritten version of the spendAP function */

        AttackDownAI(); /*< AttackDownAI Constructor */
        ~AttackDownAI(); /*< AttackDownAI Deconstructor */

};

#endif
