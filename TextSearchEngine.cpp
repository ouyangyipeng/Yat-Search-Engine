#include "TextSearchEngine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <cctype>

void TextSearchEngine::saveIndex(const std::string &filepath)
{
    std::ofstream out(filepath, std::ios::binary);
    if (!out.is_open())
    {
        std::ofstream logFile("./log/query_log.txt", std::ios::app);
        logFile << "无法打开文件以保存索引: " << filepath << std::endl;
        logFile.close();
        return;
    }
    // 保存句子数量
    size_t sentenceCount = sentences.size();
    out.write(reinterpret_cast<char *>(&sentenceCount), sizeof(sentenceCount));
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
    std::ofstream logFile("./log/query_log.txt", std::ios::app);
    logFile << "索引已保存到 " << filepath << std::endl;
    logFile.close();
}

void TextSearchEngine::loadIndex(const std::string &filepath)
{
    std::ifstream in(filepath, std::ios::binary);
    if (!in.is_open())
    {
        std::ofstream logFile("./log/query_log.txt", std::ios::app);
        logFile << "无法打开索引文件: " << filepath << std::endl;
        logFile.close();
        return;
    }
    // 清空当前数据
    sentences.clear();
    exactIndex.clear(); // 将 index.clear() 修改为 exactIndex.clear()
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
    // 读取每个索引项
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
        exactIndex[word] = sentVec; // 将 index[word] 修改为 exactIndex[word]
    }
    in.close();
    std::ofstream logFile("./log/query_log.txt", std::ios::app);
    logFile << "索引已从 " << filepath << " 加载" << std::endl;
    logFile.close();
}

void TextSearchEngine::loadTexts(const std::vector<std::string> &files)
{
    for (const auto &file : files)
    {
        std::ifstream infile(file);
        if (!infile)
        {
            std::cerr << "无法打开文件: " << file << std::endl;
            continue;
        }

        std::string line;
        while (std::getline(infile, line))
        {
            sentences.push_back(line);
            // 索引精确查询
            std::string word;
            for (auto &c : line)
            {
                if (std::isalnum(c))
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
            std::cout << "\t" << sentences[idx] << "." << std::endl;
            // 可视化匹配位置
            size_t pos = sentences[idx].find(keyword);
            if (pos != std::string::npos)
            {
                std::string marker(sentences[idx].size(), ' ');
                std::fill(marker.begin() + pos, marker.begin() + pos + keyword.length(), '^');
                std::cout << "       " << marker << std::endl;
            }
        }
    }
    else
    {
        std::cout << "未找到精确匹配 \"" << keyword << "\" 的结果." << std::endl;
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
                std::cout << "       " << marker << std::endl;
            }
        }
    }
    if (!found)
    {
        std::cout << "未找到模糊匹配 \"" << keyword << "\" 的结果." << std::endl;
    }
    // 记录日志
    std::ofstream logFile("./log/query_log.txt", std::ios::app);
    logFile << "模糊查询: " << keyword << " 执行完成" << std::endl;
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
        std::string a = "        ";
        marker.insert(0, a);
        std::cout << marker << std::endl;
    }
}

const std::vector<std::string> &TextSearchEngine::getSentences() const
{
    return sentences; // 返回句子列表
}
