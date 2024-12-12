#ifndef REGEXSEARCH_H
#define REGEXSEARCH_H

#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <fstream>
#include <iostream>

// 由于正则比较特殊，所以我把它分开来写，但在尝试写了之后发现比想象的简单些
class RegexSearch
{
public:
    // 构造函数
    RegexSearch(){
        try
        {
            std::locale::global(std::locale("zh_CN.UTF-8"));
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "无法设置区域设置 zh_CN.UTF-8: " << e.what() << std::endl;
            // 处理错误，例如设置为默认区域设置或退出程序
            std::locale::global(std::locale(""));
        }
    }
    // 正则查询
    static void regexQuery(const std::vector<std::string> &sentences, const std::string &pattern);
    // 中文正则查询
    static void chineseRegexQuery(const std::vector<std::string> &sentences, const std::string &pattern);
};

#endif
