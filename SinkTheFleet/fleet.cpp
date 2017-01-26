//----------------------------------------------------------------------------
// File:	fleet.cpp
// 
// Functions: 
//	  setShipInfo()	
//	  allocMem() 
//	  deleteMem()
//	  printShip() 
//	  printGrid() 
//	  initializePlayer() 
//	  setships()	      
//	  saveGrid()
//	  getGrid()
//	  getCoord()
//	  validLocation() 
//	  header() 
//	  endBox() 
//----------------------------------------------------------------------------
#include "fleet.h"
//---------------------------------------------------------------------------------
// YOU ARE RESPONSIBLE FOR CORRECT HEADERS -- one for each function
// include the definitions for each of the non-template functions
//    declared in fleet.h 
//---------------------------------------------------------------------------------

const char* shipNames[SHIP_SIZE_ARRAYSIZE] =
{ "No Ship", "Mine Sweeper", "Submarine", "Frigate",
"Battleship", "Aircraft Carrier" };
const int TOTALPIECES = 17; // total pieces in all ships

							//---------------------------------------------------------------------------------
							// Function:	setShipInfo()
							// Title:		Set ShipInfo
							// Description:
							//		Sets struct ShipInfo fields
							// Programmer:
							// 
							// Date:	12/20/05
							//
							// Version:	0.1
							// 
							// Environment: Intel Xeon PC 
							//                Software:   MS Windows 7 for execution; 
							//                Compiles under Microsoft Visual C++.Net 2013
							//
							// Calls:
							//
							// Called By:initializePlayer()
							//
							// Parameters:	shipInfoPtr: ShipInfo *; pointer to the ShipInfo to be set
							//				name: Ship;	enumerated name of type of ship; default: NOSHIP
							//				orientation: Direction;	enumerated direction; default: HORIZONTAL
							//				row: unsigned short; row-coordinate in grid; default: 0
							//				col: unsigned short; column-coordinate in grid; default: 0
							// 
							// Returns:	void
							//
							// History Log:
							//		12/20/05 PB completed v 0.1
							//		1/24/2017 TR completed for assignment 1 v0.2
							//---------------------------------------------------------------------------------
void setShipInfo(ShipInfo * shipInfoPtr, Ship name, Direction orientation,
	unsigned short row, unsigned short col)
{
	// your code here
	shipInfoPtr->m_name = name;
	shipInfoPtr->m_orientation = orientation;
	shipInfoPtr->m_bowLocation = { row, col }; 
	shipInfoPtr->m_piecesLeft = shipSize[name];
}

//---------------------------------------------------------------------------------
// Function:	allocMem()
// Title:		Allocate Memory
// Description:
//		allocates memory for current grids
// Programmer:	Paul Bladek
// modified by:	
// 
// Date:	9/13/06
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls: deleteMem() // if new fails
//
// Called By:	main()
//
// Parameters:	players: Player[]; 	the array of 2 players in the game
//		size: char;	'	S' or 'L' (small or large)
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 1.0 
//		9/13/06  PB completed v 1.01
//		1/16/2017 NP, TR completed v1.02
//
//---------------------------------------------------------------------------------
void allocMem(Player players[], char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	try
	{
		for (short playerIndex = 0; playerIndex < NUMPLAYERS; ++playerIndex)
		{
			// Setting the gameGride to a nullptr and then to an array (8 or 10) of ships
			players[playerIndex].m_gameGrid[0] = nullptr; 
			players[playerIndex].m_gameGrid[1] = nullptr; 
			players[playerIndex].m_gameGrid[0] = new Ship*[numberOfRows];
			players[playerIndex].m_gameGrid[1] = new Ship*[numberOfRows];
			// iterate over all the rows
			for (short rowIndex = 0; rowIndex < numberOfRows; ++rowIndex)
			{
				//-------------------------------------------------
				players[playerIndex].m_gameGrid[0][rowIndex] = nullptr;
				players[playerIndex].m_gameGrid[1][rowIndex] = nullptr;
				players[playerIndex].m_gameGrid[0][rowIndex] = new Ship[numberOfCols];
				players[playerIndex].m_gameGrid[1][rowIndex] = new Ship[numberOfCols];
				
				//--------------------------------------------------
				
				// iterate over the columns and set them as no ship spots
				for (short columnIndex = 0; columnIndex < numberOfCols; ++columnIndex)
				{
					players[playerIndex].m_gameGrid[0][rowIndex][columnIndex] = NOSHIP;
					players[playerIndex].m_gameGrid[1][rowIndex][columnIndex] = NOSHIP;
				} // end for columns
			} // end for rows
		} // end for player
	}
	catch (bad_alloc e)
	{
		deleteMem(players, size);
		cerr << "exception: " << e.what() << endl;
		cout << "shutting down" << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		exit(EXIT_FAILURE);
	}
}

