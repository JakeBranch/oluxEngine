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
	void Entity::onUpdate()
	{
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
			it != components.end(); it++)
		{
			if (!(*it)->began)
			{
				(*it)->onBegin();
				(*it)->began = true;
			}

			(*it)->onUpdate();
		}
	}

	/**
	* Trigger onDisplay() on all of the Entity's components
	*/
	void Entity::onDisplay()
	{
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
			it != components.end(); it++)
		{
			(*it)->onDisplay();
		}
	}

	void Entity::onGui()
	{
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
			it != components.end(); it++)
		{
			(*it)->onGui();
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

	std::string Entity::getTag()
	{
		return tag;
	}

	void Entity::setTag(std::string tag)
	{
		this->tag = tag;
	}
}