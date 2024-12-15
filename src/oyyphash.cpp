#include "oyyphash.h"
#include <algorithm>

HashTable::HashTable(size_t size) : bucket_count(size), table(size), element_count(0) {
    // 初始化哈希表
}

void HashTable::insert(const std::string &key, size_t value) {
    size_t hash = hasher(key);
    size_t index = hash % bucket_count;
    for (auto &pair : table[index]) {
        if (pair.first == key) {
            pair.second.push_back(value);
            return;
        }
    }
    table[index].emplace_back(key, std::vector<size_t>{value});
    element_count++;
}

std::vector<size_t> HashTable::find(const std::string &key) const {
    size_t hash = hasher(key);
    size_t index = hash % bucket_count;
    for (const auto &pair : table[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    return {};
}

void HashTable::remove(const std::string &key, size_t value) {
    size_t hash = hasher(key);
    size_t index = hash % bucket_count;
    for (auto &pair : table[index]) {
        if (pair.first == key) {
            auto it = std::find(pair.second.begin(), pair.second.end(), value);
            if (it != pair.second.end()) {
                pair.second.erase(it);
                // 如果该键下没有值了，可以选择移除键
                if (pair.second.empty()) {
                    table[index].erase(std::remove(table[index].begin(), table[index].end(), pair), table[index].end());
                    element_count--;
                }
            }
            return;
        }
    }
}

size_t HashTable::size() const {
    return element_count;
}

void HashTable::clear() {
    for(auto &bucket : table) {
        bucket.clear();
    }
    element_count = 0;
}

std::vector<size_t>& HashTable::operator[](const std::string &key) {
    size_t hash = hasher(key);
    size_t index = hash % bucket_count;
    for (auto &pair : table[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    table[index].emplace_back(key, std::vector<size_t>());
    element_count++;
    return table[index].back().second;
}

// iterator 构造函数
HashTable::iterator::iterator(HashTable* table, size_t bucket, size_t index)
    : table(table), current_bucket(bucket), current_index(index) {}

// 解引用操作
std::pair<const std::string, std::vector<size_t>>& HashTable::iterator::operator*() const {
    return table->table[current_bucket][current_index];
}

std::pair<const std::string, std::vector<size_t>>* HashTable::iterator::operator->() const {
    return &table->table[current_bucket][current_index];
}

// 递增操作
HashTable::iterator& HashTable::iterator::operator++() {
    advance();
    return *this;
}

HashTable::iterator HashTable::iterator::operator++(int) {
    iterator temp = *this;
    advance();
    return temp;
}

void HashTable::iterator::advance() {
    if (current_bucket >= table->table.size()) return;
    current_index++;
    while (current_bucket < table->table.size()) {
        if (current_index < table->table[current_bucket].size()) {
            return;
        }
        current_bucket++;
        current_index = 0;
    }
}

// 比较操作
bool HashTable::iterator::operator==(const iterator& other) const {
    return table == other.table &&
           current_bucket == other.current_bucket &&
           current_index == other.current_index;
}

bool HashTable::iterator::operator!=(const iterator& other) const {
    return !(*this == other);
}

HashTable::iterator HashTable::begin() {
    for (size_t i = 0; i < table.size(); ++i) {
        if (!table[i].empty()) {
            return iterator(this, i, 0);
        }
    }
    return end();
}

HashTable::iterator HashTable::end() {
    return iterator(this, table.size(), 0);
}
