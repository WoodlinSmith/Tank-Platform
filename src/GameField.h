/**
 * @file GameField.h
 * @author David Donahue
 * @brief GameField manages the play field and actors.
 */

#ifndef SLACKERS_PLATFORM_GAMEFIELD_H
#define SLACKERS_PLATFORM_GAMEFIELD_H

#include <algorithm>
#include <ctime>
#include "Actor.h"
#include "ActorInfo.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "GameFieldUtils.h"

/***************************************************************************//**
* @class GameField
* @author David Donahue
* @par Description
* The class that will act as the manager of the gamefield
* *****************************************************************************/

class Game;

class GameField
{

protected:
    /*!< This is all of the actors on the field: tanks + projectiles */
    vector<ActorInfo> actors;
    vector<ActorInfo> deceased;
    vector<pair<int,int>> SFX;

    /*!< The turn count number */
    int turnCount = 0;

    /*
     * Struct with width, height, and a vector of ints in row major order, 0
     * for empty tiles and actor id for nonempty.
     */
    MapData fieldMap;

    //Callback function to update the dispaly with the map, actors, and turn count
    void (*displayCallback)(MapData, std::vector<ActorInfo>, int);
    void updateMap();
    void runMoves(ActorInfo &a, MapData &fog, PositionData &pos);
    ActorInfo nullActor = ActorInfo (NULL, 0, 0, 0, 0, 0);

    //Action points for each actor
    int ap;
    GLfloat y_scalar = 0;
    GLfloat x_scalar = 0;
    bool checkObjectStrike(ActorInfo &a);
    bool crate_o_doom(int x, int y, ActorInfo &a);
    bool checkHealth(ActorInfo &a, bool object = true);
    void animateMove(ActorInfo &a);
    Game *gameptr = nullptr;
    

    //Moving functions
    bool noObs(int xpos, int ypos);
    void moveUp(int yPos, int xPos, int &yoff, int &health );
    void moveDown(int yPos, int xPos, int &yoff, int &health);
    void moveLeft( int xpos, int ypos, int &xoff, int &health);
    void moveRight(int xpos, int ypos, int &xoff, int &health);
    void moveUR(int xpos, int ypos, int &xoff, int &yoff, int &health);
    void moveUL(int xpos, int ypos, int &xoff, int &yoff, int &health);
    void moveDR(int xpos, int ypos, int &xoff, int &yoff, int &health);
    void moveDL(int xpos, int ypos, int &xoff, int &yoff, int &health);
    void checkMoves( int xpos, int ypos, int &xoff, int &yoff, int &health, direction dir);

    //Helper function
    void checkObjectRegrowth();

public:
    void setSPECIAL(int points, const attributes baseStats);

    /**
     * Each turn will be as follows:
     * a tank will have the option to move and then a tank will fire, once all
     * of the tanks have fired it starts over again
     */
    void nextTurn();
    void addActor(ActorInfo);
    void checkForCheaters(int pointsAvailable);
    void addObstacle(int x, int y, int type = 1);
    void removeObstacle(int x, int y);

    /**
     * Removes all actors that have a health of 0 from the game (not actors
     * with health less than 0)
     */
    void cull();
    string getWinner();
    vector<ActorInfo> getDeceased();

    /**
     * This will find all the actors in a single cell
     * @return vector of actors that all have the same position
     */
    vector<ActorInfo> findActorsByCoord(int x, int y);

    /*******************************/
    /********Constructors***********/
    /*******************************/

    GameField();
    GameField(int width, int height);
    GameField(int width, int height, vector<ActorInfo> startActors);
    GameField(int width, int height, vector<ActorInfo> startActors,
              void (*d_callback)(MapData, vector<ActorInfo>, int));
    GameField(int width, int height, vector<ActorInfo> startActors,
              void (*d_callback)(MapData, vector<ActorInfo>, int), Game *);
    GameField(int width, int height, vector<ActorInfo> startActors,
              void (*d_callback)(MapData, vector<ActorInfo>, int), int ap);
    GameField(int width, int height, vector<ActorInfo> startActors,
              int actionpoints);


    ~GameField();

    /*******************************/
    /*************Getters***********/
    /*******************************/

    int getTurnCount();
    int getWidth();
    int getHeight();
    vector<int> getMap();
    vector<ActorInfo> getActors();
    vector<ActorInfo> * getActorsPointer();
    const vector<ActorInfo> &getActorsConst();
    vector<pair<int,int>> getSFX();
    vector<pair<int,int>> * getSFXPointer();
    const vector<pair<int,int>> &getSFXConst();
    void clearSFX();
    MapData getMapData();
    ActorInfo & actorInfoById(int id);
    int obstacleAt(int x, int y);
    void create_fog_of_war(MapData &map, ActorInfo current_actor);


    /*******************************/
    /************Setters************/
    /*******************************/

    friend class Game;
};

#endif //SLACKERS_PLATFORM_GAMEFIELD_H
