#ifndef __PROJECTILEUTILS__H__
#define __PROJECTILEUTILS__H__

#include <GL/freeglut.h>
#include "direction.h"
#include "global.h"

int setAngle( direction dir );

void enableGL( GLfloat screenX, GLfloat screenY, float offstX, float offstY,
    int angle, bool bind, int turnVal );

void disableGL();

void drawTrail( float xScal, float yScal, float sizeMod, float extMod,
    float xMod1, float xMod2 );

#endif // !1