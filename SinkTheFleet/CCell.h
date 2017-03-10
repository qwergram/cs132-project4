#pragma once
#include "CCell.h"
#include "SinkTheFleet.h"


namespace STFGame {

	
	/* Original Data Structure
	struct Coord {
		short x;
		short y;
	};
	//*/

	class CCell {
	public:
		CCell(unsigned short row = 0, unsigned short col = 0) : m_row(row), m_col(col) {}
		CCell(char row, unsigned short col) : m_row(row - (int)'A'), m_col(col - (int)'0') {}

		// accessors/mutators
		unsigned short getRow() { return this->m_row; }
		unsigned short getCol() { return this->m_col; }
		
		// syntatic synonyms
		int y() { return this->m_row; }
		int x() { return this->m_col; }

		// cast overloads
		operator std::string();

		// Required but unused specs
		void print(std::ostream & sout) const { sout << this->operator std::string; }
		void print() const { this->print(std::cout); }
		bool inputCoordinates(std::istream & sin, char size);
	private:
		unsigned short m_row;
		unsigned short m_col;
	};

	// should just call print and return the ostream.  This does not need to be and should not be a friend.
	std::ostream & operator << (std::ostream & sout, const CCell & cell);
}