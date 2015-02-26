#ifndef CELL_H_
#define CELL_H_

#include <string>
#include <SFML/Graphics/Rect.hpp>

namespace Marx
{
	typedef unsigned int* tile_id;
	
	/* 
	*	A basic cell class that contains an element.
	*
	*/
	class Cell : public sf::IntRect
	{
		public:
			explicit Cell(int x = 0, int y = 0): xcoord_(x), ycoord_(y) {}

			// Getters and setters for id
			void setId(std::string id);
			std::string getId();

			// Getters and setters for tile id
			void setTileId(tile_id t_id);
			tile_id getTileId();
			
			// Getters and setters for coords
			void	setX(const int& x);
			void	setY(const int& y);
			void	setCoord(const int& x, const int& y);
			int		getX();
			int		getY();

			// overloading == operator
			bool operator==(const Cell& cell);
			
		private:
			tile_id tile_id_;
			std::string cell_id_;
			//position on the map
			int xcoord_;
			int ycoord_;
	};
} /* namespace Marx */

#endif /* CELL_H_ */
