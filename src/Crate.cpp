/***************************************************************************//**
* @file Crate.cpp
* @author Jon McKee
* @brief Contains all maintenance functions for Crate class.
* *****************************************************************************/

#include "Drawable.h"

/***************************************************************************//**
* @author Jon McKee
* @brief Creates a crate with both it's X/Y Coordinates  and it's Scrren X/Y
* drawing coordinates
*
* @param[in] x_coor - coordinate to spawn crate
* @param[in] y_coor - coordinate to spawn crate
* @param[in] actx - grid x coordinate to spawn crate
* @param[in] acty - grid y coordinate to spawn crate
* *****************************************************************************/
Crate::Crate( GLfloat xCoor, GLfloat yCoor, int actX, int actY )
{
    screen_x = xCoor;
    screen_y = yCoor;
    gridx = actX;
    gridy = actY;
    tex = 7;
    health = 1;
}

/***************************************************************************//**
* @author Jon McKee
* @brief Draws the crate in the gamefield
* @param[in] x - X input coordinate (Currently unused)
* @param[in] y - Y input coordinate (Currently unused)
* *****************************************************************************/
void Crate::draw( int x, int y )
{
    glEnable( GL_TEXTURE_2D );
    glPushMatrix();
    glTranslatef( screen_x, screen_y, -5.0f );
    glBindTexture( GL_TEXTURE_2D, gameTex[tex] );
    glBegin( GL_QUADS );
    glTexCoord2f( 0.0f, 0.0f );
    glVertex3f( -0.12f * xscalar, -0.14f * yscalar,  1.0f );
    glTexCoord2f( 1.0f, 0.0f );
    glVertex3f( 0.12f * xscalar, -0.14f * yscalar,  1.0f );
    glTexCoord2f( 1.0f, 1.0f );
    glVertex3f( 0.12f * xscalar,  0.14f * yscalar,  1.0f );
    glTexCoord2f( 0.0f, 1.0f );
    glVertex3f( -0.12f * xscalar,  0.14f * yscalar,  1.0f );
    glEnd();
    glPopMatrix();
    glDisable( GL_TEXTURE_2D );
}
