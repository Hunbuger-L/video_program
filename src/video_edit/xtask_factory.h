#pragma once
#include "xtask.h"
#include <memory>

class XTaskFactory
{
public:
	static std::unique_ptr<XTask> Creat(int type = 0);
};

