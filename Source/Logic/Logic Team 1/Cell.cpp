#include "Cell.h"

/* Default constructor */
Cell::Cell()
{
	type = G;
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
		case G:
			return 'G';
			break;

		case S:
			return 'S';
			break;

		case A:
			return 'A';
			break;
	}
}