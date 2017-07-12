#include "Simulation.hpp"

// Default constructor
Simulation::Simulation()
{
	// The user that is created
	Ender = new Cadet("Ender"); 

	// The spaces that the user may enter
	training = new trainingGrounds(Ender);
	bugPlanet1 = new buggerInstallation(Ender);
	bugPlanet2 = new buggerInstallation(Ender);
	bugPlanet3 = new buggerInstallation(Ender);
	eggWorld = new Giant(Ender);
	gravity = new BlackHole(Ender);
	outPost = new Mazer(Ender);
	bomber = new Doctor(Ender);
	finalPlanet = new HivePlanet(Ender);

	// Whether user completed the game
	missionOutcome = false;

	// The level of difficulty for the bug planets
	buggerLevel = 0; 

	// User starts with 2 lives
	life = 2; 

	//The map has 3 rows and 3 columns
	int numRow = 3;
	int numCol = 3;

	// Initialize the map
	for (int row = 0; row < numRow; row++)
	{
		for (int col = 0; col < numCol; col++)
		{
			map[row][col] = ' ';
		}
	}

	// Set links for each of the spaces
	setLinks();
}

// Destructor
Simulation::~Simulation()
{
	// Release memory of player
	delete Ender;

	// Release memory of spaces
	delete training;
	delete bugPlanet1;
	delete bugPlanet2;
	delete bugPlanet3;
	delete eggWorld;
	delete gravity;
	delete outPost;
	delete bomber;
	delete finalPlanet;
}

/*********************************************************************
*                 setLinks()
* @param none
* @return: void
* Description: Function creates links between the spaces so that the user
* 		may traverse through the universe through each of the spaces.
*		Listed Top, bottom, Left, Right, and name of the Space
*********************************************************************/
void Simulation::setLinks()
{
	training->linkSpace(finalPlanet, eggWorld, bugPlanet1, bugPlanet2, "Battle School");
	bugPlanet1->linkSpace(bomber, bugPlanet3, bugPlanet2, training, "Bug Planet 1");
	bugPlanet2->linkSpace(gravity, outPost, training, bugPlanet1, "Bug Planet 2");
	bugPlanet3->linkSpace(bugPlanet1, bomber, outPost, eggWorld, "Bug Planet 3");
	eggWorld->linkSpace(training, finalPlanet, bugPlanet3, outPost, "Forgotten Castle");
	gravity->linkSpace(outPost, bugPlanet2, finalPlanet, bomber, "Defy Physics");
	outPost->linkSpace(bugPlanet2, gravity, eggWorld, bugPlanet3, "Saving the Commander");
	bomber->linkSpace(bugPlanet3, bugPlanet1, gravity, finalPlanet, "Little Device");
	finalPlanet->linkSpace(eggWorld, training, bomber, gravity, "The Hive Planet");

	// Set user's current location to the training coordinate
	currentCoordinate = training;

	// Set items in each location.
	setItems();
}

/*********************************************************************
*                 setItems()
* @param none
* @return: void
* Description: Function inputs items into the spaces so that the
*		item may be retrieved by user after they accomplish the task
*		in that space.
*********************************************************************/
void Simulation::setItems()
{
	training->setItem("Freeze Gun (Adds 25% Attack Damage)");
	bugPlanet1->setItem("Bugger Poop (You can't always find something valuable in space)");
	bugPlanet2->setItem("Ansible Communication (Adds 2 to defense)");
	bugPlanet3->setItem("Additional forces");
	eggWorld->setItem("Queen Egg (To rebuild what was destroyed)");
	gravity->setItem("Warp Speed (Improves defense)");
	outPost->setItem("Commander Mazer Rackham");
	bomber->setItem("Dr. Device");
	finalPlanet->setItem("Mission Complete"); 
}


