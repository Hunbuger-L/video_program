#pragma once
#include "logger.h"
#include "x_log_conf.h"
#include <string>
#include "xlog.h"
class XLOG_API LogFac
{
public:
	static LogFac& Instance() {
		static LogFac logfac;
		return logfac;
	}
	void Init(const std::string& con_file = "xlog.conf");
	Logger& logger() { return logger_; }
private:
	LogFac() {}	
	Logger logger_;
};

#define XLOGINIT() LogFac::Instance().Init(); 
#define XLOGOUT(l,s) LogFac::Instance().logger().Write(l, s , __FILE__, __LINE__)
#define LOGDEBUG(s)  XLOGOUT(XLog::DEBUG,s)
#define LOGINFO(s) XLOGOUT(XLog::INFO,s)
#define LOGERROR(s) XLOGOUT(XLog::ERROR,s)
#define LOGFATAL(s) XLOGOUT(XLog::FATAL,s)
