/*************************************************************************
** Program Name: Final Project
** Author: Matthew Castillo
** Date: 6/13/17
** Description: The Mazer class creates an interaction for the user to 
** solve 3 riddles presented to them. The user will need to answer 2 of the
** riddles correctly in order to complete the task and obtain the item. 
*************************************************************************/
#ifndef MAZER_HPP
#define MAZER_HPP
#include <iostream>
#include <vector>
#include <string>
#include "Space.hpp"
#include "Validate.hpp"
using std::vector;
using std::string;

// problem Structure holds the different answers
// that the user may select from for the riddle presented
struct problem
{
	string answer1;
	string answer2;
	string answer3;
	string correctAnswer; 
	int	finalAnswer; 
};

// Mazer Class Declaration
class Mazer : public Space
{
	private:
		problem riddle1;
		problem riddle2;
		problem riddle3;
		vector<string> riddles;
		vector<problem> answers; 
	public:
		// Constructor
		Mazer(Unit *);

		// Destructor
		~Mazer(); 

		 // Get specific description
		std::string getSpaceDescription();

		// The instructions for the interaction with the location
		void spaceInteraction();

		// The instruction if user already interacted with the location
		void spaceInteracted();

		// Get item within the location
		void getItem();

		// Sets the riddle that the user will be asked to answer
		void setRiddle(); 
};

#endif // ! MAZER_HPP