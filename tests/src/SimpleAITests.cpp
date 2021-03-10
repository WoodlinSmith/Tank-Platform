#include "catch.hpp"
#include <SimpleAI.h>
#include <MapData.h>
#include <PositionData.h>
#include <iostream>
#include<SimpleActor.h>
#include<GameField.h>
#include<Actor.h>
TEST_CASE("SimpleAI constructs")
{
    SimpleAI ai;
    REQUIRE(sizeof(ai) > 0);
}
TEST_CASE("SimpleAI does not attack when no other actors are present")
{
    SimpleAI ai;
    MapData map(1,1); //1x1 map
    PositionData pos(1, 1, 0, 0, 2); //ID of 1, health of 1, position 0,0
    map.map[0] = 1; //place tank on the map

    REQUIRE(ai.attack(map, pos) == STAY);
}
TEST_CASE("SimpleAI attacks the nearest actor")
{
    SimpleAI ai;
    MapData map(1,2); //1x2 map
    PositionData pos(1, 1, 0, 0, 2); //ID of 1, health of 1, position 0,0
    map.map[0] = 1; //place AI on the map
    map.map[1] = 2; //place enemy tank on map

    REQUIRE(ai.attack(map, pos) == DOWN);
}
TEST_CASE("SimpleAI moves toward the nearest enemy tank")
{
    SimpleAI ai;
    MapData map(1,3); //1x3 map
    PositionData pos(1, 1, 0, 0, 2); //ID of 1, health of 1, position 0,0
    map.map[0] = 1; //place AI on the map
    map.map[2] = 2; //place enemy tank on map

    REQUIRE(ai.move(map, pos) == DOWN);
}
TEST_CASE("SimpleAI stays in place if no other tanks are present")
{
    SimpleAI ai;
    MapData map(1,3); //1x3 map
    PositionData pos(1, 1, 0, 0, 2); //ID of 1, health of 1, position 0,0
    map.map[0] = 1; //place AI on the map

    REQUIRE(ai.move(map, pos) == STAY);
}
TEST_CASE("SimpleAI stays in place if only projectiles are present")
{
    SimpleAI ai;
    MapData map(1,3); //1x3 map
    PositionData pos(1, 1, 0, 0, 2); //ID of 1, health of 1, position 0,0
    map.map[0] = 1; //place AI on the map
    map.map[2] = -2; //enemy projectile

    REQUIRE(ai.move(map, pos) == STAY);
}
TEST_CASE("SimpleAI does not crash into other actors")
{
    SimpleAI ai;
    MapData map(1,3); //1x3 map
    PositionData pos(1, 1, 0, 0, 2); //ID of 1, health of 1, position 0,0
    map.map[0] = 1; //place AI on the map
    map.map[1] = 2; //enemy projectile

    REQUIRE(ai.move(map, pos) == STAY);
}
TEST_CASE("SimpleAI avoids obstacles below")
{
    SimpleAI ai;
    MapData map(3,3); //3x3 map
    PositionData pos(1, 1, 1, 0); //ID of 1, health of 1, position 1,0
    map.map[1] = 1; //place AI on the map at 1,0
    map.map[7] = 2; //enemy at 1,2
    map.obstacleMap[4] = true; //obstacle at 1,1
    REQUIRE((ai.move(map, pos) == LEFT || ai.move(map,pos) == RIGHT));
}
TEST_CASE("SimpleAI avoids obstacles to the left")
{
    SimpleAI ai;
    MapData map(3,3); //3x3 map
    PositionData pos(1, 1, 2, 1); //ID of 1, health of 1, position 2,1
    map.map[5] = 1; //place AI on the map at 2,1
    map.map[3] = 2; //enemy at 0,1
    map.obstacleMap[4] = true; //obstacle at 1,1
    REQUIRE((ai.move(map, pos) == UP || ai.move(map,pos) == DOWN));
}

TEST_CASE("SimpleAI avoids obstacles above")
{
    SimpleAI ai;
    MapData map(3,3); //3x3 map
    PositionData pos(1, 1, 1, 2); //ID of 1, health of 1, position 1,2
    map.map[7] = 1; //place AI on the map at 1,2
    map.map[1] = 2; //enemy at 1,0
    map.obstacleMap[4] = true; //obstacle at 1,1
    REQUIRE((ai.move(map, pos) == RIGHT || ai.move(map,pos) == LEFT));
}
TEST_CASE("SimpleAI avoids obstacles to the right")
{
    SimpleAI ai;
    MapData map(3,3); //3x3 map
    PositionData pos(1, 1, 0, 1); //ID of 1, health of 1, position 0, 1
    map.map[3] = 1; //place AI on the map at 0, 1
    map.map[5] = 2; //enemy at 2, 1
    map.obstacleMap[4] = true; //obstacle at 1,1
    REQUIRE((ai.move(map, pos) == UP || ai.move(map,pos) == DOWN));
}

TEST_CASE("SimpleAI avoids obstacles to the top-right")
{
    SimpleAI ai;
    MapData map(3,3); //3x3 map
    PositionData pos(1, 1, 1, 1); //ID of 1, health of 1, position 1, 1
    map.map[4] = 1; //place AI on the map at 1, 1
    map.map[6] = 2; //enemy at 2, 0
    map.obstacleMap[2] = true; //obstacle at 0, 2
    REQUIRE(ai.move(map, pos) != UPRIGHT);
}

