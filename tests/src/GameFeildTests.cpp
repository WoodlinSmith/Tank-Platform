#include "catch.hpp"
#include <GameField.h>
#include <Actor.h>
#include <SimpleActor.h>


TEST_CASE("Instantiate GameField")
{
    GameField g;
    REQUIRE(sizeof(g) > 0);
}

TEST_CASE("Get Turn Count")
{
    GameField g;
    REQUIRE(g.getTurnCount() == 0);
}

TEST_CASE("nextTurn increments turnCount")
{
    GameField g;
    g.nextTurn();
    //Cannot be tested without adding a game object to the GameField
    //REQUIRE(g.getTurnCount() == 1);
}
TEST_CASE("addSimpleActor adds an actor to actors")
{
    GameField g;
    SimpleActor * a = new  SimpleActor;
    ActorInfo ai( a, 1, 1, 0, 0, 1);
    g.addActor(ai);
    REQUIRE(g.getActors()[0].act_p == a);

}

TEST_CASE("findActorByCoord() works with no actors")
{
    GameField g;
    REQUIRE(g.findActorsByCoord(0,0).size() == 0);
}

TEST_CASE("findActorByCoord() returns correct actors")
{
    GameField g;
    ActorInfo a1 (NULL, 1, 1, 0, 0, 1);
    ActorInfo a2 (NULL, 2, 1, 0, 0, 1);
    ActorInfo a3 (NULL, 3, 1, 1, 1, 1);



    g.addActor(a1);
    g.addActor(a2);
    g.addActor(a3);

    std::vector<ActorInfo> hits = g.findActorsByCoord(0,0);
    //make sure that 2 actors are returned and they are the right ones
    REQUIRE((hits.size() == 2
             && (hits[0] == a1 || hits[1] == a1)
             && (hits[0] == a2 || hits[1] == a2) ));

}

TEST_CASE("cull() removes only actors with health of 0")
{
    GameField g;
    ActorInfo a1 (NULL, 1, 0, 0, 0, 0);
    ActorInfo a2 (NULL, 0, 0, 0, 0, 0);
    ActorInfo a3 (NULL, 0, 0, 0, 0, 0);
    ActorInfo a4 (NULL, -1, 0, 0, 0, 0);
    g.addActor(a1);
    g.addActor(a2);
    g.addActor(a3);
    g.addActor(a4);
    g.cull();
    REQUIRE(g.getActors().size() == 2);
}

TEST_CASE("Construct GameField with dimensions")
{
    GameField g (4, 5);
    REQUIRE ((g.getWidth() == 4 && g.getHeight() == 5));
}

TEST_CASE("getMap() returns valid map")
{
    GameField g (2, 2);
    std::vector<int> ref = {0, 0, 0, 0};
    REQUIRE(g.getMap() == ref);
}

TEST_CASE("GameField constructs with actors")
{
    SimpleActor * a1 = new SimpleActor;
    SimpleActor * a2 = new SimpleActor;
    std::vector<ActorInfo> actors(2);
    actors[0].act_p = a1;
    actors[1].act_p = a2;
    GameField g (10, 10, actors);
    REQUIRE(g.getActors().size() == 2);
}

TEST_CASE("GameField correctly places actors on the map at construction")
{
    std::vector<ActorInfo> actorVect(2);
    actorVect[0].act_p = NULL;
    actorVect[0].id = 1;
    actorVect[0].x = 1;
    actorVect[0].y = 0;
    actorVect[0].health = 1;
    actorVect[1].act_p = NULL;
    actorVect[1].id = 2;
    actorVect[1].x = 0;
    actorVect[1].y = 1;
    actorVect[1].health = 1;
    GameField g (2, 2, actorVect);
    std::vector<int> ref = {0, 1, 2, 0};
    REQUIRE(g.getMap() == ref);
}

