#ifndef __DOUBLEHASHINGHASHTABLE_H__
#define __DOUBLEHASHINGHASHTABLE_H__

#include "openAddressingHashTable.h"

class DoubleHashingHashTable : public OpenAddressingHashTable
{
private:
    int (*hash2)(string, int); 

protected:
    int hi(string k, int i) const override;

public:
    DoubleHashingHashTable(int m, int (*hash)(string, int), int (*hash2)(string, int));
};

#endif // __DOUBLEHASHINGHASHTABLE_H__