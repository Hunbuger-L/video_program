#include "log_console_output.h"
#include <iostream>

void LogConsoleOutPut::OutPut(const std::string& log) {
	std::cout << log << std::endl;
}