/**
 * @file GameField.cpp
 * @author David Donahue
 */

#include "event.h"
#include "GameField.h"

/**
 * @author David Donahue
 * @par Description:
 * Default constructor, makes a 10x10 empty map
 */
GameField::GameField() : ap(2)
{
    turnCount = 0;
    fieldMap.width = 10;
    fieldMap.height = 10;
    fieldMap.map.resize(100);
    fieldMap.obstacleMap.resize(100);
    fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), 0);
    displayCallback = NULL;
}

/**
 * @author David Donahue
 * @par Description:
 * Destructor, deletes all actors left on the feild
 */
GameField::~GameField()
{
    for( auto &a : actors )
    {
        if( a.act_p != NULL )
            delete a.act_p;
    }
}

/**
 * @author David Donahue
 * @par Description:
 * Constructs game field with given dimensions
 */
GameField::GameField( int width, int height ) : ap(2)
{
    //Turn = 0 and map dimensions are set to passed in arguments
    turnCount = 0;
    fieldMap.width = width;
    fieldMap.height = height;

    //Resize map accordingly
    fieldMap.map.resize(width * height);
    fieldMap.obstacleMap.resize(width * height);

    //Fill map with obstacles
    fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
    displayCallback = NULL;
}

/**
 * @author David Donahue
 * @par Description:
 * Constructor with dimensions and a vector of ActorInfo
 */
GameField::GameField( int width, int height, vector<ActorInfo> acts ) :
    actors(acts), ap(2)
{
    //Turn = 0 and map dimensions are set to passed in arguments
    turnCount = 0;
    fieldMap.width = width;
    fieldMap.height = height;

    //Resize map accordingly
    fieldMap.map.resize(width * height);
    fieldMap.obstacleMap.resize(width * height);

    //Fill map with obstacles
    fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
    updateMap();
    displayCallback = NULL;
}

/**
 * @author Riley Kopp
 * @par Description:
 * Constructor with dimensions and a vector of ActorInfo, and action points
 */
GameField::GameField(int width, int height, vector<ActorInfo> acts
, int actionpoints) : actors(acts), ap(actionpoints)
{
    //Turn = 0 and map dimensions are set to passed in arguments
    turnCount = 0;
    fieldMap.width = width;
    fieldMap.height = height;

    //Resize map accordingly
    fieldMap.map.resize(width * height);
    fieldMap.obstacleMap.resize(width * height);

    //Fill map with obstacles
    fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
    updateMap();
    displayCallback = NULL;
}

GameField::GameField(int width, int height, vector<ActorInfo>
                     startActors, void (*d_callback)(MapData, vector<ActorInfo>, int)) :
    actors(startActors), ap(2)
{
    //Turn = 0 and map dimensions are set to passed in arguments
    turnCount = 0;
    fieldMap.width = width;
    fieldMap.height = height;

    //Resize map accordingly
    fieldMap.map.resize(width * height);
    fieldMap.obstacleMap.resize(width * height);

    //Fill map with obstacles
    fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
    updateMap();
    displayCallback = d_callback;
}

GameField::GameField(int width, int height, vector<ActorInfo>
                     startActors, void (*d_callback)(MapData, vector<ActorInfo>, int),
                     Game *game) : actors(startActors), ap(2)
{
    //Turn = 0 and map dimensions are set to passed in arguments
    turnCount = 0;
    fieldMap.width = width;
    fieldMap.height = height;

    //Resize map accordingly
    fieldMap.map.resize(width * height);
    fieldMap.obstacleMap.resize(width * height);

    //Fill map with obstacles
    fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);

    //Updates x and y scalar values
    x_scalar = 4.0717*pow(width, -1.031);
    y_scalar = 3.1923*pow(height, -1.08);

    updateMap();
    displayCallback = d_callback;
    gameptr = game;
}

GameField::GameField(int width, int height, vector<ActorInfo>
                     startActors, void (*d_callback)(MapData, vector<ActorInfo>, int), int
                     AP) : actors(startActors), ap(AP)
{
    //Turn = 0 and map dimensions are set to passed in arguments
    turnCount = 0;
    fieldMap.width = width;
    fieldMap.height = height;

    //Resize map accordingly
    fieldMap.map.resize(width * height);
    fieldMap.obstacleMap.resize(width * height);

    //Fill map with obstacles
    fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
    updateMap();
    displayCallback = d_callback;
}


/**
 * @author David Donahue
 * @par Description:
 * Gets the number of turns that have elapsed
 */
int GameField::getTurnCount()
{
    return turnCount;
}

/**
 * @author David Donahue
 * @par Description:
 * Gets the width of the field
 */
int GameField::getWidth()
{
    return fieldMap.width;
}

/**
 * @author David Donahue
 * @par Description:
 * Gets the height of the field
 */
