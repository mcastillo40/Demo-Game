#include "buggerInstallation.hpp"

/*********************************************************************
*                 Constructor
*********************************************************************/
buggerInstallation::buggerInstallation(Unit *Wiggins)
{
	this->player1 = Wiggins;
}

/*********************************************************************
*                 Destructor
*********************************************************************/
buggerInstallation::~buggerInstallation()
{}

/*********************************************************************
*                 getSpaceDescription()
* @param none
* @return: string (Description of the location)
* Description: Display the description of the location before the user
*	interacts with the Space and after the user interacts with the Space
*********************************************************************/
std::string buggerInstallation::getSpaceDescription()
{
	if (!interacted)
	{
		std::string description = "You see, from a distance, a planet swarming with buggers\n";
		std::string description1 = "    With every new engagement, you learn more of war. \n";
		std::string description2 = "   It is up to you, commander, to engage or fly around. \n";

		return description + description1 + description2;
	}
	else
	{
		std::string description =  "   You see floating debris of ships from the carnage.\n";
		std::string description1 = " 'The power to cause pain is the only power that matters, \n";
		std::string description2 = "    the power to kill and destroy, because if you can't\n";
		std::string description3 = "     kill then you are always subject to those who can,\n";
		std::string description4 = "         and nothing and no one will ever save you'\n";
		return description + description1 + description2 + description3 + description4;
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
void buggerInstallation::getItem()
{
	std::string itemToTake;
	bool valid = false;
	bool correctInput = false;
	int choice;

	if (item.empty())
	{
		cout << "     There are no items available here" << endl;
		cout << "  You have already taken " << this->itemTakenStack.at(0) << endl << endl;
		cout << "    Press Enter to continue your mission." << endl;
		pause();
	}
	else
	{
		cout << "      At the location you discovered " << endl;
		cout << "   " << this->item.at(0) << endl << endl;

		if (this->item.at(0) == "Additional forces")
		{
			cout << "  Do you want to add them to your squadron: " << endl;
		}
		else
		{
			cout << "Did you want to put it in your cargo:" << endl;
		}
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

		// If user selcts to add the item then the player's setCargo() function
		// will be called to ensure that the player has room to add it into their
		// cargo, if added then the item will be removed from the item stack but will
		// be added to the taken stack. 
		// Else if the user chooses not to take item then they will be informed that 
		// they can pick it up later 
		if (choice == 1 && !(this->item.at(0) == "Additional forces"))
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
		// If the Space contains Additional forces, then 5 squadron will
		// be added to the user's life. The category will then be added
		// to the takenItem list of the buggerInstallation 
		else if (choice == 1 && (this->item.at(0) == "Additional forces"))
		{
			itemToTake = this->item.at(0);

			cout << "  5 additional forces were added to your squadron" << endl;
			this->player1->addSquadron(5);

			this->itemTakenStack.push_back(itemToTake);

			removeItem();
			player1->setItemTakenFalse();

		    cout << "\n      Press Enter to continue your mission." << endl;
			pause();
		}
		else
		{
			cout << "   You may come back to pick up the item later" << endl;
			cout << "\n     Press Enter to continue your mission." << endl;
			pause();
		}
	}
}

/*****************************************************************************
*                 spaceInteraction()
* @param none
* @return: none
* Description: The function controls the interaction between the player and
*	the buggerInstallation class. This allows the user engage the enemy through
*	several rounds. They will take turns attacking each other and taking damage. 
*	The loser will be the unit that losses all of their squadron. The player
*	will be notified of the outcome of the interaction. If the user wins then
*	they will be able to collect the item at the location else they will have
*	to try again. 
****************************************************************************/
void buggerInstallation::spaceInteraction()
{
	bool valid = false;
	bool correctInput = false;
	bool found = false; 
	int currentHealth = 0;
	int afterBattle = 0;
	int choice = 0;
	int rounds = 1;
	int playerTurn = 1;
	int attack = 0;

	if (!interacted)
	{
		// Initialize enemy
		colony = new Buggers;

		// Increase the enemy's squadron for each time the bugger Installation is called 
		colony->addSquadron(level);

		// Get the user's curren health 
		currentHealth = player1->getSquadron();

		emptySpace();

		cout << endl << " The enemy sees you coming and prepares for battle!" << endl;
		cout << "       Your squadron gets into formation" << endl << endl;
		cout << "       You attack with strategic prowess" << endl;
		cout << "\n         Press Enter to begin the fight" << endl;
		pause();

		emptySpace();

		// Iterate through each round while one is attacking and the other defending 
		do
		{
			if (playerTurn) // Player 1 is attacking , Player 2 is defending
			{
				player1->rollAttackDie();
				attack = player1->getAttack();

				colony->damage(attack);

				// Change to have player 2 go first next round 
				playerTurn = 0;
			}
			else // Player 2 is attacking , Player 1 is defending
			{
				colony->rollAttackDie();
				attack = colony->getAttack();

				player1->damage(attack);

				// Change to have player 1 go attack next round 
				playerTurn = 1;
			}

			// increment round count 
			++rounds;

		} while (player1->getSquadron() > 0 && colony->getSquadron() > 0);

		// Get the player's health after the battle
		afterBattle = player1->getSquadron();

		// Check to see if the user has an item to deflect all damage from the enemy 
		found = player1->checkCargo("Warp Speed (Improves defense)");

		// If user decides to use item then the user section will calculate how many fighters the
		// user lost and add them back to the user's health. Additionally, the item will be removed from
		// the user's cargo. 
		if (found)
		{
			cout << "Do you want to use 'Warp Speed(Improves defense)' to prevent all damage" << endl;
			cout << "It will be removed from your cargo after being used." << endl;
			cout << "1: Use Shield";
			cout << "\t2: Willing to take the hits" << endl;

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

			// Calculate how much health the user lost then add it back to the user's squadron 
			if (choice == 1)
			{
				int addHealth = 0;

				addHealth += (currentHealth - afterBattle);
				player1->addSquadron(addHealth);

				cout << "You prevented the loss of " << addHealth << " fighters" << endl << endl; 
				player1->removeSpecificCargo("Warp Speed (Improves defense)");
			}
			else
			{
				cout << "You may use Warp Speed at a later time" << endl << endl; 
			}
		}
		valid = false;
		correctInput = false;

		// If the user won the battle then inform the player how many rounds were played and how many more 
		// squadron he has left. 
		// User will also get the option to iunspect the item that he unlocked. 
		// Set location to being interacted with 
		if (player1->getSquadron() > 0)
		{
			bool valid = false;
			bool correctInput = false;
			int choice;

			cout << endl << "     You won after " << rounds << " tough rounds" << endl;
			cout << "   Your squadron has " << player1->getSquadron() << " fighters left" << endl << endl;
			cout << " Something catches your eye in the debris\n";
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
				getItem();	// Give user option to add item to cargo 
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
			cout << "    You lost all your forces during the battle" << endl;
			cout << "             Better luck next time" << endl; 
			cout << "\n    Press Enter to continue your mission." << endl;

			pause();
		}

		// De-allocate memory 
		delete colony;
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
void buggerInstallation::spaceInteracted()
{
	bool valid = false;
	bool correctInput = false;
	int choice;

	std::string description = "    You have already conquered this battle\n\n";
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
		cout << "\n     You remember the soldiers you lost" << endl;
		cout << "\n    Press Enter to continue your mission." << endl;
		pause();
	}

	emptySpace();
}