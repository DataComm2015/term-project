#ifndef MAP_H_
#define MAP_H_

#include "Cell.h"

namespace Marx
{
	/* 
	*	Map base class
	*   
	*/
	class Map
	{
		public:
			Map();
			void setCell(const int& x, const int& y, const Cell& cell);
			Cell getCell(const int& x, const int& y);
		
		private:
			Cell cells_[][10];	// temp value to remove compilation error for now
								// can be changed to a different container
	};
} /* namespace Marx */

#endif /* MAP_H_ */
