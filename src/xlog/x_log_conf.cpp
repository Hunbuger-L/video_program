#include "x_log_conf.h"
#include <iostream>
#include <fstream>
#include <cerrno>

const std::string XLogConf::Get(const std::string& key) {
	auto c = conf_.find(key);
	if (c == conf_.end())
		return " ";
	return c->second;
}

bool XLogConf::Read(const std::string& file) {
	std::ifstream ifs(file);
	if (!ifs.is_open()) {
		char err_buf[256] = { 0 };
		// 参数顺序：缓冲区指针、缓冲区大小、错误码
		strerror_s(err_buf, sizeof(err_buf), errno);

		std::cout << "打开文件失败" << std::endl;
		std::cout << "错误原因：" << err_buf << std::endl;
		return false;
	}
	std::string line;
	for (;;) {
	  std::getline(ifs, line);
	  std::string k, v;
	  if(!line.empty())
	  {
		  auto p = line.find("=");
		  if (p <= 0) continue;
		  k = line.substr(0, p);
		  v = line.substr(p+1);

		  conf_[k] = v;
	  }
	  if (!ifs.good()) break;
	}
	return true;
}