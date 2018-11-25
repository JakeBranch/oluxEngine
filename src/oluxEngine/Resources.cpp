#include "Resources.h"

namespace OluxEngine
{
    /**
	*Clean up un-used resources from memory
	*/
    void Resources::cleanUp()
    {
        for (std::list<std::shared_ptr<Resource>>::iterator it = resources.begin(); it != resources.end(); ++it)
        {
            if(it->use_count() <= 1)
            {
                it = resources.erase(it);
                it--;
            }
        }
    }
}