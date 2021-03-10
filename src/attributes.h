#ifndef __ATTRIBUTES_
#define __ATTRIBUTES_

/*********************//*
 * @author Original Development Team
 * @author Jon McKee
 * @brief these are the default stats for a tank object.
 * All values default to 0 but can be set by users or the
 * game map via constructor
 *
 ***********************/
struct attributes
{
    int tankHealth = 0;
    int tankDamage = 0;
    int tankAP = 0;
    int tankShots = 0;
    int tankAmmo = 0;
    int tankRadar = 0;
    int tankRange = 0; 
    attributes( int tH = 0, int tD = 0, int tR = 0, int tS = 0, int tV = 0, int tA = 0, int tRa = 0)  
    {
        tankHealth=tH;
        tankDamage=tD;
        tankAP=tR;
        tankShots=tS;
        tankAmmo=tA;
        tankRadar=tV;
        tankRange=tRa;
    }

};

#endif
