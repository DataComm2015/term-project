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
#include <stdexcept> 
#include "Cell.h"
#include "../Multimedia/graphics/object/BGO.h"
#include "../Multimedia/graphics/Renderer.h"


namespace Marx 
{
    typedef unsigned int uint;
    /* 
    *    Map base class
    *   
    */
    class Map : public BGO
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
			std::set<Entity*> getEntities() const;
			const sf::Transform& getLocalTransform() const override;
			sf::Transform trans;
            
	protected:
		void draw(Renderer& renderer, sf::RenderStates states) const override;

        private:
            unsigned int width_;
            unsigned int height_;
            unsigned int texture_id_;
            std::vector<Cell*> cells_;
    };
} /* namespace Marx */

#endif /* MAP_H_ */
