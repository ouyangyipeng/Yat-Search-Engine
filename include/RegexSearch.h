#ifndef REGEXSEARCH_H
#define REGEXSEARCH_H

#include <string>
#include <vector>

class RegexSearch
{
public:
    static void regexQuery(const std::vector<std::string> &sentences, const std::string &pattern);
};

#endif
