/*************************************************************************
** Program Name: Final Project
** Author: Matthew Castillo
** Date: 6/13/17
** Description: The Space class is the parent class for the various spaces
**		in the game. Additionally, each space will be linked to one another
**		from top, bottom, left and right. The class will have a name and
**		description of the space that the user will be entering. Each space
**		will also have an item that the user will be able to grab. The user must
**		complete the task in order to take the item. The unit will be passed
**		into each class so that they may interact with the area.
*************************************************************************/
#ifndef Space_HPP
#define Space_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Unit.hpp"
#include "Validate.hpp"

using std::cout;
using std::endl;
using std::cin;
using std::vector;

// Space Class Declaration
class Space
{
	protected:
		Space *up;
		Space *down;
		Space *right;
		Space *left;
		std::string spaceDescription;
		std::string areaName;
		bool interacted;
		bool essentialItem;
		Unit *player1;
		std::vector<std::string> item;
		std::vector<std::string> itemTakenStack;
		int level;
		bool mission;

	public:
		// Default Constructor
		Space();

		// Pure virtual functions
		virtual ~Space() = 0;
		virtual std::string getSpaceDescription() = 0;
		virtual void spaceInteraction() = 0;
		virtual void spaceInteracted() = 0;
		virtual void getItem() = 0;

		// Mutator Functions
		void setItem(const std::string&);
		void setDescription(const std::string&);
		void setInteracted();
		void setLevel(const int&levelUp) { level = levelUp; };
		void setMission() { mission = true; }

		// Accessor Functions
		Space* getUp() const;
		Space* getDown() const;
		Space* getRight() const;
		Space* getLeft() const;
		std::string getAreaName() const;
		bool getInteracted() const;
		int getLevel() { return level; };

		// Remove item from space
		void removeItem();

		// return if mission was complete
		bool missionComplete() { return mission; };

		// Print a blank space
		void emptySpace();

		// Pause interaction
		void pause();

		// Link each space as well as name the location
		void linkSpace(Space*, Space*, Space*, Space*, const std::string&);
};

#endif // ! Space_HPP
