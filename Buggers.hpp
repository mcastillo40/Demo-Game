/*********************************************************************
* Author: Matthew Castillo
** Date: 6/13/17
* Description: The Buggers Unit inherits from the Unit class.
* The buggers are a basic unit that only utilize basic functions
* such as attack and defense. They are utilized in the bugger Installation
* when attacked by the user. The buggers squadron size increase for each 
* installation that the user attacks. 
* Attack based on 1 roll of a 5 sided die, defense based on 1 roll
* of a 5 sided die, and 10 squadron points starting off and will increase
* by 5 for each time the user enters their bugger planet.
*********************************************************************/
#ifndef Buggers_HPP
#define Buggers_HPP
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include"Unit.hpp"

class Buggers : public Unit
{
	private:
		int randomNumber;
		unsigned seed;
	public:
		// Default constructor
		Buggers();

		// Default destructor
		~Buggers();

		virtual void addSquadron(const int&type)
		{
			squadron += type;
		}

		virtual void removeSpecificCargo(std::string item);
		virtual bool checkCargo(const std::string&);
		virtual void manageCargo() {};
		virtual void setCargo(std::string) {};
		virtual void removeCargo() {};
		virtual void viewCargo() {};

		// Random number generator based on the number
		// of sides of attack die for specific unit
		virtual void rollAttackDie();

		// Random number generator based on the number
		// of sides of defense die for specific unit
		virtual void rollDefenseDie();

		// The total damage taken based on attacker's points
		// against defender's armor and defense pts
		virtual	void damage(int);
};

#endif // ! Cadet_HPP