ENDERSGAME = output
CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
OBJS = main.o Simulation.o Space.o Unit.o Cadet.o Buggers.o Giant.o trainingGrounds.o buggerInstallation.o BlackHole.o Doctor.o HivePlanet.o Mazer.o Menu.o Validate.o 

$(ENDERSGAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(ENDERSGAME)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Simulation.o: Simulation.cpp Simulation.hpp
	$(CXX) $(CXXFLAGS) -c Simulation.cpp

Space.o: Space.cpp Space.hpp
	$(CXX) $(CXXFLAGS) -c Space.cpp

Unit.o: Unit.cpp Unit.hpp
	$(CXX) $(CXXFLAGS) -c Unit.cpp

Cadet.o: Cadet.cpp Cadet.hpp
	$(CXX) $(CXXFLAGS) -c Cadet.cpp

Buggers.o: Buggers.cpp Buggers.hpp
	$(CXX) $(CXXFLAGS) -c Buggers.cpp

Giant.o: Giant.cpp Giant.hpp
	$(CXX) $(CXXFLAGS) -c Giant.cpp

trainingGrounds.o: trainingGrounds.cpp trainingGrounds.hpp
	$(CXX) $(CXXFLAGS) -c trainingGrounds.cpp

buggerInstallation.o: buggerInstallation.cpp buggerInstallation.hpp
	$(CXX) $(CXXFLAGS) -c buggerInstallation.cpp

BlackHole.o: BlackHole.cpp BlackHole.hpp
	$(CXX) $(CXXFLAGS) -c BlackHole.cpp

Doctor.o: Doctor.cpp Doctor.hpp
	$(CXX) $(CXXFLAGS) -c Doctor.cpp

HivePlanet.o: HivePlanet.cpp HivePlanet.hpp
	$(CXX) $(CXXFLAGS) -c HivePlanet.cpp

Mazer.o: Mazer.cpp Mazer.hpp
	$(CXX) $(CXXFLAGS) -c Mazer.cpp

Menu.o: Menu.cpp Menu.hpp
	$(CXX) $(CXXFLAGS) -c Menu.cpp

Validate.o: Validate.cpp Validate.hpp
	$(CXX) $(CXXFLAGS) -c Validate.cpp

clean:
	rm *.o $(ENDERSGAME)

debug: 
	valgrind --leak-check=full ./$(ENDERSGAME)

run:
	./$(ENDERSGAME)

.PHONY: clean debug run


