#ifndef OLUXENGINE_RESOURCES_H
#define OLUXENGINE_RESOURCES_H

#include "Resource.h"

#include <memory>
#include <list>
#include <iostream>

namespace OluxEngine
{
	class Resources
	{
		public:
			template <typename T, typename A>
			std::shared_ptr<T> Load(A a)
			{
				std::shared_ptr<T> rtn = T::Load(a);
				resources.push_back(rtn);

				return rtn;
			}

			template <typename T, typename A, typename B>
			std::shared_ptr<T> Load(A a, B b)
			{
				std::shared_ptr<T> rtn = T::Load(a, b);
				resources.push_back(rtn);

				return rtn;
			}

		private:
			std::list<std::shared_ptr<Resource>> resources;
	};
}

#endif