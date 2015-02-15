#ifndef BGO_H
#define BGO_H

#include <SFML\Graphics.hpp>
#include <vector>

typedef const unsigned int* id_go;

class Batch;

/**
 * Base Game Object.
 * 
 * All objects present in the game (both visible or otherwise)
 * ultimately inherit from this.
 * 
 * @author Melvin Loho
 */
class BGO
{
public:
	/**
	 * Constructor.
	 */
	BGO();

	/**
	 * Virtual Destructor.
	 */
	virtual ~BGO();

	/**
	 * Gets this BGO's ID
	 * 
	 * @return the ID
	 */
	id_go getID() const override;

	/**
	 * Gets this BGO's children.
	 * 
	 * @return the vector of children
	 */
	const std::vector<BGO*> &getChildren() const;

	/**
	 * Gets the parent of this BGO if it has one.
	 * 
	 * @return the parent or null
	 */
	BGO* getParent() const;

	/**
	 * Adds the specified BGO to this one.
	 *
	 * @param gO the specified BGO
	 */
	void add(BGO &gO);

	/**
	 * Removes the specified BGO from this one.
	 *
	 * @param  gO the specified BGO
	 * @return    the removed BGO
	 */
	const BGO *rem(const BGO &gO);

	/**
	 * Removes the BGO with the specified ID from this one.
	 *
	 * @param  id the specified ID
	 * @return    the removed BGO
	 */
	const BGO *rem(go_id id);

	/**
	 * Checks whether or not this BGO is carrying
	 * any unignored children.
	 * 
	 * @return true/false
	 */
	bool hasChildren() const;

	/**
	 * Ignores/unignores all children held by this BGO.
	 *
	 * @param arg to ignore or not to ignore
	 */
	void ignoreChildren(bool arg) const;

	/**
	 * Gets the local transformation matrix belonging to the
	 * object that this BGO is representing.
	 *
	 * @return the transformation matrix
	 */
	virtual const sf::Transform &getLocalTransform() const;

	/**
	 * Updates this BGO and its children.
	 *
	 * @param t the elapsed time
	 */
	void updateSG(const sf::Time& t);

	/**
	 * Updates this BGO.
	 *
	 * @param t the elapsed time
	 */
	virtual void update(const sf::Time& t);

	/**
	 * Draws this BGO's children and itself.
	 *
	 * @param batch  the batcher used to render
	 * @param states the render states used to render
	 */
	void drawSG(Batch &batch, sf::RenderStates states) const;

	/**
	 * Draws this BGO.
	 *
	 * @param batch  the batcher used to render
	 * @param states the render states used to render
	 */
	virtual void draw(Batch &batch, sf::RenderStates states) const;

private:
	static unsigned int ID_GO;

	std::vector<BGO*> m_children;
	BGO *m_parent;
	id_go m_id;
};

#endif // BGO_H