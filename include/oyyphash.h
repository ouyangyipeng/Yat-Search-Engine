#ifndef OYYPHASH_H
#define OYYPHASH_H

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

struct oyypHash
{
    size_t operator()(const std::string &key) const
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
    HashTable(size_t size = 1024);
    void insert(const std::string &key, size_t value);
    std::vector<size_t> find(const std::string &key) const;
    void remove(const std::string &key, size_t value); // 新增移除方法
    size_t size() const;
    void clear();
    std::vector<size_t>& operator[](const std::string &key);
    
    // 自定义迭代器
    class iterator {
    public:
        // 构造函数
        iterator(HashTable* table, size_t bucket, size_t index);
        
        // 解引用操作
        std::pair<const std::string, std::vector<size_t>>& operator*() const;
        std::pair<const std::string, std::vector<size_t>>* operator->() const;
        
        // 递增操作
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
    
    iterator begin();
    iterator end();

private:
    std::vector<std::vector<std::pair<const std::string, std::vector<size_t>>>> table;
    oyypHash hasher;
    size_t bucket_count;
    size_t element_count; // 新增成员变量用于跟踪元素数量
};

#endif // OYYPHASH_H
