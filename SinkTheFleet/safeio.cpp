//----------------------------------------------------------------------------
// File:	safeio.cpp
// 
// Function:
//      	safeChoice()
//			getValidCoordinate()
//			emptyWaters()
//----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "SinkTheFleet.h"

using namespace std;

//---------------------------------------------------------------------------------
// Function: 	Coord getValidCoordinate(char shipOrrientation, short shipSize, 
//					Player player, bool noclip)
//
// Title:	Get Valid Coordinate
//
// Description: 
//		gets valid coordinates for placing a ship and firing 
//   
// Programmer:	Paul Bladek & Norton Pengra & Tabitha Roemish
// 
// 
// Date:	12/20/05
//
// Version: 	1.2
// 
// Environment: Hardware: i7
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	string input from console
//
// Output:	Screen display of invalid prompts
//
// Calls: 	emptyWaters()
//
// Called By:	launchMissile
//				manuallyPopulate
//
//
// Parameters:	shipOrientation: Char (V or H)
//				shipSize: short (ship size array index)
//				player: Player Struct
//				noclip: bool (distinguishes between firing or placing ships)
//		
// 
// Returns:	the character input and validated
//
// History Log:
//		12/20/05 PB completed v 1
//      1/27/2017 TR completed v1.1
//		1/31/2017 NP completed v1.2
// ------------------------------------------------------------------------------

Coord getValidCoordinate(char shipOrrientation, short shipSize, Player player, bool noclip) { // return a coordinate struct
	string userInput;
	Coord userCoordinate;
	Coord offsets;
	bool valid = false;
	

	while (!valid) {

		getline(cin, userInput);

		userCoordinate.x = atoi(&userInput.c_str()[1]) - 1; // parse into integer (-1 for grid index)
		userCoordinate.y = indexOf(LETTER_TO_INT, toupper(userInput[0])); //obtain grid index for letter input

		offsets.x = (!noclip && shipOrrientation == HORIZONTAL_SHIP) ? userCoordinate.x + shipSize : userCoordinate.x + (short)noclip;
		offsets.y = (!noclip && shipOrrientation == VERTICAL_SHIP) ? userCoordinate.y + shipSize : userCoordinate.y + (short)noclip;


		// check if within bounds
		if (offsets.x <= BOARD_COLS && userCoordinate.x >= 0 && offsets.y <= BOARD_ROWS && userCoordinate.y >= 0) {
			if (noclip || emptyWaters(userCoordinate, offsets, shipOrrientation, shipSize, player)) {
				return userCoordinate;
			}
			else {
				cout << "You have a ship occupying that spot: ";
			}
		}
		else {
			cout << "Please type in a valid coordinate: ";
		}
	}
}

//---------------------------------------------------------------------------------
// Function:	bool emptyWaters(Coord coords, Coord offsets, char orrientation, 
//					short shipSize, Player player)
// Title:	Empty Waters
// Description:
//		checks if a ship is already occupying the area
// Programmer: Paul Bladek & Norton Pengra & Tabitha Roemish
// 
// Date:	12/20/05
//
// Version:	1.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls: none
//
// Called By: getValidCoordinate()
//
// Parameters:	coord: Coord struct (intial corrdinates)
//				offsets: coord struct (adjusted coordinates)
//				orrientation: char (V or H)
//				shipSize: short (size of ship)
//				player: Player struct
// 
// Returns: bool -- 	false if water is occupied
//				
//
// History Log:
//		12/20/05 PB completed v 1
//      01/31/2017 NP & TR completed 1.1
//---------------------------------------------------------------------------------

bool emptyWaters(Coord coords, Coord offsets, char orrientation, short shipSize, Player player) {
	// check if there's a ship there
	bool valid;
	if (orrientation == VERTICAL_SHIP) {
		for (short index = coords.y; index < offsets.y; index++) {
			valid = player.gameGrid[index][coords.x] == NOSHIP;
			if (!valid) {
				return false;
			}
		}
	}
	else {
		for (short index = coords.x; index < offsets.x; index++) {
			valid = player.gameGrid[coords.y][index] == NOSHIP;
			if (!valid) {
				return false;
			}
		}
	}
	return true;
}


//---------------------------------------------------------------------------------
// Function: 	safeChoice(string prompt, char choice1, char choice2)
//
// Title:	safeChoice
//
// Description: 
//		Safely allows user to select one of two characters
//   
// Programmer:	Paul Bladek
// 
// Date:	5/1/2006
//
// Version: 	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Input:	char input from console
//
// Output:	Screen display of prompt
//
// Calls: 	none
//
// Called By:	main()
//		setships()
//
//
// Parameters:	prompt: string;	prompt for input
//		choice1: char;	the default choice; default value: 'Y'
//		choice2: char;	the other choice;   default value: 'N'
// 
// Returns:	the character input and validated
//
// History Log:
//		5/1/06 PB completed version 1.0
// ------------------------------------------------------------------------------
char safeChoice(string prompt, char choice1, char choice2)
{
	char input = choice1;
	ostringstream outSStream;
	outSStream << " (" << choice1 << "/" << choice2 << "): " << choice1 << "\b";
	cout << prompt << outSStream.str();
	while ((input = toupper(input = cin.get())) != choice1
		&& input != choice2 && input != '\n')
	{
		cin.ignore(BUFFER_SIZE, '\n');
		cout << prompt << outSStream.str();
	}
	if (input == '\n')
		input = choice1;
	else
		cin.ignore(BUFFER_SIZE, '\n');
	return input;
}