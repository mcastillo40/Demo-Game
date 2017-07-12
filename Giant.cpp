#include "Giant.hpp"

/*********************************************************************
*                 Constructor
*********************************************************************/
Giant::Giant(Unit *Wiggins)
{
	this->player1 = Wiggins;
	attempts = 0; 
}

/*********************************************************************
*                 Destructor
*********************************************************************/
Giant::~Giant()
{}

/*********************************************************************
*                 getSpaceDescription()
* @param none
* @return: string (Description of the location)
* Description: Display the description of the location before the user
*	interacts with the Space and after the user interacts with the Space
*********************************************************************/
std::string Giant::getSpaceDescription()
{
	if (!interacted)
	{
		std::string description = "You decide to take a break from battle to play a game\n";
		std::string description1 = "  A game where persistence and frustration is key\n";
		std::string description2 = "      You have been transformed into a mouse\n";
		std::string description3 = "     Are you willing to play the Guessing Game\n";

		return description + description1 + description2 + description3;
	}
	else
	{
		std::string description = "      You look at the screen with a toppled Giant.\n";
		std::string description1 = " 'This was supposed to be a Game. Not a choice between \n";
		std::string description2 = " his own grisly death and an even worse murder. I'm a\n";
		std::string description3 = " \t murderer, even when I play.'\n";
		std::string description4 = " It's hard to manage frustration but you are persistent\n";
		return description + description1 + description2 + description3 ;
	}
}

/*****************************************************************************
*                 getItem()
* @param none
* @return: none
* Description: The function checks to see if the space currently has an item
*	avalialbe to be taken by the player. If available, the user will be notified
*	of the item at the location and given the option to place it in their cargo.
*	If the item is taken by the user then it is removed from the Space's inventory.
****************************************************************************/
void Giant::getItem()
{
	std::string itemToTake;
	bool valid = false;
	bool correctInput = false;
	int choice;
	char ch; 

	if (item.empty())
	{
		cout << "        There are no items available here" << endl;
		cout << "You have already taken " << this->itemTakenStack.at(0) << endl;
		cout << "\n    Press Enter to continue your mission." << endl;
		cin.clear();
		cin.ignore();
		cin.get(ch);
	}
	else
	{
		cout << "At the location you discovered: " << endl;
		cout << this->item.at(0) << endl << endl;

		cout << "Did you want to put it in your cargo:" << endl;
		cout << "1: Yes";
		cout << "\t\t2: No\n" << endl;

		// Get user choice and validate input
		while (!valid)
		{
			cout << "Decision: ";
			cin >> choice;

			if (cin)
			{
				correctInput = true;
			}
			valid = validate(choice, 1, 2, correctInput);
		}

		// If user selcts to add theitem then the player's setCargo() function
		// will be called to ensure that the player has room to add it into their
		// cargo, if added then the item will be removed from the item stack but will
		// be added to the taken stack. 
		// Else if the user chooses not to take item then they will be informed that 
		// they can pick it up later 
		if (choice == 1)
		{
			bool fullCargo = false;
			itemToTake = this->item.at(0);

			// Attempt to place item in player's cargo
			player1->setCargo(itemToTake);

			// Check to see if the user's cargo is full 
			fullCargo = player1->getItemTaken();

			// If the cargo was not full then add to cargo and remove
			// item from bugger Installation. Also place item into 
			// taken stack 
			if (fullCargo)
			{
				cout << "\nItem was placed in your cargo\n";

				this->itemTakenStack.push_back(itemToTake);

				removeItem();
				player1->setItemTakenFalse();
			}
			else
			{
			}

			cout << "\n    Press Enter to continue your mission." << endl;
			pause();
		}
		else
		{
			cout << "You may come back to pick up the item later" << endl;
			cout << "\n    Press Enter to continue your mission." << endl;
			cin.clear();
			cin.ignore();
			cin.get(ch);
		}
	}
}

