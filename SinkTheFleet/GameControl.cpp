#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "SinkTheFleet.h"

using namespace std;

/*
<PENGRABOT OPERATION="AUTO_GEN_CODE AUTO_GEN_HEADER AUTO_FORMAT_VSRULES" SECONDARYLANGUAGE="NORTON_SCRIPT_7" VERSION="7.9">
<STATUS>DELTA<STATUS/>
<TIME UNIT="SECONDS">0.249<TIME/>
<ERRORS>
<WARNING CODE="D_82_BD" TRANSPILATION="JAVASCRIPT" FATAL=FALSE/>
<WARNING CODE="D_82_9D" TRANSPILATION="JAVASCRIPT" FATAL=FALSE/>
<WARNING CODE="D_82_LD" TRANSPILATION="JAVASCRIPT" FATAL=FALSE/>
</ERRORS>
<!-- Have a good day, Mr. Pengra -->
</PENGRABOT>
*/
/* ----------------------- CPP FILE START ----------------------- */

// checks if the current player has any more fleet left
bool isAlive(Player player) {
	int playerHealth = 0;
	for (short shipIndex = 0; shipIndex < GRID_ENTITIES_COUNT; shipIndex++) {
		playerHealth += player.playerHealth[shipIndex];
	}
	return playerHealth > 0;
}

// ask the user to place ships themselves
void manuallyPopulate(Player player) {
	string shipName;
	GridEntities shipEnum;
	short shipSize;
	char shipOrrientation;
	bool shipOkay;
	Coord coordinates;

	for (short shipId = SHIP_RANGES[0]; shipId < SHIP_RANGES[1]; ) {
		clearScreen();
		printGrid(player.gameGrid);

		// get currentShip Info
		shipName = SHIPS[shipId];
		shipEnum = (GridEntities)shipId;
		shipSize = player.playerHealth[shipId];

		// get orrientation
		shipOrrientation = safeChoice(player.name + ", Enter " + shipName + " orrientation", VERTICAL_SHIP, HORIZONTAL_SHIP);

		// get location
		cout << player.name << ", Enter " << shipName << " coordinates: ";
		coordinates = getValidCoordinate(shipOrrientation, shipSize, player);

		// place ship
		placeShip(coordinates, shipOrrientation, shipId, player);

		// confirm location
		clearScreen();
		printGrid(player.gameGrid);
		shipOkay = safeChoice("Is this ship placement correct?") == 'Y';

		// if confirmed, move on
		if (!shipOkay) {
			removeShip(coordinates, shipOrrientation, shipId, player);
		}
		else {
			shipId++;
		}
	}
}

// remove the ship on this grid
void removeShip(Coord coordinates, char orrientation, short shipId, Player player) {
	placeShip(coordinates, orrientation, NOSHIP, player, player.playerHealth[shipId]);
}

// place the ship on board at location specified
void placeShip(Coord coordinates, char orrientation, short shipId, Player player, short size) {
	size = (size < 0) ? player.playerHealth[shipId] : size;
	if (orrientation == HORIZONTAL_SHIP) {
		for (short colIndex = 0; colIndex < size; colIndex++) {
			player.gameGrid[coordinates.y][coordinates.x + colIndex] = (GridEntities)shipId;
		}
	}
	else {
		for (short rowIndex = 0; rowIndex < size; rowIndex++) {
			player.gameGrid[coordinates.y + rowIndex][coordinates.x] = (GridEntities)shipId;
		}
	}
}


// deallocate memory for each player
void deletePlayer(Player player) {
	// delete the board
	if (player.gameGrid != nullptr) {
		for (short rowIndex = 0; rowIndex < BOARD_ROWS; rowIndex++) {
			if (player.gameGrid[rowIndex] != nullptr) {
				delete[] player.gameGrid[rowIndex];
			}
			else {
				break;
			}
		}
	}
	delete[] player.gameGrid;
}

// allocate memory for the player's boards and set player names
Player initPlayer(short playerId) {
	Player newPlayer;
	newPlayer.name = getPlayerName(playerId);
	// allocate the memory first
	newPlayer.gameGrid = allocMemory();
	return newPlayer;
}

// allocateMemory operations
GridEntities ** allocMemory() {

	// set it to nullptrs first
	GridEntities ** grid = nullptr;
	grid = new GridEntities *[BOARD_ROWS];

	for (short rowIndex = 0; rowIndex < BOARD_ROWS; ++rowIndex) {
		// set as nullptr first
		GridEntities * row = nullptr;
		row = new GridEntities[BOARD_COLS];

		for (short cellIndex = 0; cellIndex < BOARD_COLS; ++cellIndex) {
			// set it to NOSHIP
			row[cellIndex] = NOSHIP;
		}
		grid[rowIndex] = row;

	}
	return grid;
}

// get player's name
string getPlayerName(short playerId) {
	string playerName;
	cout << "What is player #" << playerId << "'s name?" << endl << "Name: ";
	getline(cin, playerName);
	return playerName;
}

// ask what the board the user would like to use and set global params
void setBoardSize() {
	char userChoice = safeChoice("Which size grid would you like to use", 'S', 'L');
	BOARD_ROWS = (userChoice == 'S') ? BOARD_ROWS_SMALL : BOARD_ROWS_LARGE;
	BOARD_COLS = (userChoice == 'S') ? BOARD_COLS_SMALL : BOARD_COLS_LARGE;
}

