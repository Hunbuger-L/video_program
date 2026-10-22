#pragma once
#ifdef _WIN32
	#ifdef XLOG_EXPORTS
	#define XLOG_API __declspec(dllexport)
	#else
	#define XLOG_API __declspec(dllimport)
	#endif
#else
#define XLOG_API
#endif 


// 此类是从 dll 导出的
class XLOG_API Cxlog {
public:
	Cxlog(void);
	// TODO: 在此处添加方法。
};
