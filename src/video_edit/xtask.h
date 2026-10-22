#pragma once
#include <String>

class XTask {
public:
	struct Data 
	{
		std::string type;
		std::string src;
		std::string out;
		std::string password;
		bool is_enc{ true };
		int begin_sec{ 0 };
		int end_sec{ 0 };
	};

	virtual bool Start(const Data& para) = 0;

	virtual int Progess() = 0;

	virtual int TotalSec() = 0;
	
	virtual bool Running() = 0;

	virtual void Clear() = 0;
};