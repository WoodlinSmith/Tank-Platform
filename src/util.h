/***************************************************************************//**
* @file util.h
* @author Chezka Gaddi
* @brief Contains all utility function prototypes
*******************************************************************************/
#ifndef __UTIL_H
#define __UTIL_H

#include "callbacks.h"
#include "event.h"
#include "Texture.h"

void initOpenGL(int, char**, int, int, gameMode);
//void utilityCentral(int, char**, Event *);
void utilityCentral( gameMode, Event * );
#endif
