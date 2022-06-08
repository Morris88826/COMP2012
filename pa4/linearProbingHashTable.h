#ifndef __LINEARPROBINGHASHTABLE_H__
#define __LINEARPROBINGHASHTABLE_H__

#include "openAddressingHashTable.h"

class LinearProbingHashTable : public OpenAddressingHashTable
{
protected:
    int hi(string k, int i) const override;

public:
    LinearProbingHashTable(int m, int (*hash)(string, int)); 
};

#endif // __LINEARPROBINGHASHTABLE_H__