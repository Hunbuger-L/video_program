#include "log_fac.h"
#include "log_console_output.h"

#include "log_file_output.h"
#include "xlogformat.h"
#include "x_log_conf.h"
#include "xml_format.h"
#define LOGFILE "log.txt"
#include <iostream>
using namespace std;
void LogFac::Init(
    const std::string& con_file)
{
    XLogConf conf;
    bool re = conf.Read(con_file);
    string log_type = "console";
    string log_file = LOGFILE;
    string log_level = "debug";
    string log_format = "xlog";
    if (re)
    {
        log_type = conf.Get("log_type");
        log_file = conf.Get("log_file");
        log_level = conf.Get("log_level");
        log_format = conf.Get("log_format");
    }

    if(log_format == "xlog")
        logger_.setFormat(make_unique<XLogFormat>());
    else if(log_format == "xml")
        logger_.setFormat(make_unique<XmlFormat>());


    if (log_level == "info")
    {
        logger_.setLevel(XLog::INFO);
    }
    else if (log_level == "error")
    {
        logger_.setLevel(XLog::ERROR);

    }
    else if (log_level == "fatal")
    {
        logger_.setLevel(XLog::FATAL);
    }

    if (log_type == "file")
    {
        if (log_file.empty())
        {
            log_file = LOGFILE;
        }
        auto fout = make_unique<LogFileOutPut>();
        if (!fout->Open(log_file))
        {
            cerr << "open file failed "
                << log_file << endl;
        }
        logger_.setOutPut(move(fout));
    }
    else
    {
        logger_.setOutPut(
           make_unique<LogConsoleOutPut>());
    }
}