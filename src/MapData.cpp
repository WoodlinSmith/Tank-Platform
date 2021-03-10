/** @file
 @brief overloaded output function for the mapdata structure.  Only outputs the game obstacle map.
 */

#include "MapData.h"
#include <iostream>

//Constructor for the MapData class
MapData::MapData()
{

}
/*****************//*
 * Author Original Developers
 * Constructor for the MapData object.  Resizes and creates a proper size obstacleMap
 *
 *******************/
MapData::MapData ( int w, int h ) : width ( w ), height ( h )
{
    map.resize ( w * h );
    obstacleMap.resize ( w * h );
    std::fill ( map.begin(), map.end(), 0 );
    std::fill ( obstacleMap.begin(), obstacleMap.end(), false );
}

std::ostream& operator<< ( std::ostream& output, const MapData& mapInfo )
{
    int i, j;
    //ANSI Stuff
    output << "\x1B[2J"; // clear screen and home cursor
    output << " ";

    //Outputting the overall field of the map 
    for ( j = 0; j < mapInfo.width; ++j )
    {
        output << "   " << j << "  ";
        
        if ( j < 10 )
            output << " ";
    }

    output << '\n' << ' ';

    for ( j = 0; j < mapInfo.width; ++j )
        output << " ______";
    
    output << '\n';
    
    //Output a grid structure for the map
    for ( i = 0; i < mapInfo.height; ++i )
    {
        output << " |";
        for ( j = 0; j < mapInfo.width; ++j ) //top of cell
            output << "      |";

        output << "\n |";
        for ( j = 0; j < mapInfo.width; ++j ) // top of the 'sprite'
        {
            if ( mapInfo.map[j + i * mapInfo.width] > 0 ) //tank actor (top is 2 circles)
                output << "  o-o |";

            else if ( mapInfo.obstacleMap[j + i * mapInfo.width] ) //Obstacle
                output << "******|";

            else
                output << "      |";
        }

        output << "\n" << i << "|";

        for ( j = 0; j < mapInfo.width; ++j ) //middle of cell
        {
            if ( mapInfo.map[j + i * mapInfo.width] > 0 ) //tank actor (Tank represented as a pipe)
                output << "  |" << mapInfo.map[j + i * mapInfo.width] << "| |";

            else if ( mapInfo.map[j + i * mapInfo.width] < 0 ) // projectile actor (Projectile is a *)
                output << "   *  |";

            else if ( mapInfo.obstacleMap[j + i * mapInfo.width] ) //Obstacle (Obstacle is a bunch of stars)
                output << "******|";

            else
                output << "      |";
        }

        output << "\n" << " |";

        for ( j = 0; j < mapInfo.width; ++j ) //bottom of 'sprite'
        {
            if ( mapInfo.map[j + i * mapInfo.width] > 0 ) //tank actor (tank is represented as circles)
                output << "  o-o |";

            else if ( mapInfo.obstacleMap[j + i * mapInfo.width] ) //Obstacle
                output << "******|";

            else
                output << "      |";
        }

        output << "\n |";
        for ( j = 0; j < mapInfo.width; ++j ) //bottom of cell
            output << "______|";

        output << '\n'; //end of row
    }

    return output;
}



/****************//*
 * @ author Jon McKee
 * @ brief a printMap function to any specified map array as a 2d ascii map
 *
 ******************/
void MapData::printMap ( vector<int> storedMap )
{
    for ( int i = 0; i < height; i++ )
    {
        for ( int j = 0; j < width; j++ )
        {
            cout << storedMap[j + i * width] << " ";
            if ( j == width - 1 )
                cout << "\n";
        }
    }
}


