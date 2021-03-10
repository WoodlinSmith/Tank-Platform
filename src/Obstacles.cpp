/***************************************************************************//**
* @file Obstacles.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for the Obstacles class.
* *****************************************************************************/

#include "Drawable.h"

/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Initializes the x and y coordinates where the obstacle will be spawned.
*
* @param[in] x_coor - coordinate to spawn obstacle
* @param[in] y_coor - coordinate to spawn obstacle
* *****************************************************************************/
Obstacles::Obstacles(int id, GLfloat x_coor, GLfloat y_coor, int gx, int gy )
{
    //id's:
    // 0 = Tree   1 = Rocks   2 = Bushes  3 = Water   4 = Other
    //Textures:
    //0-9   Trees  - Packaged Trees  0-3   - 4 Trees
    //10-19 Rocks  - Packaged Rocks  10-12 - 3 Rocks
    //20-29 Bushes - Packaged Bushes 20-23 - 4 Bushes
    screen_x = x_coor;
    screen_y = y_coor;
    gridx = gx;
    gridy = gy;

    if (id == 0)//It's a tree
    { 
      health = 2;
      tex = ((rand() % 4));
      regrow_rate = 3;
    }
    else if( id == 1)//It's a Rocks
    { 
      health = 4;
      tex = ((rand() % 3) + 10);
      regrow_rate = 5;
    }
    else if( id == 2)//It's a Bushes
    { 
      health = 9999;
      tex = ((rand() % 4) + 20);
      regrow_rate = 2;
    }
    else if( id == 3)//It's a Waters
    { 
      tex = 0 + 30;
      regrow_rate = 0;
    }
    else if (id == 50)
    {
      tex = (8 + 50);
    }
    else //default to tree if we got a bad id
    {
      cout << "BAD ID" << endl;
      tex = 1; 
    }
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
*
* Draws the obstacle will be into the gamefield.
* *****************************************************************************/
void Obstacles::draw(int, int)
{
    glEnable(GL_TEXTURE_2D);
    glColor4ub(255,255,255,255);
    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    glTranslatef(screen_x, screen_y, -5.0f);
    //Check what obstacle it is
    if (tex >= 0 && tex <= 9) //It's a tree
    {
      glBindTexture(GL_TEXTURE_2D, treeTex[tex]);
    }
    else if( tex >= 10 && tex <= 19) //It's a Rocks
    { 
      glBindTexture(GL_TEXTURE_2D, rockTex[tex-10]);
    }
    else if( tex >= 20 && tex <= 29) //It's a Bushes
    {
      glBindTexture(GL_TEXTURE_2D, bushTex[tex-20]);
    }
    else if( tex >= 30 && tex <= 39) //It's a Waters
    { 
      glBindTexture(GL_TEXTURE_2D, waterTex[tex - 30]);
    }
    else if( tex >= 50 && tex <= 60) //It's a hedgehog
    { 
      glBindTexture(GL_TEXTURE_2D, gameTex[tex-50]);
    }

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.16f * xscalar, -0.19f * yscalar,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.16f * xscalar, -0.19f * yscalar,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.16f * xscalar,  0.19f * yscalar,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.16f * xscalar,  0.19f * yscalar,  1.0f);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

/****************//*
 * @author Jon McKee
 * @brief Checks if the obstacle should be regrown
 * @param[in] turn the current turn
 * @param[in] actor the object to check
 ******************/
void Obstacles::regrow(int turn, const std::vector<ActorInfo> actor){
  bool taken = false;
  if (destroyed == -1)
    return;

  if (destroyed+regrow_rate < turn)
  {
    if (tex < 10) //It's a tree
    { 
      health = 3;
    }
    else if( tex < 20) //It's a Rock
    {
      for (int i = 0; unsigned(i) < actor.size(); i++)
      {
        if (actor[i].x == gridx && actor[i].y == gridy)
          taken = true;
      }
      if (!taken)
        health = 5;
    }
    else if( tex < 30) //It's a Bush
    { 
      health = 1;
    }
    if (health >= 0)
      destroyed = -1;
  }
}

/**********************//*
 * @author Jon McKee
 * @brief set the current obstacle as destoryed
 * @param[in] d the turn the obstacle was destroyed on
 ************************/
void Obstacles::set_destroyed(int d)
{
  destroyed = d;
}
