#include "MyHashTable.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

unsigned int MyHashTable::hash(const std::string &key) const
{
    unsigned int h = 5381;
    for (char c : key)
    {
        h = ((h << 5) + h) + c;
    }
    return h % table.size();
}

void MyHashTable::rehash()
{

    int newSize = getNextPrime(table.size() * 2);
    vector<Entry> newTable(newSize);
    for (unsigned int i = 0; i < table.size(); i++)
    {
        if (table[i].occupied)
        {
            int newHash = hash(table[i].acc.website); // !
            newTable[newHash] = table[i];
        }
    }
    table = newTable;
}

void MyHashTable::insert(const Account &acc)
{
    double loadFactor = 1.0 * (numElements + 1) / table.size(); // TODO
    if (loadFactor >= maxLoadFactor)
    {
        rehash();
    }
    int x = hash(acc.passwordHash);
    int i = 0;
    int M = table.size();
    int R = getLastPrime(M);
    int Pos = 0;
    if (hashMethod == 1)
    {
        do
        {
            Pos = (x + i) % M;
            i++;
        } while (table[Pos].occupied);
    }
    else if (hashMethod == 2)
    {
        do
        {
            Pos = (x + i * i) % M;
            i++;
        } while (table[Pos].occupied);
    }
    else if (hashMethod == 3)
    {
        do
        {
            Pos = (x + i * (R - x % R)) % M;
            i++;
        } while (table[Pos].occupied);
    }
    table[Pos].acc = acc;
    table[Pos].occupied = true;
    numElements++;
}

bool MyHashTable::login(const std::string &website, const std::string &username, const std::string &passwordHash) const
{
    int M = table.size();

    for (int i = 0; i < M; i++)
    {
        if (table[i].occupied && table[i].acc.website == website && table[i].acc.username == username && table[i].acc.passwordHash == passwordHash)
        {

            return true;
        }
    }

    return false;
}

void MyHashTable::listEntries() const
{

    int M = table.size();
    for (int i = 0; i < M; i++)
    {
        if (table[i].occupied)
        {
            cout << "Website: " << table[i].acc.website << "  " << "Benutzername: " << table[i].acc.username << endl;
        }
    }
}

int MyHashTable::getNextPrime(int x) const
{
    x = x + 1;
    bool found = true;
    while (true)
    {
        found = true;
        for (int i = 2; i <= sqrt(x); i++)
        {
            if (x % i == 0)
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return x;
        }
        x += 1;
    }
}

int MyHashTable::getLastPrime(int x) const
{
    x = x - 1;
    bool found = true;
    while (true)
    {
        found = true;
        for (int i = 2; i <= sqrt(x); i++)
        {
            if (x % i == 0)
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return x;
        }
        x -= 1;
    }
}