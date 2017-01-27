#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "SinkTheFleet.h"

using namespace std;


/* ----------------------- CPP FILE START ----------------------- */


// get a coordinate
Coord getValidCoordinate(char shipOrrientation, short shipSize, Player player, bool noclip) { // return a coordinate struct
	string userInput;
	Coord userCoordinate;
	Coord offsets;
	bool valid = false;
	// for including size of the ship

	while (!valid) {

		getline(cin, userInput);

		// parse into integer
		userCoordinate.x = atoi(&userInput.c_str()[1]) - 1;
		userCoordinate.y = indexOf(LETTER_TO_INT, toupper(userInput[0]));

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


// check if it overlaps a ship
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