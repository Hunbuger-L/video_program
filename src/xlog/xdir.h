#pragma once
#include "xlog.h"
#include <string>
#include <vector>
/// <summary>
/// 目录处理，默认c++17
/// </summary>
struct XLOG_API XFile
{
    std::string name;
    std::string path;
    std::string ext;
};
class XLOG_API XDir
{
public:
    /// <summary>
    /// 获取path目录下的所有文件
    /// </summary>
    /// <param name="path">读取的目录文件</param>
    /// <returns>目录文件列表</returns>
    std::vector<XFile> GetFiles(const std::string& path);
    static bool IsDir(const std::string& path);
    static bool Create(const std::string& path);
};