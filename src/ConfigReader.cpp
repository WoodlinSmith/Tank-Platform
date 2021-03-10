#include "ConfigReader.h"

void loadAI ( bool & isQuiet, vector<string> & AINames, string & args,
    vector<pair<int, int>> & tankLocations, vector<string> & tankImages,
    int & wPad, int & hPad )
{
    //Default Tank Images
    const vector<string> AIDefImg = { "images/Default/tankD_U.png",
        "images/Default/tankD_R.png", "images/Default/tankD_D.png",
        "images/Default/tankD_L.png", "images/Default/bulletD.png"
    };

    int i = 0, x = 0, y = 0;
    string name;
    pair<int, int> padCoordPair;
    vector<string> AIImages;

    i = args.find ( ' ' );
    AINames.push_back ( args.substr ( 0, i ) );

    stringstream ( args.substr ( i + 1 ) ) >> x >> y;

    padCoordPair = pair<int, int> ( x + wPad, y + hPad );
    tankLocations.push_back ( padCoordPair );

    for ( x = 0; (unsigned)x < tankLocations.size(); x++ )
        for ( y = x + 1; (unsigned)y < tankLocations.size(); y++ )
            if ( tankLocations.at ( x )
                    == tankLocations.at ( y ) )
            {
                if ( !isQuiet )
                    cout << "Tanks cannot spawn on the same tile!"
                         << endl;

                exit ( 1 );
            }

    i = args.find( ' ', i + 1 ); //skip x
    i = args.find( ' ', i + 1 ); //skip y

    args = args.substr( i + 1 );

    for ( x = 0; x < 5; x++ )
    {
        i = args.find( ' ' ); //skip y
        name = args.substr( 0, i );

        AIImages.push_back( name );
        args = args.substr( i + 1 );

        if ( args == AIImages[x] )
            break;
    }


    if ( AIImages.size() != 5 )
        tankImages.insert( end( tankImages ),
            begin( AIDefImg ), end( AIDefImg ) );

    else
        tankImages.insert( end( tankImages ),
            begin( AIImages ), end( AIImages ) );

    AIImages.clear();
}


void setFieldParams ( string tag, string & args, int & width, int & height,
    int & maxTurns, vector<string> & fieldImgName )
{
    if ( tag == "WIDTH" )
        setAttribute ( args, width, 5, 50 );
    else if ( tag == "HEIGHT" )
        setAttribute ( args, height, 5, 21 );
    else if ( tag == "MAXTURNS" )
        setAttribute ( args, maxTurns, 1, 1000 );
    else if ( tag == "FIELDIMAGE" )
        loadBackImage ( args, fieldImgName );
}

void setAttribute ( string & args, int & attribute, int lowLim, int highLim )
{
    stringstream ( args ) >> attribute;

    if ( attribute < lowLim )
        attribute = lowLim;

    else if ( attribute > highLim )
        attribute = highLim;
}

void loadBackImage ( string & args, vector<string> & fieldImgName )
{
    string name;
    stringstream ( args ) >> name;
    fieldImgName.push_back ( name );
}


void loadObstacleLocations ( string tag, string & args, int width, int height,
    vector<pair<int, int>> tankLoc, vector<pair<int, int>> & obsLoc,
    vector<pair<int, int>> & treeLoc, vector<pair<int, int>> & rockLoc,
    vector<pair<int, int>> & bushLoc, vector<pair<int, int>> & specLoc,
    vector<pair<int, int>> & watLoc, bool & taken, bool & isQuiet )
{
    int x = 0, y = 0;
    pair<int, int> coordinates;

    if ( isObstacle ( tag ) )
    {
        stringstream ( args ) >> x >> y;

        if ( ( ( x > width - 1 ) || ( x < 0 ) || ( y > height - 1 ) 
            || ( y < 0 ) ) && !isQuiet )
            cout << "Invalid obstacle location: (" << x << ", " << y
                << "). Ranges: (0-" << ( width - 1 ) << ", 0-" 
                << ( height - 1 ) << ")\n";

        else
        {
            for ( unsigned int i = 0; i < tankLoc.size(); i++ )
                if ( tankLoc[i].first == x && tankLoc[i].second == y )
                    taken = true;
            if ( !taken )
                for ( unsigned int i = 0; i < obsLoc.size(); i++ )
                    if ( obsLoc[i].first == x && obsLoc[i].second == y )
                        taken = true;

            coordinates = pair<int, int> ( x, y );
            if ( !taken && tag == "TREE" )
                treeLoc.push_back ( coordinates );

            else if ( !taken && tag == "ROCK" )
                rockLoc.push_back ( coordinates );

            else if ( !taken && tag == "BUSH" )
                bushLoc.push_back ( coordinates );

            else if ( !taken && tag == "CRATE" )
                specLoc.push_back ( coordinates );

            else if ( !taken && tag == "WATER" )
                watLoc.push_back ( coordinates );

            else
                obsLoc.push_back ( coordinates );

            taken = false;
        }

    }
}


bool isObstacle ( string tag )
{
    return ( tag == "OBSTACLE" || tag == "TREE" || tag == "ROCK" || tag == "BUSH"
             || tag == "BUSH" || tag == "CRATE" || tag == "WATER" );
}


