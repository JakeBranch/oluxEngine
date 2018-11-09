#ifndef OLUXENGINE_COMPONENT_H
#define OLUXENGINE_COMPONENT_H

#include <memory>

namespace OluxEngine
{

	class Entity;
	class Core;

	/**
	* Base class for game components
	*/
	class Component
	{
		friend class Entity;

	public:
		virtual ~Component();
		std::shared_ptr<Core> getCore();
		std::shared_ptr<Entity> getEntity();

	private:
		/**
		* Reference to the entity the component is attached to
		*/
		std::weak_ptr<Entity> entity;

		/**
		*Flag to check if components onBegin() has been called
		*/
		bool began;

		virtual void onInit();
		virtual void onBegin();
		virtual void update();
		virtual void onDisplay();
	};

}

#endif