/***************************************************************************//**
* @file Texture.h
* @author Chezka Gaddi
* @brief Contains libraries needed for loading textures
*******************************************************************************/
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <GL/glut.h>
#include <fstream>
#include "SOIL.h"
#include "global.h"

using namespace std;

//int LoadGLTextures(vector <string>,vector <string>);
int LoadGLTextures( vector <string> images, vector <string> gameimgs,
	vector <string> trees, vector <string> rocks,
	vector <string> bushes, vector <string> waters );

int loadTextureArray( vector<string> inputImageStrings, GLuint textureArray[],
	int size );

#endif