void loadImages ( string tag, string args, vector<string> & gameImages,
    vector<string> & treeImages, vector<string> & rockImage,
    vector<string> & waterImage, vector<string> & bushImage )
{
    if ( tag == "OBSTACLE_IMAGE" )
        addImage ( args, gameImages );
    else if ( tag == "TREE_IMAGE" )
        addImage ( args, treeImages );
    else if ( tag == "ROCK_IMAGE" )
        addImage ( args, rockImage );
    else if ( tag == "WATER_IMAGE" )
        addImage ( args, waterImage );
    else if ( tag == "BUSH_IMAGE" )
        addImage ( args, bushImage );
}


void addImage ( string args, vector<string> & imgList )
{
    bool done = false;
    int i = 0;
    while ( !done )
    {
        if ( args.find ( ' ' ) == string::npos )
        {
            done = true;
            imgList.push_back ( args );
        }
        else
        {
            i = args.find ( ' ' );
            imgList.push_back ( args.substr ( 0, i ) );
            args = args.substr ( i + 1 );
        }
    }
}


void setTankParams ( string tag, string & args, int & damage, int & health,
    int & ap, int & radar, int & range, int & special, int & ammo, int width )
{
    if ( tag == "DAMAGE" )
        setAttribute ( args, damage, 0, 8 );
    else if ( tag == "HEALTH" )
        setAttribute ( args, health, 0, 8 );
    else if ( tag == "AP" )
        setAttribute ( args, ap, 0, 6 );
    else if ( tag == "RADAR" )
        setAttribute ( args, radar, 0, width );
    else if ( tag == "RANGE" )
        setAttribute ( args, range, 0, 10 );
    else if ( tag == "SPECIAL" )
        setAttribute ( args, special, 0, 20 );
    else if ( tag == "AMMO" )
        setAttribute ( args, ammo, 0, 10 );

}

//SET SPECIAL


void writeConfig ( ofstream & out )
{
    out << "WIDTH 30\n" << "HEIGHT 14\n" << "MAP\n"
     << "xxxxxxxxRRRRRRxxxxxxxxRRRRRRxx\n"
     << "xxxxxxxTWWRRWWTxxxxxxTWWRRWWTx\n"
     << "xxxxxxTTTBTTTBTTxxxxTTTBTTTBTT\n"
     << "xxxxxCxxxxxxxxxxxxxxxxxxxxxxxx\n"
     << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxB\n"
     << "xxxxTxxxxxTxxxxxTxxxxxTxxxxBBT\n"
     << "xxTTBTTxTTBTTxTTBTTxTTBTTxxTTB\n"
     << "xxRxRxRxRxRxRxRxRxRxRxRxRxxRxR\n"
     << "Oxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
     << "Oxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
     << "OxxRxxxxxRxxxxxRxxxxWRxxxxxxxx\n"
     << "xxTTTxxxTTTxxxTTTWWWTTTxxxxxxx\n"
     << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
     << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
     << "#AI LIST: AI <NAME> <STARTX> <STARTY> <UPIMAGE> <RIGHTIMAGE> "
         << "<DOWNIMAGE> <LEFTIMAGE> <BULLETIMAGE>\n\n"
     << "#AI IDLE SPEED: AI_SPEED <750>\n"
     << "AI_SPEED 750\n\n"
     << "#FIELDIMAGE <MAP FILE>\n"
     << "FIELDIMAGE images/green.png\n\n"
     << "#OBSTACLE_IMAGE <IMAGE1> [<IMAGE2>]\n"
     << "OBSTACLE_IMAGE images/tree/tree.png images/rock/rock.png\n"
     << "TREE_IMAGE images/tree/tree.png images/tree/treeb.png "
         << "images/tree/treec.png images/tree/treed.png\n"
     << "BUSH_IMAGE images/bush/bush1.png images/bush/bush2.png "
         << "images/bush/bush3.png images/bush/bush4.png\n"
     << "ROCK_IMAGE images/rock/rock.png images/rock/rockb.png "
         << "images/rock/rockc.png\n"
     << "WATER_IMAGE images/Water/waterTex.png images/Water/waterTexNS.png"
         << " images/Water/waterTexES.png images/Water/waterTexSS.png "
         << "images/Water/waterTexWS.png images/Water/waterTexNES.png "
         << "images/Water/waterTexSES.png images/Water/waterTexSWS.png "
         << "images/Water/waterTexNWS.png images/Water/waterTexEWS.png "
         << "images/Water/waterTexNSS.png images/Water/waterTexNWES.png "
         << "images/Water/waterTexNESS.png images/Water/waterTexSEWS.png "
         << "images/Water/waterTexNWSS.png images/Water/waterTexPond.png\n\n"
     << "#Game Settings\n"
     << "#MAXTURNS 200\n"
     << "MAXTURNS 200\n\n"
     << "#AI_SPEED <750>\n"
     << "AI_SPEED 750\n\n"
     << "#BULLET_SPEED <80>\n"
     << "BULLET_SPEED 80\n\n"
     << "#TANK_SPEED <400>\n"
     << "TANK_SPEED 400\n\n"
     << "#ANIMATION_SPEED <20>\n"
     << "ANIMATION_SPEED 20\n\n"
     << "#DISABLEUI UNCOMMENT TO DISABLE GUI\n"
     << "#DISABLEGUI \n\n"
     << "#TANK RULES\n"
     << "#STAT <AMMOUNT>\n"
     << "#VALID STATS: DAMAGE, HEALTH, RADAR, AP, SPECIAL, RANGE, AMMO\n"
     << "DAMAGE 1\n"
     << "HEALTH 3\n"
     << "RADAR 4\n"
     << "AP 2\n"
     << "SPECIAL 1\n"
     << "RANGE 4\n"
     << "AMMO 6\n";
}
