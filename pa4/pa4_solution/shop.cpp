#include "shop.h"
#include <iostream>
#include <cctype> //hint: you may use the isupper function in it
using std::cout;
using std::endl;

Shop::Shop(HashTable* fireTable, HashTable* iceTable, HashTable* lightningTable) : profit(0), fireTable(fireTable), iceTable(iceTable), lightningTable(lightningTable)
{
}

Shop::~Shop()
{
    delete fireTable;
    delete iceTable;
    delete lightningTable;
}

HashTable* Shop::getTable(string prefix) const
{
    if(prefix == "Fire")
        return fireTable;
    else if(prefix == "Ice")
        return iceTable;
    else // if(prefix == "Lightning")
        return lightningTable;
}

//my own helper function
void splitString(string input, string& prefix, string& suffix)
{
    int splitPosition = 1;
    while(!isupper(input[splitPosition]))
        splitPosition++;
    prefix = input.substr(0, splitPosition);
    suffix = input.substr(splitPosition, input.length());
}

bool Shop::stockUp(string name, int quantity, int price) const
{
    string prefix, suffix;
    splitString(name, prefix, suffix);
    HashTable* table = getTable(prefix);

    Magic* m = table->get(suffix);
    if(m)
    {
        m->quantity += quantity;
        m->price = price;
        return true;
    }
    else
    {
        Magic* magic = new Magic{prefix, suffix, price, quantity};
        if(!table->add(magic))
        {
            delete magic;
            return false;
        }
        else
            return true;
    }
}

bool Shop::sell(string name, int quantity)
{
    string prefix, suffix;
    splitString(name, prefix, suffix);
    HashTable* table = getTable(prefix);

    Magic* m = table->get(suffix);
    if(m)
    {
        if(m->quantity >= quantity)
        {
            profit += quantity * m->price;
            if(quantity == m->quantity)
                table->remove(suffix);
            else
                m->quantity -= quantity;
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
