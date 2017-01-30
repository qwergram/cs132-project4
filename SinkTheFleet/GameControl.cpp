//----------------------------------------------------------------------------
// File:	GameControl.cpp
// 
// Functions: 
//		isAlive()	
//		manuallyPopulate()
//		removeShip()
//		placeShip()
//		deletePlayer()
//		initPlayer()
//		allocMemory()
//		getPlayerName()
//		setBoardSize()
//		launchMissile()
//		populateGrid()
//		
//		
//----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "SinkTheFleet.h"

using namespace std;


//---------------------------------------------------------------------------------
// Function: 	bool isAlive(Player player)
//
// Title:	isAlive
//
// Description: checks if the current player has any more fleet left
//   
// Programmer:	Norton Pengra
// 
// Date:	1/27/2017
//
// Version: 	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	None
//
// Output:	none
//
// Calls: 	none
//
// Called By: main()
//		
// Parameters:	player: Player struct
//		
// Returns:	bool
//
// History Log:
//		1/31/2017 NP & TR v1 completed
// ------------------------------------------------------------------------------

bool isAlive(Player player) {
	int playerHealth = 0;
	for (short shipIndex = 0; shipIndex < GRID_ENTITIES_COUNT; shipIndex++) {
		playerHealth += player.playerHealth[shipIndex];
	}
	return playerHealth > 0;
}
//---------------------------------------------------------------------------------
// Function: 	void manuallyPopulate(Player player)
//
// Title:	Manually Populate
//
// Description: Provides prompts to enter ships manually and populates grid with ships
//   
// Programmer:	Norton Pengra & Tabitha Roemish
// 
// Date:	1/27/2017
//
// Version: 	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	orientation (H, V), coordinates(Row Col, ex. A1), shipOkay (Y, N) 
//
// Output:	Prints grid
//
// Calls: 	clearScreen()
//			getValidCoordinate()
//
// Called By: PopulateGrid()
//
// Parameters:	player: Player struct
//		
// Returns:	none
//
// History Log:
//		1/31/2017 NP & TR v1 completed
// ------------------------------------------------------------------------------

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
//---------------------------------------------------------------------------------
// Function: 	void removeShip(Coord coordinates, char orrientation, short shipId, Player player)
//
// Title:	Remove Ship
//
// Description: 
// remove the ship on this grid
//   
// Programmer:	Norton Pengra & Tabitha Roemish
// 
// Date:	1/27/2017
//
// Version: 	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	none
//
// Output:	none
//
// Calls: 	placeShip()
//
// Called By: manuallyPopulate()
//
// Parameters:	coordinates: Coord struct
//				orrientation: Char (V or H) 
//				shipId: short (index of ship)
//				player: Player struct
// Returns:	none
//
// History Log:
//		1/31/2017 NP & TR v1 completed
// ------------------------------------------------------------------------------

void removeShip(Coord coordinates, char orrientation, short shipId, Player player) {
	placeShip(coordinates, orrientation, NOSHIP, player, player.playerHealth[shipId]);
}
//---------------------------------------------------------------------------------
// Function: 	void placeShip(Coord coordinates, char orrientation, short shipId, Player player, short size)
//
// Title:	Place Ship
//
// Description:  place the ship on board at location specified
//		
//   
// Programmer:	Norton Pengra & Tabitha Roemish
// 
// Date:	1/27/2017
//
// Version: 	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	none
//
// Output:	none
//
// Calls: 	none
//
// Called By:	manuallyPopulate()
//				removeShip()
//	
// Parameters:	coordinates: Coord struct
//				orrientation: char (V or H)
//				shipId: short (ship index)
//				player: Player struct
//				size: short (size of ship)
// Returns:	none
//
// History Log:
//		1/27/2017 NP & TR v1 completed
// ------------------------------------------------------------------------------

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

//---------------------------------------------------------------------------------
// Function: 	void deletePlayer(Player player)
//
// Title:	Delete Player
//
// Description: deallocate memory for each player
// 
// Programmer:	Norton Pengra & Tabitha Roemish
// 
// Date:	1/27/2017
//
// Version: 	1.1
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	none
//
// Output:	none
//
// Calls: 	none
//
// Called By: main()
//		
// Parameters:	player: Player struct
//		
// Returns:	none
//
// History Log:
//		1/31/2017 NP & TR v1.1 completed
// ------------------------------------------------------------------------------

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
//---------------------------------------------------------------------------------
// Function: 	Player initPlayer(short playerId)
//
// Title:	Init Player
//
// Description: allocate memory for the player's boards and set player names
//		
// Programmer:	Norton Pengra & Tabitha Roemish
// 
// Date:	1/27/2017
//
// Version: 	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	none
//
// Output:	none
//
// Calls: 	allocMemory()
//			getPlayerName()
//
// Called By:	main()
//		
// Parameters:	playerID: short (1st or 2nd player)
// 
// Returns:	Player struct
//
// History Log:
//		1/31/2017 NP & TR v1 completed
// ------------------------------------------------------------------------------

