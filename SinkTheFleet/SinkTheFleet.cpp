//----------------------------------------------------------------------------
// File:	SinkTheFleetleet.cpp
// 
// Function:
//      main()
//----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include "fleet.h"
using namespace std;
extern const char* shipNames[7];
//---------------------------------------------------------------------------------
// Function:	main()
// Title:		Set ShipInfo
// Description:
//				Runs the Sink the Fleet Game
// Programmer:	Paul Bladek
// modified by:
// 
// Date:		12/9/2010
//
// Version:		0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input:		
//
// Output:		
//
// Calls:		initializePlayer()
//				allocMem()
//				safeChoice()
//				getGrid()
//				printGrid()
//				resetGrid()
//				setships()
//				header()
//				getCoord()
//				deleteMem()
//				endBox()
//
// Called By:	n/a
//
// Parameters:	void
// 
// Returns:		int -- EXIT_SUCCESS upon successful completion
//
// History Log: 
//				12/9/2010 PB completed v 0.5
//   
//---------------------------------------------------------------------------------
int main(void)
{
	short numRows = SMALLROWS;			// total number of rows in the array
	short numCols = SMALLCOLS;			// total number of columns in the array
	char again = 'N';
	char gridSize = 'S';
	short whichPlayer = 0;
	bool gameOver = false;
	bool reshot = false;
	Cell coord = { 0, 0 };
	string message;
	string filename;
	Ship shipHit = NOSHIP;
	Player game[NUMPLAYERS];	// the two players in an array
								// other stuff ...
	
	do
	{
		system("cls");
		cout << endl;
		header(cout);
		gridSize = safeChoice("Which size grid to you want to use", 'S', 'L');

		if (gridSize == 'L')
		{
			numRows = LARGEROWS;
			numCols = LARGECOLS;
		}
		else
		{
			numRows = SMALLROWS;
			numCols = SMALLCOLS;
		}
		initializePlayer(game);
		initializePlayer(game + 1);
		// dynamically create the rows of the array
		allocMem(game, gridSize);

		// ... your code goes here
		
		for (whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
		{
		// enter grid files or let users enter ships
			
			//create function for below - get file name, call getGrid in fucntion....
			char uploadGrid = 'Y'; 
			const int nameSize = 50;
			char fileName[nameSize];
			uploadGrid = safeChoice("Would you like to upload a saved grid?", 'Y', 'N');
			cout << "Please enter the name of the file to open";
			if (uploadGrid == 'Y')
			{
				getGrid(game, whichPlayer, gridSize, fileName); // getGrid should print out grid to cout and ask if grid is good
				// if not it should loop and ask if user wants to upload grid. 
			}
			else
				setShips(game, gridSize, whichPlayer); // add ships manually, asks to save grid
		}
		
		// game play outline
			// Begin Game: clear screen & print header again with prompt "To begin game press <enter>"
		whichPlayer = 0;
		while (!gameOver)
		{
		// ... a lot more stuff ...
			// Play Game:
				// while (whichPlayer)
					// printGrid[1]
					// get firing coordinates
					// check that firing coordintates have not already been guessed
					// compare coordinates to opponents grid [0] for hit or miss
					// Add HIT or MISS to players grid[1]
					// printGrid[1] with HIT or MISS
					// track opponents remaining ships (track peices left as well as ship space)
						//	if ship space == 0 then cout << shipName << "has been sunk!";
						//  if either player(!whichPlayer).m_piecesLeft == 0, then gameOver = True; 
					// if MISS, switch players
						// clear screen
			whichPlayer = !whichPlayer;  // switch players
		}
			// End Game: 
				// cout << "All opponents battleships have been sunk, congratulations! You win." 

		again = safeChoice("Would you like to play again?", 'Y', 'N');
	} while (again == 'Y');

	return EXIT_SUCCESS;
}
