/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Cell.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: February 16, 2015
--
-- REVISIONS:
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

    typedef unsigned int* tile_id;
    
    /* 
    *    A basic cell class that contains an element.
    *
    */
    class Cell : public sf::FloatRect
    {
        public:
            explicit Cell(int x = 0, int y = 0): xcoord_(x), ycoord_(y) {}

            // Getters and setters for id
            void setId(std::string id);
            std::string getId() const;

            // Getters and setters for tile id
            void setTileId(tile_id t_id);
            tile_id getTileId() const;
            
            // Getters and setters for coords
            void    setX(const int& x);
            void    setY(const int& y);
            void    setCoord(const int& x, const int& y);
            int     getX() const;
            int     getY() const;
            std::set<Entity*> getEntity();
            // overloading == operator
            bool operator==(const Cell& cell);
            
        private:
            tile_id tile_id_;
            std::string cell_id_;
            //position on the map
            int xcoord_;
            int ycoord_;
            std::set<Entity*> entity;
    };
} /* namespace Marx */

#endif /* CELL_H_ */
