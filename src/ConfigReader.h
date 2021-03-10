#ifndef CONFIGREADER_H
#define CONFIGREADER_H


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;


void loadAI( bool & isQuiet, vector<string> & AINames, string & args,
    vector<pair<int, int>> & tankLocations, vector<string> & tankImages,
    int & wPad, int & hPad );

void setFieldParams ( string tag, string & args, int & width, int & height,
    int & maxTurns, vector<string> & fieldImgName );

void setAttribute ( string & args, int & attribute, int lowLim, int highLim );

void loadBackImage ( string & args, vector<string> & fieldImgName );

void loadObstacleLocations ( string tag, string & args, int width, int height,
    vector<pair<int, int>> tankLoc, vector<pair<int, int>> & obsLoc,
    vector<pair<int, int>> & treeLoc, vector<pair<int, int>> & rockLoc,
    vector<pair<int, int>> & bushLoc, vector<pair<int, int>> & specLoc,
    vector<pair<int, int>> & watLoc, bool & taken, bool & isQuiet );

bool isObstacle ( string tag );

void loadImages ( string tag, string args, vector<string> & gameImages,
    vector<string> & treeImages, vector<string> & rockImage,
    vector<string> & waterImage, vector<string> & bushImage );

void addImage ( string args, vector<string> & imgList );

void setTankParams ( string tag, string & args, int & damage, int & health,
    int & ap, int & radar, int & range, int & special, int & ammo, int width );

void writeConfig ( ofstream & out );

#endif