int GameField::getHeight()
{
    return fieldMap.height;
}

/**
 * @author David Donahue
 * @par Description:
 * Gets just the map as a vector of ints
 */
vector<int> GameField::getMap()
{
    return fieldMap.map;
}

/**
 * @author David Donahue
 * @par Description:
 * Update the map with the current postions of all actors
 */
void GameField::updateMap()
{
    //Erase the map
    fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    for( auto a : actors )
    {
        //For each actor fill in its id on the map
        if( a.health > 0 )
            fieldMap.map[a.x+ fieldMap.width * a.y] = a.id;
    }

}

/***************************************************************************//**
 * @brief
 * Prompts the actors to choose attributes to specialize int
 * @author Riley Kopp
 ******************************************************************************/
void GameField::setSPECIAL( int points, const attributes baseStats )
{
    int sum = 0;

    for( auto &actor: actors )
    {
        //Set tank attribute points
        actor.tankAttributes = actor.act_p->setAttribute(points, baseStats);

        //Set sum equal to tank's total number of attributes
        sum = actor.tankAttributes.tankHealth + actor.tankAttributes.tankAP;
        sum += actor.tankAttributes.tankRadar + actor.tankAttributes.tankDamage;
        sum += actor.tankAttributes.tankAmmo + actor.tankAttributes.tankRange;

        //Check that user did not use more than the points allowed
        if( sum  <= points )
        {
            //Update tank attributes
            actor.health += actor.tankAttributes.tankHealth;
            actor.AP += actor.tankAttributes.tankAP;
            actor.radar += actor.tankAttributes.tankRadar;
            actor.damage += actor.tankAttributes.tankDamage;
            actor.ammo += actor.tankAttributes.tankAmmo;
            actor.range += actor.tankAttributes.tankRange;

            //Check that no tank attribute goes beyond specified values
           checkAllAttributes(actor.health,actor.AP,actor.radar,actor.damage,
                            actor.ammo,actor.range,getWidth());
        }

        else
            fixTankAttributes(actor.health,actor.AP,actor.radar,
                            actor.damage,actor.ammo,actor.range,getWidth());
    }
}

/*********************************************************************//*
 * @author Jon McKee, Riley Campbell
 * @brief This function creates the animation effect for the object
 * passed into it. The function works by checking the previous X and Y
 * values of the actor and then continuously redrawing the object specified
 * by the number of samples in the animation speed game option.  Once the
 * draw is complete the object will be at it's new position with the new
 * location saved as the previous location for the next animation call.
 *
 * During this functions call the idletime is temporarily set to 0 and
 * reset back to the game setting at the end of the function.
 *
************************************************************************/
void GameField::animateMove( ActorInfo &a )
{
    //If so, then we didn't actually move
    if( (a.x == a.prevx && a.y == a.prevy) || a.prevx == -1 || a.prevy == -1 )
        return;

    //Set previous and next x and y values to our tank values
    int px = a.prevx;
    int py = a.prevy;
    int nx = a.x;
    int ny = a.y;

    //If we're testing default to 1 sample
    int samples = 1;

    GLfloat tempx, tempy;
    GLfloat prevx, prevy;

    //If we end up here while running catch tests, block out the invalid pointer
    //(Other errors will occur)
    if (gameptr != nullptr)
    {
        samples = gameptr->getAniSpeed();

        //Check if we need speed for a tank or projectile
        if ( a.id < 0 )
            TimerEvent::idleSpeed = gameptr->getbullet_speed();
        else
            TimerEvent::idleSpeed = gameptr->gettank_speed();
    }

    //moving up, down, or diagonal
    if( a.heading != STAY && a.heading != RIGHT && a.heading != LEFT )
    {
        //Moving up, down, or diagonal
        //Smaller
        tempy = -1.75 - ( ny * y_scalar );
        //Bigger
        prevy = -1.75 - ( py * y_scalar );
        //Scaler
        tempy = (prevy - tempy);
        //Scale it
        tempy = tempy / samples;
    }

    ///moving left, right, or diagonal
    if( a.heading != STAY && a.heading != DOWN && a.heading != UP)
    {
       //Smaller
       tempx = .75 - ( nx * x_scalar );
       //Bigger
       prevx = .75 - ( px * x_scalar );
       //Scaler
       tempx = -( prevx - tempx );
       //Scale it
       tempx = tempx / samples;
    }
    //Display the movement
    for( int i = 1; i < samples; i++ )
    {
       if( a.heading != STAY && a.heading != LEFT && a.heading != RIGHT )
          a.offsety = tempy * ( samples - i );
       if( a.heading != STAY && a.heading != UP && a.heading != DOWN )
          a.offsetx = tempx * ( samples - i );
       if( gameptr != nullptr )
          displayCallback( fieldMap, actors, gameptr->turn );
    }

    //Reset value
    a.offsety = a.offsetx = 0;

    //Save new previous values
    a.prevx = a.x;
    a.prevy = a.y;

    //Skip during testing
    if (gameptr != nullptr)
       TimerEvent::idleSpeed = gameptr->getAISpeed(); //Fix idle speed
}

