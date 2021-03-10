#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <time.h>

// x = grass
// T = tree
// B = bush
// C = crates
// R = rocks

#define T 1
#define F 0
#define DEFAULTW 30
#define DEFAULTH 13

#define GRASS 'x'
#define TREE 'T'
#define BUSH 'B'
#define CRATE 'C'
#define ROCK 'R'
#define WATER 'W'


using namespace std;

void generateDefaultMap(int width, int height, int map[DEFAULTW][DEFAULTH], char mapC[DEFAULTW][DEFAULTH]);
void printMap(int width, int height, char map[DEFAULTW][DEFAULTH]);
void zeroMap(int width, int height, int map[DEFAULTW][DEFAULTH]);
void fillDefaultMap(int width, int height, int map[DEFAULTW][DEFAULTH], char mapC[DEFAULTW][DEFAULTH]);
void fillNormalMap(int width, int height, int map[DEFAULTW][DEFAULTH], char mapC[DEFAULTW][DEFAULTH]);
void printMapInt(int width, int height, int map[DEFAULTW][DEFAULTH]);
void outputMap(int width, int height, char map[DEFAULTW][DEFAULTH]);
bool checkIsolatedRock(const int i, const int j, int kernel, char map[DEFAULTW][DEFAULTH]);
bool checkIsolatedWater(const int i, const int j, int kernel, char map[DEFAULTW][DEFAULTH]);

vector<int> randomPair( int maxA, int maxB,vector<vector<int>> usedSpace );




// S = special effects (exploding, marsh, campfire, trail, explosion)
int main(int argc, char *argv[])
{
    int mapSkeleton[DEFAULTW][DEFAULTH];
    char map[DEFAULTW][DEFAULTH];

    bool defaultGen = T;

    int seed;

    if(argc == 1)
        seed = 2;
    else
        seed = atoi(argv[1]);
    

    //11 is a good seed, 12 has cool formations, 17 is rock heavy
    srand(seed);

    if(defaultGen == T)
    {
        generateDefaultMap(DEFAULTW, DEFAULTH, mapSkeleton, map);
        //printMap(DEFAULTW, DEFAULTH, map);
    }


    return 0;
}

void generateDefaultMap(int width, int height, int map[DEFAULTW][DEFAULTH], char mapC[DEFAULTW][DEFAULTH])
{
    zeroMap(width, height, map);
    //fillDefaultMap(width, height, map, mapC);
    fillNormalMap(width, height, map, mapC);
    
}

void fillDefaultMap(int width, int height, int map[DEFAULTW][DEFAULTH], char mapC[DEFAULTW][DEFAULTH])
{
    int i = 0, j = 0;
    
    for(i = 0; i < DEFAULTH; i++)
    {
        for(j = 0; j < DEFAULTW; j++)
        {
            map[i][j] = rand() % 5;
        }
    }

    for(i = 0; i < DEFAULTH; i++)
    {
        for(j = 0; j < DEFAULTW; j++)
        {
            if(map[i][j] == 0)
                mapC[i][j] = 'T';
            else
                mapC[i][j] = 'x';  
        }
    }
}


