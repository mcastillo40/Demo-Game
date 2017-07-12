/*************************************************************************
** Program Name: Final Project
** Author: Matthew Castillo
** Date: 6/13/17
** Description: The Hive Planet class is the last planet that the user will 
** enter to win the game. All the player needs to do is have with them 
** is the egg and the little device to win the game. 
*************************************************************************/
#ifndef HIVEPLANET_HPP
#define HIVEPLANET_HPP
#include <string>
#include "Space.hpp"
#include "Validate.hpp"
#include <iostream>

// Hive Planet Class Declaration
class HivePlanet : public Space
{
private:

public:
	// Constructor
	HivePlanet(Unit *);

	// Destructor
	~HivePlanet(); 

	// Get specific description
	std::string getSpaceDescription();

	// The instructions for the interaction with the location
	void spaceInteraction();

	// The instruction if user already interacted with the location
	void spaceInteracted();

	// Get item within the location
	void getItem();
};

#endif // !HIVEPLANET_HPP