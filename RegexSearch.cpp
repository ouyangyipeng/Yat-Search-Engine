#include "RegexSearch.h"
#include <iostream>
#include <regex>

void RegexSearch::regexQuery(const std::vector<std::string> &sentences, const std::string &pattern)
{
    try
    {
        std::regex regexPattern(pattern);
        std::cout << "正则查询结果 \"" << pattern << "\":" << std::endl;
        bool found = false;

        for (const auto &sentence : sentences)
        {
            std::smatch match;
            if (std::regex_search(sentence, match, regexPattern))
            {
                std::cout << "\t" << sentence << "." << std::endl;
                found = true;
                size_t startPos = match.position();
                size_t length = match.length();
                std::string marker(sentence.size(), ' ');
                std::fill(marker.begin() + startPos, marker.begin() + startPos + length, '^');
                std::string a = "        ";
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
        std::cerr << "正则表达式错误: " << e.what() << std::endl;
    }
}
