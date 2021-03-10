#include "ProjectileUtils.h"


/***************************************************************************//**
 * @author --
 * @brief setAngle
 * @par Description:
 * Sets the angle of the projectile based on a given direction.
 *
 * @param[in] dir - direction used to determine angle.
 *
 * @return angle the angle based on the direction.
 *
 *******************************************************************************/
int setAngle( direction dir )
{
    int angle = 0;

    switch ( dir )
    {
        case UP:
            angle = 90;
            break;

        case UPRIGHT:
            angle = 45;
            break;

        case RIGHT:
            angle = 0;
            break;

        case DOWNRIGHT:
            angle = -45;
            break;

        case DOWN:
            angle = -90;
            break;

        case DOWNLEFT:
            angle = -135;
            break;

        case LEFT:
            angle = 180;
            break;

        case UPLEFT:
            angle = 135;
            break;

        case STAY:
            break;

        default:
            break;
    }

    return angle;
}


/***************************************************************************//**
 * @author --
 * @brief enablesGL
 * @par Description:
 * Enables OpenGL 2D textures, pushes the matrix, translates float values in 
 * OpenGL and rotates the OpenGL values.  Binds a Texture is necessary.
 *
 * @param[in] screenX - value of X on screen
 * @param[in] screenY - value of Y on screen
 * @param[in] offstX  - offset of X
 * @param[in] offstY  - offset of Y
 * @param[in] angle   - angle of projectile
 * @param[in] bind    - boolean determining if texture will be bound
 * @param[in] turnVal - value to turn
 *
 *******************************************************************************/
void enableGL( GLfloat screenX, GLfloat screenY, float offstX, float offstY,
    int angle, bool bind, int turnVal )
{
    glEnable( GL_TEXTURE_2D );
    glPushMatrix();

    if ( bind )
        glBindTexture( GL_TEXTURE_2D, sfxTex[turnVal % 4] );

    glTranslatef( screenX + offstX, screenY + offstY, -5.0f );
    glRotatef( angle, 0, 0, 1 );
}


/***************************************************************************//**
 * @author --
 * @brief disableGL
 * @par Description:
 * Ends GL, pops the matrix, and disables OpenGL 2D textures.
 *
 *******************************************************************************/
void disableGL()
{
    glEnd();
    glPopMatrix();
    glDisable( GL_TEXTURE_2D );
}


/***************************************************************************//**
 * @author --
 * @brief drawTrail
 * @par Description:
 * Draws projectile trail.
 *
 * @param[in] xScal - X Scalar for trail.
 * @param[in] yScal - Y Scalar for trail.
 * @param[in] sizeMod - Size modifier for X and Y value of trail.
 * @param[in] extMod - Extra modifier for X and Y value of trail.
 * @param[in] xMod1 - First modifier for X value of trail.
 * @param[in] xMod2 - Second modifier for X value of trail.
 *
 *******************************************************************************/
void drawTrail( float xScal, float yScal, float sizeMod, float extMod,
    float xMod1, float xMod2 )
{
    glTexCoord2f( 0.0f, 0.0f );

    glVertex3f( xMod1 * xScal * sizeMod * extMod,
        -0.07f * yScal * sizeMod * extMod, 1.0f );

    glTexCoord2f( 1.0f, 0.0f );

    glVertex3f( xMod2 * xScal * sizeMod * extMod,
        -0.07f * yScal * sizeMod * extMod, 1.0f );

    glTexCoord2f( 1.0f, 1.0f );

    glVertex3f( xMod2 * xScal * sizeMod * extMod,
        0.07f * yScal * sizeMod * extMod, 1.0f );

    glTexCoord2f( 0.0f, 1.0f );

    glVertex3f( xMod1 * xScal * sizeMod * extMod,
        0.07f * yScal * sizeMod * extMod, 1.0f );
}