//---------------------------------------------------------------------------------
// Function:	deleteMem()
// Title:		Delete Memory
// Description:
//		Safely deletes memory for grids
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[]; 	the array of the 2 Players
//		size: char;	'	S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//   
//---------------------------------------------------------------------------------
void deleteMem(Player players[], char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	// your code goes here ...
	// delete[] in reverse order of allocMem()
	// be sure to check if the memory was allocated (!nullptr) BEFORE deleting
	for (short playerIndex = 0; playerIndex < NUMPLAYERS; ++playerIndex)
	{ 
		for (short gameGridIndex = 0; gameGridIndex < 2; ++gameGridIndex)
		{
			if (players[playerIndex].m_gameGrid[gameGridIndex] != nullptr)
			{
				for (short rowIndex = 0; rowIndex < numberOfRows; ++rowIndex)
				{
					if (players[playerIndex].m_gameGrid[gameGridIndex][rowIndex] != nullptr)
						delete[] players[playerIndex].m_gameGrid[gameGridIndex][rowIndex];
					else
						break;
				}
			}
			delete[] players[playerIndex].m_gameGrid[gameGridIndex];
		}
	}

}

//---------------------------------------------------------------------------------
// Function:	printShip()
// Title:	Print Ship 
// Description:
//		Print grid element for the proper ship
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:		three characters representing one ship to sout
//
// Calls:
//
// Called By:	printGrid()
//
// Parameters:	sout: ostream&;	the stream to print to
//				thisShip: Ship;	the Ship to be printed in the grid format
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void printShip(ostream & sout, Ship thisShip)
{
	sout << ' ';
	switch (thisShip)
	{
	case NOSHIP: sout << ' ';
		break;
	case MINESWEEPER: sout << 'M';
		break;
	case SUB: sout << 'S';
		break;
	case FRIGATE: sout << 'F';
		break;
	case BATTLESHIP: sout << 'B';
		break;
	case CARRIER: sout << 'C';
		break;
	case HIT: sout << 'H';
		break;
	case MISSED: sout << MISS;
		break;
	default: sout << 'X';
	}
	sout << VERT;
}

//---------------------------------------------------------------------------------
// Function:	printGrid()
// Title:	Print Ship 
// Description:
//		Print grid element for the proper ship
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	a single grid to sout
//
// Calls:	printShip()
//
// Called By:	main()
//		setships()
//		saveGrid()
//
// Parameters:	sout: ostream&;	the stream to print to
//		grid: Ship**;	the 2-D array of Ships 
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//     
//---------------------------------------------------------------------------------
void printGrid(ostream& sout, Ship** grid, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	system("cls");

	for (short columnIndex = 1; columnIndex <= numberOfCols; ++columnIndex) {
		sout << setw(3) << columnIndex;
	}	
	sout << endl;
	// your code goes here ...
	// use printShip for each element in the grid
	
	char rowLetter = 'A';
	for (int i = 0; i < numberOfRows; i++)
	{
		sout << rowLetter;
		for (int j = 0; j < numberOfCols; j++)
			printShip(sout, grid[i][j]); // default grid value is NOSHIP
		sout << endl;
		//builds graph lines
		for (int columnIndex = 0; columnIndex < numberOfCols; columnIndex++)
		{
			if (columnIndex == 0)
				sout << setw(3) << sout.fill(HORIZ);
			else if (columnIndex == numberOfCols - 1)
				sout << (char)CROSS << setw(2) << sout.fill(HORIZ) << (char)CL;
			else
				sout << (char)CROSS << setw(2) << sout.fill(HORIZ);
		}
		sout << endl;
		rowLetter++;
	}
	// end of additional code
}

