#ifndef BGO_H
#define BGO_H

#include <SFML/Graphics.hpp>
#include <vector>

class Renderer;

typedef unsigned int id_go;

class BGO
{
public:
	BGO();
	virtual ~BGO();

	id_go getID() const;
	const std::vector<BGO*>& getChildren() const;
	BGO* getParent() const;

	void add(BGO& gO);
	bool rem(const BGO& gO);
	bool rem(id_go id);

	bool hasChildren() const;
	void ignoreChildren(bool arg);

	virtual sf::Transform getLocalTransform() const;
	const sf::Transform& getGlobalTransform() const;

	void updateSG(const sf::Time& t);
	virtual void update(const sf::Time& t);

protected:
	friend class Renderer;

	void drawSceneGraph(Renderer& renderer, sf::RenderStates states) const;
	virtual void drawChildren(Renderer& renderer, sf::RenderStates states) const;
	virtual void draw(Renderer& renderer, sf::RenderStates states) const;

private:
	static id_go ID_GO;

	std::vector<BGO*> m_children;
	BGO* m_parent;
	id_go m_id;
	bool m_ignoringChildren;

	mutable sf::Transform m_globaltrans;
};

#endif // BGO_H
