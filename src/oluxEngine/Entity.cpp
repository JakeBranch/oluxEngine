#include "Entity.h"

#include <cstdlib>

#include <iostream>

namespace OluxEngine
{
	/**
	* Return reference to core
	*/
	std::shared_ptr<Core> Entity::getCore()
	{
		return core.lock();
	}

	/**
	* Trigger Update() on all of the entity's components
	*/
	void Entity::update()
	{
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
			it != components.end(); it++)
		{
			if (!(*it)->began)
			{
				(*it)->onBegin();
				(*it)->began = true;
			}

			(*it)->update();
		}
	}

	/**
	* Trigger onDisplay() on all of the Entity's components
	*/
	void Entity::display()
	{
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
			it != components.end(); it++)
		{
			(*it)->onDisplay();
		}
	}

	/**
	*	Mark enity for deletion
	*/
	void Entity::destroy()
	{
		alive = false;
	}

	/**
	* Return alive 
	*/
	bool Entity::getAlive()
	{
		return alive;
	}
}