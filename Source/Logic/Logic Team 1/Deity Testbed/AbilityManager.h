#ifndef ABILITY_MANAGER_H_
#define ABILITY_MANAGER_H_

#include "../../../Engine/Map.h"
#include "../../../Engine/Entity.h"

using namespace Marx;

/* An enum containing all possible abilities */
enum AbilityId { TEST1, TEST2 };
typedef enum AbilityId AbilityId;

/* An array of cooldowns for the abilities (in frames) */
const int cooldowns[] = { 60, 60 };

/* An array of names for the abilities */
const char* names[] = { "Test 1", "Test 2" };

/* An array of descriptions for the abilities */
const char* descriptions[] = { "This is a test", "This is also a test" };

/* An array of file paths for the ability images */
const char* images[] = { "./images/test1", "./images/test2" };


/* A struct containing the information for a specific Ability */
struct Ability
{
	AbilityId id;
	int cooldown;
	const char* name;
	const char* description;
	const char* image;
};

typedef struct Ability Ability;


/*
	The AbilityManager class is a singleton class used to cast abilities
	on entities and coordinates within a map.
*/
class AbilityManager
{
	public:
		AbilityManager(Map *m);
		~AbilityManager();

		Ability getAbilityDetails(AbilityId id);
		bool castAbility(int x, int y, AbilityId id);
		bool castAbility(Entity *e, AbilityId id);

		static AbilityManager* getInstance(Map *m = NULL);
	private:
		Map *cMap;
		static AbilityManager *instance;
};

#endif