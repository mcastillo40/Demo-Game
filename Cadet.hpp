/*********************************************************************
* Author: Matthew Castillo
** Date: 6/13/17
* Description: The Cadet unit inherits from the unit class.
* The Cadet has a cargo space so that they may store an item that they
* pick up from traversing the game. The functions allow the user to 
* manage their inventory by viewing, adding and removing an item from
* their cargo. When the cadet is attacking an opponent their attack
* is based on 1 roll of a 10 sided die, defense based on 1 roll
* of a 5 sided die. The cadet had 25 squadron points. 
*********************************************************************/
#ifndef Cadet_HPP
#define Cadet_HPP
#include"Unit.hpp"
#include "Validate.hpp"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>

// Set Cadet's max life to 25
const int MAX_SQUADRON_SIZE = 25;

class Cadet : public Unit
{
	private:
		int randomNumber;
		unsigned seed;
		std::vector<std::string> cargo;
	public:
		// Default constructor
		Cadet(std::string);

		// Default destructor
		~Cadet();

		// Give options to manage inventory
		void manageCargo();

		// Set item into the cargo
		void setCargo(std::string);

		// Remove specific item from cargo
		void removeSpecificCargo(std::string item);

		// Remove an item choosen by user from cargo
		void removeCargo();

		// Display inventory
		void viewCargo();

		// Validate that an item is in the user's inventory
		virtual bool checkCargo(const std::string&);

		// Add squadron to the cadet's health
		virtual void addSquadron(const int&);

		// Random number generator based on the number
		// of sides of attack die for the barbarian
		virtual void rollAttackDie();

		// Random number generator based on the number
		// of sides of defense die for the barbarian
		virtual void rollDefenseDie();

		// The total damage taken based on attacker's points
		// against the Cadet's defense pts
		virtual	void damage(int);
};

#endif // ! Cadet_HPP