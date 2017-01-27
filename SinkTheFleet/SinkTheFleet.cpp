
#include "SinkTheFleet.h"

using namespace std;



/* ----------------------- CPP FILE START ----------------------- */

// Board size
short BOARD_ROWS;
short BOARD_COLS;

// Players
Player PLAYER1;
Player PLAYER2;

// main game loop
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
		// TODO:
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
}


