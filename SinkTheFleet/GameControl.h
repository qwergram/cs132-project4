#pragma once
//----------------------------------------------------------------------------
// File:		fleet.h
// 
// Description: Sink the Fleet declarations
//	
// Programmer:	Paul Bladek
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//----------------------------------------------------------------------------
#ifndef FLEET_H
#define FLEET_H

#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include "textGraphics.h"
#include "safeio.h"

using namespace std;

const short NUMPLAYERS = 2;	// number of players in game
const short SMALLROWS = 8;	// number of rows/columns in small sea array 
const short LARGEROWS = 10;	// number of rows/columns in large sea array
const short SMALLCOLS = 12;	// number of rows/columns in small sea array 
const short LARGECOLS = 24;	// number of rows/columns in large sea array

const short BOXWIDTH = 79;	// maximum screen line length


const int SHIP_SIZE_ARRAYSIZE = 6; // size of the shipSize array
const short shipSize[SHIP_SIZE_ARRAYSIZE] = { 0, 2, 3, 3, 4, 5 };
const short SHIP_PIECES_ENUM_VALUE[SHIP_SIZE_ARRAYSIZE] = {-1, 0, 1, 2, 3, 4};
const string SHIP_NAMES[SHIP_SIZE_ARRAYSIZE] = { "",
												 "minesweep", 
												 "submarine", 
												 "wsfrigate", 
												 "bttleship", 
												 "accarrier" };
// number of elements for each ship

//----------------------------------------------------------------------------
// enumerated type for ships
//----------------------------------------------------------------------------
enum Ship
{
	NOSHIP,		 // 0
	MINESWEEPER, // 1 (1-5) -- used only for owner
	SUB,		 // 2
	FRIGATE,	 // 3
	BATTLESHIP,	 // 4
	CARRIER,	 // 5
	HIT,		 // 6 (6-7)-- used only for other side
	MISSED,		 // 7 
};

//----------------------------------------------------------------------------
// enumerated type for direction on grid
//----------------------------------------------------------------------------
enum Direction
{
	HORIZONTAL, // 0
	VERTICAL	// 1
};


//----------------------------------------------------------------------------
// row and column location
//----------------------------------------------------------------------------
struct Cell
{
	unsigned short m_row;	// row
	unsigned short m_col;	// column
};

//----------------------------------------------------------------------------
// needed info about each ship
//----------------------------------------------------------------------------
struct ShipInfo
{
	Ship m_name;			// which ship?
	Direction m_orientation;// which direction is the ship facing? 
	Cell m_bowLocation;		// which cell is the bow location?
	short m_piecesLeft;		// how many sections are left undestroyed?
};

//----------------------------------------------------------------------------
// needed info about each player
//----------------------------------------------------------------------------
struct Player
{
	Ship ** m_gameGrid[NUMPLAYERS]; // one 2-d array for each player
									// [0] is player's grid;
									// [1] is opponant's grid
	ShipInfo m_ships[SHIP_SIZE_ARRAYSIZE];	// ships in fleet-- [0] is blank	
	short m_piecesLeft;	// how many sections of fleet are left undestroyed?
};

//----------------------------------------------------------------------------
// function prototypes for ship
//----------------------------------------------------------------------------

// prints to sout one individual ship
void printShip(ostream & sout, Ship thisShip);

// builds ship in player grid or removes it
void buildShipSpace(const Player& player, short shipIndex, char response);

// returns true if ship has been sunk (no points left)
bool isSunk(Ship thisShip);

//  prints a specific game grid
void printGrid(ostream& sout, Ship** grid, char size);

// automatically builds a grid with ships
void autoGrid(Player players[], char size, short whichPlayer);

//----------------------------------------------------------------------------
// function prototypes for ShipInfo
//----------------------------------------------------------------------------
// sets ShipInfo fields
void setShipInfo(ShipInfo * shipInfoPtr, Ship name = NOSHIP,
	Direction orientation = HORIZONTAL,
	unsigned short row = 0, unsigned short col = 0);

//----------------------------------------------------------------------------
// function prototypes for Player
//----------------------------------------------------------------------------
// sets initial values for m_ships and m_piecesLeft
void initializePlayer(Player* playerPtr);

// allocates memory for grids
void allocMem(Player players[], char size);

// deletes memory for grids
void deleteMem(Player players[], char size);

// saves the ship grid to a file
void saveGrid(Player players[], short whichPlayer, char size);

// reads grid from a file	
bool getGrid(Player players[], short whichPlayer, char size, string fileName);

// allows user to put ships in grid
void setShips(Player players[], char size, short whichPlayer);

// returns a cell with coordinates set by user
Cell getCoord(istream& sin, char size);

// can the ship go there?
bool validLocation(const Player& player, short shipNumber, char size);

// ...
//----------------------------------------------------------------------------
// other function prototypes
//----------------------------------------------------------------------------
// prints opening graphic
void header(ostream& sout);
// prints closinging graphic
void endBox(short player);
// your headers go here 

const unsigned BUFFER_SIZE = 256;
char safeChoice(string prompt, char choice1 = 'Y', char choice2 = 'N');

template<class T>
void safeRead(istream& sin, T& input,
	const char* prompt = "invalid input--please input a NUMBER: ");

//---------------------------------------------------------------------------------
// Function:	template<class T>
//				void safeRead(istream& sin, T& input, const char* prompt)
//
// Title:		safeRead
//
// Description: Safely reads in a variable (input) from sin.
//					Re-prompts and re-enters if input is invalid  
//
// Programmer:	Paul Bladek
// 
// Date:		5/1/2006
//
// Version: 1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input: T& input from istream& sin
//
// Output: Screen display of prompt
//
// Calls: none
//
// Called By: 
//
// Parameters:	istream& sin		-- the input stream
//				T& input			-- theinput variable
//				const char* prompt	-- prompt if not a number
// 
// Returns: none
//
// History Log:
//				5/1/06 PB completed version 1.0
// ------------------------------------------------------------------------------
template<class T>
void safeRead(istream& sin, T& input, const char* prompt)
{
	while (!(sin >> input))		// read in number--enter loop if fail
	{
		sin.clear();
		sin.ignore(BUFFER_SIZE, '\n');
		cout << prompt;
	}
	sin.ignore(BUFFER_SIZE, '\n');
}
#endif
