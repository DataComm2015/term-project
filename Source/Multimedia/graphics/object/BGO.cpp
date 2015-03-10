/**
 * Base Game Object.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @notes      All objects present in the game (both visible or otherwise) ultimately inherit from this.
 */

#include "BGO.h"

#include <iostream>
#include "../Renderer.h"

id_go BGO::ID_GO = 0;

/**
 * Constructor.
 */
BGO::BGO() :
m_parent(nullptr),
m_id(++ID_GO),
m_ignoringChildren(false)
{
	std::cout << "Constructed: " << "GO" << "[" << getID() << "]" << std::endl;
}

/**
 * Virtual Destructor.
 */
BGO::~BGO()
{
	std::cout << "Destructed: " << "GO" << "[" << getID() << "]" << std::endl;
}

/**
 * Gets this game object's ID.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @return     The ID
 */
id_go BGO::getID() const
{
	return m_id;
}

/**
 * Gets this game object's children.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @return     The vector of children
 */
const std::vector<BGO*>& BGO::getChildren() const
{
	return m_children;
}

/**
 * Gets the parent of this game object if it has one.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @return     The parent or null
 */
BGO* BGO::getParent() const
{
	return m_parent;
}

/**
 * Adds the specified game object to this one.
 * The added game object (child) will then be influenced by this game object (parent).
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      gO The specified game object
 */
void BGO::add(BGO& gO)
{
	if (gO.m_id == m_id) {
		throw std::string("Are you crazy!? You just tried to add a graphic object to itself!");
	}
	else {
		if (gO.m_parent) gO.m_parent->rem(gO);
		gO.m_parent = this;
		m_children.push_back(&gO);
	}
}

/**
 * Removes the specified game object from this one.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      gO The specified game object
 *
 * @return     Success/Fail
 */
bool BGO::rem(const BGO& gO)
{
	for (std::vector<BGO*>::iterator iter = m_children.begin();
		iter != m_children.end();
		++iter) {
		if (*iter == &gO) {
			m_children.erase(iter);
			return true;
		}
	}
	return false;
}

/**
 * Removes the game object with the specified ID from this one.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      id The specified ID
 *
 * @return     Success/Fail
 */
bool BGO::rem(id_go id)
{
	for (std::vector<BGO*>::iterator iter = m_children.begin();
		iter != m_children.end();
		++iter) {
		if ((*iter)->m_id == id) {
			m_children.erase(iter);
			return true;
		}
	}
	return false;
}

/**
 * Checks whether or not this game object is carrying any un-ignored children.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @return     True/False
 */
bool BGO::hasChildren() const
{
	if (m_ignoringChildren || m_children.empty()) return false;
	else return true;
}

/**
 * Ignores/un-ignores all children held by this game object.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      arg to ignore or not to ignore
 */
void BGO::ignoreChildren(bool arg)
{
	m_ignoringChildren = arg;
}

/**
 * Gets the local transformation matrix belonging to the object that is represented by this game object.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @return     The transformation matrix
 */
const sf::Transform& BGO::getLocalTransform() const
{
	return sf::Transform::Identity;
}

/**
 * Updates this game object and its children.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      t The elapsed time
 */
void BGO::updateSG(const sf::Time& t)
{
	update(t);

	if (hasChildren())
	{
		for (BGO* bgo : m_children)
		{
			bgo->updateSG(t);
		}
	}
}

/**
 * Updates this game object.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      t The elapsed time
 */
void BGO::update(const sf::Time& t)
{}

/**
 * Draws this game object's children and itself.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      renderer The renderer
 * @param      states   The render states
 */
void BGO::drawSG(Renderer& renderer, sf::RenderStates states) const
{
	// Draw children
	if (hasChildren())
	{
		// Combine transformations (parent's + current's)
		sf::RenderStates combinedStates = states;
		combinedStates.transform.combine(getLocalTransform());

		for (const BGO* go : m_children)
		{
			go->drawSG(renderer, combinedStates);
		}
	}

	// Draw self
	draw(renderer, states);
}

/**
 * Draws this game object.
 *
 * @date       2015-02-25
 *
 * @revisions
 *
 * @designer   Melvin Loho
 *
 * @programmer Melvin Loho
 *
 * @param      renderer The renderer
 * @param      states   The render states
 */
void BGO::draw(Renderer& renderer, sf::RenderStates states) const
{}
