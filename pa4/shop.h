#ifndef __SHOP_H__
#define __SHOP_H__

#include "hashTable.h"

class Shop
{
private:
    int profit;
    HashTable* fireTable;
    HashTable* iceTable;
    HashTable* lightningTable;

    HashTable* getTable(string prefix) const;

public:
    Shop(HashTable* fireTable, HashTable* iceTable, HashTable* lightningTable);
    ~Shop();
    bool stockUp(string name, int quantity, int price) const; 
    bool sell(string name, int quantity);

    //given; do NOT modify
    void print() const
    {
        cout << "Shop accumulated Profit = $" << profit << endl;
        cout << "************ Fire table: ************" << endl;
        fireTable->print();
        cout << "************ Ice table: ************" << endl;
        iceTable->print();
        cout << "************ Lightning table: ************" << endl;
        lightningTable->print();
    }
};

#endif // __SHOP_H__