#include "xexec.h"
#include <iostream>

#include <string>
#ifdef _WIN32
#else
#define _popen popen
#endif

bool XExec::Start(const char* cmd,
	std::function<void (const std::string &)>func) {
	std::cout << " Start Cmd : " << cmd << std::endl;

	std::string tem = cmd;
	tem += " 2>&1";//重定向 将标准错误输出重定向到标准输出中，这个格式是通用格式，2代表标准错误输出；
	auto fp = _popen(tem.c_str(), "r");
	if (!fp) return false;
	running_ = true;
	fut_ =std::async([fp,this, func]{
		std::string tem;
		char c = 0;
		while (c = fgetc(fp)) {
			if (c == EOF) break;
			if (c == '\n' || c == '\r') 
			{
				/*std::cout << tem << std::endl;*/
				if (tem.empty()) continue;
				{
					if (func) {
						func(tem);
					}
					else {
						std::lock_guard<std::mutex> lock(mux_);
						outs_.push(tem);
					}
				}
				tem = ' ';
				continue;
			}
			tem += c;
		}
		_pclose(fp);
		running_ = false;
		return true;
		});
	return true;
}

bool XExec::GetOutPut(std::string& out) {
	std::lock_guard<std::mutex> lock(mux_);
	if (outs_.empty()) return false;
	out = move(outs_.front());
	outs_.pop();
	return true;
}