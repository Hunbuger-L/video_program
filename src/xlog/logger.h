#pragma once
#include <string>
#include "log_output.h"
#include "log_format.h"
#include "xlog.h"
#include <memory>
enum class XLog {
	DEBUG,
	INFO,
	ERROR,
	FATAL
};

class XLOG_API Logger {
public:
	void Write(
	XLog level,
	const std::string& log,
	const std::string& file,
	int line
	);
	void setOutPut(std::unique_ptr<LogOutPut> out) {
		output_ = move(out);
	}
	void setFormat(std::unique_ptr<LogFormat> f) {
		format_ = move(f);
	}
	void setLevel(XLog level) {
		log_level = level;
	}
	~Logger() {}
private:
	//LogFormat* formater_{ nullptr };
	//LogOutPut* output_{ nullptr };
	std::unique_ptr<LogFormat> format_;
	std::unique_ptr<LogOutPut> output_;

	XLog log_level{ XLog::DEBUG };
};