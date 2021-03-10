/**
 * SimpleActor.h
 * a simple actor class with an 'AI' of:
 *   -Move up
 *   -Attack 0,0
 */

#ifndef __SIMPLE_ACTOR_H
#define __SIMPLE_ACTOR_H

#include "Actor.h"
#include <iostream>

class SimpleActor : public Actor
{
    direction dir;
    direction atk;
    
    public:
        virtual direction move(MapData map, PositionData status);
        virtual direction attack(MapData map, PositionData status);
        virtual attributes setAttribute(int pointsAvailable, attributes baseStats);
        virtual int spendAP(MapData map, PositionData status);

        SimpleActor();
        SimpleActor(direction mv, direction d);

        void setAttack(direction d);
        void setMove  (direction d);
};

#endif
