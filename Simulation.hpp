/*************************************************************************
** Program Name: Final Project
** Author: Matthew Castillo
** Date: 6/13/17
** Description: The Simulation class controls the game environment in order
** to create a user and the spaces needed to traverse through the environment.
*************************************************************************/
#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include "Unit.hpp"
#include "Cadet.hpp"
#include "Buggers.hpp"
#include "Space.hpp"
#include "trainingGrounds.hpp"
#include "buggerInstallation.hpp"
#include "Giant.hpp"
#include "BlackHole.hpp"
#include "Mazer.hpp"
#include "Doctor.hpp"
#include "HivePlanet.hpp"
#include "Validate.hpp"
#include "Menu.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

// Creature Class Declaration
class Simulation 
{
	private:
		Unit *Ender;
		Space *training;
		Space *bugPlanet1;
		Space *bugPlanet2;
		Space *bugPlanet3;
		Space *currentCoordinate; 
		Space *eggWorld;
		Space *gravity; 
		Space *outPost;
		Space *bomber; 
		Space *finalPlanet;
		bool missionOutcome; 
		char map[3][3];
		int buggerLevel; 
		int life; 

	public:
		// Default Constructor
		Simulation();

		// Destructor 
		~Simulation();

		// Link spaces to each another
		void setLinks();

		// Set the items available in the spaces
		void setItems();

		// Let the user traverse through the area
		void traverse();

		// This will increase the level of difficulty for a space 
		void levelUpBugs();

		// View outcome
		void displayOutcome();

		// Display user's map
		void displayMap();

		// Clear the terminal screen
		void clearScreen();
};

#endif // !SIMULATION_HPP
