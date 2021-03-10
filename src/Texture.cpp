/***************************************************************************//**
* @file Texture.cpp
* @author Chezka Gaddi
* @brief Contain the function that creates the game textures
*******************************************************************************/

#include "Texture.h"
#include <iostream>

// Initialize texture arrays
GLuint tankTex[80];      /*!<Texture array for the tanks and their projectiles*/
GLuint gameTex[20];      /*!<Texture array for game constants */
GLuint treeTex[20];      /*!<Texture array for the trees */
GLuint bushTex[20];      /*!<Texture array for the bushes */
GLuint rockTex[20];      /*!<Texture array for the rocks */
GLuint sfxTex[20];       /*<Texture array for the special effects */
GLuint waterTex[30];     /*<Texture array for water tiles */

const vector<string> bImages = {"images/bush/bush1.png",
                                "images/bush/bush2.png", 
                                "images/bush/bush3.png", 
                                "images/bush/bush4.png"};
const vector<string> rImages = {"images/rock/rockc.png", 
                                "images/rock/rockb.png", 
                                "images/rock/rock.png"};
const vector<string> sImages = {"images/seffect/bTrail.png", 
                                "images/seffect/bTrail2.png", 
                                "images/seffect/bTrail3.png", 
                                "images/seffect/bTrail4.png", 
                                "images/seffect/campfire.png", 
                                "images/seffect/explosiona.png", 
                                "images/seffect/explosionsb.png", 
                                "images/seffect/explosionsc.png", 
                                "images/seffect/fire.png", 
                                "images/seffect/fire2.png", 
                                "images/seffect/fire3.png", 
                                "images/seffect/marsh.png", 
                                "images/seffect/smoke.png", 
                                "images/seffect/smoke2.png", 
                                "images/seffect/smoke3.png", 
                                "images/seffect/smoke4.png"};
const vector<string> tImages = {"images/tree/tree.png", 
                                "images/tree/tree.png", 
                                "images/tree/tree.png", 
                                "images/tree/tree.png", 
                                "images/tree/treeS.png", 
                                "images/tree/trees.png"};
const vector<string> gImages = {"images/UI/background.png", 
                                "images/UI/green.png", 
                                "images/UI/heart.png", 
                                "images/UI/textbox.png", 
                                "images/UI/bomb.png", 
                                "images/UI/GAME.png", 
                                "images/UI/hbar.png", 
                                "images/misc/ammo.png", 
                                "images/misc/hedgehog.png"};

/***************************************************************************//**
* @author Chezka Gaddi and Isaac Egermier
* @brief load_texture_array
* 
* @par Description:
* This function takes in a vector of strings, a GLuint array, a size integer, 
* and a bool. The function loads textures from the vector of strings using SOIL
* into the GLuint texture array. It then performs a glBindTexture for GLUT and 
* returns true if successful. The function effectively loads and saves all the 
* textures needed for the game in texture arrays.
*
* @param[in] inputImageStrings - a vector containing the names of the image 
* files to be used for textures
*
* @param[in] textureArray - an array used by soil to hold data on the textures
*
* @param[in] size - an integer specifying the length of the array
*
* @param[in] quiet - a bool that determines whether the function should produce
* verbal output concerning its actions
*
* @returns true if successful
*******************************************************************************/
int loadTextureArray( vector<string> inputImageStrings, GLuint textureArray[], 
    int size )
{
    for ( int i = 0; i < size; i++ )
    {
        const char *c = inputImageStrings[i].c_str();

        textureArray[i] = SOIL_load_OGL_texture(
            c, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

        if ( textureArray[i] == 0 )
            return false;

        glBindTexture( GL_TEXTURE_2D, tankTex[i] );
    }

    return true;
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief LoadGLTextures
*
* Loads and saves all the textures needed for the game in texture arrays.
*******************************************************************************/
int LoadGLTextures( vector <string> images,  vector <string> gameimgs,
	vector <string> trees, vector <string> rocks, vector <string> bushes, 
    vector <string> waters )
{
    // Load in the tank texure information
    loadTextureArray(images,tankTex, images.size() );

    // Load in the tree texure information
    loadTextureArray(tImages,treeTex,tImages.size() );

    // Load in the tree texure information
    loadTextureArray(trees, treeTex, trees.size() );

    // Load in the rock texures information
    loadTextureArray(rImages, rockTex, rImages.size() );

    // Load in the rock texures information
    loadTextureArray(rocks, rockTex, rocks.size() );

    // Load in the bush texure information
    loadTextureArray(bImages, bushTex, bImages.size() );

    // Load in the bush texure information
    loadTextureArray(bImages, bushTex, bushes.size() );

    // Load in the bush texure information
    loadTextureArray(waters, waterTex, waters.size() );

    // Load in constant game images
    loadTextureArray(gImages, gameTex, gImages.size() );

    // Load in sfx game images
    loadTextureArray(sImages, sfxTex, sImages.size() );
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    return true;
}
