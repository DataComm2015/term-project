#ifndef DEITY_H
#define DEITY_H

#include <SFML/Graphics.hpp>
#include "../../Engine/Map.h"
#include "../../Engine/Entity.h"
#include "../../Engine/Cell.h"
#include "../../Engine/Controller.h"
#include "../../Engine/TileManager.h"
#include "AbilityManager.h"

class Deity : public Marx::Entity
{
    public:
        Deity(Marx::Map * gmap, float x, float y, Marx::Controller* controller);
        virtual ~Deity();
		virtual void onUpdate();
    
    private:
        AbilityManager abilityMan;
        AbilityId oneId;
        AbilityId twoId;
        bool movingLeft;
        bool movingRight;
        bool movingUp;
        bool movingDown;
		float xSpeed;
		float ySpeed;
};

#endif