/**
 * @author David Donahue
 * @author Jon McKee (Heavily Modified by)
 * @par Description:
 * Executes the move phase of an AI's turn and then AI's are culled
 */
void GameField::runMoves( ActorInfo &a, MapData &fog, PositionData &pos )
{

    int i, xoff = 0, yoff = 0, tHealth = 0, hit = 0;
    bool hitObj = false, redraw = false;
    direction dir;

    //Get the AI's desired move
    dir = a.act_p->move( fog, pos );
    //Not the best move if we chose to stay
    a.heading = ( dir == STAY ) ? a.heading : dir;

    //If it checks out, execute it
    //If the actor hits a wall or obstacle, do not execute the move and deal 1 damage
    //We aren't playing this game with dead actors anymore
    if( a.health <= 0 || a.id == 0 || dir == STAY )
        return;

    //Store prev coordinates
    a.prevx = a.x;
    a.prevy = a.y;

    //Try and move
    checkMoves(a.x,a.y,xoff,yoff,a.health,dir);

    //Set our new positions
    a.x += xoff;
    a.y += yoff;


    //Check if our projectile hit a non-actor
    hitObj = checkObjectStrike(a);

    //Check if we're a tank that hit a rock or water
    if(a.id > 0 && (obstacleAt(a.x, a.y) == 'R' || obstacleAt(a.x, a.y) == 'W'))
    {
        a.x -= xoff;
        a.y -= yoff;

        //Allows us to skip the rest of the checking if we ran into a rock or water
        hitObj = true;
        //Allows us to skip animation
        redraw = true;

        a.health--;
    }

    //Run the main loop through actors to see if we hit one
    if( a.health > 0 && hitObj == false && ( xoff != 0 || yoff != 0 ) )
    {
        if ( a.id > 0 )
        {
            a.cDetect = 0;
            a.camp = false;
        }

        //Check each actor
        for( i = 0; (unsigned)i < actors.size(); ++i )
        {
            if( a.id < 0 && actors[i].id == -a.id )
                a.camp = actors[i].camp;

            if( a.health > 0 && actors[i].health > 0   //Make sure neither is dead
                    && actors[i].x == a.x    //Make sure we're on the same column
                    && actors[i].y == a.y    //Make sure we're on the same row
                    && a.id != actors[i].id ) //Make sure our tank doesn't damage itself
            {
                //Check tank to tank ramming
                if( a.id > 0 && actors[i].id > 0 )
                {
                    //Reverse the move
                    a.x -= xoff;
                    a.y -= yoff;

                    //Store target tanks health
                    tHealth = actors[i].health;
                    //Deal our full health damage to target
                    actors[i].health -= a.health;

                    //Logic for ramming
                    if(a.health == 1)
                        //Tank kills self
                        hit += a.health;
                    
                    else if(tHealth >= a.health)
                        //Prevent tank's death (at least from ramming)
                        hit += a.health - 1;
                    

                    //Otherwise take damage as normal
                    else
                        //Tank survives
                        hit += tHealth;
                    

                    //A tank hit is still a hit right?
                    a.hits++;

                    if(checkHealth(actors[i]))
                        a.kills++;
                    //This is the end of the road for this move, don't animate
                    redraw = true;
                }

                //Check if we ran into a projectile (What we are doesn't matter)
                else if( actors[i].id < 0 )
                {
                    //Store future damage
                    hit += actors[i].damage;

                    //Destroy the projectile
                    actors[i].health = 0;

                    //Give the owner a hit, but not a self hit and not a missile to missle hit
                    if( a.id > 0 && -actors[i].id != a.id )
                    {
                        actorInfoById(-actors[i].id).hits++;

                        //Give the owner a kill if we suicided
                        if ( a.health -= hit <= 0 )
                            actorInfoById( -actors[i].id != a.id );
                    }

                    //We hit something, don't animate more
                    redraw = true;
                }

                //If we're a projectile and we hit a tank (Do not allow self hit)
                else if( a.id < 0 && a.id != -actors[i].id )
                {
                    //Damage the tank
                    actors[i].health -= a.damage;

                    //Should be enough to kill us
                    hit += a.health + 1;

                    //No self hits which shouldn't be possible
                    //Give our owner a hit
                    if(a.id != -actors[i].id)
                        actorInfoById(-a.id).hits++;

                    //Get a kill
                    if( checkHealth(actors[i]) )
                        actorInfoById(-a.id).kills++;

                    redraw = true;
                }
            }
        }
    }

    a.health -= hit;
    checkHealth(a, hitObj);

    //Skip animating if we're not displaying the game
    if ( gameptr != nullptr )
    {
        //If we didn't hit an object and we don't need to force a redraw (Does not update map)
        if( !redraw && !hitObj )
            animateMove(a);

        //If either condition is true, animate
        else
        {
            animateMove(a);

            //Update actors and map
            updateMap();

            //Redraw screen
            if (gameptr != nullptr)
                displayCallback(fieldMap, actors, gameptr->turn);

            //Clear the explosions
            SFX.clear();
        }
    }

}

