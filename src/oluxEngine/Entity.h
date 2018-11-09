#include "Component.h"

#include <memory>
#include <vector>

#include "Exception.h"

#define ADDCOMPONENT \
	std::shared_ptr<T> rtn = std::make_shared<T>(); \
	rtn->entity = self; \
	rtn->began = false; \
	components.push_back(rtn);

namespace OluxEngine
{
	class Core;

	class Entity
	{
		friend class Core;

		public:
			/**
			*Template function to add a component to an entity
			*/
			template <typename T>
			std::shared_ptr<T> addComponent()
			{
				ADDCOMPONENT
				rtn->onInit();

				return rtn;
			}

			/**
			*Template function to add a component to an entity with one argument
			*/
			template <typename T, typename A>
			std::shared_ptr<T> addComponent(A a)
			{
				ADDCOMPONENT
				rtn->onInit(a);

				return rtn;
			}

			/**
			*Template function to add a component to an entity with two arguments
			*/
			template <typename T, typename A, typename B>
			std::shared_ptr<T> addComponent(A a, B b)
			{
				ADDCOMPONENT
					rtn->onInit(a, b);

				return rtn;
			}

			std::shared_ptr<Core> getCore();

			/**
			*Trigger for deletion. 
			*
			*If(alive = true) delete entitiy
			*/
			bool alive = true;

		private:
			/**
			*Reference to self
			*/
			std::weak_ptr<Entity> self;

			/**
			*Reference to core
			*/
			std::weak_ptr<Core> core;

			/**
			*Reference to all components attached to the entity
			*/
			std::vector<std::shared_ptr<Component>> components;

			void update();
			void display();
			void destroy();

			bool getAlive();
	};
}