void fillNormalMap(int width, int height, int map[DEFAULTW][DEFAULTH], char mapC[DEFAULTW][DEFAULTH])
{
    int i = 0, j = 0;
    int chance = 0;
    int xAxis = 0, yAxis = 0;
    int xCoord = 0, yCoord = 0;
    
    //generate original number matrix

    for(i = 0; i < DEFAULTH; i++)
    {
        for(j = 0; j < DEFAULTW; j++)
        {
            map[i][j] = rand() % 100;
        }
    }

    //Break into character map

    for(i = 0; i < DEFAULTH; i++)
    {
        for(j = 0; j < DEFAULTW; j++)
        {
            if(map[i][j] >= 7 && map[i][j] < 14) //range of 10
                mapC[i][j] = TREE;
            else if (map[i][j] >= 4 && map[i][j] < 9) //range of 10
                mapC[i][j] = ROCK;
            else if (map[i][j] >= 0 && map[i][j] < 4) //range of 5
                mapC[i][j] = CRATE;
            else if (map[i][j] >= 14 && map[i][j] < 20) //range of 10
                mapC[i][j] = BUSH;
            else if (map[i][j] >= 20 && map[i][j] < 22) //range of 10
                mapC[i][j] = WATER;
            else if (map[i][j] >= 22 && map[i][j] < 100) //range of 45
                mapC[i][j] = GRASS;
        }
    }

    //Optimization of map

    for(i = 2; i < (DEFAULTH - 2); i++)
    {
        for(j = 2; j < (DEFAULTW - 2); j++)
        {
            if(mapC[i][j] == ROCK)
            {
                //check if the rock is isolated

                if(checkIsolatedRock(i, j, 1, mapC) == true)
                {
                    chance = rand() % 70;

                    if (chance < 33)
                    {
                        xAxis = rand() % 3;
                        yAxis = rand() % 3;

                        while(xAxis == 1 && yAxis == 1)
                        {
                            xAxis = rand() % 3;
                            yAxis = rand() % 3;
                        }

                        xAxis -= 1;
                        yAxis -= 1;

                        xCoord = i + xAxis;
                        yCoord = j + yAxis;

                        mapC[xCoord][yCoord] = ROCK; 
                    }
                    else if (chance < 43)
                    {
                        mapC[i-1][j] = ROCK;
                        mapC[i+1][j+1] = ROCK;
                        mapC[i+1][j] = ROCK;
                    }
                    else if (chance < 48)
                    {
                        mapC[i-2][j] = ROCK;
                        mapC[i-1][j] = ROCK;
                        mapC[i+1][j+1] = ROCK;
                        mapC[i+1][j] = ROCK;
                        mapC[i][j-2] = ROCK;
                        mapC[i][j-1] = ROCK;
                    }
                    else if (chance < 53)
                    {
                        mapC[i][j-2] = ROCK;
                        mapC[i][j-1] = ROCK;
                        mapC[i-1][j-1] = ROCK;
                        mapC[i][j+1] = ROCK;
                        mapC[i-2][j] = ROCK;
                        mapC[i-1][j] = ROCK;
                    }
                }






            if(mapC[i][j] == WATER)
            {
                //check if the rock is isolated

                if(checkIsolatedWater(i, j, 1, mapC) == true)
                {
                    chance = rand() % 70;

                    if (chance < 33)
                    {
                        xAxis = rand() % 3;
                        yAxis = rand() % 3;

                        while(xAxis == 1 && yAxis == 1)
                        {
                            xAxis = rand() % 3;
                            yAxis = rand() % 3;
                        }

                        xAxis -= 1;
                        yAxis -= 1;

                        xCoord = i + xAxis;
                        yCoord = j + yAxis;

                        mapC[xCoord][yCoord] = WATER; 
                    }
                    else if (chance < 43)
                    {
                        mapC[i-1][j] = WATER;
                        mapC[i+1][j+1] = WATER;
                        mapC[i+1][j] = WATER;
                    }
                    else if (chance < 48)
                    {
                        mapC[i-2][j] = WATER;
                        mapC[i-1][j] = WATER;
                        mapC[i+1][j+1] = WATER;
                        mapC[i+1][j] = WATER;
                        mapC[i][j-2] = WATER;
                        mapC[i][j-1] = WATER;
                    }
                    else if (chance < 53)
                    {
                        mapC[i][j-2] = WATER;
                        mapC[i][j-1] = WATER;
                        mapC[i-1][j-1] = WATER;
                        mapC[i][j+1] = WATER;
                        mapC[i-2][j] = WATER;
                        mapC[i-1][j] = WATER;
                    }
                }


            }
                
                
            }
        }
    }

    outputMap(width, height, mapC);
}


bool checkIsolatedRock(const int i, const int j, int kernel, char map[DEFAULTW][DEFAULTH])
{
    int k = 0, z = 0, count = 0;
    for(k = -kernel; k <= kernel; k++)
    {
        for(z = -kernel; z <= kernel; z++)
        {
            if(map[i+k][j+z] == ROCK)
            {
                count++;
            }
        }
    }

    if(count > 1)
        return false;
    
    return true;
}

bool checkIsolatedWater(const int i, const int j, int kernel, char map[DEFAULTW][DEFAULTH])
{
    int k = 0, z = 0, count = 0;
    for(k = -kernel; k <= kernel; k++)
    {
        for(z = -kernel; z <= kernel; z++)
        {
            if(map[i+k][j+z] == WATER)
            {
                count++;
            }
        }
    }

    if(count > 1)
        return false;
    
    return true;
}




void printMap(int width, int height, char map[DEFAULTW][DEFAULTH])
{
    int i = 0, j = 0;
    for(i = 0; i < DEFAULTH; i++)
    {
        for(j = 0; j < DEFAULTW; j++)
        {
            cout << map[i][j];
        }

        cout << endl;
    }
}


