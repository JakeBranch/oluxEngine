#ifndef OLUXENGINE_EXCEPTION_H
#define OLUXENGINE_EXCEPTION_H

#include <exception>
#include <string>

namespace OluxEngine
{
    /**
    * Wrapper class for exception handling
    */
    class Exception : public std::exception
    {
        public:
            Exception(std::string message);
            ~Exception() throw();

            const char *what();

        private:
            /**
            * Error message to be sent with exception
            */ 
            std::string message;
    };
}

#endif