TEST_CASE("SimpleAI avoids obstacles to the top-left")
{
    SimpleAI ai;
    MapData map(3,3); //3x3 map
    PositionData pos(1, 1, 1, 1); //ID of 1, health of 1, position 1, 1
    map.map[4] = 1; //place AI on the map at 1, 1
    map.map[8] = 2; //enemy at 2, 2
    map.obstacleMap[0] = true; //obstacle at 0,0
    REQUIRE(ai.move(map, pos) != UPLEFT);
}

TEST_CASE("SimpleAI avoids obstacles to the bottom-left")
{
    SimpleAI ai;
    MapData map(3,3); //3x3 map
    PositionData pos(1, 1, 1, 1); //ID of 1, health of 1, position 1, 1
    map.map[4] = 1; //place AI on the map at 1, 1
    map.map[2] = 2; //enemy at 0, 2
    map.obstacleMap[6] = true; //obstacle at 2,0
    REQUIRE(ai.move(map, pos) != DOWNLEFT);
}

TEST_CASE("SimpleAI avoids obstacles to the bottom-right")
{
    SimpleAI ai;
    MapData map(3,3); //3x3 map
    PositionData pos(1, 1, 1, 1); //ID of 1, health of 1, position 1, 1
    map.map[4] = 1; //place AI on the map at 1, 1
    map.map[0] = 2; //enemy at 0,0
    map.obstacleMap[8] = true; //obstacle at 2,2
    REQUIRE(ai.move(map, pos) != DOWNRIGHT);
}


TEST_CASE ("AI will move through bushes to get to target")
{
	SimpleActor *tank1 = new SimpleActor();
	SimpleActor *tank2 = new SimpleActor();

	ActorInfo tank_1(tank1, 100, 0, 0, 1, 2, 2, 2);

	ActorInfo tank_2(tank2, 100, 0, 2, 1, 3, 2, 2);


	std::vector<ActorInfo> actor_list = {tank_1, tank_2};

	GameField gamefield(3, 3, actor_list);


	gamefield.addObstacle(0, 0, 'R');

	gamefield.addObstacle(0, 2, 'R');

	gamefield.addObstacle(1, 1, 'B');

	gamefield.addObstacle(1, 0, 'R');

	gamefield.addObstacle(1, 2, 'R');

	tank1->setMove(RIGHT);
	tank1->setAttack(STAY);

	tank2->setMove(STAY);
	tank2->setAttack(STAY);
	gamefield.nextTurn();

	std::vector<int> expected_map = {0, 0, 0,  0, 2, 3,  0, 0, 0 };

	std::vector<int> actual_map = gamefield.getMap();

	REQUIRE (expected_map == actual_map);

}

TEST_CASE ("AI will not move through water to get to target")
{
        SimpleActor *tank1 = new SimpleActor();
        SimpleActor *tank2 = new SimpleActor();

        ActorInfo tank_1(tank1, 100, 0, 0, 1, 2, 2, 2);

        ActorInfo tank_2(tank2, 100, 0, 2, 1, 3, 2, 2);


        std::vector<ActorInfo> actor_list = {tank_1, tank_2};

        GameField gamefield(3, 3, actor_list);


        gamefield.addObstacle(0, 0, 'R');

        gamefield.addObstacle(0, 2, 'R');

        gamefield.addObstacle(1, 1, 'W');

        gamefield.addObstacle(1, 0, 'R');

        gamefield.addObstacle(1, 2, 'R');

        tank1->setMove(RIGHT);
        tank1->setAttack(STAY);

        tank2->setMove(STAY);
        tank2->setAttack(STAY);
        gamefield.nextTurn();

        std::vector<int> expected_map = {0, 0, 0,  2, 0, 3,  0, 0, 0 };

        std::vector<int> actual_map = gamefield.getMap();

        REQUIRE (expected_map == actual_map);

}

TEST_CASE ("AI will not move through rocks to get to target")
{
        SimpleActor *tank1 = new SimpleActor();
        SimpleActor *tank2 = new SimpleActor();

        ActorInfo tank_1(tank1, 100, 0, 0, 1, 2, 2, 2);

        ActorInfo tank_2(tank2, 100, 0, 2, 1, 3, 2, 2);


        std::vector<ActorInfo> actor_list = {tank_1, tank_2};

        GameField gamefield(3, 3, actor_list);


        gamefield.addObstacle(0, 0, 'R');

        gamefield.addObstacle(0, 2, 'R');

        gamefield.addObstacle(1, 1, 'R');

        gamefield.addObstacle(1, 0, 'R');

        gamefield.addObstacle(1, 2, 'R');

        tank1->setMove(RIGHT);
        tank1->setAttack(STAY);

        tank2->setMove(STAY);
        tank2->setAttack(STAY);
        gamefield.nextTurn();

        std::vector<int> expected_map = {0, 0, 0,  2, 0, 3,  0, 0, 0 };

        std::vector<int> actual_map = gamefield.getMap();

        REQUIRE (expected_map == actual_map);
}
