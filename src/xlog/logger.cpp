#include "logger.h"


void Logger::Write(
    XLog level,
    const std::string& log,
    const std::string& file,
    int line) {
    if (!format_ || !output_) return;
    if (level < log_level)return;

    //日志级别枚举类型转为字符串
    std::string levelstr = "debug";
    switch (level) //switch只支持数字
    { //比if效率高
    case XLog::INFO:
        levelstr = "info";
        break;
    case XLog::ERROR:
        levelstr = "error";
        break;
    case XLog::FATAL:
        levelstr = "fatal";
        break;
    default:
        break;
    }
    auto str = format_->Format(levelstr,log,file,line);
    output_->OutPut(str);
}

