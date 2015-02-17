#ifndef MAP_H_
#define MAP_H_

#include "Cell.h"

/* 
*	Map base class
*   
*/
class Map
{
	public:
		Map();
		void setCell(int x, int y);
		Cell getCell(int x, int y);
	
	private:
		Cell cells_[][10]; // temp value to remove compilation error for now
};

#endif /* MAP_H_ */
