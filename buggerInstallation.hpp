/*************************************************************************
** Program Name: Final Project
** Author: Matthew Castillo
** Date: 6/13/17
** Description: The Bugger Installation will be a battle ground where the user
**	and the buggers fight one another through several rounds. The winner will be 
**	announced to the user.
*************************************************************************/
#ifndef BUGGERINSTALLATION_HPP
#define BUGGERINSTALLATION_HPP
#include <string>
#include "Space.hpp"
#include "Unit.hpp"
#include "Buggers.hpp"
#include <iostream>

// Bugger Installation Class Declaration
class buggerInstallation : public Space
{
	private:
		Unit *colony;

	public:
		// Default constructor 
		buggerInstallation(Unit *);

		// Destructor
		~buggerInstallation(); 

		// Get specific description
		std::string getSpaceDescription();

		// The instructions for the interaction with the location
		void spaceInteraction();

		// The instruction if user already interacted with the location
		void spaceInteracted();

		// Get item within the location
		void getItem();

};

#endif // ! BUGGERINSTALLATION_HPP
