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


	while (true) {
		// player one goes first, display their hit/fire board
		// or display their own board if "O" typed
		// or surrender if 'S' typed
		// ask for coordinates

		pauseScreen(PLAYER1);
		do {
			hit = launchMissile(PLAYER1, &PLAYER2);
			if (!isAlive(PLAYER2)) {
				winner = PLAYER1;
				gameOver = true;
				break;
			}
		} while (hit);

		if (gameOver) { break; }

		pauseScreen(PLAYER2);
		do {
			hit = launchMissile(PLAYER2, &PLAYER1);
			if (!isAlive(PLAYER1)) {
				winner = PLAYER2;
				gameOver = true;
				break;
			}
		} while (hit);

		if (gameOver) { break; }
				
	}

	// if user wants to play again
	if (congratulateWinner(winner)) 
		main();
	
	// deallocate memory for boards/users
	deletePlayer(PLAYER1);
	deletePlayer(PLAYER2);

    return EXIT_SUCCESS;
}