void printMapInt(int width, int height, int map[DEFAULTW][DEFAULTH])
{
    int i = 0, j = 0;
    for(i = 0; i < DEFAULTH; i++)
    {
        for(j = 0; j < DEFAULTW; j++)
        {
            cout << map[i][j] << " ";
        }

        cout << endl;
    }
}


void zeroMap(int width, int height, int map[DEFAULTW][DEFAULTH])
{
    int i = 0, j = 0;

    for(i = 0; i < DEFAULTH; i++)
    {
        for(j = 0; j < DEFAULTW; j++)
        {
            map[i][j] = 0;
        }
    }
}

void outputMap(int width, int height, char map[DEFAULTW][DEFAULTH])
{
    int i, j;
    ofstream fout;
    vector<int> tempPair={-1,-1};
    vector<vector<int>> coordinates={};
    coordinates.push_back(tempPair);
    fout.open("config.txt");

    srand( time( NULL ) );

    fout << "WIDTH " << width << endl;
    fout << "HEIGHT " << height << endl;
    fout << "MAP" << endl;

    for(i = 0; i < DEFAULTH; i++)
    {
        for(j = 0; j < DEFAULTW; j++)
        {
            fout << map[i][j];
        }
        fout << endl;
    }


    fout << "#AI LIST: AI <NAME> <STARTX> <STARTY> <UPIMAGE> <RIGHTIMAGE> <DOWNIMAGE> <LEFTIMAGE> <BULLETIMAGE>";
    fout << endl;
    tempPair = randomPair(width, height,coordinates);
    coordinates[0]=tempPair;
    fout << "AI SimpleAI " << tempPair[0] << " " << tempPair[1];
    fout << endl;
    
    tempPair = randomPair(width, height,coordinates);
    coordinates.push_back(tempPair);
    fout << "AI SimpleAI " << tempPair[0] << " " << tempPair[1] << " images/Blue/tank-25U.png images/Blue/tank-25R.png images/Blue/tank-25D.png images/Blue/tank-25L.png images/Blue/bulletB.png";
    fout << endl;
    tempPair = randomPair(width, height,coordinates);
    coordinates.push_back(tempPair);
    fout << "AI SimpleAI " << tempPair[0] << " " << tempPair[1] << " images/Red/tank-13U.png images/Red/tank-13R.png images/Red/tank-13D.png images/Red/tank-13L.png images/Red/bulletR.png";
    fout << endl;
    tempPair = randomPair(width, height,coordinates);
    coordinates.push_back(tempPair);
    fout << "AI SimpleAI " << tempPair[0] << " " << tempPair[1] << " images/PurpleBlueTank/PurpleBlueTank-U.png images/PurpleBlueTank/PurpleBlueTank-R.png images/PurpleBlueTank/PurpleBlueTank-D.png images/PurpleBlueTank/PurpleBlueTank-L.png images/PurpleBlueTank/bulletB.png";
    fout << endl;
    tempPair = randomPair(width, height,coordinates);
    coordinates.push_back(tempPair);
    fout << "AI SimpleAI " << tempPair[0] << " " << tempPair[1] << " images/BWTank/BWTank-U.png images/BWTank/BWTank-R.png images/BWTank/BWTank-D.png images/BWTank/BWTank-L.png images/BWTank/bulletBW.png";
    fout << endl;
    tempPair = randomPair(width, height,coordinates);
    coordinates.push_back(tempPair);
    fout << "AI SimpleAI " << tempPair[0] << " " << tempPair[1] << " images/BluePinkTank/BluePinkTank-U.png images/BluePinkTank/BluePinkTank-R.png images/BluePinkTank/BluePinkTank-D.png images/BluePinkTank/BluePinkTank-L.png images/BluePinkTank/bulletC.png";
    fout << endl;
    tempPair = randomPair(width, height,coordinates);
    coordinates.push_back(tempPair);
    fout << "AI SimpleAI " << tempPair[0] << " " << tempPair[1] << " images/GreenBlueTank/GreenBlueTank-U.png images/GreenBlueTank/GreenBlueTank-R.png images/GreenBlueTank/GreenBlueTank-D.png images/GreenBlueTank/GreenBlueTank-L.png images/GreenBlueTank/bulletLi.png";
    fout << endl;
    tempPair = randomPair(width, height,coordinates);
    coordinates.push_back(tempPair);
    fout << "AI SimpleAI " << tempPair[0] << " " << tempPair[1] << " images/GreenPurpleTank/GreenPurpleTank-U.png images/GreenPurpleTank/GreenPurpleTank-R.png images/GreenPurpleTank/GreenPurpleTank-D.png images/GreenPurpleTank/GreenPurpleTank-L.png images/GreenPurpleTank/bulletP.png";
    fout << endl;
    tempPair = randomPair(width, height,coordinates);
    coordinates.push_back(tempPair);
    fout << "AI SimpleAI " << tempPair[0] << " " << tempPair[1] << " images/RedBlueTank/RedBlueTank-U.png images/RedBlueTank/RedBlueTank-R.png images/RedBlueTank/RedBlueTank-D.png images/RedBlueTank/RedBlueTank-L.png images/RedBlueTank/bulletR.png";
    fout << endl;
    tempPair = randomPair(width, height,coordinates);
    coordinates.push_back(tempPair);
    fout << "AI SimpleAI " << tempPair[0] << " " << tempPair[1] << " images/WhiteTank/WhiteTank-U.png images/WhiteTank/WhiteTank-R.png images/WhiteTank/WhiteTank-D.png images/WhiteTank/WhiteTank-L.png images/WhiteTank/bulletD.png";
    fout << endl;
    fout << "#FIELDIMAGE <MAP FILE>";
    fout << endl;
    fout << "FIELDIMAGE images/city.png";
    fout << endl;
    fout << "#OBSTACLE_IMAGE <IMAGE1> [<IMAGE2>]";
    fout << endl;
    fout << "OBSTACLE_IMAGE images/tree/tree.png images/rock/rock.png";
    fout << endl;
    fout << "TREE_IMAGE images/tree/tree.png images/tree/tree.png images/tree/tree.png images/tree/tree.png";
    fout << endl;
    fout << "BUSH_IMAGE images/bush/bush1.png images/bush/bush2.png images/bush/bush3.png images/bush/bush4.png";
    fout << endl;
    fout << "ROCK_IMAGE images/rock/rock.png images/rock/rockb.png images/rock/rockc.png";
    fout << endl;
    fout << "WATER_IMAGE images/Water/waterTex.png images/Water/waterTexNS.png images/Water/waterTexES.png images/Water/waterTexSS.png images/Water/waterTexWS.png images/Water/waterTexNES.png images/Water/waterTexSES.png images/Water/waterTexSWS.png images/Water/waterTexNWS.png images/Water/waterTexEWS.png images/Water/waterTexNSS.png images/Water/waterTexNWES.png images/Water/waterTexNESS.png images/Water/waterTexSEWS.png images/Water/waterTexNWSS.png images/Water/waterTexPond.png";
    fout << endl;
    fout << "#Max Turns <200>";
    fout << endl;
    fout << "MAXTURNS 200i";
    fout << endl;
    fout << "#TANK RULES";
    fout << endl;
    fout << "#STAT <AMMOUNT>";
    fout << endl;
    fout << "#VALID STATS: DAMAGE, HEALTH, RADAR, AP, SPECIAL, RANGE, AMMO";
    fout << endl;
    fout << "DAMAGE 2";
    fout << endl;
    fout << "HEALTH 2";
    fout << endl;
    fout << "RADAR 4";
    fout << endl;
    fout << "AP 2";
    fout << endl;
    fout << "SPECIAL 1";
    fout << endl;
    fout << "RANGE 4";
    fout << endl;
    fout << "AMMO 6";
    fout << endl;
    fout << "#AI IDLE SPEED: AI_SPEED <750>";
    fout << endl;
    fout << "AI_SPEED 750";
    fout << endl;
    fout << "#ANIMATION SPEED: ANIMATION_SPEED <20>";
    fout << endl;
    fout << "ANIMATION_SPEED 20";
    fout << endl;
    fout << "#BULLET SPEED: BULLET_SPEED <80>";
    fout << endl;
    fout << "BULLET_SPEED 80";
    fout << endl;
    fout << "#TANK SPEED: TANK_SPEED <400>";
    fout << endl;
    fout << "TANK_SPEED 400";
    fout << endl;
    fout << "#DISABLEGUI Disables GUI";
    fout << endl;
    fout << "#DISABLEGUI";
    fout << endl;

    fout.close();
}


vector<int> randomPair( int maxA, int maxB, vector<vector<int>> usedSpace )
{
    unsigned int i=0;
    vector<int> rPair = { 0, 0 };
    while(i<usedSpace.size())
    {
        rPair.at( 0 ) = rand() % ( maxA + 1 );
        rPair.at( 1 ) = rand() % ( maxB + 1 );
        if(!(rPair[0]==usedSpace[i][0]&&rPair[1]==usedSpace[i][1]))
            i++;
    }    

    return rPair;
}
