/*************************************************************************
** Program Name: Final Project
** Author: Matthew Castillo
** Date: 6/13/17
** Description: The trainingGrounds class creates an interaction for the user 
** so that they get a basic understanding of the controls in the game.
** They will need to complete this interaction before they are able to begin 
** the game. It also provides the user with instructions on how to win the game. 
*************************************************************************/
#ifndef trainingGrounds_HPP
#define trainingGrounds_HPP
#include <iostream>
#include <string>
#include "Space.hpp"
#include "Unit.hpp"
#include "Cadet.hpp"
#include "Menu.hpp"
using std::cout;
using std::endl;
using std::cin;

// trainingGrounds Class Declaration
class trainingGrounds : public Space
{
	private:
		Unit *Salamander; 

	public:
		//Constructor
		trainingGrounds(Unit *);

		// Destructor
		~trainingGrounds(); 

		// Get specific description
		std::string getSpaceDescription();

		// The instructions for the interaction with the location
		void spaceInteraction();

		// The instruction if user already interacted with the location
		void spaceInteracted();

		// Get item within the location
		void getItem();
};

#endif // ! trainingGrounds_HPP
