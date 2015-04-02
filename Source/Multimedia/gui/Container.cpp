#include "Container.h"


namespace GUI
{
	/**
	* Initializes a container
	*
	* @date         2015-02-26
	*
	* @revisions	2015-03-18 - Removed BGO parent from constructor
	*
	* @designer
	*
	* @programmer   Jonathan Chu
	*				Marc Rafanan
	*
	* @return       initializer
	*/
	Container::Container(SGO* firstSGO, SGO* secondSGO, sf::Vector2f theSize, orientation theOrientation)
	{
		A = firstSGO;
		B = secondSGO;
		size = theSize;
		orient = theOrientation;
		ratio = 0.5f;
		separator = NULL;

		add(*A);
		add(*B);
	}

	/**
	* Sets the separator for the containers
	*
	* @date         2015-02-26
	*
	* @revisions
	*
	* @designer
	*
	* @programmer   Jonathan Chu
	*
	* @return       void
	*/
	void Container::setSeperator(SGO* theSeparator)
	{
		separator = theSeparator;
	}

	/**
	* Sets the ratio of the container
	*
	* @date         2015-02-26
	*
	* @revisions
	*
	* @designer
	*
	* @programmer   Jonathan Chu
	*
	* @return       void
	*/
	void Container::setRatio(float theRatio)
	{
		ratio = theRatio;
	}

	/**
	* Sets the orientation of the container
	*
	* @date         2015-02-26
	*
	* @revisions
	*
	* @designer
	*
	* @programmer   Jonathan Chu
	*
	* @return       void
	*/
	void Container::setOrientation(orientation theOrientation)
	{
		orient = theOrientation;
	}

	/**
	* Sets the position of the container
	*
	* @date         2015-03-11
	*
	* @revisions
	*
	* @designer
	*
	* @programmer   Lewis Scott
	*
	* @return       void
	*/
	void Container::setPosition(sf::Vector2f newpos)
	{
		pos = newpos;
	}

	/**
	* Sets the orientation of the container
	*
	* @date         2015-03-11
	*
	* @revisions
	*
	* @designer
	*
	* @programmer   Lewis Scott
	*
	* @return       void
	*/
	void Container::pack()
	{
		bool side = (orient == HORIZONTAL);
		float sep_size = 0.0f;

		if (separator != NULL)
			sep_size = side ? separator->sprite().getScale().x : separator->sprite().getScale().y;

		float total = (side ? size.x : size.y) - sep_size;
		float side_size = total*(ratio);

		// Scale and position A
		sf::Vector2f size_a((side ? side_size : A->sprite().getScale().x), (side ? A->sprite().getScale().y : side_size));
		A->sprite().setScale(size_a);
		A->sprite().setPosition(pos);

		// Position separator
		sf::Vector2f offset = pos;
		offset += sf::Vector2f(side ? side_size : 0.0f, side ? 0.0f : side_size);
		separator->sprite().setPosition(offset);

		// Scale and position B
		side_size = total - side_size;
		sf::Vector2f size_b(side ? side_size : B->sprite().getScale().x, side ? B->sprite().getScale().y : side_size);
		offset += sf::Vector2f(side ? (separator->sprite().getScale().x) : 0.0f, side ? 0.0f : (separator->sprite().getScale().y));
		B->sprite().setScale(size_b);
		B->sprite().setPosition(offset);
	}

	/**
	* Gets the size of the container
	*
	* @date         2015-03-18
	*
	* @revisions
	*
	* @designer   	Melvin Loho
	*				Marc Rafanan
	*
	* @programmer   Marc Rafanan
	*
	* @return       void
	*/
	sf::Vector2f Container::getSize()
	{
		return size;
	}

}
