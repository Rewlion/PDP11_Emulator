#include "Error.h"

namespace Common
{
    Error::Error(const dbg_line& line, const std::string& msg, ErrorType type)
        : Msg(line + std::string(msg))
        , Type(type)
    {
    }

    Error::Error(const dbg_line& line, const char* const msg, ErrorType type)
        : Msg(line + std::string(msg))
        , Type(type)
    {
    }

    Error::Error(const dbg_line& line, ErrorType type)
        : Msg(line)
        , Type(type)
    {
    }

    char const* Error::what() const noexcept
    {
        return Msg.c_str();
    }

    ErrorType Error::type() const
    {
        return Type;
    }
}