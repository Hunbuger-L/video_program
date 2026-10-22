#pragma once
#include "xtask.h"
#include "xexec.h"
class FFtask :public XTask
{
public:
	bool Start(const Data& prara)override;

	int Progess() { return progess_; }
	
	int TotalSec()override { return total_sec; }

	bool Running() override { return exec_.Running(); }

	virtual void Clear()
	{
		total_sec = 0;
		progess_ = 0;

	}
private:
		int total_sec = { 0 };
		int progess_ = { 0 };
		XExec exec_;
};

