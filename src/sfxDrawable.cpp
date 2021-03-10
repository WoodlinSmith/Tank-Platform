/***************************************************************************//**
* @file sfxDrawable.cpp
* @author Jon McKee
* @brief Contains all maintenance functions for sfxDrawable class.
* *****************************************************************************/

#include "Drawable.h"

/***************************************************************************//**
* @author Jon McKee
* @brief Constructor
*
* Initiates the coordinates of where sfx is to be drawn and what it will look
* like.
*
* @param[in] ID - sfx id
* @param[in] x_coor - coordinate to spawn sfx
* @param[in] y_coor - coordinate to spawn sfx
* *****************************************************************************/
sfxDrawable::sfxDrawable( GLfloat x_coor, GLfloat y_coor )
{
    screen_x = x_coor;
    screen_y = y_coor;

    tex = (rand() % 3 + 5);
}

/***************************************************************************//**
* @author Jon McKee
* @brief draw
*
* Generates the sfx onto the gamefield
* *****************************************************************************/
void sfxDrawable::draw(int x, int y)
{
    glEnable(GL_TEXTURE_2D);
    glColor4ub(255,255,255,255);
    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    glTranslatef(screen_x, screen_y, -5.0f);
    glRotatef(angle,0,0,1);
    glBindTexture(GL_TEXTURE_2D, sfxTex[tex]);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.13f * xscalar, -0.1f * yscalar,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.13f * xscalar, -0.1f * yscalar,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.13f * xscalar,  0.1f * yscalar,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.13f * xscalar,  0.1f * yscalar,  1.0f);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
