//-----------------------------------------------
// File: CShipInfo.h
// Class: CShipInfo
//-----------------------------------------------
#ifndef CSHIPINFO_H
#define CSHIPINFO_H
#include "CCell.h"
using namespace std;

namespace STFleet
{
	class CShipInfo
	{
		public:
			CShipInfo(CShip name, CDirection orientation, CCell bowlocation, short m_piecesLeft = 17); //Initializes all properties.

			void print(ostream& sout) const; //takes in an ostream reference. Prints out the proprties (e.g., "Frigate, located vertically at B4--2 pieces left")
			
			void print() const; //prints to cout
			
			static const short shipSize[6];
			CShip getName() const;
			CDirection getOrientation() const;
			CCell getBowLocation() const;
			short getPiecesLeft();
			void setName();
			void setOrientation();
			void setBowLocation();
			void setPiecesLeft();
			
			CShipInfo operator--(); //decrements m_piecesLeft and returns the current object.
			
			bool isSunk() { if (m_piecesLeft != 0) return true; }; //returns true if there are no pieces left

		private:
			CShip m_name; //the type of ship
			CDirection m_orienation; //which direction is the ship facing?.
			CCell m_bowLocation; //coordinates of the front of the ship
			short m_piecesLeft; //the number of parts of the ship left unsunk.

	};

	ostream& operator<< (ostream& sout, const CShipInfo & ship); //should just call print and return the ostream.  This does not need to be and should not be a friend.
}
#endif
