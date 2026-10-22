#pragma once
#include "log_output.h"
#include <fstream>
class LogFileOutPut :
    public LogOutPut
{
public:
    bool Open(const std::string& file);
    void OutPut(const std::string& log)override;
private:
    std::ofstream ofs;
};

