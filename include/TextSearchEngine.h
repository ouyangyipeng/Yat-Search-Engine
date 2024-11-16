#ifndef TEXTSEARCHENGINE_H
#define TEXTSEARCHENGINE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

struct CustomHash
{
    size_t operator()(const std::string &key) const
    {
        // 自定哈希表
        size_t hash = 0;
        for (char c : key)
        {
            hash = hash * 101 + c;
        }
        return hash;
    }
};

class TextSearchEngine
{
public:
    // 加载文本文件
    void loadTexts(const std::vector<std::string> &files);
    // 精确查询
    void exactQuery(const std::string &keyword);
    // 模糊查询
    void fuzzyQuery(const std::string &keyword);
    // 正则表达式查询
    void regexQuery(const std::string &pattern);
    // 获取句子
    const std::vector<std::string> &getSentences() const;
    // 持久化存储
    void saveIndex(const std::string &filename);
    void loadIndex(const std::string &filepath);

private:
    // 句子集合
    std::vector<std::string> sentences;
    // 使用自定义哈希函数
    std::unordered_map<std::string, std::vector<size_t>> exactIndex;

    // 索引句子
    void indexSentence(const std::string &sentence);
    // 可视化匹配
    void visualizeMatch(const std::string &sentence, const std::string &keyword);
};

#endif
