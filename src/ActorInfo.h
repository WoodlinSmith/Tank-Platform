/***********************************************************
 * @file
 *
 * @brief
 * This is the header file for the ActorInfo structure.
 * This structure will keep track of actors' stats so that 
 *  they are not modifiable by the players
 *
 ***********************************************************/

#ifndef __ACTOR_INFO_H
#define __ACTOR_INFO_H

#include "Actor.h"
#include "ProjectileActor.h"
#include <iostream>
#include <memory>

using namespace std;

/*! \struct ActorInfo
    \brief A structure containing Actor stats and info

    This structure will hold health, damage, x & y coordinates, id number, and range
*/
struct ActorInfo
{
    Actor *act_p;  /*!< The pointer to the constructed actor */
    int health = 0; /*!< The amount of health the Actor has remaining */
    int damage = 0; /*!< The amount of damage the Actor does */
    int x; /*!< The actors current X position */
    int y; /*!< The actors current Y position */
    int prevx = -1; /*!< The previous X component for the actor (Used in animation) */
    int prevy = -1; /*!< The previous Y component for the actor (Used in animation) */
    int id = 0; /*!< The Actors ID number */
    int AP = 0; /*!< The number of Action points for the Actor */
    int range = 0; /*!< The range of the Actor */
    int hits = 0; /*!< The total number of hits made by the Actor */
    int shots = 0; /*!< The total number of shots made by the Actor */
    attributes tankAttributes; /*!< The actors attribute structure */
    int radar = 0; /*!< The size of the Actors radar (How far it can see away from itself) */
    int max_health = 0; /*!< The max health for this actor*/
    int ammo = 0; /*!< The current ammo the actor has available*/
    int max_ammo = 0; /*!< The max number of ammo for this actor */
    int cDetect = 0; /*!< number of actions the actor has not moved */
    bool camp = false; /*!< Flag for checking if the actor is considered camping */
    bool sMod = false; /*!< Modular flag for smoke/fire trails */
    float scale = 1; /*!< */
    float offsetx = 0; /*!< The stored x offset for drawing the actor */
    float offsety = 0; /*!< The stored y offset for drawing the actor */
    string name = "default\n"; /*!< The actors stored name */
    int kills = 0; /*!< The number of kills the actor has made */
    direction heading; /*!< The actors heading*/
    //Default constructor for structure
    ActorInfo(Actor *a
              , int h  //Health
              , int d  //Damage
              , int xpos //x
              , int ypos //y
              , int i    //id
              , int ap = 1 //Action points
              , int r = 0 //Range
              , int s = 0 //Shots
              , int v = 0 //Radar
              , int b = 1 //ammo
              , std::string n = "default") 
                   : act_p(a), health(h), damage(d), x(xpos), y(ypos), id(i), 
                   AP(ap), range(r), hits(0), shots(s), tankAttributes(), 
                   radar(v), max_health(h), ammo(b), max_ammo(b), name(n), 
                   kills(0), heading(RIGHT){} 
                   /*!< Constructor with options to set. */
    
    ActorInfo() : act_p(NULL), health(0), damage(0), x(0), y(0), id(0), 
    range(0), hits(0), shots(0), max_health(0), ammo(0), max_ammo(0), 
    heading(RIGHT){} 
    /*!< Constructor with no options set (default construcor) */
};

bool operator==(const ActorInfo& lhs, const ActorInfo& rhs);
/*!< Overloaded comparison operator */

#endif