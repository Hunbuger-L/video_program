#pragma once
#include <memory>
#include "xtask.h"
class XVideoInput
{
public:
	void Start(std::unique_ptr<XTask>task);
private:
	void RunTask(XTask& task, const XTask::Data& data);
};

