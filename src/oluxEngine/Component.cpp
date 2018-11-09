#include "Component.h"
#include "Entity.h"

namespace OluxEngine
{

	Component::~Component() { }
	void Component::onInit() { }
	void Component::onBegin() { }
	void Component::update() { }
	void Component::onDisplay() { }

	/**
	*Return reference to the entity the component is attached to
	*/
	std::shared_ptr<Entity> Component::getEntity()
	{
		return entity.lock();
	}

	/**
	*Return reference to core via the entity the component is attached to
	*/
	std::shared_ptr<Core> Component::getCore()
	{
		return getEntity()->getCore();
	}

}