#include "Mazer.hpp"

/*********************************************************************
*                 Constructor
*********************************************************************/
Mazer::Mazer(Unit *Wiggins)
{
	this->player1 = Wiggins;
	setRiddle();
}

/*********************************************************************
*                 Destructor
*********************************************************************/
Mazer::~Mazer()
{}

/*
*cite riddles: http://www.braingle.com/brainteasers/teaser.php?id=7424&op=2&comm=1#c
*http://www.riddlesandanswers.com/v/233102/how-will-a-mathematician-win-a-war-easily/#ixzz4jZGuImPL
*/
void Mazer::setRiddle()
{
	string description = "\tCastles may rise and castles may fall\n"
		"\tSoldiers will fight and stand tall\n"
		"\tLords of war are enjoying the kill\n"
		"\tNot really caring about lives they spill\n"
		"\tWinners take all, winners are brave\n"
		"\tBut in this war they are buried in a grave\n"
		"\t\tWhat is this war ? \n";
	riddles.push_back(description); 

	description = "\tHow will a mathematician win a war easily?\n";
	riddles.push_back(description);

	description = "\tWhat do you call an army ant?\n";
	riddles.push_back(description);

	riddle1.answer1 = "1: Mobile Strike";
	riddle1.answer2 = "2: Chess Game";
	riddle1.answer3 = "3: Trojan War";
	riddle1.correctAnswer = "Chess Game";
	riddle1.finalAnswer = 2; 

	answers.push_back(riddle1);

	riddle2.answer1 = "1: By putting his enemy in close brackets";
	riddle2.answer2 = "2: By giving him endless pie";
	riddle2.answer3 = "3: Because your days are numbered";
	riddle2.correctAnswer = "By putting his enemy in close brackets";
	riddle2.finalAnswer = 1;

	answers.push_back(riddle2);

	riddle3.answer1 = "1: Antagonist";
	riddle3.answer2 = "2: Militant";
	riddle3.answer3 = "3: Variant";
	riddle3.correctAnswer = "Militant";
	riddle3.finalAnswer = 2;

	answers.push_back(riddle3);

}

