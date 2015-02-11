#ifndef CELL_H_
#define CELL_H_

#include <ostream>

using std::ostream;


enum CellType {GRASS, STONE, ARBITER};
typedef enum CellType CellType;

class Cell
{
	public:
		Cell();
		void setType(CellType c);
		char operator()();
	private:
		CellType type;
};

#endif