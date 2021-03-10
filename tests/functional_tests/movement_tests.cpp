////////////////////////////////////////////////////////////////////////////////
// File name: movement_test.cpp
// Author: Riley Kopp
// Description: This file will test the movement of the tank across the
//              gamefield.
// Date: 19 Sep 18
////////////////////////////////////////////////////////////////////////////////


// Include(s)
#include <catch.hpp>
#include <GameField.h>
#include <vector>
#include <iostream>
#include <direction.h>
#include <SimpleActor.h>

////////////////////////////////////////////////////////////////////////////////
// FEATURE:
//    The tanks can move around the game field and react with walls and
//    other tanks.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Single tank basic Movement
////////////////////////////////////////////////////////////////////////////////
SCENARIO("The tank moves around the gamefield")
{
    GIVEN("A tank and a working gamefield")
    {
        // Create Tank
        SimpleActor * tank = nullptr;
        tank = new SimpleActor();
        direction moveUp = UP;
        direction moveDown = DOWN;
        direction moveLeft = LEFT;
        direction moveRight = RIGHT;
        direction moveStay = STAY;
        REQUIRE(tank != nullptr);

        // Load Tanks
        ActorInfo tank_s(tank, 100, 0, 1, 1, 2, 2, 6);

        // Add a tank into a vector of actors
        std::vector<ActorInfo> actor_list = {tank_s};

        

        GameField gamefield(3, 3, actor_list);

        WHEN("The tank tries to move up")
        {
            tank->setMove(moveUp);
            tank->setAttack(STAY);
            gamefield.nextTurn();

            THEN("The tank moves up")
            {
                //Compare map with the initial map
                std::vector<int> expected_map = { 0, 2, 0, 0, 0, 0, 0, 0, 0 };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }

        WHEN("The tank tries to move down")
        {
            std::vector<int> expected_map = { 0, 0, 0, 0, 2, 0, 0, 0, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
            tank->setMove(moveDown);
            gamefield.nextTurn();

            THEN("The tank moves down")
            {
                //Compare map with the initial map
                std::vector<int> expected_map = { 0, 0, 0, 0, 0, 0, 0, 2, 0 };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }

        WHEN("The tank tries to move right")
        {
            std::vector<int> expected_map = { 0, 0, 0, 0, 2, 0, 0, 0, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
            tank->setMove(moveRight);
            gamefield.nextTurn();
            THEN("The tank moves right")
            {
                //Compare map with the initial map
                std::vector<int> expected_map = { 0, 0, 0, 0, 0, 2, 0, 0, 0 };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }

        WHEN("The tank tries to move left")
        {
            std::vector<int> expected_map = { 0, 0, 0, 0, 2, 0, 0, 0, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
            tank->setMove(moveLeft);
            gamefield.nextTurn();
            THEN("The tank moves left")
            {
                //Compare map with the initial map
                std::vector<int> expected_map = { 0, 0, 0, 2, 0, 0, 0, 0, 0 };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Hitting Wall Boundries
////////////////////////////////////////////////////////////////////////////////

SCENARIO("The tank encounters a wall")
{
    GIVEN("A tank and a gamefield")
    {
        // Create Tank
        SimpleActor * tank = nullptr;
        tank = new SimpleActor();

        direction moveUp = UP;
        direction moveDown = DOWN;
        direction moveLeft = LEFT;
        direction moveRight = RIGHT;
        direction moveStay = STAY;
	direction moveUpRight = UPRIGHT;
	direction moveDownRight = DOWNRIGHT;
	direction moveUpLeft = UPLEFT;
	direction moveDownLeft = DOWNLEFT;
        REQUIRE(tank != nullptr);

        // Load Tanks
        ActorInfo   tank_s(tank, 100, 0, 0, 0, 2, 5);

        // Add a tank into a vector of actors
        std::vector<ActorInfo> actor_list = {tank_s};

        GameField gamefield(1, 1, actor_list);

        WHEN("A tank hits a wall going up")
        {
            tank->setMove(moveUp);
            gamefield.nextTurn();
            THEN("The tank cannot move up anymore")
            {
                std::vector<int> expected_map = { 2 };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }

        WHEN("A tank hits a wall going left")
        {
            tank->setMove(moveLeft);
            gamefield.nextTurn();
            THEN("The tank cannot move up anymore")
            {
                std::vector<int> expected_map = { 2 };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }

        WHEN("A tank hits a wall going right")
        {
            tank->setMove(moveRight);
            gamefield.nextTurn();
            THEN("The tank cannot move up anymore")
            {
                std::vector<int> expected_map = { 2 };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }

        WHEN("A tank hits a wall going down")
        {
            tank->setMove(moveDown);
            gamefield.nextTurn();
            THEN("The tank cannot move up anymore")
            {
                std::vector<int> expected_map = { 2 };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }

    
    	WHEN("A tank hits a wall going right up ")
	{
		tank->setMove(moveUpRight);
		gamefield.nextTurn();
		THEN ("Tank cannot move up right anymore")
		{
			std::vector<int> expected_map = {2};
			std::vector<int> actual_map = gamefield.getMap();
			REQUIRE(expected_map == actual_map);


		}
		
	}

	WHEN("A tank hits a wall going right down ")
        {
                tank->setMove(moveDownRight);
                gamefield.nextTurn();
                THEN ("Tank cannot move down right anymore")
                {
                        std::vector<int> expected_map = {2};
                        std::vector<int> actual_map = gamefield.getMap();
                        REQUIRE(expected_map == actual_map);


                }

        }

	WHEN("A tank hits a wall going left up ")
        {
                tank->setMove(moveUpLeft);
                gamefield.nextTurn();
                THEN ("Tank cannot up left anymore")
                {
                        std::vector<int> expected_map = {2};
                        std::vector<int> actual_map = gamefield.getMap();
                        REQUIRE(expected_map == actual_map);


                }

        }

	WHEN("A tank hits a wall going down left ")
        {
                tank->setMove(moveDownLeft);
                gamefield.nextTurn();
                THEN ("Tank cannot move down left anymore")
                {
                        std::vector<int> expected_map = {2};
                        std::vector<int> actual_map = gamefield.getMap();
                        REQUIRE(expected_map == actual_map);


                }

       }
    
    }
}

////////////////////////////////////////////////////////////////////////////////
// Tank Collision Test
////////////////////////////////////////////////////////////////////////////////

SCENARIO("Tanks drive right into each other")
{
    GIVEN("A 3 x 1 Game Field with two tanks")
    {
        SimpleActor * tank_1 = nullptr;
        SimpleActor * tank_2 = nullptr;

        direction moveRight = RIGHT;
        direction moveLeft = LEFT;

        tank_1 = new SimpleActor();
        tank_2 = new SimpleActor();

        ActorInfo tank_1_s(tank_1, 100, 1000, 0, 0, 1, 2, 6);
        ActorInfo tank_2_s(tank_2, 100, 1000, 2, 0, 2, 2, 6);

        std::vector<ActorInfo> actor_list = {tank_1_s, tank_2_s};

        GameField gamefield(3, 1, actor_list);

        WHEN("Tanks try to move into the same spot")
        {
            tank_1->setMove(moveRight);
            tank_2->setMove(moveLeft);
            gamefield.nextTurn();
            THEN("the first tank dies and the other takes a portion of the damage")
            {
                REQUIRE(gamefield.getActors().size() == 1);
            }
        }

    }
}
