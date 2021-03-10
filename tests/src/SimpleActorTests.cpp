#include "catch.hpp"
#include <SimpleActor.h>
#include <Actor.h>


TEST_CASE("SimpleActor constructs correctly")
{
    SimpleActor a;
    REQUIRE(sizeof(a) > 0);
}
TEST_CASE("default SimpleActor.move() returns up")
{
    SimpleActor* a = new SimpleActor; //Apparently the constructor does not run when delcaring directly.
    MapData m;
    PositionData p;
    REQUIRE(a->move(m,p) == UP);
    delete a;
}
TEST_CASE("default SimpleActor.attack() attacks 0,0 with 0 damage")
{
    SimpleActor* a = new SimpleActor;
    MapData m;
    PositionData p;
    direction result;
    result = a->attack(m,p);
    REQUIRE(result == STAY);
    delete a;
}
TEST_CASE("SimpleActor moves in the direction specified at construction")
{
    SimpleActor* a = new SimpleActor(DOWN, STAY);
    MapData m;
    PositionData p;
    REQUIRE(a->move(m,p) == DOWN);
    delete a;
}
TEST_CASE("SimpleActor.attack() attacks specified point with specified damage")
{
    SimpleActor* a = new SimpleActor(STAY, STAY);
    MapData m;
    PositionData p;
    direction result;
    a->setAttack(DOWNRIGHT);
    result = a->attack(m,p);
    REQUIRE(result == DOWNRIGHT);
    delete a;
}
TEST_CASE("SimpleActor.setMove() changes the return of SimpleActor.move()")
{
    SimpleActor* a = new SimpleActor(UP, STAY);
    MapData m;
    PositionData p;
    a->setMove(DOWN);
    REQUIRE(a->move(m,p) == DOWN);
    delete a;
}