TEST_CASE("GameField correctly places actors on the map when added")
{
    SimpleActor * a = new SimpleActor;
    ActorInfo newAI(a, 1, 1, 1, 0, 1);
    GameField g (2, 2);
    g.addActor(newAI);
    std::vector<int> ref = {0, 1, 0, 0};
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("SimpleActor moves when nextTurn() is called")
{
    SimpleActor * a = new SimpleActor(STAY, UP);
    ActorInfo newAI(a, 100, 1, 1, 1, 1, 2, 2);
    GameField g (2, 2);
    g.addActor(newAI);
    std::vector<int> ref = {0, 1, 0, 0};
    a->setMove(UP);
    a->setAttack(STAY);
    g.nextTurn();
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("Actors are prevented from moving off the map")
{
    SimpleActor * a = new SimpleActor;
    ActorInfo newAI(a, 5, 1, 1, 1, 1, 2);
    GameField g (2, 2);
    g.addActor(newAI);
    std::vector<int> ref = {0, 1, 0, 0};
    g.nextTurn();
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("Actors can attack the desired space on nextMove() and dead Actors are culled")
{
    SimpleActor * a1 = new SimpleActor(UP, STAY);
    SimpleActor * a2 = new SimpleActor(STAY, STAY);
    ActorInfo newAI1(a1, 1, 2, 0, 2, 1, 1, 6);
    ActorInfo newAI2(a2, 1, 2, 0, 1, 2, 1, 6);
    GameField g (1, 3);
    g.addActor(newAI1);
    g.addActor(newAI2);
    a1->setAttack(UP);
    a1->setMove(STAY);
    a2->setAttack(STAY);
    a2->setMove(STAY);
    std::vector<int> ref = {0, 0, 1};
    g.nextTurn();
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("Actors move until their range is depleted")
{
    SimpleActor * a = new SimpleActor(STAY, DOWN);
    ActorInfo newAI(a, 10, 1, 0, 1, 1, 3, 6);
    GameField g (1,4);
    g.addActor(newAI);
    std::vector<int> ref = {0, 0, 0, 1};
    a->setMove(DOWN);
    a->setAttack(STAY);
    g.nextTurn();
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("Actors spawn and move projectiles on attack")
{
    SimpleActor * a = new SimpleActor(UP, STAY);
    ActorInfo newAI(a, 10, 1, 0, 7, 1, 1, 6);
    GameField g (1, 8);
    g.addActor(newAI);
    std::vector<int> ref = {0, -1, 0, 0, 0, 0, 0, 1};
    a->setAttack(UP);
    a->setMove(STAY);
    g.nextTurn();
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("Actors take 1 point of damage from the walls of the arena")
{
    SimpleActor * a = new SimpleActor(STAY, UP);
    ActorInfo newAI(a, 6, 1, 1, 0, 1, 2);
    GameField g (1, 1);
    g.addActor(newAI);
    a->setMove(UP);
    a->setAttack(STAY);
    g.nextTurn();
    REQUIRE(g.getActors().back().health == 5); //check for damage from the wall
}

TEST_CASE("Actors are culled and do not move after collision")
{
    SimpleActor * t1 = new SimpleActor(UP, UP); //attacker tank
    SimpleActor * t2 = new SimpleActor(STAY, STAY); //target tanks
    SimpleActor * t3 = new SimpleActor(STAY, STAY);

    ActorInfo t1i (t1, 1, 1, 0, 3, 1, 1, 6);
    ActorInfo t2i (t2, 1, 1, 0, 1, 2, 1, 6);
    ActorInfo t3i (t3, 1, 1, 0, 0, 3, 1, 6); //Initial map of {3, 2, 0 ,1}

    std::vector<ActorInfo> tvect(3);
    tvect[0] = t1i;
    tvect[1] = t2i;
    tvect[2] = t3i;

    GameField g (1, 4, tvect);

    g.nextTurn(); //tank 1 will fire up at the other tanks

    std::vector<int> ref = {3, 0, 0, 1}; //Tank 2 hit, Tank 3 and 1 remain
    REQUIRE(g.getMap() == ref);

}


TEST_CASE("Collision is checked when firing point-blank")
{
    SimpleActor * t1 = new SimpleActor(STAY, UP); //attacker tank
    SimpleActor * t2 = new SimpleActor(STAY, STAY); //target tanks
    SimpleActor * t3 = new SimpleActor(STAY, STAY);

    ActorInfo t1i (t1, 1, 1, 0, 2, 1, 1, 6);
    ActorInfo t2i (t2, 1, 1, 0, 1, 2, 1, 6);
    ActorInfo t3i (t3, 1, 1, 0, 0, 3, 1, 6); //Initial map of {3, 2, 1}

    std::vector<ActorInfo> tvect(3);
    tvect[0] = t1i;
    tvect[1] = t2i;
    tvect[2] = t3i;

    GameField g (1, 3, tvect);

    g.nextTurn(); //tank 1 will fire up at the other tanks, point blank on t2

    std::vector<int> ref = {3, 0, 1}; //Tank 2 hit, Tank 3 and 1 remain

    //failure looks like {0, 2, 1}
    REQUIRE(g.getMap() == ref);

}


TEST_CASE("SimpleActor shot counter incremented on attacking")
{
    SimpleActor * a = new SimpleActor(STAY, UP);
    ActorInfo newAI(a, 1, 1, 0, 1, 1, 1);
    GameField g (1, 2);
    g.addActor(newAI);
    g.nextTurn();

    REQUIRE(g.getActors().at(0).shots == 1);
}
TEST_CASE("SimpleActor hit counter incremented on hiting an enemy")
{
    SimpleActor * a1 = new SimpleActor(UP, STAY);
    SimpleActor * a2 = new SimpleActor(DOWN, STAY);

    ActorInfo AI1(a1, 10, 1, 0, 1, 1, 1, 6);
    ActorInfo AI2(a2, 10, 1, 0, 0, 2, 1, 6);

    GameField g (1, 2);
    g.addActor(AI1);
    g.addActor(AI2);
    a1->setAttack(UP);
    a2->setAttack(DOWN);
    g.nextTurn();

    REQUIRE(g.actorInfoById(1).hits == 1);
}

TEST_CASE("GameField.actorInfoById returns a null actor (All fields 0) when ID not found")
{
    GameField g;
    REQUIRE(g.actorInfoById(2) == ActorInfo (0,0,0,0,0,0));
}
TEST_CASE("GameField.actorInfoById returns a reference to the desired actor")
{
    GameField g;
    SimpleActor * a = new SimpleActor;
    ActorInfo newAI(a, 1, 1, 0, 0, 1, 0);

    g.addActor(newAI);

    REQUIRE(g.actorInfoById(1) == newAI);
}
TEST_CASE("GameField.actorInfoById references can be used to update actors on the field")
{
    GameField g;
    SimpleActor * a = new SimpleActor;
    ActorInfo newAI(a, 1, 1, 0, 0, 1, 0);

    g.addActor(newAI);

    g.actorInfoById(1).health = 10;
    newAI.health = 10;

    REQUIRE(g.actorInfoById(1) == newAI);
}


TEST_CASE("Obstacles can be added to the gamefield")
{
    GameField g; //10x10 empty gamefield

    REQUIRE(g.obstacleAt(1, 1) == false); //make sure the space starts empty

    g.addObstacle(1, 1);

    REQUIRE(g.obstacleAt(1, 1) == true); //check to make sure the obstacle was added
}

TEST_CASE("Obstacles can be removed from the gamefield")
{
    GameField g; //10x10 empty gamefield

    g.addObstacle(1, 1);
    g.removeObstacle(1, 1);

    REQUIRE(g.obstacleAt(1, 1) == false); //check to make sure the obstacle was added
}
TEST_CASE("Actors take 1 point of damage from hitting obstacles")
{
    SimpleActor * a = new SimpleActor(STAY, UP);
    ActorInfo newAI(a, 2, 1, 0, 2, 1, 2);
    GameField g (1, 3);
    g.addActor(newAI);
    g.addObstacle(0, 1);
    a->setMove(UP);
    a->setAttack(STAY);
    g.nextTurn();
    REQUIRE(g.actorInfoById(1).health== 1); //check for damage from the obstacle
}
TEST_CASE("Actors do not take damage when shooting an obstacle point-blank")
{
    SimpleActor * a = new SimpleActor(STAY, UP);
    ActorInfo newAI(a, 2, 1, 0, 1, 1, 1);
    GameField g (1, 2);
    g.addActor(newAI);
    g.addObstacle(0, 0);
    a->setAttack(DOWN);
    g.nextTurn();
    REQUIRE(g.actorInfoById(1).health== 2); //check for damage from the obstacle
}
TEST_CASE("Actors take 1 point of damage from the wall trying to move up/left")
{
    SimpleActor *a = new SimpleActor(UPLEFT, STAY);
    ActorInfo newAI(a, 2, 1, 1, 0, 1, 2); // set up to hit upper wall
    GameField g (2, 2);
    g.addActor(newAI);
    a->setMove(UPLEFT);
    g.nextTurn();
    REQUIRE(g.getActors().back().health == 1);
    SimpleActor *a2 = new SimpleActor(UPLEFT, STAY);
    ActorInfo newAI2(a2, 2, 1, 0, 1, 1, 2); // setup to hit left wall
    GameField g2 (2, 2);
    g.addActor(newAI2);
    a2->setMove(UPLEFT);
    g.nextTurn();
    REQUIRE(g.getActors().back().health == 1);
}
TEST_CASE("SimpleActor moves diagonal up/left and changes position")
{
    SimpleActor *a = new SimpleActor(UPLEFT, STAY);
    ActorInfo newAI(a, 2, 1, 1, 1, 1, 2);
    GameField g (2, 2);
    g.addActor(newAI);
    g.nextTurn();
    REQUIRE(g.getActors().back().x == 0);
    REQUIRE(g.getActors().back().y == 0);
}
TEST_CASE("SimpleActor moves diagonal up/right and changes position")
{
    SimpleActor *a = new SimpleActor(UPRIGHT, STAY);
    ActorInfo AI(a, 2, 1, 0, 1, 1, 2);
    GameField g (2, 2);
    g.addActor(AI);
    g.nextTurn();
    REQUIRE(g.getActors().back().x == 1);
    REQUIRE(g.getActors().back().y == 0);
}
TEST_CASE("Actors moves diagonal up/right into a wall and takes damage")
{
    SimpleActor *a = new SimpleActor(UPRIGHT, STAY);
    SimpleActor *a2 = new SimpleActor(UPRIGHT, STAY);
    ActorInfo AI(a, 2, 1, 1, 1, 1, 2); // setup to hit right wall
    ActorInfo AI2(a2, 2, 1, 0, 0, 1, 2); // setup to hit upper wall
    GameField g (2, 2);
    GameField g2 (2, 2);
    g.addActor(AI);
    g2.addActor(AI2);
    g.nextTurn();
    g2.nextTurn();
    REQUIRE(g.getActors().back().health == 1);
    REQUIRE(g2.getActors().back().health == 1);
}
TEST_CASE("SimpleActor moves diagonal down/left and changes position")
{
    SimpleActor *a = new SimpleActor(DOWNLEFT, STAY);
    ActorInfo AI(a, 2, 1, 1, 0, 1, 2);
    GameField g (2, 2);
    g.addActor(AI);
    g.nextTurn();
    REQUIRE(g.getActors().back().x == 0);
    REQUIRE(g.getActors().back().y == 1);
}
TEST_CASE("SimpleActor moves diagonal down/left and collides with wall")
{
    SimpleActor *a = new SimpleActor(DOWNLEFT, STAY);
    SimpleActor *a2 = new SimpleActor(DOWNLEFT, STAY);
    ActorInfo AI(a, 2, 1, 0, 0, 1, 2); // setup to hit left wall
    ActorInfo AI2(a2, 2, 1, 0, 1, 1, 2); // setup to hit lower wall
    GameField g (2, 2);
    GameField g2 (2, 2);
    g.addActor(AI);
    g2.addActor(AI2);
    g.nextTurn();
    g2.nextTurn();
    REQUIRE(g.getActors().back().health == 1);
    REQUIRE(g2.getActors().back().health == 1);
}
TEST_CASE("SimpleActor moves diagonal down/right and changes position")
{

    SimpleActor *a = new SimpleActor(DOWNRIGHT, STAY);
    ActorInfo AI(a, 2, 1, 0, 0, 1, 2);
    GameField g (2, 2);
    g.addActor(AI);
    g.nextTurn();
    REQUIRE(g.getActors().back().x == 1);
    REQUIRE(g.getActors().back().y == 1);
}
TEST_CASE("SimpleActor moves diagonal down/right and collides with wall")
{

    SimpleActor *a = new SimpleActor(DOWNRIGHT, STAY);
    SimpleActor *a2 = new SimpleActor(DOWNRIGHT, STAY);
    ActorInfo AI(a, 2,
                 1, 1, 0, 1, 2); // setup to hit right wall
    ActorInfo AI2(a2, 2, 1, 0, 1, 1, 2); // setup to hit lower wall
    GameField g (2, 2);
    GameField g2 (2, 2);
    g.addActor(AI);
    g2.addActor(AI2);
    g.nextTurn();
    g2.nextTurn();
    REQUIRE(g.getActors().back().health == 1);
    REQUIRE(g2.getActors().back().health == 1);
}
TEST_CASE("Checks for cheaters. Sets cheaters' tanks to have 1 for each attributes")
{
   int pointsAvailable = 20;
   SimpleActor *a = new SimpleActor();
   SimpleActor *a2 = new SimpleActor();
   attributes AIAttributes;
   AIAttributes = a->setAttribute(pointsAvailable, AIAttributes);
   ActorInfo AI(a, AIAttributes.tankHealth, AIAttributes.tankDamage, 1, 1, 1,
                AIAttributes.tankAP, AIAttributes.tankShots); 
   ActorInfo AI2(a2, 10, 10, 0, 0, 2, 10, 10); // invalid tank: defaults all to one
   AI.tankAttributes = AIAttributes;
   GameField g (2, 2);
   g.addActor(AI);
   g.addActor(AI2);
   g.checkForCheaters(pointsAvailable);
   REQUIRE(g.getActors().at(0).health >= 4);
   REQUIRE(g.getActors().at(0).damage >= 4);
   REQUIRE(g.getActors().at(0).range >= 4);
   REQUIRE(g.getActors().at(0).shots == 0);
   REQUIRE(g.getActors().at(1).health == 1);
   REQUIRE(g.getActors().at(1).damage == 1);
   REQUIRE(g.getActors().at(1).range == 1); 
   REQUIRE(g.getActors().at(1).shots == 1);
}
TEST_CASE("GameField updates heading of ActorInfo")
{
    SimpleActor *a = new SimpleActor(UPRIGHT, STAY);
    ActorInfo AI(a, 1, 1, 0, 1, 1, 2);

    GameField g (2, 2);

    g.addActor(AI);

    g.nextTurn();
    REQUIRE(g.actorInfoById(1).heading == UPRIGHT);
}


TEST_CASE("Game Field properly gets attributes from actors")
{
    SimpleActor * actor_1 = new SimpleActor(UPRIGHT, STAY);
    attributes baseStats;

    ActorInfo test(actor_1, 1, 1, 0, 1, 1, 2);
    std::vector<ActorInfo> output;
    std::vector<ActorInfo> vect;

    vect.push_back(test);

    GameField manager(2, 2, vect);

    manager.setSPECIAL(4, baseStats);

    output = manager.getActors();

    REQUIRE(output[0].tankAttributes.tankHealth == 1);
    REQUIRE(output[0].tankAttributes.tankDamage == 1);
    REQUIRE(output[0].tankAttributes.tankAP == 1);
    REQUIRE(output[0].tankAttributes.tankShots == 1);




}


TEST_CASE("GameField Calculates Fog of War")
{
    SimpleActor * actor_1 = new SimpleActor(STAY, STAY);
    ActorInfo test(actor_1, 1, 1, 3, 3, 2, 1, 1, 0, 3);

    std::vector<ActorInfo> tank_list;
    tank_list.push_back(test);

    GameField manager(7, 7, tank_list);

    std::vector<int> expected_obstacles = { true, true, true, true, true, true, true,
                                            true, false, false, false, false, false, true,
                                            true, false, false, false, false, false, true,
                                            true, false, false, false, false, false, true,
                                            true, false, false, false, false, false, true,
                                            true, false, false, false, false, false, true,
                                            true, true, true, true, true, true, true
                                          };

    for(int i = 0; i < 7; i++)
    {
        manager.addObstacle(i, 0);
        manager.addObstacle(i, 6);
    }
    for (int i = 1; i < 6; i++)
    {
        manager.addObstacle(0, i);
        manager.addObstacle(6, i);
    }

    REQUIRE(manager.getMapData().obstacleMap == expected_obstacles);

    MapData test_map = manager.getMapData();

    manager.create_fog_of_war(test_map, test);
//std::fill(expected_obstacles.begin(), expected_obstacles.end(), false);

    REQUIRE(test_map.obstacleMap == expected_obstacles);



}

TEST_CASE("GameField hides other thanks in the Fog of War")
{
    SimpleActor * actor_1 = new SimpleActor(STAY, STAY);
    SimpleActor * actor_2 = new SimpleActor(STAY, STAY);
    ActorInfo test(actor_1, 1,1, 3,3, 2, 1, 1, 2);
    ActorInfo test_hidden(actor_2, 1,1,0 ,0, 2,1, 1, 1, 2);

    bool hidden = true;

    std::vector<ActorInfo> tank_list;
    tank_list.push_back(test);
    tank_list.push_back(test_hidden);

    GameField manager(7, 7, tank_list);

    MapData test_map = manager.getMapData();

    manager.create_fog_of_war(test_map, test);

    for (auto x: test_map.map)
        if(x == 21)
            hidden = false;

    REQUIRE(hidden == true);



}
