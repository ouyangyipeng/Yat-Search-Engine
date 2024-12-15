# 指定 CMake 最低版本
cmake_minimum_required(VERSION 3.10)

# 项目名称和语言
project(YatSearchEngine LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(include)

# 源文件列表
set(SOURCES
    src/main.cpp
    src/TextSearchEngine.cpp
    src/RegexSearch.cpp
    src/oyyphash.cpp
)

# 添加可执行文件
add_executable(YatSearchEngine ${SOURCES})

# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

