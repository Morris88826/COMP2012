#ifndef __OPENADDRESSINGHASHTABLE_H__
#define __OPENADDRESSINGHASHTABLE_H__

#include "hashTable.h"
#include <iostream>

using std::cout;
using std::endl;

class OpenAddressingHashTable : public HashTable
{
protected:
    Cell* table;
    virtual int hi(string k, int i) const = 0;

public:
    OpenAddressingHashTable(int m, int (*hash)(string, int)); 
    ~OpenAddressingHashTable(); 

	//given; do not modify
    void print() const override
    {
        for(int i=0; i<m; i++)
        {
            cout << i << ": ";
            if(table[i].status == CellStatus::ACTIVE)
                cout << "[Active](key=" << table[i].magic->suffix << ";hash=" << hash(table[i].magic->suffix, m) << ";name=" << table[i].magic->prefix + table[i].magic->suffix << ";price=$" << table[i].magic->price << ";quantity=" << table[i].magic->quantity << ")";
            else if(table[i].status == CellStatus::EMPTY)
                cout << "[Empty]";
            else if(table[i].status == CellStatus::DELETED)
                cout << "[Deleted]";
            if(i!=m-1) 
                cout << " | ";
        }
        cout << endl;
    }

    bool add(Magic* magic) override;
    bool remove(string key) override;
    Magic* get(string key) override;
    int getClusterCount() const override; 
    int getLargestClusterSize() const override; 
    string getClusterSizeSortedList() const override; 

private:
    void performRehashing(); 
};

#endif // __OPENADDRESSINGHASHTABLE_H__