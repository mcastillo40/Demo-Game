#include "trainingGrounds.hpp"

/*********************************************************************
*                 Constructor
*********************************************************************/
trainingGrounds::trainingGrounds(Unit *Wiggins)
{
	this->player1 = Wiggins;
	level = 0;
}

/*********************************************************************
*                 Destructor
*********************************************************************/
trainingGrounds::~trainingGrounds()
{
}

/*********************************************************************
*                 getSpaceDescription()
* @param none
* @return: string (Description of the location)
* Description: Display the description of the location before the user
*	interacts with the Space and after the user interacts with the Space
*********************************************************************/
std::string trainingGrounds::getSpaceDescription()
{
	if (!interacted)
	{
		std::string description = "            'Most of you are going to ice out. \n";
		std::string description1 = "Most of you aren't worth the price of bringing you up here. \n";
		std::string description2 = "               Some of you might make it. \n";
		std::string description3 = "      Some of you might be worth something to humanity. \n";
		std::string description4 = "                 But don't bet on it.\n";
		std::string description5 = "               I'm betting on only one.' \n\n";

		std::string beginTraining = " ***  Press 5 to engage and begin your training!  ***\n";
		return description + description1 + description2 + description3 + description4 + description5 + beginTraining;
	}
	else
	{
		std::string description = "           Welcome back to Battle School.\n";
		std::string description1 = "      You have already mastered the art of war.\n";
		std::string description2 = "\n Your goal is to locate the hive planet and destroy it. \n";
		std::string description3 = "But with your wisdom you know you must save the queen egg. \n";
		return description + description1 + description2 + description3;
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
void trainingGrounds::getItem()
{
	std::string itemToTake;
	bool valid = false;
	bool correctInput = false;
	int choice;

	if (item.empty())
	{
		cout << "       There are no items available here" << endl;
		cout << "You have already taken " << this->itemTakenStack.at(0) << endl;
		cout << "\n    Press Enter to continue your mission." << endl;
		pause();
	}
	else
	{
		cout << "At the location you discovered: " << endl;
		cout << this->item.at(0) << endl << endl;

		cout << "Did you want to put it in your cargo:" << endl;
		cout << "1: Yes";
		cout << "\t2: No" << endl;

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
		}

	}
}

/*****************************************************************************
*                 spaceInteraction()
* @param none
* @return: none
* Description: The function controls the interaction between the player and
*	the trainingGrounds class. This allows the user to engage the enemy through
*	several rounds. They will take turns attacking each other and taking damage.
*	The loser will be the unit that losses all of their squadron. The player
*	will be notified of the outcome of the interaction. If the user wins then
*	they will be able to collect the item at the location else they will have
*	to try again. This function also allows the user to understand the rules
*	and goals for the game in order to win. 
****************************************************************************/
void trainingGrounds::spaceInteraction()
{
	int choice = 0; 
	int rounds = 1;
	int playerTurn = 1; 
	int attack = 0;

	if (!interacted)
	{
		// Initialize enemy
		Salamander = new Cadet("Bonzo");
		emptySpace();

		cout << endl << "\tWelcome to your training young cadet!" << endl;
		cout << "\t  You will learn the art of combat" << endl << endl;
		cout << "  Throughout your simulation you will find items that" << endl;
		cout << "\t you may add or remove from your cargo" << endl;
		cout << " But choose wisely what you would like to keep or discard" << endl << endl;

		// User has an item placed in their inventory 
		player1->setCargo("Freeze Gun (Adds 25% Attack Damage)");
		removeItem();

		// Get user choice and validate input
		cout << "    You have been given a Freeze gun for your battle!" << endl << endl;
		while (choice != 6)
		{
			cout << "*** Select 'Manage Cargo' to see your current inventory ***" << endl;
			choice = simulationMenu();
			cout << endl; 
		}
		emptySpace();

		// User must select to view their cargo 
		player1->viewCargo();
		cout << "\n        Press Enter to continue." << endl;
		pause();

		emptySpace();

		cout << "   You have been challenged to dual \n   the highest ranking cadet 'Bonzo'" << endl; 
		cout << "   Your squadron health starts at 25" << endl;
		cout << "\n    Press Enter to begin the fight" << endl;
		pause();
		emptySpace();

		// Iterate through each round while one is attacking and the other defending 
		do
		{
			if (playerTurn) // Player 1 is attacking / Player 2 is defending
			{
				player1->rollAttackDie();
				attack = player1->getAttack();

				Salamander->damage(attack);

				// Change to have player 2 go first next round 
				playerTurn = 0;
			}
			else // Player 2 is attacking / Player 1 is defending
			{
				Salamander->rollAttackDie();
				attack = Salamander->getAttack();

				player1->damage(attack);

				if (player1->getSquadron() <= 12)
				{
					player1->addSquadron(10);
				}

				// Change to have player 1 go attack next round 
				playerTurn = 1;
			}

			// increment round count 
			++rounds;

		} while (player1->getSquadron() > 0 && Salamander->getSquadron() > 0);

		// If the user won the battle then inform the player how many rounds were played and how many more 
		// squadron he has left. 
		// User will also get the option to iunspect the item that he unlocked. 
		// Set location to being interacted with 
		cout << endl << "     You won after " << rounds << " tough rounds" << endl;
		cout << "   Your squadron has " << player1->getSquadron() << " fighters left" << endl << endl;

		if (player1->getSquadron() < 25)
			player1->addSquadron(20);

		cout << "\n       Press Enter to continue." << endl;
 		pause();

		emptySpace();
		
		cout << " 'He could see Bonzo's anger growing hot. \n "
			 << "Hot anger was bad. Ender's anger was cold, \n"
			 << "   and he could use it. Bonzo's was hot, \n"
			 << "         and so it used him.' \n" << endl;
		 cout <<"\n       Press Enter to continue." << endl;
		 pause();

		emptySpace();

		cout << "   Congratulations on your victory!" << endl;
		cout << " You are now a ready and able commander" << endl;
		cout << "    Your squadron was replenished" << endl;
		cout << "\n  Press Enter to view your mission." << endl;
		pause();
		emptySpace();

		// De-allocate memory
		delete Salamander;

		// Set the user completed the tasks and has interacted with the location 
		setInteracted();

		// Display goal to win the game 
		cout << "                    The goal of your mission is to locate " << endl;
		cout << "                       \"Dr.Device\" and the \"Queen Egg\" " << endl; 
		cout << "   Only then will you be able to enter the Hive Planet and destroy their colony" << endl << endl;
		cout << "    An icon will be placed on the map once you complete the task of a location" << endl; 
		cout << "\n                     Press Enter to begin your mission." << endl;
		pause();
		emptySpace();
	}
	else
	{
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
void trainingGrounds::spaceInteracted()
{
	bool valid = false;
	bool correctInput = false;
	int choice;

	std::string description = "Good job on your training, you are a brilliant commander\n\n";
	cout << description;

	cout << "You see your old locker, do you want to open it" << endl;
	cout << "1: Yes";
	cout << "\t2: No" << endl;

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
		getItem();
	}
	else
	{
		cout << "\n       You reminisce of the early days" << endl;
		cout << "\n    Press Enter to continue your mission." << endl;
		pause();
	}
	emptySpace();
}
