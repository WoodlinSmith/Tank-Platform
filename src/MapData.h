/**
 * @file
 * @brief
 * struct that contains the map and the dimensions of the field.
 */

#ifndef __MAP_DATA_H
#define __MAP_DATA_H

#include <vector>
#include <ostream>
#include <algorithm>

using namespace std;
/*******************************************************************//**
 * @author David Donahue
 *
 * @struct MapData
 * @par Description:
 * The map ADT for the platform
 *
 *
 **********************************************************************/
struct MapData
{
        /** row-major-order list the ID's of anything on the tiles on the map (tanks, projectiles, and obstacles) */
        vector<int> map;

        /*!< row-major-order map of obstacles, true means that an obstacle is present */
        vector<int> obstacleMap;
        vector<int> healthMap;

        int width;  /*!< The width value of the map */
        int height; /*!< The height value of the map */

	//void printMap ( vector<int> storedMap ); /*!< Print the specified map as a 2d ascii map */
        MapData ( int w, int h );
        MapData();
        void printMap ( vector<int> storedMap ); /*!< Print the specified map as a 2d ascii map */
};

/* overload << to display to console */
ostream& operator<< ( ostream& output, const MapData& mapInfo );

#endif
