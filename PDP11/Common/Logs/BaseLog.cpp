#include "BaseLog.h"

#include <iostream>

void BaseLog::Log(const LogType type, const std::string_view message)
{
    std::printf("%s\n", message);
}