//---------------------------------------------------------------------------------
// Function:	initializePlayer()
// Title:	Initialize Player 
// Description:
//		sets initial values for m_ships and m_piecesLeft
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls:
//
// Called By:	main()
//
// Parameters:	playerPtr: Player*;	a pointer to the current Player
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void initializePlayer(Player* playerPtr)
{
	for (short shipIndex = 0; shipIndex < SHIP_SIZE_ARRAYSIZE; shipIndex++)
		setShipInfo(playerPtr->m_ships + shipIndex, static_cast<Ship>(shipIndex));

	playerPtr->m_piecesLeft = TOTALPIECES;
}

//---------------------------------------------------------------------------------
// Function:	setships()
// Title:	Set Ships 
// Description:
//		Allows user to put ships in grid
// Programmer:	Paul Bladek
// modified by:	
// 
// Date:	9/12/06
//
// Version:	0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input:	location and orientation using getCoord from cin
//
// Output:	prompts to cout
//
// Calls:	printGrid()
//		safeChoice()
//		getCoord()
//		saveGrid()
//
// Called By:	main()
//
// Parameters:	players: Player[];	the array of 2 players 
//		size: char;		'S' or 'L'
//		whichPlayer: short;	the player number (0 or 1)
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 0.5
//     
//---------------------------------------------------------------------------------
void setShips(Player players[], char size, short whichPlayer)
{
	char input = 'V';
	char ok = 'Y';
	char save = 'N';
	ostringstream outSStream;
	Cell location = { 0, 0 };
	for (short shipIndex = 1; shipIndex < SHIP_SIZE_ARRAYSIZE; shipIndex++)
	{
		system("cls");
		printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
		outSStream.str("");
		outSStream << "Player " << whichPlayer + 1 << " Enter "
			<< shipNames[shipIndex] << " orientation";
		input = safeChoice(outSStream.str(), 'V', 'H');
		players[whichPlayer].m_ships[shipIndex].m_orientation
			= (input == 'V') ? VERTICAL : HORIZONTAL; 
		cout << "Player " << whichPlayer + 1 << " Enter " << shipNames[shipIndex] <<
			" bow coordinates <row letter><col #> ";
		players[whichPlayer].m_ships[shipIndex].m_bowLocation = getCoord(cin, size);

		// if ok
		if (!validLocation(players[whichPlayer], shipIndex, size))
		{
			cout << "invalid location. Press <enter>";
			cin.get();
			shipIndex--; // redo
			continue;
		}
		// your code goes here ...
	
		// build ship space (Ship** grid, int shipIndex)
		buildShipSpace(players[whichPlayer], shipIndex, 'Y'); // 'Y' for build, 'N' to clear
		
		// clear screen and print ship on grid
		system("cls"); 
		printGrid(cout, players[whichPlayer].m_gameGrid[0], size);

		// ask if ship placement is OK?
		ok = safeChoice("Is this ship placement OK?");
		if (ok == 'N') // if ship placements is not ok, set ship spots to NOSHIP and redo
		{
			buildShipSpace(players[whichPlayer], shipIndex, 'N'); //clear ship
			shipIndex--; //redo
			continue;
		}

	} // end for j
	
	// ask if final grid is OK?
	ok = safeChoice("Is this grid ok?");
	if (ok == 'N') //if grid is not OK, set all grid spots to NOSHIP and reset/ call setShips
	{
		short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
		//clear grid
		for (short rowIndex = 0; rowIndex < numberOfRows; ++rowIndex)
			for (short columnIndex = 0; columnIndex < numberOfCols; ++columnIndex)
				players[whichPlayer].m_gameGrid[0][rowIndex][columnIndex] = NOSHIP;
		//place ships again
		setShips(players, size, whichPlayer);
	}
	
	// save grid?
	save = safeChoice("\nSave starting grid?", 'Y', 'N');
	if (save == 'Y')
		saveGrid(players, whichPlayer, size);
}

