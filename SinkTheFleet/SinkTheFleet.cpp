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
			cout << "Player " << whichPlayer;
			char uploadGrid = 'Y';
			uploadGrid = safeChoice("would you like to upload a saved grid?", 'Y', 'N');
			
			//create function for get file name to use in getGrid and saveGrid...(check for .shp and return string)
			// string getFileName(string openOrClose);
			const int nameSize = 50;
			char fileName[nameSize];
			
			if (uploadGrid == 'Y')
			{
				cout << "Please enter the name of the file to open";
				cin.getline(fileName, nameSize); 
				getGrid(game, whichPlayer, gridSize, fileName); // getGrid should print out grid to cout and ask if grid is good
				// if not it should loop and ask if user wants to upload grid. 
			}
			else
				setShips(game, gridSize, whichPlayer); // add ships manually, asks to save grid
		}
		
		
		// Begin Game: clear screen & print header again with prompt "To begin game press <enter>"
		system("cls");
		header(cout);
		cout << "To begin the game, press <enter>";
		cin.get();
		

		// Play Game:
		whichPlayer = 0;
		while (!gameOver)
		{
		// ... a lot more stuff ...
				printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);

				// get firing coordinates
				cout << "Player " << whichPlayer << ", enter coordinates for firing";
				coord = getCoord(cin, gridSize);

				// check that firing coordintates have not already been guessed
				if (game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] != NOSHIP)
				{
					cout << "You've already guessed that location";
					continue;
				}
				else
					if (game[whichPlayer].m_gameGrid[0][coord.m_row][coord.m_col] != NOSHIP) //if ship hit
					{
						shipHit = game[whichPlayer].m_gameGrid[0][coord.m_row][coord.m_col]; // get ship from grid[0]
						game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = HIT; // add hit to grid[1]
						printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize); // print hit on grid
						game[!whichPlayer].m_ships[shipHit].m_piecesLeft--; // take ship point from opponent
						if (game[!whichPlayer].m_ships[shipHit].m_piecesLeft == 0)
							cout << "Opponents " << shipHit << "has been sunk!\n";
						game[!whichPlayer].m_piecesLeft--; // take total point from opponent
						if (game[!whichPlayer].m_piecesLeft == 0)
						{
							cout << "All opponents battleships have been sunk!";
							endBox(whichPlayer);
							gameOver = true;
						}
						cout << "Hit! You get to guess again. Press <enter> to continue.";
						cin.get();
					}
					else // if miss
					{
						game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = MISSED; // add miss to grid[1]
						printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize); // print miss on grid
						cout << "Missed! Your turn is over. Press <enter> to continue";
						cin.get();
						whichPlayer = !whichPlayer;  // switch players	
					}
		}
			 
		again = safeChoice("Would you like to play again?", 'Y', 'N');
	} while (again == 'Y');

	return EXIT_SUCCESS;
}
