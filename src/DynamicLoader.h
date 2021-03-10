//
// Created by jlee on 10/12/18.
//

#ifndef SRC_DYNAMICLOADER_H
#define SRC_DYNAMICLOADER_H

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include "Actor.h"

typedef void* makeTank_Fptr;

vector<Actor*> dynamicTankLoader ( vector<string> objectNames );

#endif //SRC_DYNAMICLOADER_H