// launches a missile onto a ship returns true if hit and false if miss
bool launchMissile(Player attacker, Player * defender) {
	Coord target;
	short cell;
	string shipName = "ship";

	while (true) {
		printGrid(defender->gameGrid, true);
		cout << attacker.name << ", please enter a coordinate: ";

		target = getValidCoordinate(HORIZONTAL_SHIP, HIT, *defender, true);
		cell = (short)defender->gameGrid[target.y][target.x];
		if (cell <= SHIP_RANGES[1])
			break;
		cout << "You have already guessed that position." << endl;
		getline(cin, shipName);
	}

	// check if the cell is a ship
	if (cell < SHIP_RANGES[1] && cell >= SHIP_RANGES[0]) {
		defender->gameGrid[target.y][target.x] = HIT;
		printGrid(defender->gameGrid, true);
		cout << attacker.name << " hit ";
		defender->playerHealth[cell]--; // = defender.playerHealth[cell] - 1;
		if (defender->playerHealth[cell] < 1) {
			cout << "and sunk ";
			shipName = SHIPS[cell];
		}
		cout << defender->name << "'s " << shipName << '!' << "\n<enter> to continue" << endl;

		getline(cin, shipName);
		return true;
	}
	else if (cell == SHIP_RANGES[1]) {
		cout << "You already guessed that position\n<enter> to continue" << endl;
		getline(cin, shipName);
		return true;
	}
	else {
		defender->gameGrid[target.y][target.x] = MISSED;
		printGrid(defender->gameGrid, true);
		cout << attacker.name << " missed!\n<enter> to continue" << endl;

		getline(cin, shipName);
		return false;
	}
}

// ask if the user has a file they'd like to load
void populateGrid(Player player) {
	bool useFile = safeChoice(player.name + ", Would you like to load from a file?") == 'Y';
	bool loaded = false;
	while (true) {
		if (useFile) {
			loaded = loadFile(player);
			if (loaded)
				break;
			else
				cout << player.name << "'s board was unable to be loaded." << endl;
		}
		else {
			manuallyPopulate(player);
			saveMenu(player);
			break;
		}
	}
	clearScreen();
}

// load a file
bool loadFile(Player player) {
	ifstream handle;
	string filepath;
	string contents;

	short splitIndex = 0;
	short gridEntity;
	short rowIndex;
	short colIndex;

	cout << player.name << ", please specify filename: ";
	getline(cin, filepath);
	handle.open(filepath);
	if (handle.is_open()) {
		while (!handle.eof()) {
			getline(handle, contents);
			// 0, 1, 2 == GridEntities, rowIndex, colIndex

			int splitContents[3] = { 0, 0, 0 };

			for (short lineIndex = 0; lineIndex < contents.length(); lineIndex++) {

				if (contents[lineIndex] == ' ') {
					splitIndex++;
				}
				else {
					string int_as_str = contents.substr(lineIndex, 1);
					splitContents[splitIndex] = atoi(int_as_str.c_str());
					// throw exception("needs more work");
				}
			}

			splitIndex = 0;

			if (splitContents[0] != 0) { // ignore noship tiles
				player.gameGrid[splitContents[1]][splitContents[2]] = (GridEntities)splitContents[0];
			}

		}
	}
	else {
		return false;
	}
	handle.close();
	printGrid(player.gameGrid);

	if (safeChoice("Is board okay?") == 'N') {
		return false;
	}
	return true;
}

// ask the user if they'd like to save, and if they do, save the map.
void saveMenu(Player player) {
	if (safeChoice("Would you like to save the map?") == 'Y') {
		string filePath;
		string fileType = ".shp";
		cout << "Please type the relative file path: ";
		getline(cin, filePath);

		// add .shp extension if it doesn't already have it
		filePath = (equal(fileType.rbegin(), fileType.rend(), filePath.rbegin())) ? filePath : filePath + fileType;

		// save the map
		generateSave(filePath, player);

	}
}

// write the save file
void generateSave(string filePath, Player player) {
	ofstream handle(filePath);
	GridEntities cell;

	// go through the ships and save their coordinates

	for (short rowIndex = 0; rowIndex < BOARD_ROWS; rowIndex++) {
		for (short colIndex = 0; colIndex < BOARD_COLS; colIndex++) {
			cell = player.gameGrid[rowIndex][colIndex];
			if ((short)cell > 0) {
				handle << (short)cell << ' ' << rowIndex << ' ' << colIndex << endl;
			}
		}
	}

	handle.close();
}

// find the Index of the array
int indexOf(const char * charArray, char toFind) {
	int index = 0;
	while (true) {
		try {
			if (charArray[index] == toFind) {
				return index;
			}
			index++;
		}
		catch (exception) {
			return -1;
		}
	}
}

void randomGrid(Player player)
{
	for (short shipIndex = SHIP_RANGES[1]; shipIndex < SHIP_RANGES[2]; shipIndex++)
	{
		Coord location;
		char direction;

		do {
			srand(time(NULL));
			location.x = rand() % (BOARD_ROWS - 1) + 1;
			location.y = rand() % (BOARD_COLS - 1) + 1;
			int randomDirection = rand() % 2;
			direction = (randomDirection == 0) ? HORIZONTAL_SHIP : VERTICAL_SHIP;
			placeShip(location, direction, shipIndex, player);
		} while (isValidCoordinate(location, direction, shipIndex, player, false));
	}
}