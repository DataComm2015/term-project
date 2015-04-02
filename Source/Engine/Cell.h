/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Cell.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: February 16, 2015
--
-- REVISIONS: March 29, 2015 - Added Blocking mechanic
--
-- DESIGNER: Marc Vouve
--           Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- NOTES:
--        This file defines the Cell class members
--
----------------------------------------------------------------------------------------------------------------------*/
#include "Entity.h"

#ifndef CELL_H_
#define CELL_H_


#include <string>
#include <SFML/Graphics/Rect.hpp>
#include <set>


namespace Marx
{
    class Entity;

    typedef unsigned int tile_id;
    
    /* 
    *    A basic cell class that contains an element.
    *
    */
    class Cell : public sf::FloatRect
    {
        public:
            explicit Cell(int x = 0, int y = 0, tile_id tid = 0, bool block = false): xcoord_(x), ycoord_(y), tile_id_(tid), blocking(block) {}

            // Getters and setters for tile id
            void setTileId(tile_id t_id);
            tile_id getTileId() const;
            
            // Getters and setters for coords
            void    setX(const int& x);
            void    setY(const int& y);
            void    setCoord(const int& x, const int& y); 
			void	addEntity(Entity *);
			void	removeEntity(Entity *);
			void	setBlocking( bool );
			bool	getBlocking();
            int     getX() const;
            int     getY() const;
            std::set<Entity*> getEntity();
            // overloading == operator
            bool operator==(const Cell& cell);
            
        private:
            tile_id tile_id_;
            int xcoord_;
            int ycoord_;
            std::set<Entity*> entity;
			bool blocking;
    };
} /* namespace Marx */

#endif /* CELL_H_ */
