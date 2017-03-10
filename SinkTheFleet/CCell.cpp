#include "SinkTheFleet.h"
#include "CCell.h"

STFGame::CCell::operator string()
{
	stringstream result;
	result << ('A' + this->m_row);
	result << ('0' + this->m_col);
	return result.str;
}

bool STFGame::CCell::inputCoordinates(istream & sin, char size) const
{
	bool isValid = true;
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	char highChar = static_cast<char>(numberOfRows - 1) + 'A';
	char row = 'A';
	short col = 0;
	CCell location = { 0, 0 };
	col = 0;
	cout << "Row must be a letter from A to " << highChar
		<< " and column must be  from 1 to " << numberOfCols << ": ";
	if ((row = toupper(sin.get())) < 'A' || row > highChar)
	{
		cout << "Row must be a letter from A to " << highChar
			<< " and column must be  from 1 to " << numberOfCols <<
			": ";
		isValid = false;
	}
	else if (col < 1 || col > numberOfCols)
	{
		sin >> col;
		if (!sin)
			isValid = false;
	}
	else
		isValid = false;
	location.m_col = col - 1;
	location.m_row = static_cast<short>(row - 'A');
	return isValid;
}

ostream & STFGame::operator<<(ostream & sout, const CCell & cell)
{
	cell.print(sout);
	return sout;
}
