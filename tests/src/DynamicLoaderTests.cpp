#include "catch.hpp"
#include <DynamicLoader.h>
#include <vector>
#include <string>
#include <Actor.h>
#include <MapData.h>
#include <direction.h>
#include <PositionData.h>


TEST_CASE("DynamicTankLoader returns a vector of Actor *")
{
    std::vector<Actor *> actors = dynamicTankLoader(std::vector<std::string>(0));
    REQUIRE(actors.size() == 0);
}

TEST_CASE("DynamicTankLoader can load a tank")
{
    std::vector<std::string> actNames = {"SimpleAI"};
    std::vector<Actor *> actors = dynamicTankLoader(actNames);
    REQUIRE(actors.size() == 1);
}
//TEST_CASE("DynamicTankLoader can load a non-SimpleAI tank")
//{
//    std::vector<std::string> actNames = {"AsciiTankActor"};
//    std::vector<Actor *> actors = dynamicTankLoader(actNames);
//    REQUIRE(actors.size() == 1);
//}
TEST_CASE("The dynamically loaded tanks actually work")
{
    std::vector<std::string> actNames = {"SimpleActor"};
    std::vector<Actor *> actors = dynamicTankLoader(actNames);
    REQUIRE(actors[0]->move(MapData(), PositionData()) == UP); //SimpleActor returns UP by default
}
