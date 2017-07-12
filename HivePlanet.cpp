#include "HivePlanet.hpp"

/*********************************************************************
*                 Constructor
*********************************************************************/
HivePlanet::HivePlanet(Unit *Wiggins)
{
	this->player1 = Wiggins;
}

/*********************************************************************
*                 Destructor
*********************************************************************/
HivePlanet::~HivePlanet()
{}

/*********************************************************************
*                 getSpaceDescription()
* @param none
* @return: string (Description of the location)
* Description: Display the description of the location before the user
*	interacts with the Space and after the user interacts with the Space
*********************************************************************/
std::string HivePlanet::getSpaceDescription()
{

	std::string description = "'In the moment when I truly understand my enemy, understand him well\n";
	std::string description1 = "  enough to defeat him, then in that very moment I also love him.\n";
	std::string description2 = "I think it's impossible to really understand somebody, what they want,\n";
	std::string description3 = "what they believe, and not love them the way they love themselves. And \n";
	std::string description4 = "           then, in that very moment when I love them ...\n";
	std::string description5 = "                      I destroy them!'\n";

	return description + description1 + description2 + description3 + description4 + description5;
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
void HivePlanet::getItem()
{
	std::string itemToTake;
	bool valid = false;
	bool correctInput = false;
	int choice;

	if (item.empty())
	{
		cout << "         There are no items available here" << endl;
		cout << "   You have already taken " << this->itemTakenStack.at(0) << endl;
		cout << "\n      Press Enter to continue your mission." << endl;
		pause();
	}
	else
	{
		cout << "At the location you discovered " << endl;
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

/*************************************************************************************
*                 spaceInteraction()
* @param none
* @return: none
* Description: The function controls the interaction between the player and
*	the computer. The user must have "Dr. Device" and "Queen Egg (To rebuild what was destroyed)"
*	in order to complete the tasks. The user will win the game once both of these 
*	items are collected and when the user enters this location  
*************************************************************************************/
void HivePlanet::spaceInteraction()
{
	bool foundDevice = false;
	bool foundEgg = false;
	int squadSize = 0;
	

	// Check clt's cargo for specific items 
	foundDevice = player1->checkCargo("Dr. Device");
	foundEgg = player1->checkCargo("Queen Egg (To rebuild what was destroyed)");

	emptySpace();

		if (!foundDevice || !foundEgg)
		{
			cout << "You must first locate 'Dr. Device' and the 'Queen Egg'" << endl;
			cout << "\n               Press Enter to continue." << endl;
			pause();
		}
		else
		{
			cout << "       Your ships have made it to the Hive Planet" << endl;
			cout << "  A swarm of buggers wait patiently for your next move " << endl;
			cout << "You decide to send all your ships into battle to annihilate the planet" << endl;
			cout << "\n               Press Enter to continue." << endl;
			pause();
			emptySpace();

			cout << "Your squadron goes full throttle towards the planet in order to use ..." << endl;
			cout << "          The Little Device to destroy the whole species" << endl;

			cout << "            You continue to take damage from the buggers" << endl;
			player1->damage(30);

			squadSize = player1->getSquadron();

			if (squadSize > 0)
			{
				cout << "Your shields are down and you are hit by another wave of fighters" << endl;
				player1->damage(30);
			}

			emptySpace();
			cout << " Your last ship was able to penetrate the planet's atmosphere " << endl;
			cout << "       You use your special weapon to destroy the planet!!" << endl;
			cout << "          And you realize that the simulation is over" << endl;
			cout << "\n                Press Enter to finish the Game." << endl;
			setMission();
			pause();
		}
}

// There is not an interacted content because the user would have won the game if they 
// complete the task
void HivePlanet::spaceInteracted()
{}
