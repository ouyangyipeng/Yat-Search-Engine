# Yat-Search Engine 文本搜索引擎

> *Searching Engine from Sun Yat-sen University*

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/ouyangyipeng/Yat-Search-Engine/blob/main/LICENSE)
![Static Badge](https://img.shields.io/badge/Sun_Yat_sen-University-green)
![Static Badge](https://img.shields.io/badge/Ouyang-Yipeng-blue)
[![Forks](https://img.shields.io/github/forks/ouyangyipeng/Yat-Search-Engine)](https://github.com/ouyangyipeng/Yat-Search-Engine/network/members)
[![Stars](https://img.shields.io/github/stars/ouyangyipeng/Yat-Search-Engine)](https://github.com/ouyangyipeng/Yat-Search-Engine/stargazers)
[![Contributors](https://img.shields.io/github/contributors/ouyangyipeng/Yat-Search-Engine)](https://github.com/ouyangyipeng/Yat-Search-Engine/graphs/contributors)
[![Build Status](https://img.shields.io/github/actions/workflow/status/ouyangyipeng/Yat-Search-Engine/build.yml?branch=main)](https://github.com/ouyangyipeng/Yat-Search-Engine/actions)
[![Code Size](https://img.shields.io/github/languages/code-size/ouyangyipeng/Yat-Search-Engine)](https://github.com/ouyangyipeng/Yat-Search-Engine)
[![Top Language](https://img.shields.io/github/languages/top/ouyangyipeng/Yat-Search-Engine)](https://github.com/ouyangyipeng/Yat-Search-Engine)
[![Last Commit](https://img.shields.io/github/last-commit/ouyangyipeng/Yat-Search-Engine)](https://github.com/ouyangyipeng/Yat-Search-Engine/commits/main)

## 项目简介

Yat-Search Engine 是一个高效的文本搜索引擎，支持多文件加载、精确查询、模糊查询和正则表达式查询等功能。该项目旨在提供快速、准确的文本搜索解决方案，并具备持久化存储和日志记录功能，支持中文界面。

## 项目背景

中山大学计算机学院2024年秋季学期《数据结构与算法》课程大作业。

## 功能列表

- **多文件支持**：可加载多个文本文件进行搜索。
- **精确查询**：查找精确匹配的关键词。
- **模糊查询**：查找包含关键词的单词。
- **正则表达式查询**：基于正则表达式的高级搜索。
- **可视化搜索结果**：以类似编译器报错的方式展示匹配位置。
- **无限查询与退出功能**：支持持续查询，用户可随时退出。
- **持久化存储**：保存和加载搜索索引。
- **日志功能**：记录查询历史和操作日志。
- **支持中文输出**：正确显示中文字符。(还未完工)

## 项目结构

TextSearchEngine/

│

├── .vscode/  // VSCode 配置文件

│   ├── c_cpp_properties.json

│   ├── launch.json

│   ├── tasks.json

│   └── settings.json

├── source-text/  // 存放文本文件

│   ├── text1.txt

│   ├── text2.txt

│   └── ...  // 更多文本文件

├── log

│   └── query_log.txt  // 查询日志文件

├── logo&pic

│   ├── logo.txt  // 候选图标

│   └── logo_out.txt  // 项目图标

├── main.cpp   // 主程序入口

├── TextSearchEngine.h  // 搜索引擎头文件

├── TextSearchEngine.cpp   // 搜索引擎实现

├── RegexSearch.h // 正则表达式搜索头文件

└── RegexSearch.cpp  // 正则表达式搜索实现

## 功能改进过程(TODO)

### 基础功能

1. **哈希表包含查询**
   - **改进过程**：实现自定义哈希函数 `CustomHash`，并在 `TextSearchEngine` 中使用 `unordered_map` 结合该哈希函数，以优化查询性能。

2. **文件读取**
   - **改进过程**：完善文件读取机制，确保能够正确读取和解析多个文本文件，并将内容索引到搜索引擎中。

### 增添功能

1. **多文件支持** *(已完成)*
   - **改进过程**：修改 `main.cpp`，允许用户输入多个文件名，系统将逐一加载这些文件进行索引。

2. **支持正则表达** *(已完成)*
   - **改进过程**：新增 `RegexSearch` 类，使用 C++ `<regex>` 库实现基于正则表达式的查询功能，并在主菜单中添加相应选项。

3. **精确查询** *(已完成)*
   - **改进过程**：实现 `exactQuery` 方法，通过 `unordered_map` 高效查找精确匹配的关键词，并展示匹配结果。

4. **可视化搜索结果，如模仿编译器报错的方式** *(已完成)*
   - **改进过程**：在查询结果中，使用符号 `^` 标记关键词在句子中的位置，类似编译器的错误指示，增强可读性。

5. **无限查询,退出按钮** *(已完成)*
   - **改进过程**：在主循环中添加持续查询功能，用户可选择退出程序，确保用户体验的连贯性。

6. **新的哈希函数** *(已完成)*
   - **计划改进**：优化现有的 `CustomHash` 函数，提高哈希冲突的处理效率，以进一步提升查询性能。

7. **支持中文**
   - **计划改进**：扩展系统的本地化支持，添加多语言界面，提升中国用户的使用体验。

8. **性能优化与预处理** *(已完成)*
   - **改进过程**：优化索引结构和查询算法，减少搜索时间，并在加载文本时进行预处理，如去除停用词和统一大小写。

9. **用户界面** *(已完成)*
   - **改进过程**：设计简洁直观的命令行界面，引导用户完成文件加载和查询操作。

10. **持久化存储** *(已完成)*
    - **改进过程**：实现索引的保存与加载功能，避免每次启动程序时重新构建索引，提升启动速度。

11. **日志功能，记录查询历史等** *(已完成)*
    - **改进过程**：在每次查询和重要操作后，将相关信息记录到 `query_log.txt`，便于用户查看历史记录和调试。

12. **支持中文输出** *(已完成)*
    - **改进过程**：设置本地化环境，确保程序能够正确处理和显示中文字符，提升中文用户的使用体验。

## 使用方法

### 推荐方法 - 使用VSCode

本代码库已配置了 `.vscode` 文件夹，您可以克隆到本地后直接在 VSCode 中打开本项目。

需要注意的是，您需要安装mingW编译器，并在.vscode文件夹中的c_cpp_properties.json和task/launch的三个文件中修改g++等路径为您的mingW安装路径。

当您在vscode中安装了C/C++插件后，您可以直接在vscode中按F5运行本项目。这样生成的可执行文件为Output.exe。

### 编译项目(备选)

假如选择使用命令行进行编译，确保已安装支持 C++17 的编译器，如 `g++` 或 `clang++`。C++17以下的编译器可能无法编译成功。

```bash
g++ -std=c++17 main.cpp TextSearchEngine.cpp RegexSearch.cpp -o YatSearchEngine
// 编译生成YatSearchEngine.exe可执行文件
```

### 运行程序

将需要搜索的文本文件放入 source-text 文件夹中，确保文件以 .txt 格式保存。

### 操作步骤

启动程序：运行可执行文件后，程序将显示欢迎界面并提示按回车继续。

加载文件：根据提示输入要加载的文件，每次输入一个文件名（需以 .txt 结尾），输入 done 完成文件选择。

选择查询类型：

输入 1 进行精确查询。

输入 2 进行模糊查询。

输入 3 进行正则表达式查询。

输入 4 退出程序。

输入查询内容：根据选择的查询类型，输入相应的关键词或正则表达式。

查看结果：查询结果将显示匹配的句子及其位置标记。

退出程序：选择退出选项，程序将保存索引并记录日志后退出。

### 日志查看

查询操作日志保存在 query_log.txt 文件中，用户可通过文本编辑器查看历史查询记录和操作日志。

## 贡献

欢迎贡献代码和提出建议！请提交 Pull Request 或在 Issues 中反馈您的想法。

## 许可证

本项目采用 MIT 许可证。详情请参阅 LICENSE 文件。
