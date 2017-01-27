#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

// Board size possibilities
const short BOARD_ROWS_SMALL = 8;
const short BOARD_ROWS_LARGE = 10;
const short BOARD_COLS_SMALL = 12;
const short BOARD_COLS_LARGE = 24;

const unsigned BUFFER_SIZE = 256;

// char definitions
const unsigned char UPPERLEFTCHAR = 0xda;			// upper left
const unsigned char UPPERRIGHTCHAR = 0xbf;			// upper right
const unsigned char LOWERLEFTCHAR = 0xc0;			// lower left
const unsigned char LOWERRIGHTCHAR = 0xd9;			// lower right
const unsigned char HORIZCHAR = 0xc4;				// horizontal bar
const unsigned char CROSSRIGHTCHAR = 0xc3;			// cross to the right
const unsigned char CROSSLEFTCHAR = 0xb4;			// cross to the left
const unsigned char CROSSUPCHAR = 0xc1;				// cross up 
const unsigned char CROSSDOWNCHAR = 0xc2;			// cross down
const unsigned char VERTCHAR = 0xb3;				// vertical bar
const unsigned char CROSSCHAR = 0xc5;				// crosses
const unsigned char MISSCHAR = 0xb0;				// screen pattern

const unsigned char LEFTCHAR = 'L';					// left alignment
const unsigned char RIGHTCHAR = 'R';				// right alignment
const unsigned char CENTERCHAR = 'C';				// center alignment


const short MAX_LINE_LENGTH = 79;					// longest line allowed
const int OFFSET = 2;								// number of start & end chars

													// Total ships each player has
const short GRID_ENTITIES_COUNT = 8;

// Range of enums that are actually ships
const short SHIP_RANGES[2] = { 1, 6 };

enum GridEntities // Ships on the battlefield
{
	NOSHIP,		  // 0
	MINESWEEPER,  // 1
	SUB,		  // 2
	FRIGATE,	  // 3
	BATTLESHIP,	  // 4
	CARRIER,	  // 5
	HIT,		  // 6 
	MISSED,		  // 7
};

// syntatic sugars for ship orrientation
const char VERTICAL_SHIP = 'V';
const char HORIZONTAL_SHIP = 'H';

// How to display the ships on the board
const char ASCII_SHIP[GRID_ENTITIES_COUNT] = {
	' ', 'M', 'S', 'F', 'B', 'C', 'X', MISSCHAR
};

// letter to int converter
const char LETTER_TO_INT[BOARD_ROWS_LARGE] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'
};

// string equivs of ships
const string SHIPS[GRID_ENTITIES_COUNT] = {
	"noship",
	"Minesweeper",
	"Submarine",
	"Frigate",
	"Battleship",
	"Carrier",
	"hit",
	"miss"
};


// number of hits required to win game (sum of SHIP_HEALTH)
const short PLAYER_HEALTH = 17;

// A Player Struct
struct Player {
	GridEntities ** gameGrid;		 										// This player's grid w/ oponent's hits on it
	short playerHealth[GRID_ENTITIES_COUNT] = { 0, 2, 3, 3, 4, 5, 0, 0 };   // Player's remaning health of each ship
	string name;														    // This player's name
};


// Board size
extern short BOARD_ROWS;
extern short BOARD_COLS;

// Players
extern Player PLAYER1;
extern Player PLAYER2;


// Coodinate Struct
struct Coord {
	short x;
	short y;
};

// utilities
int indexOf(const char * charArray, char toFind);

// Functions
void main();
void presentWelcome();
void setBoardSize();
string getPlayerName(short playerId);
GridEntities ** allocMemory();
bool loadFile(Player player);
void manuallyPopulate(Player player);

// building and deleting players
Player initPlayer(short playerId);
void deletePlayer(Player player);

// Grid population related functions
void populateGrid(Player player);
void placeShip(Coord coordinates, char orrientation, short shipId, Player player, short size = -1);
void removeShip(Coord coordinates, char orrientation, short shipId, Player player);

// save file operations
void saveMenu(Player player);
void generateSave(string filePath, Player player);

// safely handle user input/output functions
char safeChoice(string prompt, char choice1 = 'Y', char choice2 = 'N');
Coord getValidCoordinate(char shipOrrientation, short shipSize, Player player, bool noclip = false);
bool isValidCoordinate(Coord userCoordinate, char shipOrrientation, short shipSize, Player player, bool noclip);

// user/game logic
bool launchMissile(Player attacker, Player * defender);
bool isAlive(Player player);
bool emptyWaters(Coord coords, Coord offsets, char orrientation, short shipSize, Player player);

// clear screen
void clearScreen();

// pause screen for switching players
void pauseScreen(Player player);
bool congratulateWinner(Player player);

// prints the top line of a box					
void boxTop(ostream& sout, unsigned short length);
// prints the bottom line of a box
void boxBottom(ostream& sout, unsigned short length);
// prints text line of a box
void boxLine(ostream& sout, const string& text, unsigned short length, unsigned char alignment = LEFTCHAR, char fillc = ' ');
// Create a pretty box w/ title
void titleBox(ostream& sout, string header, string by);
// printing ships and grids to the screen
void printGrid(GridEntities ** playerGrid, bool hideShips = false);
void printGrid(ostream& sout, GridEntities ** playerGrid, bool hideShips = false);
void printShip(GridEntities thisShip, bool hideShips);

void randomGrid(Player player);
