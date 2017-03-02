//-----------------------------------------------
// File: CShip.h
// Class: CShip
//-----------------------------------------------
#ifndef CSHIP_H
#define CSHIP_H
#define private public

#include <iostream>
using namespace std;

namespace STFleet
{
	//----------------------------------------------------------------------------
	// enumerated type for ships
	//----------------------------------------------------------------------------
	enum Ship
	{
		NOSHIP,		 // 0
		MINESWEEPER, // 1 (1-5) -- used only for owner
		SUB,		 // 2
		FRIGATE,	 // 3
		BATTLESHIP,	 // 4
		CARRIER,	 // 5
		HIT,		 // 6 (6-7)-- used only for other side
		MISSED,		 // 7 
	};

	class CShip //A wrapper class for enum Ship
	{
	public:
		CShip(Ship ship) : m_ship(NOSHIP) {}; //Initializes m_ship.
		operator Ship() const; //returns m_ship
		void print(ostream& sout) const; //takes in an ostream reference. Prints out in the same format as in  project 1’s printship()
		void print() const { print(cout); }; //with no parameter. Prints to cout
		void printName(Ship ship) const; //takes in an ostream reference. Prints out the string equivalent of the ship (e.g., "Frigate")
	private:
		Ship m_ship;
	};


	ostream& operator<< (ostream& sout, const CShip & ship); //should just call print and return the ostream.
	istream& operator >> (istream& sin, CShip & ship); //should input either a name or a number and return the istream












}





















#endif
