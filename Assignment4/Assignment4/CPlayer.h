//-----------------------------------------------
// File: CPlayer.h
// Class: CPlayer
//-----------------------------------------------
#ifndef CPLAYER_H
#define CPLAYER_H
#include "CShipInfo.h"

using namespace std;

namespace STFleet
{
	class CPlayer
	{
	public:
		CPlayer(unsigned short whichPlayer, char size); //can take in an unsigned short whichPlayer and a char  gridsize.Validates and sets m_gridSize.sets m_whichPlayer, sets both gamegrids to NULL, calls allocateMemory(), and intializes the ships in m_ships.
		
		CPlayer(const CPlayer & player); //for deep-copy
		
		~CPlayer(); //calls deleteMemory to clean up all memory leaks
		
		CPlayer operator=(const CPlayer & player); //for deep-copy assignnment
		unsigned short getWhichPlayer() const;
		short getPiecesLeft() const;
		char getGridSize() const;
		
		Ship getCell(short whichGrid, CCell cell) const; // takes in short whichGrid and CCell cell. Returns the Ship in the indicated cell.
		
		void setGridSize(char size); //takes in a char  'L' or 'S'  (large or small)
		
		void setCell(short whichGrid, CCell cell, CShip ship); // takes in short whichGrid, CCell cell, and CShip ship. Set the proper cell to ship.
		
		void printGrid(ostream& sout, short whichGrid); //takes in an ostream reference and short whichGrid . Prints out the appropriate grid.
		
		void getGrid(string fileName); //takes in string filename. inputs a grid from a file.	
		
		void saveGrid(string fileName); //inputs and validates filename and prints the gridSize,  m_ships and grid[0] to the file.  Same as in   project 1

		void setShips(); //lets the player set up the grid

		void autoSetShips(); //extra credit
		
		void hitShip(CShip ship); //takes in a CShip ship. Decrements the pieces left for the ship and the fleet.

		bool isValidLocation(short whichShip); //takes in a short whichShip (the index number of which ship in the array). Returns true if the bow location is valid --i.e., will not put the ship out - of - bounds or across another ship.

		CShipInfo operator[] (short index) const; //takes in a short index. Validates index and returns m_ships[index]
		
		CPlayer operator--(); //decrements m_piecesLeft and returns the current object.


	private:
		unsigned short  m_whichPlayer;
		short  m_piecesLeft; //the number of parts of the fleet left unsunk
		CShipInfo m_ships[6]; //an array of the ships in the fleet (ignore 0) 
		char  m_gridSize; //an 'L' or 'S'  (large or small)
		CShip**  m_gameGrid[2]; //an array of two 2-dimensional grids.  Same as in   project 1
		void allocateMemory(); //allocates and initializes the game grids.
		void deleteMemory(); //clean-up

	};

	
}
#endif
