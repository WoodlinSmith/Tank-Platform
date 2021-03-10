/***************************************************************************//**
* @file game.h
* @author Chezka Gaddi
* @brief Contains all functions prototypes that maintains Game class.
*******************************************************************************/
#ifndef __GAME_H
#define __GAME_H

//Includes
#include <GL/freeglut.h>
#include "ActorInfo.h"
#include "GameField.h"
#include "Drawable.h"
#include "SimpleAI.h"
#include "DynamicLoader.h"
#include "ConfigReader.h"
#include "csv.h"
#include <utility>

/*!<Enum class for the gameMode */
enum gameMode { none, ai, sp, mp, quiet, coverage };

/***************************************************************************//**
* @author Chezka Gaddi
* @brief Class
*
* Game is an interface for the GameField class and openGl application
*******************************************************************************/
class Game
{
    public:
        GameField* tankGame;  /*!<Pointer to the game manager */
        gameMode gMode = none; /*!<Type of game to be ran */
        int turn = 0;
        int actTurn = 0; //0 causes issues on first display call
        int modCounter = 7;
        bool ui = true;
        bool paused = false;

        Game();
        Game ( gameMode mode );
        ~Game();

        void makeDrawables();
        void executeTurn();
        void initGameState();
        void closeDown();
        void earlyOut();
        void createConfig();
        float convertGLXCoordinate ( int );
        float convertGLYCoordinate ( int );
        void gameOver ( vector<ActorInfo> dead, vector<ActorInfo> winner );
        void addGenericObstacles ( GameField* playField, vector<pair<int, int>> obsLoc,
                                   vector<pair<int, int>> tankLoc, Obstacles* tempObj );
        void addCrates ( GameField* playField, vector<pair<int, int>> specLoc,
                         vector<pair<int, int>>tankLoc, Drawable* tempObj );
        void addTrees ( GameField* playField, vector<pair<int, int>> treeLoc,
                        Obstacles* tempObj );
        void addRocks ( GameField* playField, vector<pair<int, int>> tankLoc,
                        vector<pair<int, int>> rockLoc, Obstacles* tempObj );
        void addBushes ( GameField* playField, vector<pair<int, int>> bushLoc,
                         Obstacles* tempObj );
        void addWater ( GameField* playField, vector<pair<int, int>> tankLoc,
                        vector<pair<int, int>> watLoc, Drawable* temp );

        int getX()
        {
            return fieldX;
        };
        int getY()
        {
            return fieldY;
        };

        int getAISpeed()
        {
            return idleSpeed;
        };
        int getAniSpeed()
        {
            return aniSpeed;
        };
        int getbullet_speed()
        {
            return bulletSpeed;
        };
        int gettank_speed()
        {
            return tankSpeed;
        };

        vector <unique_ptr<Drawable>> objects; /*!<Holds all of the current actors */
        vector <Drawable*> constants;  /*!<Holds the GameFieldDrawable and menus */
        vector <Obstacles*> bushes;  /*!<Holds the bushes drawables */
        vector <Obstacles*> rocks;  /*!<Holds the rocks drawables */
        vector <Obstacles*> trees;  /*!<Holds the trees drawables */
        vector <Drawable*> waters;  /*!<Holds the waters drawables */
        vector <Drawable*> specials;  /*!<Holds other special drawables */
        vector <unique_ptr<Drawable>> sfx; /*!<Holds the sfx drawables */


    private:
        int fieldX;
        int fieldY;
        int idleSpeed = 750;
        int maxTurns = 200;
        int activeId;
        int aniSpeed = 20;
        int tankSpeed = 400;
        int bulletSpeed = 80;
};

#endif //__GAME_H
