#ifndef REGEXSEARCH_H
#define REGEXSEARCH_H

#include <string>
#include <vector>

// 由于正则比较特殊，所以我把它分开来写，但在尝试写了之后发现比想象的简单些
class RegexSearch
{
public:
    static void regexQuery(const std::vector<std::string> &sentences, const std::string &pattern);
};

#endif
