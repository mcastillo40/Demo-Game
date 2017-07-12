#include <iostream>
#include "Validate.hpp"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/*********************************************************************
*                 Menu()
* @param again		(if the menu should be repeated)
* @return: int		(The choice of the user)
* Description: The function displays the options of the program. It
* also prompts user to enter there choice and returns that option. 
*********************************************************************/
int menu(const int &again)
{
	int choice = 0;
	bool valid = false; 
	bool correctInput = false; 

	cout << "**********************************************************" << endl;
	cout << "		     ENDER'S GAME          " << endl;
	cout << "**********************************************************" << endl;

	if (again == 2)
		cout << "\t 1: Play Again";
	else
		cout << "\t   1: Play Game";
	cout << "\t\t 2: Exit Game" << endl;

	// Get user choice and validate input
	while (!valid)
	{
		cout << "Choice: ";
		cin >> choice;

		if (cin)
		{ correctInput = true; }
		valid = validate(choice, 1, 5, correctInput);
	}

	return choice;
}

/*********************************************************************
*                 simulationMenu()
* @param none
* @return: int		(The choice of the user)
* Description: The function displays the options of the game. It
* also prompts user to enter there choice and returns that option.
**********************************************************************/
int simulationMenu()
{
	int choice = 0;
	bool valid = false;
	bool correctInput = false;

	cout << "   1. Traverse Up";
	cout << "     2: Traverse Down" << endl;
	cout << "   3: Traverse Left";
	cout << "   4: Traverse Right" << endl;
	cout << "   5: Engage   ";
	cout << "\t      6: Manage Cargo" << endl;
	cout << "\t    7: Exit Game" << endl; 

	// Get user choice and validate input
	while (!valid)
	{
		cout << "Choice: ";
		cin >> choice;

		if (cin)
		{
			correctInput = true;
		}
		valid = validate(choice, 1, 7, correctInput);
	}

	return choice;
}
