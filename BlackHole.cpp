#include "BlackHole.hpp"

/*********************************************************************
*                 Constructor
*********************************************************************/
BlackHole::BlackHole(Unit *Wiggins)
{
	this->player1 = Wiggins;
}

/*********************************************************************
*                 Destructor
*********************************************************************/
BlackHole::~BlackHole()
{}

/*********************************************************************
*                 getSpaceDescription()
* @param none
* @return: string (Description of the location)
* Description: Display the description of the location before the user 
*	interacts with the Space and after the user interacts with the Space
*********************************************************************/
std::string BlackHole::getSpaceDescription()
{
	if (!interacted)
	{
		std::string description = "  You see through your command portal, the power of the Universe\n";
		std::string description1 = "In your search for knowledge and power will you test your abilities\n";
		std::string description2 = "         Will you dare venture into the Black hole\n";

		return description + description1 + description2;
	}
	else
	{
		std::string description = " By being compassionate you are able to help the Universe.\n";
		std::string description1 = " 'If only we were wiser or better people, perhaps the gods\n";
		std::string description2 = "  would explain to us the mad, unbearable things they do.'\n";
		return description + description1 + description2;
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
void BlackHole::getItem()
{
	std::string itemToTake;
	bool valid = false;
	bool correctInput = false;
	int choice;

	// If no item available then inform the user 
	if (item.empty())
	{
		cout << "       There are no items available here" << endl;
		cout << "   You have already taken " << this->itemTakenStack.at(0) << endl;
		cout << "\n    Press Enter to continue your mission." << endl;
		pause();
	}
	else // Inform the user of th item available at the location 
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
			pause();
		}
	}
}

/*****************************************************************************
*                 spaceInteraction()
* @param none
* @return: none
* Description: The function controls the interaction between the player and 
*	the BlackHole class. This allows the user to traverse through the black
*	hole and make decisions on what action to take next. The user will take damage
*	according to their choice. The user may elect to withdraw from the interaction
*	but by doing so will not have completed the task and thus not unlocking the 
*	item. 
****************************************************************************/
void BlackHole::spaceInteraction()
{
	bool valid = false;
	bool correctInput = false;
	int choice;
	int squadCount = 0;

	emptySpace();

	// If user has not interacted with the location 
	if (!interacted)
	{
		// Description of what the user must accomplish 
		cout << " You talk to the super computer 'Jane' so you may explore\n";
		cout << "\t\tthe wonders of a black hole" << endl << endl;

		cout << "She tells you that she is the only one to have gone through to" << endl;
		cout << "  the otherside and back to learn the secrets provided. \n" << endl;
		
		cout << "Do you dare enter through the black hole to test your might:" << endl; 
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
		valid = false;
		correctInput = false;

		emptySpace();

		// User decides to continue with the task 
		if (choice == 1)
		{
			// Inquire whether the user would to continue 
			cout << "You begin to steer your ship towards the massive entity" << endl;
			cout << "  ... Jane reappears on your console to reconsider\n";
			cout << "       Are you sure you don't want to turn back" << endl;
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
			valid = false;
			correctInput = false;

			// User decides to continue with the task 
			if (choice == 1)
			{
				emptySpace();
				cout << "     You turn off your console and proceed downwards" << endl;
				cout << "Spiraling to the dark abyss where nothing and everything lies " << endl;
				cout << "You begin seeing the truth around you and the knowledge of life" << endl;
				cout << "\t\t\t.......";

				cout << "\n\t\tPress Enter to continue." << endl;
				pause();
				emptySpace();

				// Inquire whether the user would to continue 
				cout << "  You see some of your squadron begin to emit a blue glow " << endl; 
				cout << "Fighters begin to lose formation and are reaching rapid speeds" << endl;
				cout << "     You attempt to keep them under control" << endl; 

				cout << "1: Attempt to steer away ";
				cout << "\t2: Use ships as shield to reduce damage\n" << endl;
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
				valid = false;
				correctInput = false;
				emptySpace();

				// Get user's squadron size before taking any damage 
				squadCount = player1->getSquadron(); 

				// If user continues to traverse through the tasks
				if (choice == 1)
				{
					// If user chooses 1 then 8 damage will be passed along player 1's
					// damage function
					player1->damage(8);

					// Calculate how many fighters he lost
					squadCount -= player1->getSquadron();

					// user will be notified that he got through but will also be notified of
					// how many units he lost. 
					cout << "You were unable to retreat and lost several fighters" << endl;
					cout << "   " << squadCount << " of your squadron were lost during the trip" << endl;
					cout << "But those that made it were able to locate the center" << endl; 
				}
				else
				{
					// If user chooses 1 then 5 damage will be passed along player 1's
					// damage function
					player1->damage(5);

					// Calculate how many fighters he lost
					squadCount -= player1->getSquadron();

					// user will be notified that he got through but will also be notified of
					// how many units he lost. 
					cout << "Moving your ships in a tighter formation helped reduce damage" << endl;
					cout << "  But not all were able to be saved and you took casualties" << endl;
					cout << "       " << squadCount << " of your squadron were lost during the trip" << endl;
					cout << "   But those that made it were able to locate the center" << endl;
				}
				cout << "\n           Press Enter to continue." << endl;
				pause();

				squadCount = player1->getSquadron();

				// If the user did not survive the interaction, they are informed that they lost 
				// Else they are able to select whether they would like to pick up the item at the
				// location 
				if (squadCount <= 0)
				{
					cout << "You were not able to go through the Black Hole safely" << endl; 
					cout << "\n    Press Enter to continue your mission." << endl;
					pause();
				}
				else
				{
					emptySpace();
					cout << "Amazingly the Black Hole transformed into a White Hole" << endl;
					cout << "    And a new energy was formed after the chaos." << endl;
					cout << "       You see an orb glowing around the ship\n" << endl;
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
			}
			else
			{
				// Display description of the user leaving the interaction
				// User will have not completed the task for the location 
				emptySpace();
				cout << "You may have saved your squadron from certain perail" << endl;
				cout << "   But you will not know what truths are hidden" << endl;
				cout << "The knowledge that lies on the other side of the universe" << endl;
				cout << "     On the other side of this black hole." << endl << endl;
			    cout << "\n     Press Enter to continue your mission." << endl;
				pause();
			}

		}
		else
		{
			// Display description of the user leaving the interaction
			// User will have not completed the task for the location 
			cout << "You may have saved your squadron from certain perail" << endl;
			cout << "   But you will not know what truths are hidden" << endl;
			cout << "The knowledge that lies on the other side of the universe" << endl;
			cout << "     On the other side of this black hole." << endl << endl;
			cout << "\n   Press Enter to continue your mission." << endl;
			pause();
		}
	}
	else
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
void BlackHole::spaceInteracted()
{
	bool valid = false;
	bool correctInput = false;
	int choice;

	std::string description = "The black hole has been transformed into a white hole\n\n";
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
		cout << "\n    You truly mastered the Universe" << endl;
		cout << "\n  Press Enter to continue your mission." << endl;
		pause();
	}
	emptySpace();
}