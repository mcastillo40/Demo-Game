#include "Buggers.hpp"

/*********************************************************************
*                 Constructor
*********************************************************************/
Buggers::Buggers()
{
	squadron = 10;
	seed = time(0);
	srand(seed);
	randomNumber = 0;
	name = "Crazy Critter";
}

/*********************************************************************
*                 Destructor
*********************************************************************/
Buggers::~Buggers()
{} 


/*********************************************************************
*                 rollAttackDie()
* @param none
* @return: none
* Description: Return a random roll of die for attack based on a 5
*				sided die.
*********************************************************************/
void Buggers::rollAttackDie()
{
	int rolledDie = rand() % (5 - 1 + 1) + 1;

	this->attack = rolledDie;
}

/*********************************************************************
*                 rollDefenseDie()
* @param none
* @return: none
* Description: Return a random roll of die for defense based on a 5
*              sided die.
*********************************************************************/
void Buggers::rollDefenseDie()
{
	int defenseDie = rand() % (5 - 1 + 1) + 1;

	this->defense = defenseDie;
}

/*********************************************************************
*                 damage()
* @param none
* @return: none
* Description: Calculate the damage that the Bugger took
*      based on the attack damage of the opposing player will subtract
*      from the defense points and will set the Bugger's new squadron 
*	   based on the damage done. 
*********************************************************************/
void Buggers::damage(int attackPts)
{
	int totalDamage = 0;
	rollDefenseDie();

	// Calculate the total damage
	totalDamage = attackPts - this->defense;
	if (totalDamage > 0)
		this->squadron -= totalDamage;
}

/*********************************************************************
*                 checkCargo()
* @param none
* @return: bool false
* Description: Return false because the unit does not have items collected
*********************************************************************/
bool Buggers::checkCargo(const std::string& item)
{
	return false;
}

/*********************************************************************
*                 removeSpecificCargo()
* @param none
* @return: none
* Description: Bugger does not have a specific item. 
*********************************************************************/
void Buggers::removeSpecificCargo(std::string item)
{
}