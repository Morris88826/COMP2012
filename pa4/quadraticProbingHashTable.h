#ifndef __QUADRATICPROBINGHASHTABLE_H__
#define __QUADRATICPROBINGHASHTABLE_H__

#include "openAddressingHashTable.h"

class QuadraticProbingHashTable : public OpenAddressingHashTable
{
protected:
    int hi(string k, int i) const override;

public:
    QuadraticProbingHashTable(int m, int (*hash)(string, int)); 
};

#endif // __QUADRATICPROBINGHASHTABLE_H__