/***********************************************************************//*
 * @author Jon McKee
 *
 * @brief Checks to see if the current object was killed or hit an object.
 * If the actor's health is less than or equal to 0 we 0 zero out its stats.
 * If the actor was a projectile and struck on object, we set it's health
 * equal to 0 and zero out the rest of it's stats.
 *
 *************************************************************************/
bool GameField::checkHealth( ActorInfo &a, bool object )
{
    //If whatever we have has no health left
    if( a.health <= 0 )
    {
        SFX.push_back(make_pair(a.x, a.y));

        a.damage = 0;
        a.id = 0;
        a.health = 0;
        a.AP = 0;
        return true;
    }

    //If our projectile impacted on an object
    else if( a.id < 0 && object )
    {
        SFX.push_back(make_pair(a.x, a.y));

        a.damage = 0;
        a.id = 0;
        a.health = 0;
        a.AP = 0;
        return true;
    }

    return false;
}

/****************************************************************************//*
 * @author Jon McKee
 * @brief Check to see if the current projectile hit an object. If the curent
 * actor is not a projectile immediately.  If the current actor is a projectile
 * we check the various object lists to see if we struck one and then return the
 * appropriate flag.
 *
 ******************************************************************************/
bool GameField::checkObjectStrike(ActorInfo &a)
{
    int tempOb = obstacleAt(a.x, a.y);
    int i, hits = 0;

    //Get the non projectiles back out of here
    if( a.id > 0 || a.health < 0 )
        return false;

    //If the spot is empty then we couldn't have hit anything
    if(tempOb == 0)
        return false;

    //We hit a bush; bushes don't stop bullets
    //We technically dont need this now since bushes don't do anything, but we can make them destroyable later?
    else if(tempOb == 'B' || tempOb == 'W')
        return false;

    //We hit a rock
    else if( tempOb == 'R' )
    {
        for( auto* r : gameptr->rocks )
        {
            if( r->gridx == a.x && r->gridy == a.y && r->health > 0 )
            {
                r->health -= a.damage;
                SFX.push_back(make_pair(r->gridx, r->gridy));

                //Check if the rock was destroyed
                if(r->health <= 0)
                {
                    r->health = 0;
#ifndef TESTING
                    r->set_destroyed(gameptr->turn);
                    removeObstacle(a.x, a.y);
#endif
                }

                return true;
            }
        }
    }

    //We hit a tree
    else if( tempOb == 'T' )
    {
        for( auto* t : gameptr->trees )
        {
            if( t->gridx == a.x && t->gridy == a.y && t->health > 0 )
            {
                t->health -= a.damage;
                SFX.push_back(make_pair(t->gridx, t->gridy));

                //Check to see if we destroyed the tree
                if( t->health <= 0 )
                {
                    t->health = 0;
#ifndef TESTING
                    t->set_destroyed( gameptr->turn );
                    removeObstacle( a.x, a.y );

                    //If a tree you're hiding under gets destroyed, then take 1 damage
                    for ( auto tTank : actors )
                    {
                        if ( tTank.x == a.x && tTank.y == a.y )
                            tTank.health--;
                    }
#endif
                }
                return true;
            }
        }
    }

    else if( tempOb == 'C' )
    {
        for( auto* &c : gameptr->specials )
        {
            if( c->gridx == a.x && c->gridy == a.y && c->health > 0 )
            {
                c->health--;

                //Bang the drum
                hits+= crate_o_doom(c->gridx, c->gridy, a);
                actorInfoById(-a.id).hits += hits;

                for ( i = gameptr->specials.size(); i > 0; i-- )
                {
                    if ( gameptr->specials[i-1]->health == 0 )
                    {
                        removeObstacle(gameptr->specials[i-1]->gridx, gameptr->specials[i-1]->gridy);
                        gameptr->specials.erase(gameptr->specials.begin() + i - 1);
                    }
                }

                return true;
            }
        }
    }

    return false;
}

