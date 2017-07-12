/*************************************************************************
** Program Name: Final Project
** Author: Matthew Castillo
** Date: 6/13/17
** Description: The program is in a fantasy fighting tournament environment.
** The player will select champions for 2 teams to fight amongst each other.
** They may select from a Vampire, Barbarian, Blue Men, Medusa, and Harry Potter.
** The arena class will be created and will be the field in which the
** creatures fight amongst each other. The rounds will continue until one
** team no longer has any creatures. The losing creatures of a match will be
** sent to a losing list which will then be able to be viewed at the end of the
** tournament. Then the user will be asked if they would like to play again.
*************************************************************************/
#include <iostream>
#include "Unit.hpp"
#include "Menu.hpp"
#include "Validate.hpp"
#include "Simulation.hpp"

using std::cout;
using std::endl;
using std::cin;

int main()
{
	char ch;			     // Used to exit program
	int option = 0;
	int again = 1;


	do {
		Simulation game;

		option = menu(again);

		// Create playing field
		if (option == 1)
		{
			game.traverse();

			again = 2;
		}

	} while (option != 2);

	// Exit program
	cin.clear();
	cout << "\n               Thank you for playing." << endl;
	cout << "                Press Enter to Exit." << endl;
	cin.ignore();
	cin.get(ch);

	return 0;
}

