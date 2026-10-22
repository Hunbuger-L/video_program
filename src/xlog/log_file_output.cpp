#include "log_file_output.h"

bool LogFileOutPut::Open(const std::string& file) {
	ofs.open(file, std::ios::app);
	if (ofs.is_open()) return true;
	else return false;
}
void LogFileOutPut::OutPut(const std::string& log) {
	ofs << log<<"\n";
}