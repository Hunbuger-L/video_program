#pragma once
#include "xlog.h"
#include <string>
#include <queue>
#include <functional>
#include <future>
#include <mutex>

class XLOG_API XExec
{
public:
	bool Start(const char* cmd,
		std::function<void(const std::string&)>func = nullptr);

	//判断是否运行
	bool Running() { return running_; };

	//获取输出
	bool GetOutPut(std::string &out_);

	bool Wait() { return fut_.get(); }
private:
	
	bool running_ = false;
	
	//消息缓冲队列
	std::queue<std::string>outs_;
	
	//任务执行线程
	std::future<bool> fut_;
	
	//加锁
	std::mutex mux_;
};

