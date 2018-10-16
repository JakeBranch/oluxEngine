#ifndef OLUXENGINE_EXCEPTION_H
#define OLUXENGINE_EXCEPTION_H

#include <exception>
#include <string>

namespace OluxEngine
{
    class Exception : public std::exception
    {
        public:
            Exception(std::string message);
            ~Exception() throw();

            const char *what();

        private:
            std::string message;
    };
}

#endif