#include "catch.hpp"
#include "ProjectileActor.h"
#include "PositionData.h"
#include "MapData.h"

TEST_CASE("Projectile moves the correct direction")
{
    ProjectileActor shell(DOWNRIGHT);
    PositionData status;
    MapData map;
    direction movement;
    status.field_x = 1;
    status.field_x = 1;

    movement = shell.move(map, status);
    REQUIRE (movement == DOWNRIGHT);
}

