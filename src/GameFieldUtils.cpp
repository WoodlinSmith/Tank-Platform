#include "GameFieldUtils.h"

void checkAllAttributes(int &health, int &actionPoints, int &radar, int &dam, int &ammo, int &range, int width )
{
    clampAttribute(health,8);
    clampAttribute(actionPoints,6);
    clampAttribute(radar,width);
    clampAttribute(dam,8);
    clampAttribute(ammo,10);
    clampAttribute(range,10);
}

void clampAttribute(int &attribute, int maxVal)
{
    if(attribute>maxVal)
        attribute=maxVal;
}

void fixTankAttributes(int &health, int &actionPoints, int &radar, int &damage, int &ammo, int &range, int width)
{
    //If tank was assigned too many SPECIAL points
    //Fix their attributes to half the max for balance
    health=4;
    actionPoints=3;
    radar=width/2;
    damage=4;
    ammo=5;
    range=5;
}