/*************************************************************************
** Program Name: Final Project
** Author: Matthew Castillo
** Date: 6/13/17
** Description: The Giant class creates an interaction where the user 
** will be given 2 option to either drink from a cup on the left or a cup 
** on the right. The user will not be aboe to win the interaction until
** he interacts with the location 3 times. 
*************************************************************************/
#ifndef GIANT_HPP
#define GIANT_HPP
#include <string>
#include "Space.hpp"
#include "Validate.hpp"
#include <iostream>

// Giant Class Declaration
class Giant : public Space
{
	private:
		int attempts;

	public:
		// Constructor
		Giant(Unit *);

		// Destructor
		~Giant(); 

		 // Get specific description
		std::string getSpaceDescription();

		// The instructions for the interaction with the location
		void spaceInteraction();

		// The instruction if user already interacted with the location
		void spaceInteracted();

		// Get item within the location
		void getItem();
};

#endif // ! GIANT_HPP