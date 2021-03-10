/***************************************************************************//**
* @file Projectile.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for Projectile class.
* *****************************************************************************/


#include "Drawable.h"
#include "ProjectileUtils.h"


/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Initiates the coordinates of where projectile is to be drawn and from whom the
* projectile came from.
*
* @param[in] ID - indicates who fired the projectile
* @param[in] x - coordinate to spawn projectile
* @param[in] y - coordinate to spawn projectile
* *****************************************************************************/
Projectile::Projectile( int ID, GLfloat x, GLfloat y, direction dir, bool t,
    float osX = 1, float osY = 1, bool camp = false )
{
    screen_x = x;
    screen_y = y;
    offsetX = osX;
    offsetY = osY;
    id = ID;
    trail = t;
    this->camp = camp;


    if ( dir != STAY )
        angle = setAngle( dir );


    if ( camp == true ) 
        tex = 11;

    else
        tex = ( ( -1 * id ) - 1 ) * 5 + 4;
}




/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
*
* Draws the projectile in the gamefield
* @param[in] turnVal The current turn value
* *****************************************************************************/
void Projectile::draw( int turnVal, int y )
{
    float trailMod = .9; //Scale the trail

    enableGL( screen_x, screen_y, offsetX, offsetY, angle, false, turnVal );

    //Check if we have a marshmellow 
    if ( camp == true )
        glBindTexture( GL_TEXTURE_2D, sfxTex[tex] );
    else
        glBindTexture( GL_TEXTURE_2D, tankTex[tex] );

    glBegin( GL_QUADS );

    drawTrail( xscalar, yscalar, sizeMod, 1, -0.07f, 0.07f );

    disableGL();

    if ( trail == true ) 
    { 
        //Only draw trail on projectiles turn
        enableGL( screen_x, screen_y, offsetX, offsetY, angle, true, turnVal );

        glBegin( GL_QUADS );

        drawTrail( xscalar, yscalar, sizeMod, trailMod, -0.20f, -0.06f );

        disableGL();
    }
}