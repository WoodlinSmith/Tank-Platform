CXX = g++
CXXFLAGS = -g -std=c++11 -DTESTING -fPIC 
INCS = -I./ -I../../src/ -I../src 
#TEST_FILES = ../src/catch.hpp

PROFILE ?=

TEST_FILES = main.o
TEST_FILES += movement_tests.o
TEST_FILES += projectile_functional_tests.o

LIBS += -ldl -lglut -lGL -lGLU -lpthread
LIBS += -L../../libraries -lSOIL
SRC_PATH=../../src/

FILES += $(SRC_PATH)GameField.cpp
FILES += $(SRC_PATH)Actor.cpp
FILES += $(SRC_PATH)MapData.cpp
FILES += $(SRC_PATH)ProjectileActor.cpp
FILES += $(SRC_PATH)ActorInfo.cpp
FILES += $(SRC_PATH)Texture.cpp
FILES += $(SRC_PATH)event.cpp
FILES += $(SRC_PATH)util.cpp
FILES += $(SRC_PATH)TankDrawable.cpp
FILES += $(SRC_PATH)GameFieldDrawable.cpp
FILES += $(SRC_PATH)Projectile.cpp
FILES += $(SRC_PATH)ProjectileUtils.cpp
FILES += $(SRC_PATH)Obstacles.cpp
FILES += $(SRC_PATH)game.cpp
FILES += $(SRC_PATH)callbacks.cpp
FILES += $(SRC_PATH)DynamicLoader.cpp
FILES += $(SRC_PATH)Menu.cpp
FILES += $(SRC_PATH)sfxDrawable.cpp
FILES += $(SRC_PATH)Crate.cpp
FILES += $(SRC_PATH)SimpleActor.cpp
FILES += $(SRC_PATH)ConfigReader.cpp
FILES += $(SRC_PATH)GameFieldUtils.cpp
FILES += $(SRC_PATH)csv.cpp


%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(PROFILE) -c $< -o $@ $(INCS)

testAll: $(FILES:.cpp=.o) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) $(PROFILE) -o testFunctionalAll $(FILES:.cpp=.o) $(TEST_FILES) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf testAll *.o ../../src/*.o