/*****************************************************************************
*                 spaceInteraction()
* @param none
* @return: none
* Description: The function controls the interaction between the player and
*	the computer. The user will have to choose between two options presented
*	to them by the 'giant.' The user will continue to get the choice wrong
*	and lose 1 life for 3 attempts. However, when the user returns a 3rd time
*	they will be rewarded access to the item at the location. Additionally, 
*	the user will receive 3 of their life back. 
****************************************************************************/
void Giant::spaceInteraction()
{
	bool valid = false;
	bool correctInput = false;
	int choice;

	emptySpace();

	if (!interacted)
	{
		// Present the user with options 
		cout << "\t    'One is poison, One is not!" << endl;
		cout << "     Choose right and I'll take you into Fairyland'" << endl;
		cout << " Choose the right cup, add 1 fighter to your squadron" << endl;
		cout << " Choose the wrong cup, lose 1 fighter from your squadron" << endl << endl;

		cout << "Pick your drink\n";
		cout << "1: Left Cup";
		cout << "\t\t2: Right Cup" << endl;

		if (attempts == 0) // User's 1st attempt to select the correct cup, loses 1 life  
		{
			// Get user choice and validate input
			while (!valid)
			{
				cout << "Decision: ";
				cin >> choice;

				if (cin)
				{
					correctInput = true;
				}
				valid = validate(choice, 1, 2, correctInput);
			}
			emptySpace();
			cout << "\n\nAs you stuck your head in to drink from the cup" << endl;
			cout << "        Your head begins to dissolve" << endl; 
			cout << "     Lost 1 fighter from your Squadron" << endl;
			cout << "        Dang, Better luck next time!" << endl;
			player1->removeSquadron(1);

			cout << "\n   Press Enter to continue your mission." << endl;
			pause();
			attempts++;
		}
		else if (attempts == 1) // User's 2nd attempt to select the correct cup, loses 1 life  
		{
			// Get user choice and validate input
			while (!valid)
			{
				cout << "Decision: ";
				cin >> choice;

				if (cin)
				{
					correctInput = true;
				}
				valid = validate(choice, 1, 2, correctInput);
			}
			emptySpace();
			cout << "\n\nAs you stuck your head in to drink from the cup" << endl;
			cout << "       You catch on fire and quickly die" << endl;
			cout << "      Sometimes mice taste better cooked!" << endl;
			cout << "      Lost 1 fighter from your Squadron" << endl;
			player1->removeSquadron(1);

			cout << "\n   Press Enter to continue your mission." << endl;
			pause();
			attempts++;
		}
		else if (attempts == 2) // User's 3rd attempt to select the correct cup, loses 1 life 
		{
			// Get user choice and validate input
			while (!valid)
			{
				cout << "Decision: ";
				cin >> choice;

				if (cin)
				{
					correctInput = true;
				}
				valid = validate(choice, 1, 2, correctInput);
			}
			emptySpace();
			cout << "\n\nAs you stuck your head in to drink from the cup" << endl;
			cout << "       You jump out of the glass quickly" << endl;
			cout << "     But then turned green and rotted away!" << endl;
			cout << "      Lost 1 fighter from your Squadron" << endl;
			player1->removeSquadron(1);

			cout << "\n   Press Enter to continue your mission." << endl;
			pause();
			attempts++;
		}
		// User's 4th attempt to select the correct option but this time will
		// be presented with a different option. Gains all 3 life back 
		else if (attempts == 3) 
		{
			cout << "          He is CHEATING!!" << endl;
			cout << "    3. Jump at the Giant's face!!" << endl;
			// Get user choice and validate input
			while (!valid)
			{
				cout << "Decision: ";
				cin >> choice;

				if (cin)
				{
					correctInput = true;
				}
				valid = validate(choice, 1, 3, correctInput);
			}
			valid = false;
			correctInput = false;
			
			// User's 4th and plus attempt to select the correct cup if they do not choose option 3
			// to jump on the giant's face, will not lose life 
			if (choice == 3)  
			{
				emptySpace();
				cout << "\n\tYou begin to dig into the Giant's eye!" << endl;
				cout << "The giant falls backwards and crushes a castle behind him" << endl;
				cout << " Receive 3 of your fighters back after defeating the Giant" << endl << endl;
				player1->addSquadron(3);

				cout << "You peer through the rubble to see a mysterious object.\n" << endl;

				cout << "Do you want to inspect it: " << endl;
				cout << "1: Yes";
				cout << "\t\t2: No\n" << endl;
				// Get user choice and validate input
				while (!valid)
				{
					cout << "Decision: ";
					cin >> choice;

					if (cin)
					{
						correctInput = true;
					}
					valid = validate(choice, 1, 2, correctInput);
				}

				emptySpace();
				if (choice == 1)
				{
					getItem(); // Give user option to add item to cargo 
				}
				else
				{
					cout << "\n    Hopefully it wasn't needed commander" << endl;
					cout << "\n    Press Enter to continue your mission." << endl;
					pause();
				}

				// Set the user completed the tasks and has interacted with the location 
				setInteracted();
			}
			else
			{ 
				emptySpace();
				cout << "\n\nAs you stuck your head in to drink from the cup" << endl;
				cout << "       You fell in and began to drown" << endl;
				cout << "   I guess Mice can't breathe under water!" << endl;
				cout << "\n    Press Enter to continue your mission." << endl;
				pause();
			}
		}
	}
	else // Already interacted
	{
		// Call Interacted function if user has completed the task already
		spaceInteracted();
	}
}

/*****************************************************************************
*                 spaceInteracted()
* @param none
* @return: none
* Description: The function provides a description of the location if the user
*	has already completed the task and interacted with the location. They are
*	given the option to view whether an item is available at the location.
****************************************************************************/
void Giant::spaceInteracted()
{
	bool valid = false;
	bool correctInput = false;
	int choice;

	std::string description = "The giant lays dead on the ground in front of the broken castle\n\n";
	cout << description;

	cout << "Do you want to venture through the debris:" << endl;
	cout << "1: Yes";
	cout << "\t\t2: No\n" << endl;

	// Get user choice and validate input
	while (!valid)
	{
		cout << "Decision: ";
		cin >> choice;

		if (cin)
		{
			correctInput = true;
		}
		valid = validate(choice, 1, 2, correctInput);
	}
	emptySpace();

	if (choice == 1)
	{
		getItem(); // Give user option to add item to cargo 
	}
	else
	{
		cout << "\n    The Giant's game was quite the test" << endl;
		cout << "\n    Press Enter to continue your mission." << endl;
		pause();
	}
	emptySpace();
}