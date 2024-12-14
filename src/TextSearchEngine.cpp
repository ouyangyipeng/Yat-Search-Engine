#include "TextSearchEngine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <cctype>
#include <locale>


// 保存已经查询过的句子到index.dat文件里，和下面的load对应
// 主要是想提升加载速度设置的dat文件
void TextSearchEngine::saveIndex(const std::string &filepath)
{
    std::ofstream out(filepath, std::ios::binary);
    out.imbue(std::locale());
    if (!out.is_open())
    {
        std::ofstream logFile("../log/query_log.txt", std::ios::app);
        logFile << "无法打开文件以保存索引: " << filepath << std::endl;
        logFile.close();
        return;
    }
    // 保存句子数量
    size_t sentenceCount = sentences.size();
    out.write(reinterpret_cast<char *>(&sentenceCount), sizeof(sentenceCount)); // 使用reinterpret_cast主要是为了解决指针类型转换的问题
    // 保存每个句子
    for (const auto &sentence : sentences)
    {
        size_t length = sentence.size();
        out.write(reinterpret_cast<char *>(&length), sizeof(length));
        out.write(sentence.c_str(), length);
    }
    // 保存索引大小
    size_t indexSize = exactIndex.size();
    out.write(reinterpret_cast<char *>(&indexSize), sizeof(indexSize));
    // 保存每个索引项
    for (const auto &pair : exactIndex)
    {
        size_t keyLen = pair.first.size();
        out.write(reinterpret_cast<char *>(&keyLen), sizeof(keyLen));
        out.write(pair.first.c_str(), keyLen);
        size_t vecSize = pair.second.size();
        out.write(reinterpret_cast<char *>(&vecSize), sizeof(vecSize));
        for (auto idx : pair.second)
        {
            out.write(reinterpret_cast<char *>(&idx), sizeof(idx));
        }
    }
    out.close();
    std::ofstream logFile("../log/query_log.txt", std::ios::app);
    logFile << "索引已保存到 " << filepath << std::endl;
    logFile.close();
}

// 加载索引，也是从dat文件里加载
void TextSearchEngine::loadIndex(const std::string &filepath)
{

    std::ifstream in(filepath, std::ios::binary);// 二进制打开
    in.imbue(std::locale());
    if (!in.is_open()) // 如果没打开就在log报个错
    {
        std::ofstream logFile("../log/query_log.txt", std::ios::app);
        logFile << "无法打开索引文件: " << filepath << std::endl;
        logFile.close();
        return;
    }
    // 清空当前数据
    sentences.clear();
    exactIndex.clear();
    // 读取句子数量
    size_t sentenceCount;
    in.read(reinterpret_cast<char *>(&sentenceCount), sizeof(sentenceCount));
    // 读取每个句子
    for (size_t i = 0; i < sentenceCount; ++i)
    {
        size_t length;
        in.read(reinterpret_cast<char *>(&length), sizeof(length));
        std::string sentence(length, ' ');
        in.read(&sentence[0], length);
        sentences.push_back(sentence);
    }
    // 读取索引大小
    size_t indexSize;
    in.read(reinterpret_cast<char *>(&indexSize), sizeof(indexSize));


    // 读取每个索引项（核心步骤 !!!!）
    for (size_t i = 0; i < indexSize; ++i)
    {
        size_t wordLength;
        in.read(reinterpret_cast<char *>(&wordLength), sizeof(wordLength));
        std::string word(wordLength, ' ');
        in.read(&word[0], wordLength);
        size_t vecSize;
        in.read(reinterpret_cast<char *>(&vecSize), sizeof(vecSize));
        std::vector<size_t> sentVec; // 将 std::vector<std::string> 修改为 std::vector<size_t>
        for (size_t j = 0; j < vecSize; ++j)
        {
            size_t sentIdx;
            in.read(reinterpret_cast<char *>(&sentIdx), sizeof(sentIdx));
            sentVec.push_back(sentIdx); // 将 sentVec.push_back(sent) 修改为 sentVec.push_back(sentIdx)
        }
        exactIndex[word] = sentVec; // 每一个要索引的单词都放进哈希表
    }
    in.close();
    std::ofstream logFile("../log/query_log.txt", std::ios::app);
    logFile << "索引已从 " << filepath << " 加载" << std::endl;
    logFile.close();
}

// 这个预处理各个文件的核心要义就是分隔，多文件→单文件→段落（行）→句子→词，这里四层循环导致加载文件这步时间复杂度最高
// （后面实测也确实是最久的，不过发现即使加载许多百万字小说也没有耗时特别久，不超过0.5s，已经是很满意的速度了）
// 其中要注意全变小写（之前因为这个漏掉了很多）
void TextSearchEngine::loadTexts(const std::vector<std::string> &files)
{

    for (const auto &file : files) // 支持打开多个文件了
    {
        std::ifstream infile(file);
        infile.imbue(std::locale());
        if (!infile)
        {
            std::cout << "无法打开目标文件: " << file << std::endl; // 输出错误信息
            std::ofstream logFile("../log/query_log.txt", std::ios::app);
            logFile << "无法打开目标文件: " << file << std::endl; // 同时在log里面也记上
            logFile.close();
            continue; // 如果打不开就跳过
        }

        std::string line;// 每次读一行，或叫一段
        while (std::getline(infile, line))
        {
            std::stringstream ss(line);
            std::string sentence;
            // 使用正则表达式分割句子，分隔符为 '.' 或 '。'(在中文版里新增了这个分隔符)
            std::regex re(u8"[。.]");// 定义分隔（中途发现不显示规定u8会有时候乱码）
            std::sregex_token_iterator iter(line.begin(), line.end(), re, -1);// 查regex类的时候才发现这玩意这么好使
            std::sregex_token_iterator end;
            while (iter != end)
            {
                sentence = *iter; // 一句一句的读，最后面要自增
                if (!sentence.empty())
                {
                    sentences.push_back(sentence); // 句子放进句子列表
                    // 索引精确查询
                    std::string word;
                    for (auto &c : sentence) // 最开始把分隔字母想复杂了，后面发现其实就是sentence里面空格隔开，用auto遍历都行
                    {
                        if (std::isalnum(c)) // 检查是字母or数字（中文and符号就不用变了）
                            word += std::tolower(c);
                        else if (!word.empty())
                        {
                            exactIndex[word].push_back(sentences.size() - 1);
                            word.clear();
                        }
                    }
                    if (!word.empty())
                        exactIndex[word].push_back(sentences.size() - 1);
                }
                ++iter; // 这个迭代器的自增比我想的方便点
            }
        }
    }
}

