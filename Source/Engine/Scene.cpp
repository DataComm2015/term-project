#include "Scene.h"
#include "../Network/Session.h"

using namespace Marx;

/* ----------------------------------------------------------------------------
-- METHOD: Marx::Scene::onLoad
--
-- PROGRAMMER: Marc Vouve
--
-- DESIGNER: Melvin Loho
-- 	     Marc Vouve
--
-- DATE: Sunday February 15th, 2015
--
-- REVISIONS: none
--
-- PROTOTYPE void Marx::Scene::onLoad
--
-- NOTES: this function returns a signleton for the VOID scene, however, it
-- doesn't have to be a signleton for every scene
--
-----------------------------------------------------------------------------*/
void Scene::onLoad()
{
	//no implementation.
}

/* ----------------------------------------------------------------------------
-- METHOD: Marx::Scene::processEvents
--
-- PROGRAMMER: Marc Vouve
--
-- DESIGNER: Melvin Loho
-- 	         Marc Vouve
--
-- DATE: Sunday February 15th, 2015
--
-- REVISIONS: none
--
-- PROTOTYPE void Marx::Scene::unLoad
--
-- NOTES: This function is called when a scene needs to be unLoaded. The default
--		  Scene does not get deleted this must be done when the scene is extended.

          calls handleSessionMessages which deals with all the queued messages
          for all sessions this scene has.
--
------------------------------------------------------------------------------*/
void Scene::processEvents(sf::Event & e)
{
	return;
}

/* ----------------------------------------------------------------------------
-- METHOD: Marx::Scene::unpdate
--
-- PROGRAMMER: Marc Vouve
--
-- DESIGNER: Melvin Loho
-- 			 Marc Vouve
--
-- DATE: Sunday February 14th, 2015
--
-- REVISIONS: none
--
-- PROTOTYPE void Marx::Scene::unLoad
--
-- NOTES: This function is called when a scene needs to be unLoaded. The default
--		  Scene does not get deleted this must be done when the scene is extended.
--
------------------------------------------------------------------------------*/
void Scene::update(sf::Time)
{

	return;
}

/* ----------------------------------------------------------------------------
-- METHOD: Scene::unLoad
--
-- PROGRAMMER: Marc Vouve
--
-- DESIGNER: Melvin Loho
-- 			 Marc Vouve
--
-- DATE: Sunday February 15th, 2015
--
-- REVISIONS: none
--
-- PROTOTYPE void marx::Scene::unLoad
--
-- NOTES: This function is called when a scene needs to be unLoaded. The default
--		  Scene does not get deleted this must be done when the scene is extended.
--
------------------------------------------------------------------------------*/
void Scene::draw()
{
	// no implementation
}

void Scene::unLoad()
{

}