//---------------------------------------------------------------------------------
// Function:	saveGrid()
// Title:	Save Grid 
// Description:
//		Saves the ship grid to a file
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	grid to specified file
//
// Calls:	printGrid()
//
// Called By:	setships()
//
// Parameters:	player: sPlayer[];	the array of 2 players
//		whichPlayer: short; the player number (0 or 1) 
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
//	SAVE FILE FORMAT:

	//	<board size>
	//	<minesweeper x><minesweeper y><minesweeper orrientation>\n
	//	<sub x><sub y><sub orrientation>\n
	//	<frigate x><frigate y><frigate orrientation>\n
	//	<battleship x><battleship y><battleship orrientation>\n
	//	<carrier x><carrier y><carrier orrientation>\n
	//
	//	Example: save1.shp
	//	<board size="S"/>
	//	<minesweeper x="A" y="1" o="v"/>
	//	<sub x="D" y="3" o="H"/>
	//	...

//
// History Log:
//		12/20/05 PB completed v 0.1
//     
//---------------------------------------------------------------------------------
void saveGrid(Player players[], short whichPlayer, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	const int NAMESIZE = 50;
	string saveFileName;
	string saveFileContents = "";

	cout << "Please provide a file name for this grid: ";
	getline(cin, saveFileName);

	// Ask if the user wants to use the new or old save format
	bool useNewSaveFormat = safeChoice("Would you like to use a new save format?") == 'Y';
	
	// Check if the user put a .shp themselves
	if (saveFileName.find('.shp') == -1) {
		saveFileName += '.shp';
		if (useNewSaveFormat) {
			// use file extension .shp2
			saveFileName += '2';
		}
		
	}

	ofstream outStream(saveFileName);
	
	outStream << size << endl;
	
	if (useNewSaveFormat) {
		// Use new save format XML style document

		// add boardSize as <board size="S/L"/>
		outStream << "<board size=\"" << size << "\"/>" << endl;
		
		// keep track of which ships we've already written down
		bool ignoreList[SHIP_SIZE_ARRAYSIZE] = { true, false, false, false, false };

		// add ships in the format <shipname x="X" y="#" o="v/h"/>
		for (short rowIndex = 0; rowIndex < numberOfRows; rowIndex++)
		{
			for (short columnIndex = 0; columnIndex < numberOfCols; columnIndex++) {
				short cellValue = (short)players[whichPlayer].m_gameGrid[0][rowIndex][columnIndex];
				// If it's a ship piece and it's not ignored:
				if (cellValue >= (short)MINESWEEPER && cellValue <= (short)CARRIER && ignoreList[cellValue]) {
					// get ship code in string form e.g. "submarine"
					string shipCode = SHIP_NAMES[cellValue];
					char orrientation = 'v';

					// if next row contains ship, orrientation is h else v
					if (
						columnIndex + 1 < numberOfCols &&
						(short)players[whichPlayer].m_gameGrid[0][rowIndex][columnIndex + 1] == cellValue
						) {
						orrientation = 'h';
					}

					// write to file
					outStream << "<" << shipCode << " x=\"" << rowIndex << "\" y=\"" 
							  << columnIndex << "\" o=\"" << orrientation << "\"/>";
					ignoreList[cellValue] = true;
				}
			}
		}
		
	} else {
		printGrid(outStream, players[whichPlayer].m_gameGrid[0], size);
	}




	// Old way:
	// 
	

	outStream.close();
}

