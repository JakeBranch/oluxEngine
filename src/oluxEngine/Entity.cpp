#include "Entity.h"

#include <cstdlib>

#include <iostream>

namespace OluxEngine
{
	std::shared_ptr<Core> Entity::getCore()
	{
		return core.lock();
	}

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

			
			/*int x = (rand()%100);
			if(x >= 90)
			{
				throw Exception("Entity Thrown!!");
			}*/
		}
	}

	void Entity::display()
	{
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
			it != components.end(); it++)
		{
			(*it)->onDisplay();
		}
	}

	void Entity::destroy()
	{
		alive = false;
	}

	bool Entity::getAlive()
	{
		return alive;
	}
}