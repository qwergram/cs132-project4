//-----------------------------------------------
// File: CSinkTheFleet.h
// Class: CSinkTheFleet
//-----------------------------------------------
#ifndef CSINKTHEFLEET_H
#define CSINKTHEFLEET_H
#include "CPlayer.h"


using namespace std;

namespace STFleet
{
	class CSinkTheFleet
	{
	public:
	
		
		CSinkTheFleet(char size); //Has char parameter for gridSize. Initializes m_gridSize and the two players.
	 
		unsigned short play(); //plays the game, the same as in  project 1.  Returns the index of the winning player.
		
		CPlayer operator[] (short index); //takes in a short index. Validates index and returns m_players[index]
	
		CPlayer operator[] (short index) const; //takes in a short index. Validates index and returns m_players[index]

		static void header(); //same as in  project 1
		static void endbox(); //same as in  project 1

	private:
		CPlayer m_players[2]; //the two players 
		char m_gridSize; //an 'L' or 'S' (large or small)
	};
}
#endif