#include "Component.h"
#include "Entity.h"

namespace OluxEngine
{

	Component::~Component() { }
	void Component::onInit() { }
	void Component::onBegin() { }
	void Component::update() { }
	void Component::onDisplay() { }

	std::shared_ptr<Entity> Component::getEntity()
	{
		return entity.lock();
	}

	std::shared_ptr<Core> Component::getCore()
	{
		return getEntity()->getCore();
	}

}