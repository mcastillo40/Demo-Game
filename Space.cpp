#include "Space.hpp"

/*********************************************************************
*                 Constructor
*********************************************************************/
Space::Space()
{
	this->up = nullptr;
	this->down = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->interacted = false;
	this->mission = false;
	this->interacted = false;
}

// Destructor
Space::~Space()
{}

// Set item in Space
void Space::setItem(const std::string &itemName)
{
	this->item.push_back(itemName);
}

// Set the description of the space
void Space::setDescription(const std::string &description)
{
	this->spaceDescription = description;
}

// Set whether the user interacted with the Space
void Space::setInteracted()
{
	this->interacted = true; 
}

// Get item from the space
void Space::getItem()
{}

// Remove item from the Space's location 
void Space::removeItem()
{
	std::string itemToRemove;

	itemToRemove = this->item.at(0);

	this->itemTakenStack.push_back(itemToRemove);
	this->item.pop_back();
}

// Get the Space linked above current Space
Space* Space::getUp() const
{
	return this->up;
}

// Get the space linked below the current space 
Space* Space::getDown() const
{
	return this->down;
}

// Get the space linked to the right of the current space 
Space* Space::getRight() const
{
	return this->right;
}

// Get the space linked to the left of the current space 
Space* Space::getLeft() const
{
	return this->left;
}

// Get the name of the area
std::string Space::getAreaName() const
{
	return this->areaName; 
}

// Get if the user interacted with the space
bool Space::getInteracted() const
{
	return this->interacted;
}

// Create empty space on the terminal 
void Space::emptySpace()
{
	for (int i = 0; i < 60; i++)
		cout << "\n";
}

// Pause terminal
void Space::pause()
{
	std::string pauseScreen;
	cin.clear();
	getline(cin, pauseScreen);
//	cin.clear();
	cin.ignore();
}

// Link the space with another Space on the top, bottom, left and right, it will also initialize the name of the space 
void Space::linkSpace(Space *Top, Space *Bottom, Space *LeftS, Space *RightS, const std::string &name)
{
	this->up = Top;
	this->down = Bottom;
	this->left = LeftS;
	this->right = RightS;
	this->areaName = name;
}

