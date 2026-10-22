#pragma once
#include "log_output.h"
class LogConsoleOutPut :
    public LogOutPut
{
public:
    void OutPut(const std::string& log)override;
};

