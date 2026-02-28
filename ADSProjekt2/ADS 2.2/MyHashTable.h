#pragma once
#include <string>
#include <vector>


struct Account {
    std::string username;
    std::string passwordHash;
    std::string website;
};

class MyHashTable {
private:
    
    struct Entry {
        Account acc;
        bool occupied = false;
    };
    std::vector<Entry> table;
    int numElements;
    int hashMethod;
    double maxLoadFactor = 0.6;

    unsigned int hash(const std::string& key) const;
    void rehash();
public:
    MyHashTable(int size = 8, int hashMethod_ = 1) : table(size), numElements(0), hashMethod(hashMethod_) {}
    void insert(const Account& acc);
    bool login(const std::string& website, const std::string& username, const std::string& passwordHash) const;
    void listEntries() const;
    int getNextPrime(int x) const;
    int getLastPrime(int x) const;
};