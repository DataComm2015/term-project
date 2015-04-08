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
            Map(const int height, const int width);
            ~Map();
            int getHeight() const;
            int getWidth() const;
            void setCell(const int x, const int y, Cell* cell);
            Cell* getCell(const int x, const int y) const;
            void setTexture(const uint texture_id);
            uint getTexture() const;
            std::set<Entity*> getEntities() const;
            sf::Transform getLocalTransform() const override;
            sf::Transform trans;

        protected:
            void drawChildren(Renderer& renderer, sf::RenderStates states) const override;
            void draw(Renderer& renderer, sf::RenderStates states) const override;

        private:
            int width_;
            int height_;
            unsigned int texture_id_;
            std::vector<Cell*> cells_;
    };
} /* namespace Marx */

#endif /* MAP_H_ */
