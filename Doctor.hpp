/*************************************************************************
** Program Name: Final Project
** Author: Matthew Castillo
** Date: 6/13/17
** Description: The Doctor class creates an interaction where the user will
**	be given a description of the use of the weapon at the location. They
**	must first agree to send a letter to a family member in order to obtain
**	the item. 
*************************************************************************/
#ifndef DOCTOR_HPP
#define DOCTOR_HPP
#include <string>
#include "Space.hpp"
#include "Validate.hpp"
#include <iostream>

// Doctor Class Declaration
class Doctor : public Space
{
	private:
		bool message; 
	public:
		// Default Constructor
		Doctor(Unit *);

		// Destructor
		~Doctor(); 

		// Get specific description
		std::string getSpaceDescription();

		// The instructions for the interaction with the location
		void spaceInteraction();

		// The instruction if user already interacted with the location
		void spaceInteracted();

		// Get item within the location
		void getItem();
};

#endif // ! DOCTOR_HPP