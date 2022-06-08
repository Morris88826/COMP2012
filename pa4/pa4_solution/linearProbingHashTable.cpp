#include "linearProbingHashTable.h"

LinearProbingHashTable::LinearProbingHashTable(int m, int (*hash)(string, int)) : OpenAddressingHashTable(m, hash)
{ 
}

int LinearProbingHashTable::hi(string k, int i) const 
{
    return (hash(k, m) + i) % m;
}