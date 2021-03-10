/**************************************************************************//**
* @file Menu.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for the Menu class.
* *****************************************************************************/

//header files
#include "Drawable.h"

//function headers
void drawBitmapText ( const char* string, GLfloat x, GLfloat y, GLfloat red, GLfloat green, GLfloat blue );
void drawBitmapTurn ( int turn, GLfloat x, GLfloat y );

/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Initializes the menu with the player the menu is being made for and the stats
* to be printed.
*
* @param[in] id - player id
* @param[in] hp - health
* @param[in] ammo - ammo count
* *****************************************************************************/
Menu::Menu ( int id, int hp, int ammo, int hits, string nameIn, direction dir, int mc, int t )
{
    this->id = id;
    //for(int j = 0; j < 20; j++)
    //    name[j] = '\0';
    turn = t;

    int i = 0;

    while ( unsigned(i) < nameIn.size() && i < 20 )
    {
        name[i] = nameIn[i];
        i++;
    }
    name[i] = '\0';

    screen_x = -0.70;
    screen_y = 0.54;
    health = hp;
    bullet = ammo;
    score = hits;
    angle = 0;
    id > 0 ? bTex = ( id - 1 ) * 5 + 4 : bTex = ( -id - 1 ) * 5 + 4;
    id > 0 ? i = id : i = -id;
    if ( mc == 0 || mc == 1 || mc == 7 )
    {
        tex = ( i - 1 ) * 5 + 0; //up upright upleft
        if ( mc == 1 )
            angle = -45;
        if ( mc == 7 )
            angle = 45;
    }
    if ( mc == 2 )
        tex = ( i - 1 ) * 5 + 1; //right
    
    if ( mc == 3 || mc == 4 || mc == 5 )
    {
        tex = ( i - 1 ) * 5 + 2; //down downright downleft
        if ( mc == 3 )
            angle = 45;
        if ( mc == 5 )
            angle = -45;
    }
    if ( mc == 6 )
        tex = ( i - 1 ) * 5 + 3; //left
    
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
*
* Draws the player stats up in the menu bar.
* *****************************************************************************/
void Menu::draw ( int x, int y )
{
    glColor4ub ( 255, 255, 255, 255 );
    glPushMatrix();

    drawPlayerStats();

    glPopMatrix();
}



/***************************************************************************//**
* @author Chezka Gaddi
* @brief drawIcon
*
* Draws the health and hit icons.
* *****************************************************************************/
void drawIcon ( GLfloat x, GLfloat y, GLuint icon, bool tank, int angle = 1 )
{
    glEnable ( GL_TEXTURE_2D );
    glPushMatrix();
    glTranslatef ( x - 0.85, y + 0.65, -5.0f );
    if ( !tank )
        glBindTexture ( GL_TEXTURE_2D, gameTex[icon] );
    else
        glBindTexture ( GL_TEXTURE_2D, tankTex[icon] );
    glRotatef ( angle, 0, 0, 1 );
    glBegin ( GL_QUADS );
    glTexCoord2f ( 0.0f, 0.0f );
    glVertex3f ( -0.06f, -0.06f,  1.0f );
    glTexCoord2f ( 1.0f, 0.0f );
    glVertex3f ( 0.06f, -0.06f,  1.0f );
    glTexCoord2f ( 1.0f, 1.0f );
    glVertex3f ( 0.06f,  0.06f,  1.0f );
    glTexCoord2f ( 0.0f, 1.0f );
    glVertex3f ( -0.06f,  0.06f,  1.0f );
    glEnd();
    glPopMatrix();
    glDisable ( GL_TEXTURE_2D );
}

/***************************************************************************//**
* @author Jon McKee
* @brief drawAmmo
*
* Draws the ammo icons
* *****************************************************************************/
void drawAmmo ( GLfloat x, GLfloat y, GLuint icon, bool tank, int angle = 1 )
{
    glEnable ( GL_TEXTURE_2D );
    glPushMatrix();
    glTranslatef ( x - 0.85, y + 0.65, -5.0f );
    glBindTexture ( GL_TEXTURE_2D, tankTex[icon] );
    glRotatef ( angle, 0, 0, 1 );
    glBegin ( GL_QUADS );
    glTexCoord2f ( 0.0f, 0.0f );
    glVertex3f ( -0.06f, -0.06f,  1.0f );
    glTexCoord2f ( 1.0f, 0.0f );
    glVertex3f ( 0.06f, -0.06f,  1.0f );
    glTexCoord2f ( 1.0f, 1.0f );
    glVertex3f ( 0.06f,  0.03f,  1.0f );
    glTexCoord2f ( 0.0f, 1.0f );
    glVertex3f ( -0.06f,  0.03f,  1.0f );
    glEnd();
    glPopMatrix();
    glDisable ( GL_TEXTURE_2D );
}
/***************************************************************************//**
* @author Jon McKee
* @brief drawIcon
*
* Draws the health and hit icons.
* *****************************************************************************/
void drawTank ( GLfloat x, GLfloat y, GLuint icon, bool tank, int angle )
{
    glEnable ( GL_TEXTURE_2D );
    glPushMatrix();
    if ( !tank ) //false = bullet  true = tank
        glBindTexture ( GL_TEXTURE_2D, tankTex[icon] );
    else
        glBindTexture ( GL_TEXTURE_2D, tankTex[icon] );
    glTranslatef ( 1.5, 1.2, -5.0f );
    glRotatef ( angle, 0, 0, 1 );
    glTranslatef ( -1.5, -1.2, 5.0f );
    glTranslatef ( x - 0.95, y + 0.75, -5.0f );
    glBegin ( GL_QUADS );
    glTexCoord2f ( 0.0f, 0.0f );
    glVertex3f ( -0.2f, -0.2f,  1.0f );
    glTexCoord2f ( 1.0f, 0.0f );
    glVertex3f ( 0.06f, -0.2f,  1.0f );
    glTexCoord2f ( 1.0f, 1.0f );
    glVertex3f ( 0.06f,  0.06f,  1.0f );
    glTexCoord2f ( 0.0f, 1.0f );
    glVertex3f ( -0.2f,  0.06f,  1.0f );
    glEnd();
    glPopMatrix();
    glDisable ( GL_TEXTURE_2D );
}





/***************************************************************************//**
* @author Chezka Gaddi
* @brief drawTextBox
*
* Draws player stats text box
* *****************************************************************************/
void Menu::drawTextBox ( GLfloat x, GLfloat y )
{
    glEnable ( GL_TEXTURE_2D );
    glPushMatrix();
    glTranslatef ( x - .5, y + 0.6, -5.0f );
    glBindTexture ( GL_TEXTURE_2D, gameTex[3] );
    glBegin ( GL_QUADS );
    glTexCoord2f ( 0.0f, 0.0f );
    glVertex3f ( -0.5f, -1.5f,  1.0f );
    glTexCoord2f ( 1.0f, 0.0f );
    glVertex3f ( 3.0f, -1.5f,  1.0f );
    glTexCoord2f ( 1.0f, 1.0f );
    glVertex3f ( 3.0f,  2.0f,  1.0f );
    glTexCoord2f ( 0.0f, 1.0f );
    glVertex3f ( -0.5f,  2.0f,  1.0f );
    glEnd();
    glPopMatrix();
    glDisable ( GL_TEXTURE_2D );
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief drawPlayerStats
*
* Edits and displays all of the statistics to the screen.
* *****************************************************************************/
void Menu::drawPlayerStats()
{
    // Create text box player stats will go in
    drawTextBox ( screen_x, screen_y );


    //Output name of the player
    drawBitmapText ( name, screen_x - 0.13, screen_y + 0.22,250,250,250 );

    //Output turn
    drawBitmapTurn ( turn, screen_x + 1.40, screen_y + 0.22 );

    glColor3f(250,250,250);

    // Draw health points
    for ( int i = 0; i < health ; i++ )
        drawIcon ( screen_x - .05 + ( 0.14 * i ), screen_y - 0.04, 2, false );

    // Draw number of hits
    for ( int i = 0; i < score ; i++ )
        drawIcon ( ( screen_x + 2.05 ) + 0.1 * i, screen_y - 0.04, 4, false );

    // Draw Ammo
    for ( int i = 0; i < bullet ; i++ )
        drawAmmo ( ( screen_x + 0.69 ) + 0.1 * i, screen_y - 0.04, bTex, true, 90 );

    drawTank ( ( screen_x + 3.25 ), screen_y, tex, true, angle );
}


/***************************************************************************//**
* @author Chezka Gaddi and Woodlin Smith
* @brief drawBitmapText
*
* Generates all of the string statistics to the screen.
* *****************************************************************************/
void drawBitmapText (  const char* string, GLfloat x, GLfloat y, GLfloat red, GLfloat green, GLfloat blue )
{
    glDisable ( GL_TEXTURE_2D );
    const char* c;
    glColor3f ( red, blue, green );
    glRasterPos3f ( x, y, -2.0 );

    for ( c = string; *c != '\0'; c++ )
        glutBitmapCharacter ( GLUT_BITMAP_9_BY_15, *c );
    glutBitmapCharacter ( GLUT_BITMAP_HELVETICA_18, *c );
}

/***************************************************************************//**
* @author Jon McKee and Woodlin Smith
* @brief drawBitmapText
*
* Generates the turn string.
* *****************************************************************************/
void drawBitmapTurn ( int turn, GLfloat x, GLfloat y )
{
    string temp = "Turn: ";
    if ( turn < 10 )
        temp += "  ";
    else if ( turn < 100 )
        temp += " ";
    temp += to_string ( turn );
    drawBitmapText(temp.c_str(),x,y,255,255,255);
}
