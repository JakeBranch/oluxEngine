#include "Resources.h"

namespace OluxEngine
{
    void Resources::cleanUp()
    {
        for (std::list<std::shared_ptr<Resource>>::iterator it = resources.begin(); it != resources.end(); ++it)
        {
                if(it->use_count() <= 1)
                {
                    std::cout << "DELETE" << std::endl;
                    it = resources.erase(it);
                }
        }
    }
}