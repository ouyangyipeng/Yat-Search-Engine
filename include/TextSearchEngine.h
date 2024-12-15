#ifndef TEXTSEARCHENGINE_H
#define TEXTSEARCHENGINE_H

#include <string>
#include <vector>
// #include <unordered_map>
#include <functional>
#include <locale>
#include <codecvt>
#include <fstream>
#include <iostream>
#include "oyyphash.h"

// struct oyypHash
// {
//     size_t operator()(const std::string &key) const
//     {
//         // 我在网上查到这个 FNV-1a 哈希算法分布均匀，冲突率低，并且计算速度快
//         const size_t fnv_prime = 0x100000001b3;
//         const size_t fnv_offset_basis = 0xcbf29ce484222325;
//         size_t hash = fnv_offset_basis;
//         for (char c : key)
//         {
//             hash ^= static_cast<size_t>(c);
//             hash *= fnv_prime;
//         }
//         return hash;
//     }
// };

class TextSearchEngine
{
public:
    TextSearchEngine(){
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
    // 加载文本文件
    void loadTexts(const std::vector<std::string> &files);
    // 精确查询
    void exactQuery(const std::string &keyword);
    // 模糊查询
    void fuzzyQuery(const std::string &keyword);
    // 正则表达式查询（现在已经单独开了一个文件）
    // void regexQuery(const std::string &pattern);
    // 中文查询
    void chineseQuery(const std::string &keyword);
    // 获取句子
    const std::vector<std::string> &getSentences() const;
    // 持久化存储
    void saveIndex(const std::string &filename);
    void loadIndex(const std::string &filepath);

private:
    // 句子集合
    std::vector<std::string> sentences;
    // 使用自定义哈希函数
    // std::unordered_map<std::string, std::vector<size_t>, oyypHash> exactIndex; // 才知道这个哈希函数自定义是这样使用，放在第三个参数中

    // 自定义哈希表oyyphash
    HashTable exactIndex;


    // 索引句子
    // void indexSentence(const std::string &sentence);
    // 可视化匹配（但是有一部分现在直接挪到查找函数里面去了）
    // void visualizeMatch(const std::string &sentence, const std::string &keyword);
};

#endif
