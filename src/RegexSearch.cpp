#include "RegexSearch.h"
#include <iostream>
#include <regex>

// 之前研究编译的时候学过这个regex头文件，挺方便可以直接用
// https://en.cppreference.com/w/cpp/regex/regex_search，扔个网址在这里，查起来方便
void RegexSearch::regexQuery(const std::vector<std::string> &sentences, const std::string &pattern)
{
    try
    {
        std::regex regexPattern(pattern);
        std::cout << "正则查询结果 \"" << pattern << "\":" << std::endl;
        bool found = false;

        for (const auto &sentence : sentences)
        {
            std::smatch match; // regex头文件下有两种匹配类型，这个其实是和match results一样的
            if (std::regex_search(sentence, match, regexPattern)) // 这个函数返回的是bool值，所以可以直接用来判断
            {
                std::cout << "\t" << sentence << "." << std::endl;
                found = true;
                size_t startPos = match.position();
                size_t length = match.length();
                std::string marker(sentence.size(), ' '); // 又到了标准的可视化环节咯
                std::fill(marker.begin() + startPos, marker.begin() + startPos + length, '^'); 
                std::string a = "\t";
                marker.insert(0, a);
                std::cout << marker << std::endl;
            }
        }

        if (!found)
        {
            std::cout << "未找到正则匹配 \"" << pattern << "\" 的结果." << std::endl;
        }
    }
    catch (const std::regex_error &e)
    {
        std::cerr << "正则表达式错误: " << e.what() << std::endl; // 学到了，原来正则搜索的try catch格式是标准的
    }
}
