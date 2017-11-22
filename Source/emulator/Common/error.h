#pragma once

#include <exception>
#include <string>

namespace Common
{
    enum ErrorType
    {
        Warning = 0,
        Critical
    };

    class Error : public std::exception
    {
    public:
        Error(const std::string& msg, ErrorType type);
        Error(const char* const msg, ErrorType type);

        char const* what() const override;
        ErrorType type() const;

    private:
        std::string Msg;
        const ErrorType Type;
    };
}