/*********************************************************************
*                 traverse()
* @param none
* @return: void
* Description: Function controls the gameplay. The user is given 25
* 	life to start with and 50 moves to complete the game. The game
*   will continue until the user decides to quit the game, losses all
*   their life, or completes the game. The function will keep track
* 	of user's current location in the spaces and will provide the
* 	user with the option to interact or to continue to the next location.
*	The map, clt's life, clt's remaining moves, and clt's options will
* 	be displayed.
*********************************************************************/
void Simulation::traverse()
{
	cout << endl;
	int option = 0; 
	char ch;
	int moves = 51;

	do
	{
		clearScreen();

		// Display the description of the location 
		cout << currentCoordinate->getSpaceDescription() << endl; 

		// Display the name of the location
		cout << "\t          " << currentCoordinate->getAreaName() << endl;
		cout << "----------------------------------------------------------" << endl;

		// Clt's current location in the map will be '^'
		cout << "\t        Current Location '^'" << endl;

		// Display map
		displayMap();

		// Display clt's life and the number of moves that they have left
		cout << "Squadron size: " << Ender->getSquadron() << "\t   Moves left: " << moves << endl; 

		// Display menu 
		// Direction to move user, Interact with location, view inventory, or exit program 
		option = simulationMenu();

		cout << endl; 
		clearScreen();

		// This will occur if the clt has not begun/completed their training. 
		if (currentCoordinate->getAreaName() == "Battle School" && !currentCoordinate->getInteracted() && option != 7)
		{
			// User must select 5 as an option to continue and begin the game 
			while (!currentCoordinate->getInteracted())
			{
				// Error message if user did not choose 5
				if (option != 5)
				{
					cout << endl << "You must train/engage before you may use your controls." << endl;
					option = simulationMenu();
				}
				// User will interact with "Training grounds" space and learn the game
				else
				{
					currentCoordinate->spaceInteraction();
					currentCoordinate->setInteracted();
				}
			}
		}
		else
		{
			if (option == 1) // Traverse up
			{
				currentCoordinate = currentCoordinate->getUp();
			}
			else if (option == 2) // Traverse down
			{
				currentCoordinate = currentCoordinate->getDown();
			}
			else if (option == 3) // Traverse left
			{
				currentCoordinate = currentCoordinate->getLeft();
			}
			else if (option == 4) // Traverse right
			{
				currentCoordinate = currentCoordinate->getRight();
			}
			else if (option == 5) // Interact with current location
			{
				levelUpBugs(); // Level up bugs if entering bug world
				currentCoordinate->spaceInteraction();
			}
			else if (option == 6) // View inventory
			{
				Ender->manageCargo();
				cout << "\n    Press Enter to continue your mission." << endl;
				cin.ignore();
				cin.get(ch);
			}
		}

		// Check if mission was completed
		missionOutcome = currentCoordinate->missionComplete();

		// If user dies then they will revive with 10 health
		if (Ender->getSquadron() <= 0 && !missionOutcome)
		{
			if (life > 0)
			{
				cout << "You lost all your forces, here are your last reinforcemnts." << endl;
				cout << "       10 fighters were added to your squadron." << endl;
				cout << "           You no longer have an extra life." << endl;
				cout << "\n       Press Enter to continue your mission." << endl;
				cin.ignore();
				cin.get(ch);
				Ender->addSquadron(10);
				life--;
			}
		}

		// countdown for the number of moves left
		moves--;

	} while (life > 0 && !missionOutcome && option != 7 && moves != 0);

	// Display outcome of the game
	displayOutcome();
}

/*********************************************************************
*                 displayOutcome()
* @param: none
* @return: void
* Description: Display if the user won the game or lost the game
*********************************************************************/
void Simulation::displayOutcome()
{
	char ch; 

	if (missionOutcome)
	{
		cout << "     You were able to complete the simulation flawlessly" << endl;
		cout << "However you found out that you really destroyed a whole species" << endl;
		cout << "   Luckily you saved the egg so that the buggers may rebuild " << endl;
		cout << "\n                Press Enter to Continue." << endl;
		cin.ignore();
		cin.get(ch);
		clearScreen();
	}
	else
	{
		cout << "          You lost the game!" << endl;
		cout << "        Better luck next time" << endl;
    	cout << "\n       Press Enter to Continue." << endl;
		cin.ignore();
		cin.get(ch);
		clearScreen();
	}
}

/*********************************************************************
*                 levelUpBugs()
* @param: none
* @return: void
* Description: Level up the Bug planet for each bug world entered
*		this will increase the size of fighters for each world
*********************************************************************/
void Simulation::levelUpBugs()
{
	if (currentCoordinate->getAreaName() == "Bug Planet 3")
	{
		buggerLevel += 5;
		currentCoordinate->setLevel(buggerLevel);
	}
	else if (currentCoordinate->getAreaName() == "Bug Planet 1")
	{
		buggerLevel += 5;
		currentCoordinate->setLevel(buggerLevel);
	}
	else if (currentCoordinate->getAreaName() == "Bug Planet 2")
	{
		buggerLevel += 5;
		currentCoordinate->setLevel(buggerLevel);
	}
	else if (currentCoordinate->getAreaName() == "Hive Planet")
	{
		currentCoordinate->setLevel(10);
	}
}