//---------------------------------------------------------------------------------
// Function:	getGrid()
// Title:	GetGrid 
// Description:
//		Reads grid from a file and properly sets the ships
// Programmer:	Paul Bladek
// modified by:	
// 
// Date:	9/12/06
//
// Version:	0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input:	grid from specified file
//
// Output:	prompts to cout
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[];	the array of 2 players
//		whichPlayer: short;	the player number  (0 or 1) 
//		size: char;		'S' or 'L'
//		string fileName:	the name of the file to be opened for reading
// 
// Returns: bool -- 	true if the file is opened and read;
//			false otherwise
//
// History Log: 
//		9/12/06 PB comleted v 0.5
//     
//---------------------------------------------------------------------------------
bool getGrid(Player players[], short whichPlayer, char size, string fileName)
{
	string line;
	ifstream ifs;
	Ship ship = NOSHIP;
	short shipCount[SHIP_SIZE_ARRAYSIZE] = { 0 };
	char cell = ' ';
	char fsize = 'S';
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	try
	{
		ifs.open(fileName.c_str());
		if (!ifs)
		{
			cout << "could not open file " << fileName << endl
				<< " press <enter> to continue" << endl;
			cin.ignore(BUFFER_SIZE, '\n');
			return false;
		}
	}
	catch (exception e)
	{
		cout << "could not open file " << fileName << endl
			<< " press <enter> to continue" << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		return false;
	}
	// your code goes here ...
	   


	return true;
}

//---------------------------------------------------------------------------------
// Function:	getCoord()
// Title:	Get Coordinates 
// Description:
//		Returns a cell with coordinates set by user
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input:	cell coordinates (in the form "A13" from sin
//
// Output:	prompts to cout
//
// Calls:	none
//
// Called By:	main()
//		setships()
//
// Parameters:	sin: istream&;	the stream to read from
//		size: char;	'S' or 'L'
// 
// Returns:	Cell location -- a cell containing the input coordinates
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
Cell getCoord(istream& sin, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	char highChar = static_cast<char>(numberOfRows - 1) + 'A';
	char row = 'A';
	short col = 0;
	Cell location = { 0, 0 };
	do
	{
		col = 0;
		cout << "\nRow must be a letter from A to " << highChar
			<< " and column must be  from 1 to " << numberOfCols << ": ";
		while ((row = toupper(sin.get())) < 'A' || row  > highChar)
		{
			sin.ignore(BUFFER_SIZE, '\n');
			cout << "\nRow must be a letter from A to " << highChar
				<< " and column must be  from 1 to " << numberOfCols << ": ";
		}
		sin >> col;
		if (!sin)
			sin.clear();
		sin.ignore(BUFFER_SIZE, '\n');
	} while (col < 1 || col > numberOfCols);

	location.m_col = col - 1;
	location.m_row = static_cast<short>(row - 'A');
	return location;
}

//---------------------------------------------------------------------------------
// Function:	validLocation()
// Title:	Valid Location 
// Description:
//		Can the ship legitimately go there?
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Calls:
//
// Called By:
//
// Parameters:	player: const Player&;	a reference to the specific Player
//		shipNumber: short;	the number of the ship (1 - 5)
//					in the array player.m_ships[]
//		size: char;		'S' or 'L'
// 
// Returns: bool -- 	true if the ship would not go off the edge
//				or cross another ship;
//			false otherwise
//
// History Log:
//		12/20/05 PB completed v 0.1
//     
//---------------------------------------------------------------------------------
bool validLocation(const Player& player, short shipNumber, char size) 
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	// your code goes here ...
	int row = player.m_ships[shipNumber].m_bowLocation.m_row;
	int col = player.m_ships[shipNumber].m_bowLocation.m_col;
	
	if (player.m_ships[shipNumber].m_orientation == VERTICAL)
	{	// check size
		if (row + shipSize[shipNumber] > numberOfRows)
			return false;
		// check overlap
		for (int shipSizeIndex = 0; shipSizeIndex < shipSize[shipNumber]; shipSizeIndex++)
		{
			if (player.m_gameGrid[0][row + shipSizeIndex][col] != NOSHIP)
				return false;
		}
	}
	else //Horizontal
	{
		// check size
		if (col + shipSize[shipNumber] > numberOfCols)
			return false;
		// check overlap
		for (int shipSizeIndex = 0; shipSizeIndex < shipSize[shipNumber]; shipSizeIndex++)
		{
			if (player.m_gameGrid[0][row][col + shipSizeIndex] != NOSHIP)
				return false;
		}
	}
	// replace the return value
	return true;
}