Player initPlayer(short playerId) {
	Player newPlayer;
	newPlayer.name = getPlayerName(playerId);
	// allocate the memory first
	newPlayer.gameGrid = allocMemory();
	return newPlayer;
}
//---------------------------------------------------------------------------------
// Function: 	GridEntities ** allocMemory()
//
// Title:	Alloc Memory
//
// Description: Allocates memory for one player
//		
//   
// Programmer:	Paul Bladek & Norton Pengra & Tabitha Roemish
// 
// Date:		1/31/2017
//
// Version: 	1.03
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	none
//
// Output:	none
//
// Calls: 	none
//
// Called By:	initPlayer()
//		
// Parameters:	none
//		
// Returns:	GridEntities
//
// History Log:
//		12/20/05 PB completed v 1.0 
//		9/13/06  PB completed v 1.01
//		1/16/2017 NP, TR completed v1.02
//		1/31/2017 NP & TR v1 completed v1.03
// ------------------------------------------------------------------------------

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
//---------------------------------------------------------------------------------
// Function: 	string getPlayerName(short playerId)
//
// Title:	Get Player Name
//
// Description: prompts and inputs player name
//		
// Programmer:	Norton Pengra
// 
// Date:	1/27/2017
//
// Version: 	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	name from cin
//
// Output:	name prompt
//
// Calls: 	none
//
// Called By: initPlayer()
//		
// Parameters:	playerID: short (player 1 or 2)
//		
// Returns:	string
//
// History Log:
//		1/31/2017 NP v1 completed
// ------------------------------------------------------------------------------
string getPlayerName(short playerId) {
	string playerName;
	cout << "What is player #" << playerId << "'s name?" << endl << "Name: ";
	getline(cin, playerName);
	return playerName;
}
//---------------------------------------------------------------------------------
// Function: 	setBoardSize()
//
// Title:	Set Board Size
//
// Description: ask what the board the user would like to use and set global params
//		
//   
// Programmer:	Paul Bladek & Norton Pengra
// 
// Date:	1/27/2017
//
// Version: 	1.1
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	board size (S or L)
//
// Output:	prompt for board size
//
// Calls: 	safeChoice()
//
// Called By: main()
//		
//
// Parameters:	none
//			
// Returns:	none
//
// History Log:
//		12/20/05 PB  completed SinkTheFleet main() with board size 
//		1/31/2017 NP completed v1.1
// ------------------------------------------------------------------------------

void setBoardSize() {
	char userChoice = safeChoice("Which size grid would you like to use", 'S', 'L');
	BOARD_ROWS = (userChoice == 'S') ? BOARD_ROWS_SMALL : BOARD_ROWS_LARGE;
	BOARD_COLS = (userChoice == 'S') ? BOARD_COLS_SMALL : BOARD_COLS_LARGE;
}
//---------------------------------------------------------------------------------
// Function: 	bool launchMissile(Player attacker, Player * defender)
//
// Title:	Launch Missile
//
// Description:  asks for coordinate
// and launches a missile onto a ship returns true if hit and false if miss
//   
// Programmer:	Norton Pengra & Tabitha Roemish
// 
// Date:	1/27/2017
//
// Version: 	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	coordinates (ex. A1)
//
// Output:	prompts for coordinates
// outputs message if coordinate is already guessed
//
// Calls: 	getValidCoordinate()
//
// Called By: main()
//		
// Parameters:	attacker: Player Struct
//				defender: pointer to Player struct
// Returns:	bool
//
// History Log:
//		1/31/2017 NP & TR v1.0 completed
// ------------------------------------------------------------------------------

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
//---------------------------------------------------------------------------------
// Function: 	populateGrid(Player player)
//
// Title:	Populate Grid
//
// Description: ask if the user has a file they'd like to load or manually populate
//   
// Programmer:	Norton Pengra & Tabitha Roemish
// 
// Date:	1/27/2017
//
// Version: 	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	Y or N from safeChoice prompt
//
// Output:	cout upload error if file does not load
//
// Calls: 	clearScreen()
//			loadFile()
//			manuallyPopulate()
//			safeChoice()
//			saveMenu()
//
// Called By: main()
//	
// Parameters:	player: Player Struct
// 
// Returns:	void
//
// History Log:
//		1/31/2017 NP & TR completed v1.0
// ------------------------------------------------------------------------------

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
//---------------------------------------------------------------------------------
// Function: 	loadFile(Player player)
//
// Title:	Load File
//
// Description: 
//		
//   
// Programmer:	Norton Pengra
// 
// Date:	1/27/2017
//
// Version: 	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	
//
// Output:	
//
// Calls: 	
//
// Called By:
//		
//
//
// Parameters:	player: Player Struct
// 
// Returns:	bool - return false if file is not loaded or user selects N
//
// History Log:
//		
// ------------------------------------------------------------------------------

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
//---------------------------------------------------------------------------------
// Function: 	
//
// Title:	
//
// Description: 
//		
//   
// Programmer:	Norton Pengra
// 
// Date:	1/27/2017
//
// Version: 	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	
//
// Output:	
//
// Calls: 	
//
// Called By:
//		
//
//
// Parameters:	
//		
//		
// 
// Returns:	
//
// History Log:
//		
// ------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------
// Function: 	
//
// Title:	
//
// Description: 
//		
//   
// Programmer:	Norton Pengra
// 
// Date:	1/27/2017
//
// Version: 	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	
//
// Output:	
//
// Calls: 	
//
// Called By:
//		
//
//
// Parameters:	
//		
//		
// 
// Returns:	
//
// History Log:
//		
// ------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------
// Function: 	int indexOf(const char * charArray, char toFind)
//
// Title:	Index Of Integer in Array
//
// Description: find the Index of the array
//		
//   
// Programmer:	Norton Pengra
// 
// Date:	1/27/2017
//
// Version: 	1.0
// 
// Environment: Hardware: i7 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:	none
//
// Output:	none
//
// Calls: 	none
//
// Called By:
//		
//
//
// Parameters:	
//		
//		
// 
// Returns:	
//
// History Log:
//		
// ------------------------------------------------------------------------------

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
