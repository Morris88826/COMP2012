#include "openAddressingHashTable.h"


OpenAddressingHashTable::OpenAddressingHashTable(int m, int (*hash)(string, int)) : HashTable(m, hash)
{
    table = new Cell[m];
    for(int i=0;i<m;i++)
    {
        table[i].magic = nullptr;
        table[i].status = CellStatus::EMPTY;
    }
}

OpenAddressingHashTable::~OpenAddressingHashTable()
{
    for(int i=0;i<m;i++)
        delete table[i].magic;
    delete [] table;
}

bool OpenAddressingHashTable::add(Magic* magic)
{ 
    string key = magic->suffix;
    if(printSteps)
        cout << "hash(\"" << key << "\") = " << hash(key, m) << endl;

    if(activeCellCount > 0.5*m) //if over-load (before insertion)
        performRehashing();

    string name = magic->prefix+magic->suffix;
    for(int i=0; i<m; i++)
    {
        int h = hi(key, i);
        comparisonCount++;
        if(table[h].status != CellStatus::ACTIVE) //can reuse deleted cells
        {
            if(printSteps)
                cout << name << " added at cell " << h << endl;
            table[h].magic = magic;
            table[h].status = CellStatus::ACTIVE;
            activeCellCount++;
            return true;
        }
        else if(printSteps) 
            cout << name << " collided at cell " << h << endl;
    }
    
    if(printSteps) 
        cout << name << " cannot be added" << endl;
    return false; 
}

bool OpenAddressingHashTable::remove(string key)
{
    if(printSteps)
        cout << "hash(\"" << key << "\") = " << hash(key, m) << endl;

    for(int i=0; i<m; i++)
    {
        int h = hi(key, i);

        comparisonCount++;
        if(table[h].status == CellStatus::ACTIVE && table[h].magic->suffix == key)
        {
            if(printSteps) 
                cout << table[h].magic->prefix+table[h].magic->suffix << " removed at cell " << h << endl;
            delete table[h].magic;
            table[h].magic = nullptr;
            table[h].status = CellStatus::DELETED;
            activeCellCount--;
            return true;
        }
        else if(printSteps)
            cout << "visited cell " << h << " but could not find it" << endl;
        
        if(table[h].status == CellStatus::EMPTY)
            break;
    }

    if(printSteps)
        cout << key << " cannot be removed" << endl;
    return false;
}

Magic* OpenAddressingHashTable::get(string key) 
{
    if(printSteps)
        cout << "hash(\"" << key << "\") = " << hash(key, m) << endl;

    for(int i=0; i<m; i++)
    {
        int h = hi(key, i);

        comparisonCount++;
        if(table[h].status == CellStatus::ACTIVE && table[h].magic->suffix == key)
        {
            if(printSteps) 
                cout << table[h].magic->prefix+table[h].magic->suffix << " found at cell " << h << endl;
            return table[h].magic;
        }
        else if(printSteps)
            cout << "visited cell " << h << " but could not find it" << endl;
        
        if(table[h].status == CellStatus::EMPTY)
            break;
    }

    if(printSteps)
        cout << key << " cannot be found" << endl;
    return nullptr;
}

int OpenAddressingHashTable::getClusterCount() const 
{
    //Well we just copied the code from getClusterSizeSortedList and modified 
    //NOTE: a shorter solution may be written by using the approach we hinted in the Piazza forum - it is very easy to "fix" the answer by decreasing it by 1 when the first and last cell connect
    //NOTE: another approach may be first finding an empty slot, and we start from there, and go around the whole table once (i.e. until we reach the same index) 
    //NOTE: there are so many alternatives really... :) This is an interesting general problem!
 
    int count = 0;
    int lastIndex = m - 1;
    bool inCluster = false; //track if we are currently in a cluster, so we know when a new cluster is met

    //if we have a cluster starting from cell 0, we want to find the part of it that is at the end of the table first
    int i=0;
    if(table[0].status==CellStatus::ACTIVE)
    {
        count++;
        inCluster = true;
        while(lastIndex>0 && table[lastIndex].status==CellStatus::ACTIVE)
            lastIndex--;
        i++;
    }

    for(; i<=lastIndex; i++)
        if(table[i].status==CellStatus::ACTIVE)
        {
            if(!inCluster)
            {
                inCluster = true;
                count++;
            }
        }
        else
            inCluster = false;

    return count;
}

int OpenAddressingHashTable::getLargestClusterSize() const 
{
    string list = getClusterSizeSortedList();
    if(list == "(empty)")
        return 0;
    else
    {
        //find the first comma or endl
        size_t endPos = list.find(",");
        if(endPos == string::npos)
            endPos = list.length();
        return atoi(list.substr(0, endPos).c_str());
    }
}

//my own helper function
string arrayToString(int array[], int size) 
{
    if(size == 0)
        return "(empty)";
    string s;
    for(int i=0; i<size; i++)
    {
        s+=std::to_string(array[i]);  
        if(i!=size-1)
            s+=",";
    }
    return s;
}

string OpenAddressingHashTable::getClusterSizeSortedList() const 
{
    int count = getClusterCount();
    if(count == 0)
        return "(empty)";
    int* result = new int[count]; 
    for(int i=0; i<count; i++)
        result[i] = 0;

    int lastClusterIndex = -1;
    int lastIndex = m - 1;
    bool inCluster = false; //track if we are currently in a cluster, so we know when a new cluster is met

    //if we have a cluster starting from cell 0, we want to find the part of it that is at the end of the table first
    int i=0;
    if(table[0].status==CellStatus::ACTIVE)
    {
        inCluster = true;
        lastClusterIndex++;
        result[lastClusterIndex]+=1;
        while(lastIndex>0 && table[lastIndex].status==CellStatus::ACTIVE)
        {
            result[lastClusterIndex]+=1;
            lastIndex--;
        }
        i++;
    }

    for(; i<=lastIndex; i++)
    {
        if(table[i].status==CellStatus::ACTIVE)
        {
            if(!inCluster)
            {
                inCluster = true;
                lastClusterIndex++;
            }
            result[lastClusterIndex]+=1;
        }
        else
            inCluster = false;
    }

    //sort the list
    for(int i=0; i<count; i++)
    {
        for(int j=i+1; j<count; j++)
        {
            if(result[i]<result[j])
            {
                int temp = result[j];
                result[j] = result[i];
                result[i] = temp;
            }
        }
    }    

    string resultString = arrayToString(result, count);
    delete [] result;

    return resultString;
}

void OpenAddressingHashTable::performRehashing()
{
    if(printSteps)
            cout << "Rehashing is needed!" << endl;
    Cell* oldTable = table;
    int oldM = m;
    m = m*2; //in practice, we should find a prime close to this value
    table = new Cell[m];
    for(int i=0;i<m;i++)
    {
        table[i].magic = nullptr;
        table[i].status = CellStatus::EMPTY;
    }
    activeCellCount = 0;
    
    //add from the start of the old table array
    //note: for simplicity, you can assume no addition failure during the rehashing process
    for(int i=0;i<oldM;i++)
        if(oldTable[i].status == CellStatus::ACTIVE)
            if(!add(oldTable[i].magic))
                cout << "SHOULD NOT HAPPEN BY ASSUMPTION >.<!" << endl;
    delete [] oldTable;
    if(printSteps)
        cout << "Rehashing is done!" << endl;
}
