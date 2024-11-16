#include "TextSearchEngine.h"
#include "RegexSearch.h"
#include <iostream>
#include <limits>
#include <locale>
#include <fstream>
#include <vector>
#include <string>
#include <codecvt>

/*
    ! 基础功能:
    (done)TODO:哈希表包含查询
    (done)TODO:文件读取

    ? 增添功能:
    (done)TODO:多文件支持
    (done)TODO:支持正则表达
    (done)TODO:精确查询
    (done)TODO:可视化搜索结果，如模仿编译器报错的方式
    (done)TODO:无限查询,退出按钮
    (done)TODO:新的哈希函数
    TODO:支持中文文件
    (done)TODO:性能优化与预处理
    (done)TODO:用户界面
    (done)TODO:持久化存储
    (done)TODO:日志功能，记录查询历史等
    (done)TODO:支持中文输出
*/

int main()
{
    // TODO: 支持中文输入输出 未完成
    // 设置本地化以支持中文输入输出
    // std::wcin.imbue(std::locale("zh_CN.UTF-8"));
    // std::wcout.imbue(std::locale("zh_CN.UTF-8"));

    std::ifstream infile("./logo&pic/logo_out.txt");
    if (infile.is_open())
    {
        std::string line;
        while (std::getline(infile, line))
        {
            std::cout << line << std::endl;
        }
        infile.close();
    }
    else
    {
        std::cerr << "无法打开logo文件。" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "欢迎使用Yat-Search Engine文本搜索引擎！" << std::endl;
    std::cout << "作者：Fernandez Owen  版本：v1.3.0" << std::endl;
    std::cout << "-----------------------------重要说明-------------------------------" << std::endl;
    std::cout << "1. 本程序使用预加载上一次查询的index.dat文件来加速搜索，每次使用请确认您是否跟上次查询的文件一致，如果一致则可以直接运行程序，否则请先删除index.dat文件再运行程序。" << std::endl;
    std::cout << "2. 请确保您的源文件夹中的文件名不包含空格，否则可能会导致程序无法正常运行。" << std::endl;
    std::cout << "3. 请将需要查询的源文件放入source-text文件夹中，以txt形式存放。" << std::endl;
    std::cout << "--------------------------请按回车以继续-----------------------------" << std::endl;
    std::cin.get();

    std::ofstream logFile("./log/query_log.txt", std::ios::app);
    TextSearchEngine engine;

    // 加载 source-text 文件夹中的多个文件
    std::vector<std::string> files;
    std::string filename;
    while (true)
    {
        std::cout << "请问您要查找哪些文件？输入文件名（.txt），输入 'done' 完成输入：";
        std::cin >> filename;

        if (filename == "done")
        {
            break;
        }

        // 检查文件扩展名是否为 .txt
        if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt")
        {
            std::cout << "无效的文件扩展名，请确保文件以 .txt 结尾。\n";
            continue;
        }

        std::string filepath = "source-text/" + filename;
        std::cout << "已添加文件: " << filepath << "\n";

        std::ifstream file(filepath);
        if (!file.is_open())
        {
            std::cout << "无法打开文件: " << filepath << "。请检查是否放入目标文件夹。\n";
            continue;
        }
        files.push_back(filepath);
    }

    if (files.empty())
    {
        std::cout << "未选择任何文件，程序即将退出。\n";
        return 0;
    }

    engine.loadTexts(files);

    std::cout << "欢迎使用文本搜索引擎！\n";
    std::cout << "功能说明：\n1. 精确查询:输入一个单词，查询在什么位置出现了这个单词\n2. 模糊查询:输入为一个单词中有,输出该词组所在的句子和位置\n3. 正则查询:按照正则表达式规则进行匹配\n4. 退出查询：退出程序\n";

    bool running = true;

    while (running)
    {
        int choice;
        bool validInput;

        do
        {
            std::cout << "请选择查询类型(1-4):";
            std::cin >> choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                validInput = false;
            }
            else
            {
                validInput = (choice >= 1 && choice <= 4);
            }

            if (!validInput)
            {
                std::cout << "无效选项，请重试。\n";
            }
        } while (!validInput);

        std::string input;
        switch (choice)
        {
        case 1:
            std::cout << "输入关键词: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, input);
            engine.exactQuery(input);
            logFile << "精确查询: " << input << std::endl;
            break;
        case 2:
            std::cout << "输入关键词: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, input);
            engine.fuzzyQuery(input);
            logFile << "模糊查询: " << input << std::endl;
            break;
        case 3:
            std::cout << "输入正则表达式: ";
            std::cin.ignore();
            std::getline(std::cin, input);
            RegexSearch::regexQuery(engine.getSentences(), input);
            logFile << "正则查询: " << input << std::endl;
            break;
        case 4:
            running = false;
            engine.saveIndex("index.dat");
            logFile << "退出程序" << std::endl;
            break;
        default:
            std::cout << "无效选项，请重试。\n";
        }
    }
    std::cout << "感谢使用Yat-Search Engine！\n";
    logFile.close();
    return 0;
}