//---------------------------------------------------------------------------------
// Function:	header()
// Title:	header 
// Description:
//		Prints opening graphic
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	
//
// Calls:	boxTop()
//		boxLine()
//		boxBottom()
//
// Called By:	main()
//
// Parameters:	sout: ostream&;	the stream to print to
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void header(ostream& sout)
{
	const string empty;
	const string sink("SINK THE FLEET!");
	// your name goes here!
	const string by("By Norton Pengra & Tabitha Roemish");
	boxTop(sout, BOXWIDTH);
	boxLine(sout, empty, BOXWIDTH);
	boxLine(sout, sink, BOXWIDTH, 'C');
	boxLine(sout, empty, BOXWIDTH);
	boxLine(sout, by, BOXWIDTH, 'C');
	boxLine(sout, empty, BOXWIDTH);
	boxBottom(sout, BOXWIDTH);
}

//---------------------------------------------------------------------------------
// Function:	endBox()
// Title:	End Box 
// Description:
//		prints closinging graphic
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	
//
// Calls:	boxTop()
//		boxLine()
//		boxBottom()
//
// Called By:	main()
//
// Parameters:	player: short; the number of the winner (0 or 1)
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void endBox(short player)
{
	const string empty;
	ostringstream msg;
	msg << "Congratulations player " << player + 1 << "!";
	boxTop(cout, BOXWIDTH);
	boxLine(cout, empty, BOXWIDTH);
	boxLine(cout, msg.str(), BOXWIDTH, 'C');
	boxLine(cout, empty, BOXWIDTH);
	boxBottom(cout, BOXWIDTH);
}

//---------------------------------------------------------------------------------
// Function:	buildShipSpace()
// Title:	Build Ship Space
// Description:
//		
// Programmer:	Tabitha Roemish
// 
// Date:	1/26/2017
//
// Version:	1.0
// 
// Environment: Hardware: E5 
//              Software: OS: Windows 10; 
//              Compiles under Microsoft Visual C++ 2015
//
// Output:	
//
// Calls:	
//		
// Called By:	setShips()
//
// Parameters:	const Player&;	a reference to the specific Player
//				shipIndex: short;	the number of the ship (1 - 5)
//				response: char - build or remove
// Returns:	
//
// History Log: 
//			1/26/2017 TR completed v1
//---------------------------------------------------------------------------------
void buildShipSpace(const Player& player, short shipIndex, char response)
{
	int row = player.m_ships[shipIndex].m_bowLocation.m_row;
	int col = player.m_ships[shipIndex].m_bowLocation.m_col;

	Ship shipName = (response == 'Y') ? player.m_ships[shipIndex].m_name : NOSHIP;
	if (player.m_ships[shipIndex].m_orientation == VERTICAL)
	{
		for (int shipSizeIndex = 0; shipSizeIndex < shipSize[shipIndex]; shipSizeIndex++)
			player.m_gameGrid[0][row + shipSizeIndex][col] = shipName;
	}
	else // if horizontal
	{
		for (int shipSizeIndex = 0; shipSizeIndex < shipSize[shipIndex]; shipSizeIndex++)
			player.m_gameGrid[0][row][col + shipSizeIndex] = shipName;
	}
}

//-----------------------------------------------------------------------
//auto grid 
// 
void autoGrid(Player players[], char size, short whichPlayer)
{
	Cell location = { 0, 0 };
	Direction direction = VERTICAL;
	
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	for (short shipIndex = 1; shipIndex < SHIP_SIZE_ARRAYSIZE; shipIndex++)
	{
		srand(time(NULL));
		location.m_row = rand() % (numberOfRows-1) + 1;
		location.m_col = rand() % (numberOfCols-1) + 1; 
		int randomDirection = rand() % 2;
		direction = (randomDirection == 0) ? HORIZONTAL: VERTICAL;

		players[whichPlayer].m_ships[shipIndex].m_bowLocation = location;
		players[whichPlayer].m_ships[shipIndex].m_orientation = direction;

		if (!validLocation(players[whichPlayer], shipIndex, size))
		{
			shipIndex--;
			continue;
		}
		buildShipSpace(players[whichPlayer], shipIndex, 'Y');
	}
}