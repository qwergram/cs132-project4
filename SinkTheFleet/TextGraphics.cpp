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

//---------------------------------------------------------------------------------
// Function:	boxTop()
// Title:	Box Top
// Description:
//		draws a a line for the top of the box
// Programmer:	Paul Bladek
// 
// Date:	10/3/2006
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	Formatted line to sout
//
// Called By:	header()
//		endbox()
//
// Parameters:	sout: ostream&;		stream to print to
//		ength: unsigned short;	length of the box
// 
// Returns:	void
//
// History Log:	
//		10/3/2006	PB completed v 1.01
//   
//---------------------------------------------------------------------------------
void boxTop(ostream& sout, unsigned short length)
{
	if (length > MAX_LINE_LENGTH)
		length = MAX_LINE_LENGTH;
	sout.put(UPPERLEFTCHAR);
	for (int i = 0; i < length - OFFSET; i++)
		sout.put(HORIZCHAR);
	sout.put(UPPERRIGHTCHAR);
	sout << endl;
}

//---------------------------------------------------------------------------------
// Function:	boxBottom()
// Title:	Box Bottom
// Description:
//		draws a a line for the bottom of the box
// Programmer:	Paul Bladek
// 
// Date:	10/3/2006
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	Formatted line to sout
//
// Called By:	header()
//		endbox()
//
// Parameters:	sout: ostream&;		stream to print to
//		ength: unsigned short;	length of the box
// 
// Returns:		void
//
// History Log:	
//		10/3/2006 PB completed v 1.01
//   
//---------------------------------------------------------------------------------
void boxBottom(ostream& sout, unsigned short length) {
	if (length > MAX_LINE_LENGTH)
		length = MAX_LINE_LENGTH;
	sout.put(LOWERLEFTCHAR);
	for (int i = 0; i < length - OFFSET; i++)
		sout.put(HORIZCHAR);
	sout.put(LOWERRIGHTCHAR);
	sout << endl;
}

//---------------------------------------------------------------------------------
// Function:	boxLine()
// Title:	Box Line
// Description:
//		draws a a line of text aligned in the middle of the box
// Programmer:	Paul Bladek
// 
// Date:	10/3/2006
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Output:	Formatted text to sout
//
// Called By:	header()
//		endbox()
//
// Parameters:	sout: ostream&;	stream to print to
//		text: const string&; text to print
//		length: unsigned short;	length of the box
//		alignment: unsigned char;   'L' (left), 'C'(center),'R'(right)
//		fillc: char; fill character
// 
// Returns:	void
//
// History Log:	
//		10/3/2006 PB completed v 1.01
//   
//---------------------------------------------------------------------------------
void boxLine(ostream& sout, const string& text, unsigned short length, unsigned char alignment, char fillc) {
	long originalformat = sout.flags(); // saves original format
	alignment = toupper(alignment);
	if (alignment != LEFTCHAR && alignment != RIGHTCHAR && alignment != CENTERCHAR)
		throw exception();
	if (length > MAX_LINE_LENGTH)
		length = MAX_LINE_LENGTH;
	sout << setfill(fillc); // change fill character
	sout.put(VERTCHAR);
	if (alignment == CENTERCHAR)
	{
		sout <<
			setw((length + static_cast<streamsize>(text.length())) / 2 - 1)
			<< text
			<< setw((length - static_cast<streamsize>(text.length())) / 2 - 1)
			<< fillc;
		if (text.length() % 2 == 0)
			sout << fillc;
	}
	else
	{
		if (alignment == LEFTCHAR)
			sout << left;
		sout << setw(length - OFFSET) << text;
	}
	sout.flags(originalformat); //  reset flags
	sout.put(VERTCHAR);
	sout << endl;
}

//---------------------------------------------------------------------------------
// Function:	titleBox()
// Title:	header 
// Description:
//		Prints opening graphic
// Programmer:	Paul Bladek & Norton Pengra
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7 & Windows 10; 
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
void titleBox(ostream& sout, string header, string by)
{
	const string empty;
	boxTop(sout, MAX_LINE_LENGTH);
	boxLine(sout, empty, MAX_LINE_LENGTH);
	boxLine(sout, header, MAX_LINE_LENGTH, 'C');
	boxLine(sout, empty, MAX_LINE_LENGTH);
	boxLine(sout, by, MAX_LINE_LENGTH, 'C');
	boxLine(sout, empty, MAX_LINE_LENGTH);
	boxBottom(sout, MAX_LINE_LENGTH);
}

// print a single ship
void printShip(GridEntities thisShip, bool hideShips)
{
	if (hideShips && (short)thisShip != MISSED && (short)thisShip != HIT) {
		thisShip = NOSHIP;
	}


	cout << ' ' << ASCII_SHIP[(short)thisShip] << VERTCHAR;
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
void printGrid(GridEntities ** playerGrid, bool hideShips)
{
	printGrid(cout, playerGrid, hideShips);
}

void printGrid(ostream& sout, GridEntities ** playerGrid, bool hideShips) {
	clearScreen();
	char rowLetter = 'A';

	for (short columnIndex = 1; columnIndex <= BOARD_COLS; ++columnIndex) {
		sout << setw(3) << columnIndex;
	}
	sout << endl;

	for (int rowIndex = 0; rowIndex < BOARD_ROWS; rowIndex++)
	{
		sout << rowLetter;

		for (int cellIndex = 0; cellIndex < BOARD_COLS; cellIndex++)
			printShip(playerGrid[rowIndex][cellIndex], hideShips); // default grid value is NOSHIP
		sout << endl;

		for (int columnIndex = 0; columnIndex < BOARD_COLS; columnIndex++)
		{
			if (columnIndex == 0)
				// Always one off, requiring to manually write it out
				// cout << setw(3) << cout.fill(HORIZ);
				sout << (char)HORIZCHAR << (char)HORIZCHAR << (char)HORIZCHAR;
			else if (columnIndex == BOARD_COLS - 1)
				sout << (char)CROSSCHAR << (char)HORIZCHAR << (char)HORIZCHAR << (char)CROSSLEFTCHAR;
			else
				sout << (char)CROSSCHAR << HORIZCHAR << HORIZCHAR;
		}
		sout << endl;
		rowLetter++;
	}
}

// congratulate winner
bool congratulateWinner(Player player) {
	string a;
	clearScreen();
	titleBox(cout, player.name + " is the winner!", "Congratulations, " + player.name + "!");
	return safeChoice("Would you like to play again?") == 'Y';
}

// flush the buffer and clear the screen
void clearScreen() {
	cout << flush;
	system("cls");
}

// Welcome the user
void presentWelcome() {
	clearScreen();
	titleBox(cout, "SINK THE FLEET!", "By Norton Pengra & Tabitha Roemish");
}

// a screen for switching players
void pauseScreen(Player player) {
	string a;
	clearScreen();
	titleBox(cout, player.name + " ready?", "Press <enter> when " + player.name + " is ready!");
	getline(cin, a);
	clearScreen();
}