/***************************************************************************//**
* @file Drawable.h
* @author Chezka Gaddi
* @brief Contains all functions prototypes that maintains Drawable class and all
* of it's subclasses
*******************************************************************************/

#ifndef SLACKERS_PLATFORM_DRAWABLE_H
#define SLACKERS_PLATFORM_DRAWABLE_H

#include <cstring>
#include <GL/freeglut.h>
#include "ActorInfo.h"
#include "direction.h"
#include "global.h"

/***************************************************************************//**
* @author Chezka Gaddi
* @class Drawable
* @brief Drawable is the parent class for all GUI objects and has a draw function that
* must be overwritten by subclasses.
*******************************************************************************/
class Drawable
{
    public:
        string name;   /*!<The name of the drawable */
        int id;             /*!<The id number of the drawable */
        GLfloat screen_x;   /*!<The screen x coordinate of the drawable */
        GLfloat screen_y;   /*!<The scren y coordinate of the drawable */

        int health;         /*!<The health value of the drawable */
        int max_health;     /*!<The max health of the drawable object */
        GLuint tex;            /*!<Texture to draw object with */

        Drawable() {}       /*!< Drawable constructor */
        ~Drawable() {}      /*!< Drawable deconstructor */

        virtual void draw( int, int ) = 0; /*!<A pure virtual function to ensure drawable objects define how they are drawn */

    protected:
         int gridx;          /*!< Drawables grid x coordinate */
         int gridy;          /*!< Drawables grid y coordinate */

         static float xscalar; /*!< Drawable x shared scalar value */
         static float yscalar; /*!< Drawable y shared scalar value */

    friend class Game;        //Make Game class a friend of the drawable classes
    friend class GameField;   //Make GameField class a friend of the drawable classes
};


/***************************************************************************//**
* @author Chezka Gaddi
* @class GameFieldDrawable
* @brief GameField contains instructions to draw the GameField
*******************************************************************************/
class GameFieldDrawable : public Drawable
{
    public:
        GLuint tex;   /*!< GameField Texture */
        GameFieldDrawable(); /*!< GameField Drawable constructor */

        void draw( int, int ); /*!< Draw function for the GameFieldDrawable Object */
};


/***************************************************************************//**
* @author Chezka Gaddi
* @class Menu
* @brief Menu contains instructions to draw the player statistics
*******************************************************************************/
class Menu : public Drawable
{
    public:
        char name[20];       /*!<Name of the player to be displayed */
        int health;         /*!<Player's health */
        int bullet;         /*!<Current bullet count */
        int score;          /*!<Current score */
        int angle = 0;      /*!<Angle used for the menu */
        int bTex;           /*!<Secondary texture used (Primarily tank texture) */
        int turn = 0;       /*!<Current turn modifier for mini tank direction */

        Menu( int, int, int, int, string, direction, int, int ); /*!<Menu drawable constuctor */

        void drawTextBox( GLfloat, GLfloat ); /*!< Function to prepare the menu's background box */
        void drawPlayerStats();  /*!< Function to populate player stats into text box */
        void draw( int, int ); /*!< Function to draw the final Menu object */
};


/***************************************************************************//**
* @author Chezka Gaddi
* @class Obstacles
* @brief Obstacles contains instructions to draw trees or rocks
*******************************************************************************/
class Obstacles : public Drawable
{
    public:
        Obstacles( int, GLfloat, GLfloat, int, int ); /*!< Initial constructor for the Obstacle drawables */
        void regrow( int turn, const vector<ActorInfo> actor ); /*!< Function to check for a rock/Tree regrowing */
        void draw( int, int ); /*!< Function to draw the Obstacle on the map */

    protected:
        int destroyed = -1; /*!< The turn the obstacle was destoryed on */
        int regrow_rate = 8; /*!< The number of turns the obstacle takes to regrow */
        void set_destroyed( int d ); /*!< Set's the turn the object was destroyed on */

    friend class GameField; // Make the gamefield class a friend of the Obstacle sub-class
};


/***************************************************************************//**
* @author Chezka Gaddi
* @class Projectile
* @brief Projectile contains instructions to draw the Projectiles
*******************************************************************************/
class Projectile : public Drawable
{
    public:
        int angle;  /*!< The angle of the projectile */
        float offsetX; /*!< The x offset of the projectile for drawing */
        float offsetY; /*!< The y offset of the projectile for drawing */
        bool camp; /*!< Check to see if the tank is consider camping so we can set the projectile accordingly */

        Projectile( int ID, GLfloat x, GLfloat y, direction dir, bool t, 
        float osX, float osY, bool camping ); /*!< Constructor for the projectile drawable object */

        void draw( int, int ); /*!< The draw function for the Projectile class */

        float sizeMod = 1;  /*!< Scalar specific for projectiles.  Used in projectile stacking */
        bool trail; /*!< Flag used to signify if the fire trail should be on or off */
};


/***************************************************************************//**
* @author Chezka Gaddi
* @class TankDrawable
* @brief TankDrawable contains instructions to draw the TankDrawable
*******************************************************************************/
class TankDrawable : public Drawable
{
    public:
        int angle;  /*!< The angle of the tank */
        int turn; /*!< The turn counter for the tank drawable */
        int sMod; /*!< Smoke mode counter for alternating smoke */
        float offsetx; /*!< x offset for the tank drawable */
        float offsety; /*!< y offset for the tank drawable */
        bool camp; /*!< bool setting for the tank detected as camping */

        TankDrawable( int ID, GLfloat x, GLfloat y, direction dir, int t, int sMod,
        float osx, float osy, bool camping ); /*!< The constructor for making a Tank Drawable object */

        void draw( int, int ); /*!< The draw function for displaying a tank drawable object */
        void setHealth( int h ); /*!< Setting the health of the drawable object */
        void setMax_health( int mh ); /*!< Setting the max health of the drawable object */
};


/***************************************************************************//**
* @author Jon McKee
* @class sfxDrawable
* @brief sfxDrawable contains instructions to draw the sfxDrawable
*******************************************************************************/
class sfxDrawable : public Drawable
{
    public:
        int angle; /*!< The angle to draw the special effects */

        sfxDrawable( GLfloat x, GLfloat y ); /*!< The constructor for drawing the special efects */

        void draw( int, int ); /*!< The draw function for displaying the special effects objects */
};


/***************************************************************************//**
* @author Jon McKee
* @class crate
* @brief crate contains instructions to draw the party crate
*******************************************************************************/
class Crate : public Drawable
{
    public:
        int angle; /*!< The angle at which the crate is drawn */
        Crate( GLfloat x, GLfloat y, int, int ); /*!< The constructor for the crate objects */

        void draw( int, int );  /*!< The draw function for the Crate drawable objects */
};


#endif //SLACKERS_PLATFORM_DRAWABLE_H
