#ifndef OLUXENGINE_COMPONENT_H
#define OLUXENGINE_COMPONENT_H

#include <memory>

namespace OluxEngine
{

	class Entity;
	class Core;

	class Component
	{
		friend class Entity;

	public:
		virtual ~Component();
		std::shared_ptr<Core> getCore();
		std::shared_ptr<Entity> getEntity();

	private:
		std::weak_ptr<Core> core;
		std::weak_ptr<Entity> entity;
		bool began;

		virtual void onInit();
		virtual void onBegin();
		virtual void update();
		virtual void onDisplay();
	};

}

#endif