/*********************************************************************
*                 getSpaceDescription()
* @param none
* @return: string (Description of the location)
* Description: Display the description of the location before the user
*	interacts with the Space and after the user interacts with the Space
*********************************************************************/
std::string Mazer::getSpaceDescription()
{
	if (!interacted)
	{
		std::string description = "     'I am your enemy, the first one you've ever had \n";
		std::string description1 = "      who was smarter than you. There is no teacher\n";
		std::string description2 = "    but the enemy. No one but the enemy will tell you \n";
		std::string description3 = "   what the enemy is going to do. No one but the enemy \n";
		std::string description4 = "      will ever teach you how to destroy and conquer.' \n";
		return description + description1 + description2 + description3 + description4;
	}
	else
	{
		std::string description = "\n       'Humanity does not ask us to be happy.\n";
		std::string description1 = "  It merely asks us to be brilliant on its behalf.'\n";
		return description + description1;
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
void Mazer::getItem()
{
	std::string itemToTake;
	bool valid = false;
	bool correctInput = false;
	int choice;
	char ch;

	if (item.empty())
	{
		cout << "          There are no items available here" << endl;
		cout << " You have already picked up " << this->itemTakenStack.at(0) << endl;
		cout << "\n    Press Enter to continue your mission." << endl;
		cin.clear();
		cin.ignore();
		cin.get(ch);
	}
	else
	{
		cout << "Mazer Racham offers to go with you into battle" << endl;

		cout << "     Did you want to take him with you" << endl;
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
				cout << "\nItem was placed in your cargo\n";

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
			cout << "       You may want to pick him up later" << endl;
			cout << "\n    Press Enter to continue your mission." << endl;
			cin.clear();
			cin.ignore();
			cin.get(ch);
		}
	}
}

/*****************************************************************************
*                 spaceInteraction()
* @param none
* @return: none
* Description: The function controls the interaction between the player and
*	the computer. The user must answer 3 riddles. The user must get 2 out of
*	the 3 correct in order to complete the task. The user will gain 1 squadron
*	for each question they get right but will lose 2 fighters for each that
*	they get wrong.
****************************************************************************/
void Mazer::spaceInteraction()
{
	bool valid = false;
	bool correctInput = false;
	int choice = 0;
	int correct = 0;
	int playerSquad; 

	emptySpace();

	if (!interacted)
	{
		cout << "\tYou meet Mazer Racham at the outPost" << endl;
		cout << " He intends to train in the art of manipulation and wits\n" << endl; 
		cout << "    He will ask you 3 riddles that you must solve" << endl;
		cout << " Get the riddle right, add a fighter to your squadron" << endl;
		cout << "   Get it wrong, lose 2 fighters from your squadron" << endl; 
		cout << "\n               Press Enter to continue" << endl; 
		pause();

		emptySpace();

		for (int count = 0; count < 3; count++)
		{
			cout << "                  Riddle Number " << count + 1 << endl;
			cout << riddles[count] << endl; 
			cout << answers[count].answer1 << endl;
			cout << answers[count].answer2 << endl;
			cout << answers[count].answer3 << endl;

			// Get user choice and validate input
			while (!valid)
			{
				cout << "Answer: ";
				cin >> choice;

				if (cin)
				{
					correctInput = true;
				}
				valid = validate(choice, 1, 3, correctInput);
			}
			valid = false;
			correctInput = false;

			if (choice == answers[count].finalAnswer)
			{
				cout << "\n\t    You chose the correct answer!" << endl;

				if (player1->getSquadron() < 25)
				{
					cout << "\t      Added 1 to your squadron." << endl;
					player1->addSquadron(1);
				}
				else
				{
					cout << " Was not able to add squadron due to being at full capacity." << endl;
				}
				correct++; 
			}
			else
			{
				cout << "\n\t     You entered the wrong answer\n";
				cout << "\t     Removed 2 from your squadron." << endl;
				if (count == 1)
					cout << "\tAnswer: " << answers[count].correctAnswer << endl; 
				else
					cout << "\t       Answer: " << answers[count].correctAnswer << endl;
				player1->removeSquadron(2);
			}
			cout << "\n               Press Enter to continue" << endl;
			pause();
			emptySpace();
		}

		playerSquad = player1->getSquadron();

		if (playerSquad <= 0 || correct == 1)
		{
			cout << "       You did not survive Rackham's tests" << endl;
			cout << "You either lost all your squadron or only got 1 riddle correct" << endl;
			cout << "\n    Press Enter to continue your mission." << endl;
			pause();
		}
		else
		{
			cout << "    What a brain teaser Rackham is" << endl;
			cout << "  Total correct: " << correct << endl << endl;
			cout << "Mazer Racham will be key to our success\n" << endl;

			cout << "Do you want to check out the rest of the outPost:" << endl;
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
			emptySpace();

			if (choice == 1)
			{
				getItem();
			}
			else
			{
				cout << "\n    Hopefully he wasn't needed, commander" << endl;
				cout << "\n    Press Enter to continue your mission." << endl;
				pause();
			}
			setInteracted();
		}
	}
	else // Already interacted
	{
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
void Mazer::spaceInteracted()
{
	bool valid = false;
	bool correctInput = false;
	int choice;

	std::string description = "Soldiers lay around twittling their thumbs in boredon.\n"
		"    Must be nice to just lay around for a bit.\n\n";
	cout << description;

	cout << "Do you want to check out the outPost:" << endl;
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
	emptySpace();

	if (choice == 1)
	{
		getItem();
	}
	else
	{
		cout << "\n  Mazer Rackham is a top-notch leader don't you think" << endl;
		cout << "\n       Press Enter to continue your mission." << endl;
		pause();
	}
	emptySpace();
}