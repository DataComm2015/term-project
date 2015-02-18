#ifndef CELL_H_
#define CELL_H_

#include <string>

namespace Marx
{
	/* 
	*	A basic cell class that contains an element.
	*
	*/
	class Cell
	{
		public:
			explicit Cell(int x = 0, int y = 0): xcoord_(x), ycoord_(y) {}

			// Getters and setters for id
			void setId(std::string id);
			std::string getId();

			// Getters and setters for coords
			void	setX(const int& x);
			void	setY(const int& y);
			void	setCoord(const int& x, const int& y);
			int		getX();
			int		getY();

			// overloading == operator
			bool operator==(const Cell& cell);
			
		private:
			std::string cell_id_;
			//position on the map
			int xcoord_;
			int ycoord_;
	};
} /* namespace Marx */

#endif /* CELL_H_ */