/*********************************************************************
*                 displayMap()
* @param: none
* @return: void
* Description: The map will be displayed to the user. If the user inrteracted
* 	in the current location then it will change the icon for that position
*   on the map
*               1    2     3
*			1	B
*			2
*			3        ^
* '^' - current location		'H' - Hive Planet
* 'B' - Bug planet				'!' - Gravity Space
* '0' - Giant Space 			'&' - Mazer Space
* '*' - Doctor Space			'@' - Training grounds
*********************************************************************/
void Simulation::displayMap()
{
	bool enteredArea = false;

	enteredArea = currentCoordinate->getInteracted(); 

	// Set the current location to be indicated on the map with '^'
	if (currentCoordinate->getAreaName() == "Bug Planet 3")
		map[0][0] = '^';
	else if (currentCoordinate->getAreaName() == "Forgotten Castle")
		map[0][1] = '^';
	else if (currentCoordinate->getAreaName() == "Saving the Commander")
		map[0][2] = '^';
	else if (currentCoordinate->getAreaName() == "Little Device")
		map[1][0] = '^';
	else if (currentCoordinate->getAreaName() == "The Hive Planet")
		map[1][1] = '^';
	else if (currentCoordinate->getAreaName() == "Defy Physics")
		map[1][2] = '^';
	else if (currentCoordinate->getAreaName() == "Bug Planet 1")
		map[2][0] = '^';
	else if (currentCoordinate->getAreaName() == "Battle School")
		map[2][1] = '^';
	else if (currentCoordinate->getAreaName() == "Bug Planet 2")
		map[2][2] = '^';


	// Display map
	cout << endl << "\t\t1    2    3" << endl;
	for (int row = 0; row < 3; row++)
	{
		cout << "\t    " <<row + 1;
		for (int col = 0; col < 3; col++)
		{
			cout << "   " << map[row][col] << " ";
		}
		cout << endl << endl;
	}

	// Change icon on the map if the user interacts with a location
	if (currentCoordinate->getAreaName() == "Bug Planet 3" && enteredArea)
		map[0][0] = 'B';
	else if (currentCoordinate->getAreaName() == "Bug Planet 3" && !(enteredArea))
		map[0][0] = ' ';
	else if (currentCoordinate->getAreaName() == "Forgotten Castle" && enteredArea)
		map[0][1] = '0';
	else if (currentCoordinate->getAreaName() == "Forgotten Castle" && !(enteredArea))
		map[0][1] = ' ';
	else if (currentCoordinate->getAreaName() == "Saving the Commander" && enteredArea)
		map[0][2] = '&';
	else if (currentCoordinate->getAreaName() == "Saving the Commander" && !(enteredArea))
		map[0][2] = ' ';
	else if (currentCoordinate->getAreaName() == "Little Device" && enteredArea)
		map[1][0] = '*';
	else if (currentCoordinate->getAreaName() == "Little Device" && !(enteredArea))
		map[1][0] = ' ';
	else if (currentCoordinate->getAreaName() == "The Hive Planet" && enteredArea)
		map[1][1] = 'H';
	else if (currentCoordinate->getAreaName() == "The Hive Planet" && !(enteredArea))
		map[1][1] = ' ';
	else if (currentCoordinate->getAreaName() == "Defy Physics" && enteredArea)
		map[1][2] = '!';
	else if (currentCoordinate->getAreaName() == "Defy Physics" && !(enteredArea))
		map[1][2] = ' ';
	else if (currentCoordinate->getAreaName() == "Bug Planet 1" && enteredArea)
		map[2][0] = 'B';
	else if (currentCoordinate->getAreaName() == "Bug Planet 1" && !(enteredArea))
		map[2][0] = ' ';
	else if (currentCoordinate->getAreaName() == "Battle School" && enteredArea)
		map[2][1] = '@';
	else if (currentCoordinate->getAreaName() == "Battle School" && !(enteredArea))
		map[2][1] = ' ';
	else if (currentCoordinate->getAreaName() == "Bug Planet 2" && enteredArea)
		map[2][2] = 'B';
	else if (currentCoordinate->getAreaName() == "Bug Planet 2" && !(enteredArea))
		map[2][2] = ' ';
}

/*********************************************************************
*                 clearScreen()
* @param: none
* @return: void
* Description: Clear area on th terminal so that the next section of 
*	the game can be shown. 
*********************************************************************/
void Simulation::clearScreen()
{
	for (int i = 0; i < 60; i++)
		cout << "\n";
}
