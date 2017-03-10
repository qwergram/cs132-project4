//-----------------------------------------------
// File: CDirection.h
// Class: CDirection
//-----------------------------------------------
#ifndef CDIRECTION_H
#define CDIRECTION_H
#include "CShip.h"
using namespace std;

namespace STFleet
{
	//----------------------------------------------------------------------------
	// enumerated type for direction on grid
	//----------------------------------------------------------------------------
	enum Direction
	{
		HORIZONTAL, // 0
		VERTICAL	// 1
	};

	class CDirection //A wrapper class for enum Direction
	{
	public:
		CDirection(Direction direction); //nitializes m_direction.
		operator Direction() const; //returns m_direction
		void print(ostream& sout) const; // takes in an ostream reference. Prints out in the same format as in  project 1 (e.g. "H" or "V")
		void print() const; //with no parameter. Prints to cout
	private:
		Direction m_direction;

	};

	ostream& operator<< (ostream& sout, const CDirection & ship); // should just call print and return the ostream. 
	istream& operator >> (istream& sin, CDirection & ship); //should input either a name or a number and return the istream.
}




#endif
