#ifndef OLUXENGINE_RESOURCE_H
#define OLUXENGINE_RESOURCE_H

#include <string>

namespace OluxEngine
{
	/**
	* Base class for resources
	*/
	class Resource
	{
		public:
			/**
			* Path of resource
			*/ 
			std::string path;
	};
}

#endif