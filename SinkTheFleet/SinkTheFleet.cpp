//----------------------------------------------------------------------------
// File:	SinkTheFleetleet.cpp
//
// Function:
//      main()
//----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include "fleet.h"

extern const char *shipNames[7];
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

    do
    {
	presentWelcome();
	setBoardSize();

	// allocate memory for boards/users
	PLAYER1 = initPlayer(1);
	PLAYER2 = initPlayer(2);

	// set game stats
	bool gameOver = false;
	bool hit;
	Player winner;

	// build board for each player
	populateGrid(PLAYER1);
	populateGrid(PLAYER2);


	

	// Begin Game: clear screen & print header again with prompt "To begin game press <enter>"
	clearScreen();
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
	    else if (game[whichPlayer].m_gameGrid[0][coord.m_row][coord.m_col] != NOSHIP) //if ship hit
	    {
		shipHit = game[whichPlayer].m_gameGrid[0][coord.m_row][coord.m_col]; // get ship from grid[0]
		game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = HIT;     // add hit to grid[1]
		printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);	  // print hit on grid
		game[!whichPlayer].m_ships[shipHit].m_piecesLeft--;		     // take ship point from opponent
		if (game[!whichPlayer].m_ships[shipHit].m_piecesLeft == 0)
		    cout << "Opponents " << SHIP_NAMES[shipHit] << " has been sunk!\n";
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
		printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);	 // print miss on grid
		cout << "Missed! Your turn is over. Press <enter> to continue";
		cin.get();
		whichPlayer = !whichPlayer; // switch players
	    }
	}

	again = safeChoice("Would you like to play again?", 'Y', 'N');
    } while (again == 'Y');

    return EXIT_SUCCESS;
}
