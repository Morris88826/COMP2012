#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "magic.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class HashTable 
{
protected:
    enum CellStatus
    {
        EMPTY, //empty cell
        ACTIVE, //active cell
        DELETED //deleted cell
    };

    struct Cell
    {
        Magic* magic; //pointer to the magic
        CellStatus status; //status of the cell
    };

    int m;
    int (*hash)(string, int);
    int activeCellCount;
    int comparisonCount;
    bool printSteps;

public:
    HashTable(int m, int (*hash)(string, int)) : m(m), hash(hash), activeCellCount(0), comparisonCount(0), printSteps(false) {}; 
    virtual ~HashTable() = default;
    void togglePrintSteps() {printSteps = !printSteps;};
    virtual bool add(Magic* magic) = 0;
    virtual bool remove(string key) = 0;
    virtual Magic* get(string key) = 0;
    virtual int getClusterCount() const = 0;
    virtual int getLargestClusterSize() const = 0;
    virtual string getClusterSizeSortedList() const = 0;
    int getActiveCellCount() const { return activeCellCount; };
    int getAccumulatedComparisonCount() const { return comparisonCount; };
    virtual void print() const = 0;
};

#endif // __HASHTABLE_H__