#include "Exception.h"

namespace OluxEngine
{
    /**
    * Sets error message
    */
    Exception::Exception(std::string message)
    {
        this->message = message;
    }

    Exception::~Exception() throw() { }

    /**
    * Returns error message
    */
    const char *Exception::what()
    {
        return message.c_str();
    }
}