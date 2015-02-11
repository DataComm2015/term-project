#include "Cell.h"

/* Default constructor */
Cell::Cell()
{
	type = GRASS;
}


/* Sets the type of the cell */
void Cell::setType(CellType c)
{
	type = c;
}


/* Prints the cell's type to the screen */
char Cell::operator()()
{
	switch(type)
	{
		case GRASS:
			return 'G';
			break;

		case STONE:
			return 'S';
			break;

		case ARBITER:
			return 'A';
			break;
	}
}