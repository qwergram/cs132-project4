#include "CCell.h"
#include "textGraphics.h"
#include "CShip.h"

STFleet::CCell::~CCell()
{
}

void STFleet::CCell::print(ostream & sout) const
{
	cout << static_cast<char>(m_row - 1) + 'A' << m_col + 1;
}

void STFleet::CCell::print() const
{
	print(cout);
}

bool STFleet::CCell::inputCoordinates(istream & sin, char size) const
{
	return false;
}

ostream & STFleet::operator<<(ostream & sout, const CCell & ship)
{
	// TODO: insert return statement here
}
