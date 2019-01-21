#pragma once

#include <exception>
#include <string>

#define DBG_LINE std::string("(") + __FILE__ + ": " + __FUNCTION__ + " at " + std::to_string(__LINE__) + ")"
typedef std::string dbg_line;

#define CHECK(condition, errMsg) \
    do\
    {\
        if(condition == false)\
            throw Common::Error(DBG_LINE, errMsg, Common::Critical);\
    } while(0)

namespace Common
{
    enum ErrorType
    {
        Warning = 0,
        Critical,
    };

    class Error : public std::exception
    {
    public:
        Error(const dbg_line& line, const std::string& msg, ErrorType type);
        Error(const dbg_line& line, const char* const msg, ErrorType type);
        explicit Error(const dbg_line& line, ErrorType type);

        char const* what() const noexcept override;
        ErrorType type() const;

    private:
        const std::string Msg;
        const ErrorType Type;
    };
}