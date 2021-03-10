/***************************************************************************//**
* @file GameField.cpp
* @brief Contains all objects and functions to be drawn with the GameField.
* @author Chezka Gaddi
* *****************************************************************************/

#include "Drawable.h"

/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Default constructor, sets tex = 1
*******************************************************************************/
GameFieldDrawable::GameFieldDrawable( ) : tex(1) {}

/***************************************************************************//**
* @author Chezka Gaddi
* @brief draws the game field using glut
*
* Overloaded draw function that creates the gamefield
*******************************************************************************/
void GameFieldDrawable::draw( int x, int y )
{
    glEnable( GL_TEXTURE_2D );

    //Draws the Background
    glPushMatrix( );
    glTranslatef( 0.0f, 0.0f, -5.0f );
    glBindTexture(GL_TEXTURE_2D, gameTex[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.0f, -2.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 2.0f, -2.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 2.0f,  2.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.0f,  2.0f,  1.0f);
    glEnd();
    glPopMatrix();
    //Draws the Field
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glBindTexture(GL_TEXTURE_2D, gameTex[tex]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.89f, -1.875f,  1.0f); //Bottom left
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.91f, -1.875f,  1.0f); //Bottom Right
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.91f,  0.92f,  1.0f);  //Top Right
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.89f,  0.92f,  1.0f);  //Top Left
    glEnd();
    glPopMatrix();
}
