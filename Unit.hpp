/*************************************************************************
** Program Name: Final Project
** Author: Matthew Castillo
** Date: 6/13/17
** Description: The Unit class is a parent class for the buggers and cadet
** classes. This initializes a character that has a name, a squadron (life),
** and attack, defense points. 
*************************************************************************/
#ifndef Unit_HPP
#define Unit_HPP
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <iomanip>

using std::cout;
using std::endl;
using std::cin;

// Unit Class Declaration
class Unit
{
	protected:
		int squadron;
		int attack;
		int defense;
		std::string name; 
		bool itemTaken; 
	public:
		// Constructor
		Unit();

		// Pure virtual functions
		virtual ~Unit() = 0; 
		virtual void removeSpecificCargo(std::string item) = 0;
		virtual void manageCargo() = 0;
		virtual void setCargo(std::string) = 0;
		virtual void removeCargo() = 0;
		virtual void viewCargo() = 0;
		virtual void rollAttackDie() = 0;
		virtual void rollDefenseDie() = 0;
		virtual	void damage(int) = 0;
		virtual bool checkCargo(const std::string&) = 0;
		virtual void addSquadron(const int&);

		// Accessor Functions
		int getAttack();
		int getDefense();
		std::string getName() const;
		int getSquadron() const;
		bool getItemTaken();

		// Mutator function
		void setItemTakenFalse();

		// Remove a number of squadron's from the unit 
		void removeSquadron(const int&);

		// Create space in the terminal 
		void clearArea();
};

#endif // ! Unit_HPP