/***************************************************************************//**
* @author Jon McKee
* @brief  Crate destruction. We check every square in the range of the crate
* and deal appropriate damage. If we struck a crate we begin chaining our damage.
******************************************************************************/
bool GameField::crate_o_doom(int x, int y, ActorInfo &a)
{
    //Steal the good parts from fog of war
    //Radar - How big the explosion is
    int x_iter, y_iter, radar = 1, x_pos = x, y_pos = y, hit = 0;

    int x_max_radar_range = radar + x_pos >= fieldMap.width ? fieldMap.width - 1 : radar + x_pos;
    int y_max_radar_range = radar + y_pos >= fieldMap.height ? fieldMap.height - 1 : radar + y_pos;
    int y_min_radar_range = y_pos - radar < 0 ? 0 : y_pos - radar;
    int x_min_radar_range = x_pos - radar < 0 ? 0 : x_pos - radar;

    for( y_iter = y_min_radar_range; y_iter <= y_max_radar_range; y_iter++ )
    {
        for( x_iter = x_min_radar_range; x_iter <= x_max_radar_range; x_iter++ )
        {
            //Now that we stole the internals do our stuff
            //Explode item at coordinates ( x, y )
            switch( obstacleAt( x_iter, y_iter ) )
            {
            //Case T - item is a tree
            case 'T':
                for( auto &t : gameptr->trees )
                {
                    if( t->gridx == x_iter && t->gridy == y_iter && t->health > 0 )
                    {
                        t->health--;

                        //Destroy tree if its health goes below 0
                        if(t->health <= 0)
                        {
                            t->destroyed = gameptr->turn;
                            removeObstacle(t->gridx, t->gridy);
                        }
                    }
                }
                break;

            //Case C - item is another crate
            case 'C':
                for( auto &c : gameptr->specials )
                {
                    if( c->gridx == x_iter && c->gridy == y_iter && c->health > 0 )
                    {
                        c->health--;

                        //Chain reaction of crates
                        hit = crate_o_doom(c->gridx, c->gridy, a);
                    }
                }
                break;

            //Case R - item is a rock
            case 'R':
                for( auto &r : gameptr->rocks )
                {
                    if( r->gridx == x_iter && r->gridy == y_iter && r->health > 0 )
                    {
                        r->health--;

                        //Destroy rock if its health goes below 0
                        if( r->health <= 0 )
                        {
                            r->destroyed = gameptr->turn;
                            removeObstacle(r->gridx, r->gridy);
                        }  
                    }
                }
                break;

            case 'B':

            //Else, check to see if a tank was hit
            default:
                for( auto &act : actors )
                {
                    if( act.x == x_iter && act.y == y_iter && act.health > 0 )
                    {
                        act.health--;

                        //Updates tank info
                        if( act.health <= 0 )
                        {
                            act.health = 0;
                            act.id = 0;
                            actorInfoById(-a.id).kills++;
                        }

                        actorInfoById(-a.id).hits++;
                    }
                }
                break;
            }

            SFX.push_back(make_pair(x_iter, y_iter));
        }
    }

    return hit;
}

/***************************************************************************//**
* @author Riley Kopp
* @brief
* turns the map into just what the current tank can see based off radar
******************************************************************************/
void GameField::create_fog_of_war( MapData &map, ActorInfo current_actor )
{
    if(current_actor.id <= 0)
        return;

    int value, x_iter, y_iter;
    int radar = current_actor.radar, x_pos = current_actor.x, y_pos = current_actor.y;

    int x_max_radar_range = radar + x_pos >= map.width ? map.width - 1 : radar + x_pos;
    int y_max_radar_range = radar + y_pos >= map.height ? map.height - 1 : radar + y_pos;
    int y_min_radar_range = y_pos - radar < 0 ? 0 : y_pos - radar;
    int x_min_radar_range = x_pos - radar < 0 ? 0 : x_pos - radar;

    MapData new_map = map;
    fill(new_map.map.begin(), new_map.map.end(), 0);
    fill(new_map.obstacleMap.begin(), new_map.obstacleMap.end(), 0);
    new_map.healthMap.resize(new_map.width * new_map.height);
    fill(new_map.healthMap.begin(), new_map.healthMap.end(), 0);

    for( y_iter = y_min_radar_range; y_iter <= y_max_radar_range; y_iter++ )
    {
        for( x_iter = x_min_radar_range; x_iter <= x_max_radar_range; x_iter++ )
        {
            value = y_iter * map.width + x_iter;

            new_map.map[value] = map.map[value];
            new_map.obstacleMap[value] = map.obstacleMap[value];

            if( map.obstacleMap[value] == 0 && map.map[value] != 0 )
            {
                for( auto act : actors )
                {
                    if( act.x == x_iter && act.y == y_iter && act.health > 0 )
                        new_map.healthMap[value] = act.health;
                }
            }

            switch( obstacleAt ( x_iter, y_iter ) )
            {
            //Case T - Obstacle at ( x, y ) is a tree
            case 'T':
                for(auto t : gameptr->trees)
                {
                    if(t->gridx == x_iter && t->gridy == y_iter && t->health > 0)
                        new_map.healthMap[value] = t->health;
                }
                break;

            //Case C - Obstacle at ( x, y ) is a crate
            case 'C':
                for(auto c : gameptr->specials)
                    new_map.healthMap[value] = c->health;
                break;

            case 'R':
                for(auto r : gameptr->rocks)
                {
                    if(r->gridx == x_iter && r->gridy == y_iter && r->health > 0)
                        new_map.healthMap[value] = r->health;
                }
                break;

                //Future use for destructible bushes
                /*case 'B':
                  for(auto b : gameptr->bushes)
                  {
                    new_map.healthMap[value] = 1;
                  }
                  break;*/
            }
        }
    }

    map = new_map;
}

