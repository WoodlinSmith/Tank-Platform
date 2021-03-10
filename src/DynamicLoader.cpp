//
// Created by jlee on 10/12/18.
//

#include "DynamicLoader.h"
#include <dlfcn.h>
#include <fstream>

/**
 * @author David Donahue
 * @par Description:
 * Loads all of the given actors from ./tanks/<name>.so.
 * It works by loading the maker() function from each .so and running it
 * to get a pointer to an instance of the class.
 *
 * @param[in] objectNames - names of the actors to load.
 * @return vector of pointers to the loaded actors
 */
vector<Actor*> dynamicTankLoader ( vector<string> objectNames )
{
    vector<Actor*> dynamicTanks;
    string relPath ( "./tanks/" );
    string soPath;
    string symName;


    for ( auto names : objectNames )
    {
        //build up the full relative file path from the given name
        soPath = ( relPath );
        soPath.append ( names );
        soPath.append ( ".so" );

        //get a 'handle' to the .so file, which can be used to load symbols
        void* handle = dlopen ( soPath.c_str(), RTLD_LAZY ); //open the .so
        if ( handle == NULL ) //make sure it opened
            {
                cout << "Failed to open " << names << "\n";
                cout << dlerror() << endl;
            }
        else
            {
                Actor* ( *maker ) () = ( Actor * ( * ) () ) dlsym ( handle,
                                        "maker" ); //get the maker() symbol
                if ( maker == NULL ) //If the symbol was not found in the .so
                    cout << "Failed to load symbol " << symName << '\n';
                else
                    dynamicTanks.push_back ( maker() ); //Run maker() to construct an instance of the class
            }

    }
    return dynamicTanks;

}


