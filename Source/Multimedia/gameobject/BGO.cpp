#include "BGO.h"

#include <iostream>
#include "../renderer/Batch.h"

/**
* Base Game Object.
*
* All objects present in the game (both visible or otherwise)
* ultimately inherit from this.
*
* @author Melvin Loho
*/

id_go BGO::ID_GO = 0;

BGO::BGO() :
m_parent(nullptr),
m_id(++ID_GO),
m_ignoringChildren(false)
{
	std::cout << "Constructed: " << "GO" << "[" << getID() << "]" << std::endl;
}

BGO::~BGO()
{
	std::cout << "Destructed: " << "GO" << "[" << getID() << "]" << std::endl;
}

id_go BGO::getID() const
{
	return m_id;
}

const std::vector<BGO*>& BGO::getChildren() const
{
	return m_children;
}

BGO* BGO::getParent() const
{
	return m_parent;
}

void BGO::add(BGO& gO)
{
	if (gO.m_id == m_id) {
		throw std::exception("Are you crazy!? You just tried to add a graphic object to itself!");
	}
	else {
		if (gO.m_parent) gO.m_parent->rem(gO);
		gO.m_parent = this;
		m_children.push_back(&gO);
	}
}

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

bool BGO::hasChildren() const
{
	if (m_ignoringChildren || m_children.empty()) return false;
	else return true;
}

void BGO::ignoreChildren(bool arg)
{
	m_ignoringChildren = arg;
}

const sf::Transform& BGO::getLocalTransform() const
{
	return sf::Transform::Identity;
}

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

void BGO::update(const sf::Time& t) {}

void BGO::drawSG(Batch& batch, sf::RenderStates states) const
{
	// Draw children
	if (hasChildren())
	{
		// Combine transformations (parent's + current's)
		states.transform.combine(getLocalTransform());

		for (const BGO* go : m_children)
		{
			go->drawSG(batch, states);
		}
	}

	// Draw self
	draw(batch, states);
}

void BGO::draw(Batch& batch, sf::RenderStates states) const {}