void TextSearchEngine::indexSentence(const std::string &sentence)
{
    std::istringstream ss(sentence);
    std::string word;
    // 逐词读取句子内容
    while (ss >> word)
    {
        // 将单词转换为小写
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        exactIndex[word].push_back(sentences.size() - 1); // 将 index[word].push_back(sentence) 修改为 exactIndex[word].push_back(sentences.size() - 1)
    }
}

void TextSearchEngine::exactQuery(const std::string &keyword)
{
    std::string key = keyword;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    auto it = exactIndex.find(key);
    if (it != exactIndex.end())
    {
        std::cout << "精确查询结果 \"" << keyword << "\":" << std::endl;
        for (auto idx : it->second)
        {
            const std::string &sentence = sentences[idx];
            std::cout << "\t" << sentence << std::endl;

            // 标出关键字的位置
            // std::string::size_type pos = sentence.find(keyword);
            // if (pos != std::string::npos)
            // {
            //     std::cout << "\t" << std::string(pos, ' ') << std::string(keyword.length(), '^') << std::endl;
            // }
            size_t pos = sentence.find(keyword);
            if (pos != std::string::npos)
            {
                std::string marker(sentence.size(), ' ');
                std::fill(marker.begin() + pos, marker.begin() + pos + keyword.length(), '^');
                std::cout << "\t" << marker << std::endl;
            }
        }
    }
    else
    {
        std::cout << "未找到关键字 \"" << keyword << "\" 的结果。" << std::endl;
    }
}

void TextSearchEngine::fuzzyQuery(const std::string &keyword)
{
    std::cout << "模糊查询结果 \"" << keyword << "\":" << std::endl;
    bool found = false;
    for (size_t i = 0; i < sentences.size(); ++i)
    {
        if (sentences[i].find(keyword) != std::string::npos)
        {
            std::cout << "\t" << sentences[i] << "." << std::endl;
            found = true;
            size_t pos = sentences[i].find(keyword);
            if (pos != std::string::npos)
            {
                std::string marker(sentences[i].size(), ' ');
                std::fill(marker.begin() + pos, marker.begin() + pos + keyword.length(), '^');
                std::cout << "\t" << marker << std::endl;
            }
        }
    }
    if (!found)
    {
        std::cout << "未找到模糊匹配 \"" << keyword << "\" 的结果." << std::endl;
    }
    // 记录日志
    std::ofstream logFile("../log/query_log.txt", std::ios::app);
    logFile << "模糊查询: " << keyword << " 执行完成" << std::endl;
    logFile.close();
}

void TextSearchEngine::chineseQuery(const std::string &keyword)
{
    std::cout << "中文查询结果 \"" << keyword << "\":" << std::endl;
    bool found = false;
    for (size_t i = 0; i < sentences.size(); ++i)
    {
        if (sentences[i].find(keyword) != std::string::npos)
        {
            std::cout << "\t" << sentences[i] << "。" << std::endl;
            found = true;
            size_t pos = sentences[i].find(keyword);
            // if (pos != std::string::npos)
            // {
            //     std::string marker(sentences[i].size(), ' ');
            //     std::string::iterator ch1 = (marker.begin() + pos);
            //     std::string::iterator ch2 = (marker.begin() + pos + keyword.length());
            //     std::fill(marker.begin() + pos, marker.begin() + pos + keyword.length(), '^');
            //     std::cout << "\t" << marker << std::endl;
            // }
        }
    }
    if (!found)
    {
        std::cout << "未找到中文匹配 \"" << keyword << "\" 的结果." << std::endl;
    }
    // 记录日志
    std::ofstream logFile("../log/query_log.txt", std::ios::app);
    logFile << "中文查询: " << keyword << " 执行完成" << std::endl;
    logFile.close();
}

void TextSearchEngine::visualizeMatch(const std::string &sentence, const std::string &keyword)
{
    size_t pos = sentence.find(keyword);
    // 如果句子中包含关键字
    if (pos != std::string::npos)
    {
        // 创建一个与句子等长的标记字符串
        std::string marker(sentence.size(), ' ');
        // 将标记字符串中关键字的位置替换为'^'
        std::fill(marker.begin() + pos, marker.begin() + pos + keyword.size(), '^');
        std::string a = "\t";
        marker.insert(0, a);
        std::cout << marker << std::endl;
    }
}

const std::vector<std::string> &TextSearchEngine::getSentences() const
{
    return sentences; // 返回回句子列表
}
