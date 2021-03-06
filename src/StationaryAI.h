#ifndef __STATIONARY_AI_H
#define __STATIONARY_AI_H

#include "Actor.h"
#include <cmath>
#include <iostream>

/************************//*
 * @author Jon McKee
 * @class StationaryAI that does nothing but sits where placed
 **************************/
class StationaryAI : public Actor
{
        // The direction moved from last turn
        direction LastDir;
    public:
        // The Overwritten Move function.
        virtual direction move ( MapData map, PositionData status );

        // The Overwritten attack function.
        virtual direction attack ( MapData map, PositionData status );

        // The Overwritten set attribute  function.
        virtual attributes setAttribute ( int pointsAvailable, attributes baseStats );

        // The Overwritten spendAP  function.
        virtual int spendAP ( MapData map, PositionData status );

        StationaryAI();
        ~StationaryAI();

    protected:
        int turn = 0;
        int maxAp = 0;
};

#endif
