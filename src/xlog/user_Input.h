#pragma once
#include "xlog.h"
#include <map>
#include <functional>
#include <string>

class XLOG_API UserInput
{
public:
	void Start(std::function<void(std::vector<std::string>)>Init_ =
		[](std::vector<std::string>) {});
	
	void Stop() { is_exit_ = true; }

	UserInput& Reg(std::string key,
		std::function<void(const std::string&)>func) {
		keys_func_[key] = func;
		return *this;
	}

	UserInput& RegTask(std::string key,
		std::function<void()>func) {
		task_func_[key] = func;
		return *this;
	}
private:
	bool is_exit_{ false };

	//回调函数
	std::map<std::string,
		std::function<void(const std::string&)>
	> keys_func_;

	//初始化函数
	//std::function<void()>Init_;
	
	//任务回调函数
	std::map<std::string,
		std::function<void()>
	> task_func_;
};