/**
 * @author David Donahue
 * @author Jon McKee (modified by)
 * @par Description:
 * Executes the move and attack phase of each AI's turn and increments the turn counter.
 * Object regrowth is checked at the beginning of the turn phase.
 * AI's are culled at the end of the turn phase.
 */
void GameField::checkObjectRegrowth()
{
    for( Obstacles* t : gameptr->trees )
    {
        if( t->health <= 0 )
        {
            t->regrow( gameptr->turn, actors );
            if ( t->health > 0 )
                addObstacle( t->gridx, t->gridy, 'T' );
        }
    }

    for( Obstacles* r : gameptr->rocks )
    {
        if( r->health <= 0 )
        {
            r->regrow( gameptr->turn, actors );
            if ( r->health > 0 )
                addObstacle( r->gridx, r->gridy, 'R' );
        }
    }

    //Currently bushes are non destructible but this will let them regrow when they do
    for( Obstacles* b : gameptr->bushes )
    {
        if( b->health <= 0 )
        {
            b->regrow( gameptr->turn, actors );
            if ( b->health > 0 )
                addObstacle( b->gridx, b->gridy, 'B' );
        }
    }
}

/**
 * @author David Donahue
 * @author Jon McKee (modified by)
 * @par Description:
 * Executes the move and attack phase of each AI's turn and increments the turn counter.
 * Object regrowth is checked at the beginning of the turn phase.
 * AI's are culled at the end of the turn phase.
 */
void GameField::nextTurn()
{
    if( gameptr != nullptr )
    {
        ++gameptr->turn;
        ++turnCount;
    }

    direction atk;
    ActorInfo newProjectile;
    PositionData pos;
    int action, act_ap, i, j = 0;
    bool grow = false;
    MapData fog_of_war = fieldMap;

    if ( gameptr != nullptr )
        checkObjectRegrowth();

    for( i = 0; (unsigned)i < actors.size(); ++i )
    {
        act_ap = actors[i].AP;

        if( actors[i].id > 0 && actors[i].health > 0 && gameptr != nullptr )
            gameptr->actTurn = actors[i].id;

        //Give each actor a fresh map
        updateMap();

        if( gameptr != nullptr )
            displayCallback( fieldMap, actors, gameptr->turn );

        SFX.clear();

        while( act_ap > 0 && actors[i].id != 0 && actors[i].health > 0 )
        {
            actors[i].cDetect++;

            if ( gameptr != nullptr )
            {
                gameptr->modCounter++;
                if( gameptr->modCounter > 7 )
                    gameptr->modCounter = 0;
            }

            updateMap();
            fog_of_war = fieldMap;
            create_fog_of_war(fog_of_war, actors[i]);
            pos.game_x = actors[i].x;
            pos.game_y = actors[i].y;
            pos.health = actors[i].health;
            pos.id = actors[i].id;
            pos.ap = act_ap;
            pos.ammo = actors[i].ammo;
            action = actors[i].act_p->spendAP(fog_of_war, pos);

            if( action == 1 )
                runMoves(actors[i], fog_of_war, pos);

            else if( action == 2 )
            {
                //PositionData to give the AI
                pos.game_x = actors[i].x;
                pos.game_y = actors[i].y;
                pos.health = actors[i].health;
                pos.id = actors[i].id;

                //Get the AI's desired attack
                atk = actors[i].act_p->attack(fog_of_war, pos);

                //Tanks attacking
                if( actors[i].id > 0 )
                {
                    if( atk != STAY && actors[i].ammo >= 1 )
                    {
                        actors[i].heading = atk;
                        j = i+1;
                        grow = false;

                        while( (unsigned)j < actors.size() && actors[i].id == -actors[j].id && actors[j].id < 0 && actors[j].health > 0 )
                        {

                            //Check projectile list for a projectile in this spot
                            //Found one
                            if( actors[i].x == actors[j].x && actors[i].y == actors[j].y )
                            {
                                actors[j].scale += .40;
                                actors[j].health += 1;
                                actors[j].ammo += 1;
                                actors[j].damage += actors[i].damage;

                                //See if the projectile is one of our own
                                grow = true;
                                break;
                            }

                            j++;
                        }

                        //If there was no projectiles in this spot create a new one
                        if( grow == false )
                        {
                            ProjectileActor * proj = new ProjectileActor(atk);

                            newProjectile.AP = actors[i].range;
                            newProjectile.id = -actors[i].id;
                            newProjectile.act_p = proj;
                            newProjectile.health = 1;
                            newProjectile.damage = actors[i].damage;
                            newProjectile.x = actors[i].x;
                            newProjectile.y = actors[i].y;
                            newProjectile.hits = 0;
                            newProjectile.ammo = 1;
                            newProjectile.heading = actors[i].heading;

                            actors.insert(actors.begin() + i + 1, newProjectile);
                            actors[i].shots++;
                            actors[i].ammo--;
                        }
                    }

                    //Forced reload on empty ammo rack
                    else if( atk != STAY )
                        actors[i].ammo = actors[i].max_ammo;
                }

            }

            //Chosen reload action
            else if( action == 4 )
                actors[i].ammo = actors[i].max_ammo;

            //Check for a camper
            if ( actors[i].health > 0 && actors[i].cDetect / actors[i].AP >= 4 )
                actors[i].camp = true;

            --act_ap;
        }
    }

    //Remove dead actors
    cull();
    updateMap();

    //Draw map
    if( gameptr != nullptr )
        displayCallback( fieldMap, actors, gameptr->turn );

    //Remove explosions that remain
    SFX.clear();
}

