#pragma once

#include <string_view>

enum class LogType
{
    Log = 0,
    Warning = 1,
    Critical = 2,
};

inline std::string_view GetLogTypeName(const LogType type)
{
    switch (type)
    {
    case LogType::Log:      return "Log";
    case LogType::Warning:  return "Warning";
    case LogType::Critical: return "Critical";
    default:                return "UNKNOWN";
    }
}