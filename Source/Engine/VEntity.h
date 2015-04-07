#ifndef VENTITY_H_
#define VENTITY_H_

#include "Entity.h"
#include "Controller.h"
#include "../Multimedia/graphics/object/SGO.h"
#include "../Logic/EntityTypes.h"


namespace Marx
{

	class VEntity : public Entity
	{
	public:
		VEntity(SGO & _sprite, Map * _map, float x, float y, Controller * ctrl, float h, float w, ENTITY_TYPES eType = ENTITY_TYPES::I_DONT_KNOW);

		sf::Transform getLocalTransform() const override;

		const SGO& getSprite() const;
		SGO& getSprite();
		void setSprite(SGO& _sprite);

	protected:
		
		virtual void draw(Renderer& renderer, sf::RenderStates states) const override;
		bool drawable;

		SGO* sprite;
	};

};

#endif
