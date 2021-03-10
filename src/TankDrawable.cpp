/**************************************************************************//**
* @file TankDrawable.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for TankDrawable class.
* ****************************************************************************/

#include "Drawable.h"

/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Initiates the coordinates of where tank is to be drawn and what it will look
* like.
*
* @param[in] ID - tank id
* @param[in] x_coor - coordinate to spawn tank
* @param[in] y_coor - coordinate to spawn tank
* *****************************************************************************/
TankDrawable::TankDrawable( int ID, GLfloat x_coor, GLfloat y_coor, 
                            direction dir, int t = 0, int s = 0, 
                            GLfloat osx = 1, GLfloat osy = 1, bool camp = false)
{
    screen_x = x_coor;
    screen_y = y_coor;
    offsetx = osx;
    offsety = osy;
    id = ID;
    turn = t;
    sMod = s;
    this->camp = camp;

    // Acesses the right image for the tanks
    //  0 is the up image,
    //  1 is right,
    //  2 is down,
    //  3 is left.
    angle = 0;
    switch(dir)
    {
    case LEFT:
    {
        tex = (ID-1) * 5 + 3;
    }
    break;
    case RIGHT:
    {
        tex = (ID-1) * 5 + 1;
    }
    break;
    case UPRIGHT:
    {
        tex = (ID-1) * 5 + 0;
        angle = -45;
    }
    break;
    case DOWNRIGHT:
    {
        tex = (ID-1) * 5 + 2;
        angle = 45;
    }
    break;
    case UPLEFT:
    {
        tex = (ID-1) * 5 + 0;
        angle = 45;
    }
    break;
    case DOWNLEFT:
    {
        tex = (ID-1) * 5 + 2;
        angle = -45;
    }
    break;
    case UP:
    {
        tex = (ID-1) * 5 + 0;
    }
    break;
    case DOWN:
    {
        tex = (ID-1) * 5 + 2;
    }
    break;
    default:
        tex = ID-1 * 5;
    }

    if (camp == true)
        tex = 4;
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
*
* Generates the tank onto the gamefield
* *****************************************************************************/
void TankDrawable::draw(int x, int y)
{
    glEnable(GL_TEXTURE_2D);
    glColor4ub(255,255,255,255);
    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    glTranslatef(screen_x + offsetx, screen_y + offsety, -5.0f);
    if (camp == true){
      glBindTexture(GL_TEXTURE_2D, sfxTex[tex]);
    }else{
      glRotatef(angle,0,0,1);
      glBindTexture(GL_TEXTURE_2D, tankTex[tex]);
    }
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
    //First smoke    
    if (health <= max_health*.66666){
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      glLoadIdentity();
      glTranslatef(screen_x + offsetx, screen_y + offsety, -5.0f);
      glBindTexture(GL_TEXTURE_2D, sfxTex[12]);

      if (sMod % 2 == 0) {
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.05f * xscalar, .3f * yscalar,  1.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 0.0f * xscalar, .3f * yscalar,  1.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( 0.0f * xscalar,  0.2f * yscalar,  1.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.05f * xscalar,  0.2f * yscalar,  1.0f);
        glEnd();
      } else {
      glBegin(GL_QUADS);
        glRotatef(45, 0, 0, 1);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.05f * xscalar, .2f * yscalar,  1.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 0.0f * xscalar, .2f * yscalar,  1.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( 0.0f * xscalar,  0.1f * yscalar,  1.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.05f * xscalar,  0.1f * yscalar,  1.0f);
        glEnd();
      }
      //second smoke
      if (health <= max_health*.5){ 
        if (sMod % 2 == 1 ) {
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-0.0f * xscalar, .3f * yscalar,  1.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f( 0.05f * xscalar, .3f * yscalar,  1.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f( 0.05f * xscalar,  0.2f * yscalar,  1.0f);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-0.0f * xscalar,  0.2f * yscalar,  1.0f);
          glEnd();
        }else{
          glBegin(GL_QUADS);
          glRotatef(45, 0, 0, 1);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-0.0f * xscalar, .2f * yscalar,  1.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f( 0.05f * xscalar, .2f * yscalar,  1.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f( 0.05f * xscalar,  0.1f * yscalar,  1.0f);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-0.0f * xscalar,  0.1f * yscalar,  1.0f);
          glEnd();
        }
      }
      //fire
      if (health <= max_health*.3){ 
          glEnable(GL_BLEND);
          glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
          glLoadIdentity();
          glTranslatef(screen_x + offsetx, screen_y + offsety, -5.0f);
          glBindTexture(GL_TEXTURE_2D, sfxTex[8]);
          
          //sizing width .05  height .05
          //left
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f( -0.07f * xscalar, -0.05f * yscalar,  1.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f( -0.02f * xscalar, -0.05f * yscalar,  1.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f( -0.02f * xscalar,  0.0f * yscalar,  1.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f( -0.07f * xscalar,  0.0f * yscalar,  1.0f);
          glEnd();
          
          //right
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f( 0.01f * xscalar, 0.01f * yscalar,  1.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f( 0.06f * xscalar, 0.01f * yscalar,  1.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f( 0.06f * xscalar,  0.06f * yscalar,  1.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f( 0.01f * xscalar,  0.06f * yscalar,  1.0f);
          glEnd();
          
          //middle
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f( -0.04f * xscalar, -0.04f * yscalar,  1.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f( 0.01f * xscalar, -0.04f * yscalar,  1.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f( 0.01f * xscalar,  0.01f * yscalar,  1.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f( -0.04f * xscalar,  0.01f * yscalar,  1.0f);
          glEnd();
        }
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
/***************************************************************************//**
 * @author Jon McKee
 * @brief allows us to set the drawables health
 * @param[in] h the current health of the object
 * ****************************************************************************/
void TankDrawable::setHealth(int h)
{
    health = h;
}
/***************************************************************************//**
 * @author Jon McKee
 * @brief allows us to set the drawables max health
 * @param[in] mh the max health of the object
 * ****************************************************************************/
void TankDrawable::setMax_health(int mh)
{
    max_health = mh;
}
