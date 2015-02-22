#ifndef MAP_H_
#define MAP_H_

#include <vector>
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
			Map(unsigned int width);
			unsigned int getWidth();
			void setCell(const Cell& cell);
			Cell getCell(const int& index);
		
		private:
			unsigned int width_;
			std::vector<Cell> cells_;
	};
} /* namespace Marx */

#endif /* MAP_H_ */
