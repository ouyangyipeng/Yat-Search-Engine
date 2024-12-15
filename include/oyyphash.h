#ifndef OYYPHASH_H
#define OYYPHASH_H

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

struct oyypHash
{
    size_t operator()(std::string &key) const
    {
        // 我在网上查到这个 FNV-1a 哈希算法分布均匀冲突率低，并且计算速度快
        const size_t fnv_prime = 0x100000001b3;
        const size_t fnv_offset_basis = 0xcbf29ce484222325;
        size_t hash = fnv_offset_basis;
        for (char c : key)
        {
            hash ^= static_cast<size_t>(c);
            hash *= fnv_prime;
        }
        return hash;
    }
};

class HashTable {
public:
    HashTable(size_t size = 1024); // 默认大小1024
    // void insert(std::string &key, size_t value);
    // std::vector<size_t> find(std::string &key) const;
    // void remove(std::string &key, size_t value);
    // 这几个函数是之前的，因为tse文件里面已经改啦，所以这里已经用不着了

    // 要把原先在unordered_map里面用到过的函数全都实现一遍
    size_t size() const;
    void clear();
    std::vector<size_t>& operator[](std::string &key);
    
    // 这个是全部里面最麻烦的部分 去网上查了很久才搞懂咋自定义
    // 迭代器在原本unordered_map里面被使用的情况比我想的还要多
    // 我甚至写tse文件的时候都没意识到for循环里面auto迭代就是用的迭代器
    // 并里面必须实现begin和end函数 不然没法自动
    class iterator {
    public:
        // 构造函数
        iterator(HashTable* table, size_t bucket, size_t index);
        
        // 解引用操作 这个在精确查询里面用到了
        std::pair<std::string, std::vector<size_t>>& operator*() const;
        std::pair<std::string, std::vector<size_t>>* operator->() const;

        // 递增操作 其实好像原本代码没有用到 我记得用到的是regex里面那个自增
        iterator& operator++();
        iterator operator++(int);
        
        // 比较操作
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    
    private:
        HashTable* table;
        size_t current_bucket;
        size_t current_index;
        void advance();
    };
    
    // 这是自动for的时候用到的
    iterator begin();
    iterator end();

private:
    std::vector<std::vector<std::pair<std::string, std::vector<size_t>>>> table;
    // 这里改了很多遍 因为它本身应该是一个pair从string映射到vector<size_t>的 但是因为它每一个key对应的位置会有很多个 这时我本来就要把它给输出出来 所以不如直接变成一个vector再for迭代一次（参考tse）
    // 最外层的vector是用来处理哈希冲突的
    oyypHash hasher; // 自定义哈希函数
    size_t bucket_count; // 跟踪桶数量
    size_t element_count; // 跟踪元素数量
};

#endif
