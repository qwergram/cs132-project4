
//----------------------------------------------------------------------------
// File:	SinkTheFleetleet.cpp
// 
// Function:
//      main()
//----------------------------------------------------------------------------

#include "SinkTheFleet.h"

using namespace std;

// Board size
short BOARD_ROWS;
short BOARD_COLS;

// Players
Player PLAYER1;
Player PLAYER2;
//---------------------------------------------------------------------------------
// Function:	main()
// Title:		Game Play
// Description:
//				Runs the Sink the Fleet Game
//
// Programmer:	Paul Bladek  
// modified by:	Norton Pengra & Tabitha Roemish
// 
// Date created: 12/9/2010
//
// Version:		0.6
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:		none
//
// Output:		none
//
// Calls:		congratulateWinner()
//				deletePlayer()
//				initPlayer()
//				isAlive()
//				launchMissile()
//				puaseScreen()
//				populateGrid()
//				presentWelcome()
//				setBoardSize()
//				main()
//
// Called By:	n/a
//
// Parameters:	void
// 
// Returns:		int -- EXIT_SUCCESS upon successful completion
//
// History Log: 
//				12/9/2010 PB completed v 0.5
//				1/31/2017	NP & TR completed v0.6
//---------------------------------------------------------------------------------

void main() {
	
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

	// start game loop
	while (true) {
		
		
		pauseScreen(PLAYER1);
		do {
			hit = launchMissile(PLAYER1, &PLAYER2); // ask for coordinates
			if (!isAlive(PLAYER2)) { // check if player2 has 0 health points
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
}


