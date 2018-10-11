#include "Entity.h"

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
}