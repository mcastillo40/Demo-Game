#include "Validate.hpp"
#include <iostream>

using std::cerr;
using std::cin;

/*********************************************************************
*                 validateInt()
* @param userInput(Integer entered by user)
* @param type(Type of character entered by user)
* @param lowerScope(The lowest choice the user can make)
* @param upperScope(The highest choice the user can make)
* @return: bool
* Description: This function validates whether the users input is
* correct.If not calid then it returns a false.
*********************************************************************/
bool validate(int userInput, int lowerScope, int upperScope, bool type)
{
	if ((userInput < lowerScope || userInput > upperScope) || !type)
	{
		cin.clear();
		cerr << "INCORRECT INPUT\n";
		cin.ignore();
		return false;
	}
	else
		return true;
}