/**
 * @author David Donahue
 * @par Description:
 * Add an actor to the list
 */
void GameField::addActor( ActorInfo a )
{
    actors.push_back(a);
    updateMap();
}

/**
 * @author Youki Lewis
 * @par Description:
 * Check if points are distributed properly
 */
void GameField::checkForCheaters( int pointsAvailable )
{
    for( auto &a : actors )
    {
        if( a.health + a.damage + a.AP + a.shots + a.range > pointsAvailable )
        {
            a.health = 1;
            a.damage = 1;
            a.range = 1;
            a.shots = 1;
            a.AP = 1;
        }
    }
}

/**
 * @author David Donahue
 * @par Description:
 * Adds an obstacle to the map
 *
 * @param[in] x - the x value of the obstacle
 * @param[in] y - the y value of the obstacle
 */

void GameField::addObstacle( int x, int y, int type )
{
    fieldMap.obstacleMap[x + fieldMap.width * y] = type;
}

/**
 * @author David Donahue
 * @par Description:
 * Removes an obstacle from the map
 *
 * @param[in] x - the x value of the obstacle
 * @param[in] y - the y value of the obstacle
 */

void GameField::removeObstacle( int x, int y )
{
    fieldMap.obstacleMap[x + fieldMap.width * y] = false;
}

vector<ActorInfo> GameField::getDeceased()
{
    return deceased;
}

/**
 * @author David Donahue
 * @par Description:
 * Get the current set of actors
 */
vector<ActorInfo> GameField::getActors()
{
    return actors;
}

/**
 * @author Jon McKee
 * @par Description:
 * Get a const version of the current set of actors
 */
vector<ActorInfo> *GameField::getActorsPointer()
{
    vector<ActorInfo> *temp;
    temp = &actors;
    return temp;
}

/**
 * @author Jon McKee
 * @par Description:
 * Get the current set of actors
 */
const vector<ActorInfo> &GameField::getActorsConst()
{
    return actors;
}

/**
 * @author Jon McKee
 * @par Description:
 * Get the current set of SFX
 */
vector<pair<int,int>> GameField::getSFX()
{
    return SFX;
}

/**
 * @author Jon McKee
 * @par Description:
 * Get the current set of SFX
 */
vector<pair<int,int>> *GameField::getSFXPointer()
{
    vector<pair<int,int>> *temp;
    temp = &SFX;
    return temp;
}

/**
 * @author Jon McKee
 * @par Description:
 * Get the current set of SFX
 */
const vector<pair<int,int>> &GameField::getSFXConst()
{
    return SFX;
}

/**
 * @author Jon McKee
 * @par Description:
 * Clear the current set of SFX
 */
void GameField::clearSFX()
{
    SFX.clear();
}

/**
 * @author David Donahue
 * @par Description:
 * Get a vector of actors at a given location on the map
 */
vector<ActorInfo> GameField::findActorsByCoord(int x, int y)
{
    vector<ActorInfo> hits;

    //Check each actor
    for( auto a : actors )
    {
        if( a.x == x && a.y == y )
            hits.push_back(a);
    }

    return hits;
}

/**
 * @author David Donahue
 * @par Description:
 * Remove actors with hp of 0 from the game
 */
