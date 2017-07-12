/*************************************************************************
** Program Name: Final Project
** Author: Matthew Castillo
** Date: 6/13/17
** Description: The user is placed in a gaming environment where they must
** traverse through different spaces and interact with the location in order
** to be able to enter the 'Hive Planet' and complete the game. The user will
** encounter various missions that they will need to complete. At the
** beginning of the game they will be walked though a training session so
** that they may understand the controls of the game. The player is given 25
** health and are allotted with 50 moves to complete the game.
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

