/*************************************************************************
** Program Name: Final Project
** Author: Matthew Castillo
** Date: 6/13/17
** Description: The Black hole class creates an interaction that has the 
**	user traverse through a black hole and provides an option for them to 
**  mitigate the damage that the user will take during their interaction. 
*************************************************************************/
#ifndef BLACKHOLE_HPP
#define BLACKHOLE_HPP
#include <string>
#include "Space.hpp"
#include "Validate.hpp"
#include <iostream>

// Black Hole Class Declaration
class BlackHole : public Space
{
	private:

	public:
		// Default constructor
		BlackHole(Unit *);

		// Destructor
		~BlackHole(); 

		// Get specific description
		std::string getSpaceDescription();

		// The instructions for the interaction with the location
		void spaceInteraction();

		// The instruction if user already interacted with the location
		void spaceInteracted();

		// Get item within the location
		void getItem();
};

#endif // ! BLACKHOLE_HPP