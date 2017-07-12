#include "Unit.hpp"

// Default Constructor
Unit::Unit()
{
	this->squadron = 0;
	this->attack = 0;
	this->defense = 0;
	this->name = "";
	this->itemTaken = false; 
}

// Destructor
Unit::~Unit()
{}


// Get Name of the unit
std::string Unit::getName() const
{
	return this->name;
}

/*********************************************************************
*                 getSqudron()
* @param none
* @return: int (health of the creature)
* Description: Returns the max health of the creature. 
*********************************************************************/
int Unit::getSquadron() const
{
	return this->squadron;
}

/*********************************************************************
*                 addSquadron()
* @param int   (The default health of the creature)
* @return: int (How much the creature was healed)
* Description: Will generate a random number from 3 to 5 which will be 
*	changed into a percentage (i.e: 3 will be 30%). Then the creature's 
*	current health will increase by that amount as long as it does not 
*	exceed it's max health. 
*********************************************************************/
void Unit::addSquadron(const int &additionForces)
{
	this->squadron += additionForces;
}

void Unit::removeSquadron(const int &removeForces)
{
	squadron -= removeForces; 
}

/*********************************************************************
*                 getAttack()
* @param none
* @return: int  (total attack damage)
* Description: Will call the rollAttackDie function based on the
*            creature being used. Will add to the total attack damage
*********************************************************************/
int Unit::getAttack()
{
	return this->attack;
}

/*********************************************************************
*                 getDefense()
* @param none
* @return: int  (total defense)
* Description: Will call the rollDefenseDie function based on the
*            creature being used. Will add to the total defense points
*********************************************************************/
int Unit::getDefense()
{
	return this->defense;
}

/*********************************************************************
*                 clearArea()
* @param none
* @return: none
* Description: Create space in the terminal
*********************************************************************/
void Unit::clearArea()
{
	for (int i = 0; i < 60; i++)
		cout << "\n";
}

/*********************************************************************
*                 getItemTaken()
* @param none
* @return: bool 
* Description: Return whether an item was taken by the user
*********************************************************************/
bool Unit::getItemTaken()
{
	return itemTaken;
}

/*********************************************************************
*                 setItemTakenFalse()
* @param none
* @return: none
* Description: Set that the item was taken to false 
*********************************************************************/
void Unit::setItemTakenFalse()
{
	itemTaken = false; 
}