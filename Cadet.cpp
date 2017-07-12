#include "Cadet.hpp"

using std::vector;
using std::cout;
using std::endl;
using std::cin;

/*********************************************************************
*                 Constructor
*********************************************************************/
Cadet::Cadet(std::string cadetName)
{
	squadron = MAX_SQUADRON_SIZE;
	name = cadetName;
	seed = time(0);
	srand(seed);
} 

/*********************************************************************
*                 Destructor
*********************************************************************/
Cadet::~Cadet()
{}

/*********************************************************************
*                 manageCargo()
* @param none
* @return: none
* Description: Display user with option to view or remove an item from
*	their cargo. Function will validate user's entry. 
*********************************************************************/
void Cadet::manageCargo()
{
	bool valid = false;
	bool correctInput = false;
	int choice;

	cout << "Do you want to:" << endl;
	cout << "1: View you Cargo";
	cout << "\t2: Remove an item from your Cargo" << endl;

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
	clearArea();

	// If user chooses 1 then view cargo, else remove an item
	if (choice == 1)
	{
		viewCargo();
	}
	else
	{
		removeCargo();
	}
}

/*********************************************************************
*                 removeSpecificCargo()
* @param string item (specific item to be removed from cargo)
* @return: none
* Description: Search the cargo for an item with the same name.
*	If found, delete from cargo, else nothing happens
*********************************************************************/
void Cadet::removeSpecificCargo(std::string item)
{
	for (unsigned int i = 0; i < cargo.size(); i++)
	{
		if (cargo.at(i) == item)
		{
			cargo.erase(cargo.begin() + i);
		}
	}
}

/*********************************************************************
*                 removeCargo()
* @param none
* @return: none
* Description: Allows the user to choose what item that they would like
*	to remove from their cargo. Item will not be able to remove "Dr. Device", 
*	"Queen Egg (To rebuild what was destroyed)", and "Commander Mazer Rackham."
*	As they are needed to complete the game. 
*********************************************************************/
void Cadet::removeCargo()
{
	bool valid = false;
	bool correctInput = false; 
	bool valuableItem = false;
	int choice;
	std::string item;
	std::string importantCargo;
	int arraySize = 3;
	std::string essentialItems[] = { "Dr. Device", "Queen Egg (To rebuild what was destroyed)", "Commander Mazer Rackham" };

	// If cargo is empty inform user that there are no items to remove
	if (cargo.empty())
	{
		cout << "\nYou do not have any items to remove." << endl;
	}
	else
	{
		int exit = 0; 
		cout << endl << "What would you like to release:" << endl;
		viewCargo();

		// Set exit to be 1 more of the count of the cargo size so that
		// it may be an exit option 
		exit = cargo.size() + 1; 
		cout << exit << ": Do not remove any items" << endl;

		// Get user choice and validate input
		while (!valid)
		{
			cout << "Decision: ";
			cin >> choice;

			if (cin)
			{
				correctInput = true;
			}
			valid = validate(choice, 1, exit, correctInput);
		}
		// Create blank space
		clearArea();

		// If user decides to remove an item
		// Compare to essential items to complete the game
		// If not essential then remove, else inform user that they
		// must keep the item. 
		if (choice != exit)
		{
			item = cargo.at(choice - 1);

			for (int count = 0; count < arraySize; count++)
			{
				importantCargo = essentialItems[count];

				if (item.compare(importantCargo) == 0)
				{
					cout << endl << item << " is important to complete your mission." << endl;
					cout << "You do not want to remove it." << endl << endl;
					valuableItem = true;
				}
			}

			if (!valuableItem)
			{
				cout << item << "\nwas removed from your cargo" << endl;
				choice--;
				cargo.erase(cargo.begin() + choice);
			}
		}
	}
}

/*********************************************************************
*                 setCargo()
* @param string item (item to add to cadet's cargo)
* @return: none
* Description: Add an item to the user's cargo as long as it does not exceed 4.
*	items. Else have the user decide to remove an additional item to be
*	replaced or not add the item. 
*********************************************************************/
void Cadet::setCargo(std::string item)
{
	bool valid = false;
	bool correctInput = false;
	int choice;

	// If addint the item will exceed 4 items then inform the user that
	// they must replace an item in their cargo or that they will not add the item. 
	if (cargo.size() == 4) 
	{
		cout << "\nYou have too many items in your cargo" << endl;
		cout << "1: Remove an Item ";
		cout << "\t2: This item isn't that important " << endl;

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

		// Create space in terminal 
		clearArea();

		// Remove item from cargo as long as it is not needed to complete the game
		// Set that the item was taken. 
		if (choice == 1)
		{
			removeCargo();

			if (cargo.size() == 4)
			{ 
				setCargo(item);
			}
			else
			{
				cargo.push_back(item);
				this->itemTaken = true;
			}
		}
		else
		{
			cout << "Maybe you can add the item to your cargo later." << endl;
			this->itemTaken = false;
		}
	}
	else
	{
		cargo.push_back(item);
		this->itemTaken = true; 
	}
}

