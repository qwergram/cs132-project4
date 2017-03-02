//-----------------------------------------------
// File: CCell.h
// Class: CCell
//-----------------------------------------------
#ifndef CCELL_H
#define CCELL_H
#include "CDirection.h"
using namespace std;

namespace STFleet
{
	class CCell
	{
	public:
		CCell(unsigned short row, unsigned short col); //Initializes m_row and m_col.
		unsigned short getRow() const;
		unsigned short getCol() const;
		void print(ostream& sout) const; //takes in an ostream reference. Prints out in the same format as in  project 1 (e.g. "A3" or "D12")
		void print() const; // with no parameter.Prints to cout
		bool inputCoordinates(istream& sin, char size) const; //takes in an istream reference and a char ('S' or 'L'). Inputs and validates the coordinates.

	private:
		unsigned short  m_row;
		unsigned short  m_col;

	};
	ostream& operator<< (ostream& sout, const CCell & ship); //should just call print and return the ostream.  This does not need to be and should not be a friend.
}
#endif
