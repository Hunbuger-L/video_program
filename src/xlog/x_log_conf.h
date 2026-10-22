#pragma once
#include <string>
#include <map>
class XLogConf
{
public:
	bool Read(const std::string& file);
	const std::string Get(const std::string& key);
private:
	std::map<std::string, std::string> conf_;
};