/*********************************************************************
*                 viewCargo()
* @param none
* @return: none
* Description: Display the items in the user's cargo 
*                CARGO
* --------------------------------------
* 1. Freeze Gun (Adds 25% Attack Damage)
*********************************************************************/
void Cadet::viewCargo()
{
	// validate that cargo is not empty
	if (cargo.empty())
	{
		cout << "You do not have any items stored." << endl;
	}
	else
	{
		int elements = 1;
		auto iter = cargo.begin();
		cout << endl << "\t\t   CARGO" << endl;
		cout << "--------------------------------------------" << endl;
		while (iter != cargo.end())
		{
			cout << "  " << elements << ": " << *iter << endl;
			elements++;
			iter++;
		}
	}
	cout << endl ;
}

/*********************************************************************
*                 checkCargo()
* @param string searchItem (Item that is being checked for in cargo)
* @return: bool (if item was found in cargo)
* Description: Return whether the item passed was found in the cadet's
*	inventory. If found return true, else return false
*********************************************************************/
bool Cadet::checkCargo(const std::string &searchItem)
{
	bool found = false;

	if (std::find(cargo.begin(), cargo.end(), searchItem) != cargo.end())
	{
		found = true;
	}

	return found;
}

/*********************************************************************
*                 addSquadron()
* @param int pilots (amount of squadron to add to the cadet)
* @return: bool (if item was found in cargo)
* Description: Add number of squadron to the cadet's health as long as it
*	does not exceed the MAX_SQUADRON_SIZE. 
*********************************************************************/
void Cadet::addSquadron(const int &pilots) 
{
	if (this->squadron == MAX_SQUADRON_SIZE)
	{
		cout << "You already have a complete squad" << endl;
	}
	else
	{
		if ((this->squadron + pilots) > MAX_SQUADRON_SIZE)
		{
			this->squadron = MAX_SQUADRON_SIZE; 
		}
		else
			this->squadron += pilots;
	}
}

/*********************************************************************
*                 rollAttackDie()
* @param none
* @return: none
* Description: A random roll of die for attack based on a 10
*	sided die. If the user has "Freeze Gun (Adds 25% Attack Damage)"
*	in their cargo then add 25% to the roll. 
*********************************************************************/
void Cadet::rollAttackDie()
{
	int rolledDie = rand() % (10 - 1 + 1) + 1;

	if (!cargo.empty())
	{
		for (unsigned int i = 0; i < cargo.size(); i++)
		{
			if (cargo.at(i) == "Freeze Gun (Adds 25% Attack Damage)")
			{
				rolledDie += (rolledDie * .25); 
				this->attack = rolledDie;
			}
		}
	}
	else
	{
		this->attack = rolledDie;
	}
}

/*********************************************************************
*                 rollDefenseDie()
* @param none
* @return: void
* Description: A random roll of die for defense based on a 5
*              sided die.
*********************************************************************/
void Cadet::rollDefenseDie()
{
	int defenseDie = rand() % (5 - 1 + 1) + 1;

	this->defense = defenseDie;
}

/*********************************************************************
*                 damage()
* @param none
* @return: none
* Description: Calculate the damage that the Cadet took
*   based on the attack damage of the opposing player will subtract
*   from the defense points and will set the Cadet's new strength based 
*	on the damage done. If the user has "Ansible Communication (Adds 2 to defense)"
*	in their cargo then add 2 to their defense pts. 
*********************************************************************/
void Cadet::damage(int attackPts)
{
	int totalDamage = 0;

	rollDefenseDie();

	if (!cargo.empty())
	{
		for (unsigned int i = 0; i < cargo.size(); i++)
		{	
			if (cargo.at(i) == "Ansible Communication (Adds 2 to defense)")
			{
				this->defense += 2;

				totalDamage = attackPts - this->defense;
				if (totalDamage > 0)
					this->squadron -= totalDamage;
			}
			else {
				// Calculate the total damage
				totalDamage = attackPts - this->defense;
				if (totalDamage > 0)
					this->squadron -= totalDamage;
			}
		}
	}
	else
	{
		// Calculate the total damage
		totalDamage = attackPts - this->defense;
		if (totalDamage > 0)
			this->squadron -= totalDamage;
	}
}

