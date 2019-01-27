#pragma once

#include "LogType.h"

#include <string_view>

class BaseLog
{
public:
    virtual void Log(const LogType type, const std::string_view message);
    virtual ~BaseLog() {}
};