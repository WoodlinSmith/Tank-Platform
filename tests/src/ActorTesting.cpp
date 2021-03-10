#include <catch.hpp>
#include <Actor.h>
#include <string>
#include <iostream>
using namespace std;

// Testing setters and default constructor
TEST_CASE("Calling getName() member function and checking constructor")
{
    Actor actor;
    string test = actor.getName();
    REQUIRE(test == "");
}

TEST_CASE("Calling getId() member function and checking constructor")
{
    Actor actor;
    int test = actor.getId();
    REQUIRE(test == 0);
}

// Testing constructor with given values
TEST_CASE("Test Constructor the will inialize all member variables from input variables")
{
    string nameTest = "DEFAULT";
    int idTest =  67;
    Actor actor("DEFAULT", 67);

    REQUIRE(nameTest == actor.getName());
    REQUIRE(idTest == actor.getId());
}

// Testing setters
TEST_CASE("Changing the value in name and using	the setHealth() function to change it")
{
    Actor actor;
    string test;

    actor.setName("George");
    test = actor.getName();
    REQUIRE(test == "George");
}

TEST_CASE("Changing the value in id and using the setId() function to change it")
{
    Actor actor;
    int test;

    actor.setId(91);
    test = actor.getId();
    REQUIRE(test == 91);
}

