#include "SinkTheFleet.h"
#include "CCell.h"

STFGame::CCell::operator string()
{
	stringstream result;
	result << ('A' + this->m_row);
	result << ('0' + this->m_col);
	return result.str;
}

bool STFGame::CCell::inputCoordinates(istream & sin, char size)
{
	bool isValid = true;
	char highChar = static_cast<char>(BOARD_ROWS - 1) + 'A';
	char row = 'A';
	short col = 0;
	cout << "Row must be a letter from A to " << highChar
		<< " and column must be  from 1 to " << BOARD_COLS << ": ";
	if ((row = toupper(sin.get())) < 'A' || row > highChar)
	{
		cout << "Row must be a letter from A to " << highChar
			<< " and column must be  from 1 to " << BOARD_COLS <<
			": ";
		isValid = false;
	}
	else if (col < 1 || col > BOARD_COLS)
	{
		sin >> col;
		if (!sin)
			isValid = false;
	}
	else
		isValid = false;
	this->m_col = col - 1;
	this->m_row = static_cast<short>(row - 'A');
	return isValid;
}

ostream & STFGame::operator<<(ostream & sout, const CCell & cell)
{
	cell.print(sout);
	return sout;
}
