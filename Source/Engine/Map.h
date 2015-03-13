/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Map.h
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
--        This file defines the Map class members
--
----------------------------------------------------------------------------------------------------------------------*/


#ifndef MAP_H_
#define MAP_H_

namespace Marx
{
	class Map;	
}

#include <vector>
#include "Cell.h"


namespace Marx
{
    typedef unsigned int uint;
    /* 
    *    Map base class
    *   
    */
    class Map
    {
        public:
            Map(const uint height, const uint width);
            ~Map();
            unsigned int getHeight() const;
            unsigned int getWidth() const;
            void setCell(const uint x, const uint y, Cell* cell);
            Cell* getCell(const uint x, const uint y) const;
            void setTexture(const uint texture_id);
            uint getTexture() const;
            
        private:
            uint width_;
            uint height_;
            uint texture_id_;
            std::vector<Cell*> cells_;
    };
} /* namespace Marx */

#endif /* MAP_H_ */