void GameField::cull()
{
    //This is used instead of the c++11 version so that we can use the index
    for( int i = 0; (unsigned)i < actors.size(); ++i )
    {
        if( actors[i].health == 0 )
        {
            if( actors[i].name != "default\n" )
                deceased.push_back(actors[i]);

            if( actors[i].act_p != NULL )
                delete actors[i].act_p;

            actors.erase( actors.begin()+i );
            //Go back one since everything just shifted back
            --i;
        }
    }

}

/**
 * @author David Donahue
 * @par Description:
 * Returns the full fieldMap as a MapData struct
 */
MapData GameField::getMapData()
{
    return fieldMap;
}

/**
 * @author David Donahue
 * @par Description:
 * Finds an actor by its ID and returns a reference to it
 *
 * @param[in] id - the ID of the actor
 * @return Reference to the desired actor or a reference to a 'null' actor
 *
 */
ActorInfo & GameField::actorInfoById( int id )
{
    for( auto &a : actors )
    {
        if( a.id == id )
            return a;
    }

    return nullActor;
}

/**
 * @author David Donahue
 * @par Description:
 * Determines whether a space has an obstacle on it
 *
 * @param[in] x - the X coordinate of the tile
 * @param[in] y - the Y coordinate of the tile
 * @return true if an obstacle exists at a tile, false if not
 *
 */
int GameField::obstacleAt( int x, int y )
{
    return fieldMap.obstacleMap[x + y * fieldMap.width];

}

string GameField::getWinner()
{
    string winner = "none";

    for( auto a : actors )
    {
        if( a.health > 0 && a.id > 0 )
            winner = a.name;
    }

    return winner;
}


void GameField::moveUp(int yPos, int xPos, int &yoff, int &health )
{
      if(yPos > 0 && noObs(xPos,yPos-1))
            yoff = -1;
        else
            health--;
}

void GameField::moveDown(int yPos, int xPos, int &yoff, int &health)
{
      if(yPos < fieldMap.height-1 && noObs(xPos,yPos+1))
            yoff = 1;
        else
           health--;
}

void GameField::moveLeft( int xpos, int ypos, int &xoff, int &health)
{
       if(xpos > 0 && noObs(xpos-1,ypos))
            xoff = -1;
        else
            health--;
}

void GameField::moveRight( int xpos, int ypos, int &xoff, int &health)
{
     if(xpos < fieldMap.width-1 && noObs(xpos+1,ypos))
            xoff = 1;
        else
            health--;
}

void GameField::moveUL(int xpos, int ypos, int &xoff, int &yoff, int &health)
{
       if(ypos > 0 && xpos > 0 && noObs(xpos-1,ypos-1))
        {
            yoff = -1;
            xoff = -1;
        }

        else
            health--;
}

void GameField::moveUR(int xpos, int ypos, int &xoff, int &yoff, int &health)
{
       if(ypos > 0 && xpos < fieldMap.width-1 && noObs(xpos+1,ypos-1))
        {
            yoff = -1;
            xoff = 1;
        }

        else
            health--;
}

void GameField::moveDL(int xpos, int ypos, int &xoff, int &yoff, int &health)
{
    if(ypos < fieldMap.height-1 && xpos > 0 &&noObs(xpos-1,ypos+1))
        {
            yoff = 1;
            xoff = -1;
        }

        else
            health--;
}
void GameField::moveDR(int xpos, int ypos, int &xoff, int &yoff, int &health)
{
     if(ypos < fieldMap.height-1 && xpos < fieldMap.width-1 && noObs(xpos+1,ypos+1))
        {
            yoff = 1;
            xoff = 1;
        }

        else
            health--;
}

void GameField::checkMoves(int xpos, int ypos, int &xoff, int &yoff, int &health, direction dir)
{
    if(dir==UP)
        moveUp(ypos,xpos,yoff,health);
    else if(dir==DOWN)
        moveDown(ypos,xpos,yoff,health);
    else if(dir==LEFT)
        moveLeft(xpos,ypos,xoff,health);
    else if(dir==RIGHT)
        moveRight(xpos,ypos,xoff,health);
    else if(dir==UPLEFT)
        moveUL(xpos,ypos,xoff,yoff,health);
    else if(dir==UPRIGHT)
        moveUR(xpos,ypos,xoff,yoff,health);
    else if(dir==DOWNLEFT)
        moveDL(xpos,ypos,xoff,yoff,health);
    else if(dir==DOWNRIGHT)
        moveDR(xpos,ypos,xoff,yoff,health);
}

bool GameField::noObs(int xpos, int ypos)
{
    return (!obstacleAt(xpos, ypos)
           || obstacleAt(xpos, ypos) == 'R'
          || obstacleAt(xpos, ypos) == 'T'
         || obstacleAt(xpos, ypos) == 'C'
        || obstacleAt(xpos, ypos) == 'B'
        || obstacleAt(xpos, ypos) == 'W');
}