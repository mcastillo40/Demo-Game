#include "Doctor.hpp"

/*********************************************************************
*                 Constructor
*********************************************************************/
Doctor::Doctor(Unit *Wiggins)
{
	message = false;
	this->player1 = Wiggins;
}

/*********************************************************************
*                 Destructor
*********************************************************************/
Doctor::~Doctor()
{}

/*********************************************************************
*                 getSpaceDescription()
* @param none
* @return: string (Description of the location)
* Description: Display the description of the location before the user
*	interacts with the Space and after the user interacts with the Space
*********************************************************************/
std::string Doctor::getSpaceDescription()
{
	if (!interacted)
	{
		std::string description =  "Before the war, there was not a need for such a deadly weapon\n";
		std::string description1 = " The device created at this Hangar was meant to end the Hive\n";
		std::string description2 = "       Enter to learn about the military intelligence \n";

		return description + description1 + description2;
	}
	else
	{
		std::string description = "      You look at the screen with a toppled Giant.\n";
		std::string description1 = " 'This was supposed to be a Game. Not a choice between \n";
		std::string description2 = " his own grisly death and an even worse murder. I'm a\n";
		std::string description3 = " \t murderer, even when I play.\n";
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
void Doctor::getItem()
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
				emptySpace();

				cout << "            You send a message to your family knowing that it may be your last." << endl;
				cout << "         Commander Mazer Rackham presents you with the commands to use 'Dr. Device" << endl;
				cout << "\n                             'Dr. Device' was placed in your cargo\n";
				message = true;

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
*	the computer. The user will have had to have "Commander Mazer Rackham" in
*	in order to enter the location. The user will be given a description of the
*	item that they will be receiving. The item will be unlocked once the user
*	decides to send a message to their family. 
****************************************************************************/
void Doctor::spaceInteraction()
{
	bool valid = false;
	bool correctInput = false;
	bool found = false; 
	int choice;

	emptySpace();

	if (!interacted)
	{
		found = player1->checkCargo("Commander Mazer Rackham"); 
		if (!found)
		{
			cout << "You must first locate 'Commander Mazer Rackham' before you may enter the Hangar" << endl; 
			cout << "\n                   Press Enter to continue." << endl;
			pause();
		}
		else
		{

			// When the user enters the location they will be given description of the item that they will be collecting 
			cout << "  They see that you brought Commander Mazer Rackham with you and let you through the gates" << endl;
			cout << "        He shows you around the base where you witness confidential experiments" << endl; 
			cout << "   You are seated at the briefing room in order to discuss the arsenal available to you" << endl;
			cout << "         Through the meeting you could only think of your family back home" << endl;
			cout << "\n                          Press Enter to continue." << endl;
			
			pause();
			emptySpace();

			cout << "         You are shown the blueprints of the Little Device also known as 'Dr. Device' " << endl;
			cout << "  It has the ability of wiping out organic creatures that are in close proximity of each other" << endl;
			cout << " The ship carrying the device has almost reached the hive planet and you will be able to use it " << endl; 
			cout << "\n                          Press Enter to continue." << endl;

			pause();
			emptySpace();

			// User must agree to send message to their family in order to unlock and obtain the item at the location 
			cout << "        Before you leave the facility would you like to send a message to your family" << endl; 
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
			valid = false;
			correctInput = false;

			emptySpace();

			if (choice == 1)
			{
				getItem(); // Give user option to add item to cargo 
			}
			else
			{
				cout << "          Hopefully, it is not too late to send the message when you get back" << endl;
				cout << "\n                     Press Enter to continue your mission." << endl;
				pause();
				emptySpace();
			}

			// Set the user completed the tasks and has interacted with the location 
			setInteracted();
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
void Doctor::spaceInteracted()
{
	bool valid = false;
	bool correctInput = false;
	int choice;

	std::string description = "The workers are done with the task of building a deadly weapon\n\n";
	cout << description;

	cout << "  Do you want to go inside Hangar 18" << endl;
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

	if (choice == 1)
	{
		if (!message)
		{
			cout << "     You must send the message to your family in order to collect the device" << endl;
			cout << "                 Would you like to send the message at this time" << endl;
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

			if (choice == 1)
			{
				getItem(); // Give user option to add item to cargo 
			}
			else
			{
				cout << "      Hopefully, it is not too late to send the message when you get back" << endl;
			}

			cout << "\n    Press Enter to continue your mission." << endl;
			pause();
		}
		else
			getItem(); // Give user option to add item to cargo 
	}
	else
	{
		cout << "\n  The survival of the human race depends on this device" << endl;
		cout << "\n       Press Enter to continue your mission." << endl;
		pause();
	}
}