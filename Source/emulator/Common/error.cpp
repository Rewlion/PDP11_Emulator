#include "error.h"

namespace Common
{
    Error::Error(const std::string& msg, ErrorType type)
        : Msg(msg)
        , Type(type)
    {
    }

    Error::Error(const char* const msg, ErrorType type)
        : Msg(msg)
        , Type(type)
    {

    }

    char const* Error::what() const
    {
        return Msg.c_str();
    }

    ErrorType Error::type() const
    {
        return Type;
    }
}
