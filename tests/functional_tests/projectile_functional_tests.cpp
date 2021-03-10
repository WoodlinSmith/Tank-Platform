////////////////////////////////////////////////////////////////////////////////
// File name: projectile_functional_tests.cpp
// Author: Adam Lenox
// Description: This file will test the projectile, directions, range,
// projectile to projectile collisions, movement, wall to projectile collision
// projectile hit and miss.
//
// Date: 27 Sep 18
////////////////////////////////////////////////////////////////////////////////

// Include(s)
#include <catch.hpp>
#include <GameField.h>
#include <SimpleActor.h>
#include <vector>
#include <iostream>
#include <catch.hpp>

////////////////////////////////////////////////////////////////////////////////
// FEATURE:
//    The projectiles can move around the game field and react with walls and
//    tanks and other projectiles.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Single projectile basic Movement, hit the wall on 2nd turn
////////////////////////////////////////////////////////////////////////////////
SCENARIO("The projectile moves around the gamefield")
{
    GIVEN("A tank and a vertical gamefield")
    {
        // Create tank
        SimpleActor * tank = nullptr;
        tank = new SimpleActor();
        REQUIRE(tank != nullptr);

        // Load a tank
        ActorInfo tank_s(tank, 100,0,0,6,2,2,6);

        //Add a tank into a vector of actors
        std::vector<ActorInfo> actor_list = {tank_s};


        // Generate the gamefield with a map that looks like this:
        // 0
        // 0
        // 0
        // 0
        // 0
        // 0
        // 2
        // 0
        // 0
        // 0
        // 0
        // 0
        // 0
        GameField gamefield(1, 13, actor_list, 1);

        WHEN("The tank tries to shoot up")
        {
            tank->setAttack(UP);
            tank->setMove(STAY);
            gamefield.nextTurn();
            THEN("The projectile goes up")
            {
                //compare actual map to expected map
                std::vector<int> expected_map = {-2, 0, 0, 0,
                                                 0, 0, 2, 0,
                                                 0, 0, 0, 0, 0
                                                };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
            tank->setAttack(STAY);
            tank->setMove(STAY);
            gamefield.nextTurn();
            THEN("The projectile hits the wall")
            {
                //compare actual map to expected map
                std::vector<int> expected_map = { 0, 0, 0, 0,
                                                  0, 0, 2, 0,
                                                  0, 0, 0, 0, 0
                                                };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }


        WHEN("The tank tries attacks to down")
        {
            tank->setAttack(DOWN);
            tank->setMove(STAY);
            gamefield.nextTurn();

            THEN("The tank shoots down")
            {
                //Compare map with the initial map
                std::vector<int> expected_map = { 0, 0, 0, 0,
                                                  0, 0, 2, 0,
                                                  0, 0, 0, 0, -2
                                                };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);

            }
            tank->setAttack(STAY);
            tank->setMove(STAY);
            gamefield.nextTurn();
            THEN("The projectile hits the wall")
            {
                //compare actual map to expected map
                std::vector<int> expected_map = { 0, 0, 0, 0,
                                                  0, 0, 2, 0,
                                                  0, 0, 0, 0, 0
                                                };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }
    }
    GIVEN("A tank and a horizontal gamefield")
    {
        // Create tank
        SimpleActor * tank = nullptr;
        tank = new SimpleActor();
        REQUIRE(tank != nullptr);

        // Load a tank
        ActorInfo tank_s(tank, 100,0,6,0,2,2,6);

        //Add a tank into a vector of actors
        std::vector<ActorInfo> actor_list = {tank_s};

        // Generate the gamefield with a map that looks like this:
        // 0,0,0,0,0,0,2,0,0,0,0,0,0
        GameField gamefield(13,1, actor_list);

        WHEN("The tank tries to shoot left")
        {
            tank->setAttack(LEFT);
            tank->setMove(STAY);
            gamefield.nextTurn();
            THEN("The projectile goes left")
            {
                //compare actual map to expected map
                std::vector<int> expected_map = {-2, 0, 0, 0,
                                                 0, 0, 2, 0,
                                                 0, 0, 0, 0, 0
                                                };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
            tank->setAttack(STAY);
            tank->setMove(STAY);
            gamefield.nextTurn();
            THEN("The projectile hits the wall")
            {
                //compare actual map to expected map
                std::vector<int> expected_map = { 0, 0, 0, 0,
                                                  0, 0, 2, 0,
                                                  0, 0, 0, 0, 0
                                                };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }


        WHEN("The tank tries attacks to right")
        {
            tank->setAttack(RIGHT);
            tank->setMove(STAY);
            gamefield.nextTurn();

            THEN("The projectile goes right")
            {
                //Compare map with the initial map
                std::vector<int> expected_map = { 0, 0, 0, 0,
                                                  0, 0, 2, 0,
                                                  0, 0, 0, 0, -2
                                                };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);

            }
            tank->setAttack(STAY);
            tank->setMove(STAY);
            gamefield.nextTurn();
            THEN("The projectile hits the wall")
            {
                //compare actual map to expected map
                std::vector<int> expected_map = { 0, 0, 0, 0,
                                                  0, 0, 2, 0,
                                                  0, 0, 0, 0, 0
                                                };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
// Projectiles can collide with each other and can be spawned from
// 2 tanks on the field, projectiles deal damage to a tank when the tank is hit.
//
////////////////////////////////////////////////////////////////////////////////
SCENARIO("The projectile collides with the actors on the gamefield")
{
    // Create 2 tanks
    SimpleActor * tank = nullptr;
    tank = new SimpleActor();
    REQUIRE(tank != nullptr);

    SimpleActor * tank2 = nullptr;
    tank2 = new SimpleActor();
    REQUIRE(tank2 != nullptr);

    // Load a tank
    ActorInfo tank_s(tank, 1,1,13,0,2,2,6);	//id is 6th place 
    ActorInfo tank_q(tank2, 100,1,0,0,3,2,6);

    //Add a tank into a vector of actors
    std::vector<ActorInfo> actor_list = {tank_s,tank_q};

    // Generate the gamefield with a map that looks like this:
    // 3,0,0,0,0,0,0,0,0,0,0,0,0,2

    GameField gamefield(14,1, actor_list, 1);
    GIVEN("A horizontal gamefeild and two tanks")
    {
        WHEN("Each tank tries to shoot a projectile")
        {
            tank->setAttack(LEFT);//attack 2nd
            tank->setMove(STAY);
            tank2->setAttack(RIGHT);//attack 1st
            tank2->setMove(STAY);
            gamefield.nextTurn();

            THEN("The projectiles spawn and travle their range")
            {
                //Compare map with the initial map
                std::vector<int> expected_map = { 3, 0, 0, 0, 0, 0, -3, -2, 0, 0, 0, 0, 0, 2 };

                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
            tank->setAttack(STAY);
            tank->setMove(STAY);
            tank2->setAttack(STAY);
            tank2->setMove(STAY);

            gamefield.nextTurn();

            THEN("The projectiles collide and despawn")
            {
                std::vector<int> expected_map = { 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 };
                std::vector<int> actual_map = gamefield.getMap();
                REQUIRE(expected_map == actual_map);
            }
        }

        WHEN("One tank shoots at the other tank and the other tank does not move")
        {
            tank->setMove(STAY);//do not move
            tank2->setAttack(RIGHT);//attack 1st
            tank2->setMove(STAY);
            gamefield.nextTurn();
            tank2->setAttack(STAY);//attack 1st
            gamefield.nextTurn();
            gamefield.nextTurn();
            gamefield.nextTurn();

            THEN("The second tank is hit and the tank takes damage")
            {
                for (auto &a : gamefield.getActors())
                {
                    REQUIRE(a.id == 3);
                }
            }
        }
    }
}



