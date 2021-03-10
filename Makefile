CXX = g++
CXXFLAGS = -g -std=c++11 -fPIC -Wall
INCS = -I./ -Isrc/
LIBS = -ldl
LIBS += -lglut -lGL -lGLU -lpthread
LIBS += -lSOIL -Llibraries
SOFLAGS = -DDYNAMIC
PROFILE ?=

SRC_PATH= src/
TANK_PATH= tanks/
LIB_PATH= libraries/

MAIN = $(SRC_PATH)main.cpp

FILES = $(MAIN)
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
FILES += $(SRC_PATH)ConfigReader.cpp
FILES += $(SRC_PATH)csv.cpp
FILES += $(SRC_PATH)GameFieldUtils.cpp

TANK_PATH= ./tanks/
TANKS = $(SRC_PATH)SimpleAI.cpp
TANKS += $(SRC_PATH)PongAI.cpp
TANKS += $(SRC_PATH)CamperAI.cpp
TANKS += $(SRC_PATH)StationaryAI.cpp
TANKS += $(SRC_PATH)AttackDownAI.cpp

TANKS_LINK = src/Actor.o #need to link in the base class for the .so to have everything.

platform: $(FILES:.cpp=.o) $(TANKS:src/%.cpp=tanks/%.so) 
	$(CXX) $(CXXFLAGS) $(INCS) -o platform $(FILES:.cpp=.o) $(LIBS)

coverage: set-coverage $(FILES:.cpp=.o) $(TANKS:src/%.cpp=tanks/%.so)
	$(CXX) $(CXXFLAGS) $(INCS) $(PROFILE) -o platform $(FILES:.cpp=.o) $(LIBS)

set-coverage:
	$(eval PROFILE:=-pg -fprofile-arcs -ftest-coverage)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(PROFILE) -c $? -o $@ 

%.h.gch: %.h
	$(CXX) -x c++-header -c $< -o $@ $(INCS) $(LIBS)

tanks/%.so: src/%.cpp ./src/Actor.o
	@mkdir -p tanks
	$(CXX) $(CXXFLAGS) $(INCS) $(PROFILE) -shared $< $(TANKS_LINK) -o $(TANK_PATH)$(@F) $(SOFLAGS) $(LIBS)

tanks: $(TANKS:%.cpp=%.so)

clean:
	@rm -rf platform results.txt src/*.o
	@rm -rf *.gc*
	@rm -rf src/*.gc*
	@rm -rf gprofresults.txt
	@rm -rf gmon.out

clean-lib: clean
	@rm -rf buildsrc
	@rm -rf libraries/libCTF.so

clean-all: clean-lib
	@rm -rf $(TANK_PATH)*
	@rm -rf coverage

clean-tests: clean-all
	@rm -rf testUnitAll
	@rm -rf testFunctionalAll
	@make clean -C tests/src
	@make clean -C tests/functional_tests

dev: clean-lib
	make gen-library -j8

gen-library: $(FILES:.cpp=.o) $(TANKS:src/%.cpp=tanks/%.so)
	@mkdir -p buildsrc/$(LIB_PATH)
	@mkdir -p buildsrc/$(SRC_PATH)
	@mkdir -p buildsrc/$(TANK_PATH)
	@mkdir -p buildsrc/images	
	#echo "Building object library"
	g++ -o buildsrc/$(LIB_PATH)libCTF.so -shared $(CXXFLAGS) $(FILES:.cpp=.o) $(SOFLAGS)
	#echo "Building platform"
	$(CXX) $(CXXFLAGS) $(INCS) -o buildsrc/platform $(FILES:.cpp=.o) $(LIBS)
	#echo "Copying support files"
	cp -R src/buildsrc/ .
	cp config.txt	buildsrc/config.sample
	cp README.md buildsrc/README.md
	cp -R images/ buildsrc/
	cp -R maps/ buildsrc/
	cp src/Actor.h buildsrc/src/
	cp src/MoveData.h buildsrc/src/
	cp src/attributes.h buildsrc/src/
	cp src/MapData.h buildsrc/src/
	cp src/direction.h buildsrc/src/
	cp src/PositionData.h buildsrc/src/
	cp $(TANKS) buildsrc/
	cp $(TANKS:.cpp=.h) buildsrc/
	#	cp -R $(SRC_PATH)*.o build/$(SRC_PATH)
	# Change tanks src to point to new directory
	sed -i 's#include "#include "src/#g' buildsrc/SimpleAI.h
	sed -i 's#include "#include "src/#g' buildsrc/PongAI.h

push-to-git: clean-lib
	mkdir -p buildsrc
	git clone git@gitlab.com:jamckee/projectx.git buildsrc/
	make gen-library -j8
	git --git-dir=buildsrc/.git --work-tree=buildsrc checkout -b pre-release
	git --git-dir=buildsrc/.git --work-tree=buildsrc add .
	#git --git-dir=buildsrc/.git --work-tree=buildsrc commit -m "Automated push of new version. 4.00"
	#git --git-dir=buildsrc/.git --work-tree=buildsrc status
	#git --git-dir=buildsrc/.git --work-tree=buildsrc push -fu origin pre-release

tests: $(TANKS:src/%.cpp=tanks/%.so) testUnitAll testFunctionalAll

testUnitAll:
	+make PROFILE="$(PROFILE)" -C tests/src
	mv tests/src/testUnitAll .

testFunctionalAll: tanks/SimpleActor.so tanks/SimpleAI.so
	+make PROFILE="$(PROFILE)" -C tests/functional_tests
	mv tests/functional_tests/testFunctionalAll .

mapGen:
	g++ -omapGen -std=c++11 -Wall -fPIC MapGen/mapGen.cpp
