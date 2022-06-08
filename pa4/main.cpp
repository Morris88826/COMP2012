#include "linearProbingHashTable.h"
#include "quadraticProbingHashTable.h"
#include "doubleHashingHashTable.h"
#include "shop.h"

using namespace std;

int (*stringLength)(string, int) = [](string s, int m) { return (int)s.length() % m; };
int (*stringHash)(string, int) = [](string s, int m)
    {
        //this is an implementation of the hash function seen on p.29 of the hashing lecture notes
        //we are not going to explain it for you
        //consider understanding it part of your task
        //but note that it ignores letter cases intentionally, and assumes input consists of English characters only
        //we also assume the input string won't cause overflow for this function for all test cases
        //it should work for any string with no more than 6 characters
        int r=0;
        for(unsigned int i=0;i<s.length();i++)
            r = (s[i] - ((s[i]>='a')?'a':'A') + 1) + r*37;
        return r % m;
    };

//a convenient helper function to print various statistics
void printStats(HashTable* hashTable, bool activeCellCount, bool comparisonCount, bool clusterCount, bool largestClusterSize, bool clusterSizeList)
{
    if(activeCellCount)
        cout << "Active cell count = " << hashTable->getActiveCellCount() << endl;
    if(comparisonCount)
        cout << "Accumulated comparison count = " << hashTable->getAccumulatedComparisonCount() << endl;
    if(clusterCount)
        cout << "Cluster count = " << hashTable->getClusterCount() << endl;
    if(largestClusterSize)
        cout << "Largest cluster size = " << hashTable->getLargestClusterSize() << endl;
    if(clusterSizeList)
        cout << "Cluster size list = " <<  hashTable->getClusterSizeSortedList() << endl;
}

//a function to generate test cases for various tables; to be used in main()
void testCaseForTable(int tableNumber, int subCase)
{
    cout << "This is for table " << tableNumber << " sub-case " << subCase << endl;

    HashTable* hashTable;
    if(tableNumber <= 3 || tableNumber == 8)
        hashTable = new LinearProbingHashTable(3, stringLength);
    else if(tableNumber == 4 || tableNumber == 7)
        hashTable = new DoubleHashingHashTable(3, stringLength, stringHash);
    else if(tableNumber == 5)
        hashTable = new LinearProbingHashTable(7, stringLength);
    else if(tableNumber == 6)
        hashTable = new QuadraticProbingHashTable(3, stringLength);

    if(subCase == 0)
        hashTable->togglePrintSteps();

    if(tableNumber == 1) //test an empty table
    {
    }
    else if(tableNumber == 2) //test a table with two items at the beginning of the table
    {
        cout << "Add: " << hashTable->add(new Magic{"Fire", "A", 100, 10}) << endl;
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Cow", 300, 30}) << endl;
    }
    else if(tableNumber == 3) //test with a table "0: [Empty] | 1: [Deleted] | 2: [Empty]"
    {
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Ball", 100, 10}) << endl;
        cout << "Remove: " << hashTable->remove("Ball") << endl;
    }
    else if(tableNumber == 4) //test failed add
    {
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Fff", 100, 10}) << endl;
        Magic* magicThatCannotBeAdded = new Magic{"Fire", "Lll", 300, 30};
        cout << "Add: " << hashTable->add(magicThatCannotBeAdded) << endl;
        delete magicThatCannotBeAdded;
    }
    else if(tableNumber == 5) //test adding back to a deleted cell
    {
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Ball", 100, 10}) << endl;
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Wind", 200, 20}) << endl;
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Rain", 300, 30}) << endl;
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Void", 400, 40}) << endl;
        cout << "Remove: " << hashTable->remove("Rain") << endl;
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Doge", 999, 99}) << endl;
    }
    else if(tableNumber == 6) //test QuadraticProbingHashTable
    {
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Ball", 400, 10}) << endl;
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Cow", 300, 20}) << endl;
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Stone", 200, 30}) << endl;
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Duck", 100, 40}) << endl;
        cout << "Remove: " << hashTable->remove("Void") << endl;
        cout << "Remove: " << hashTable->remove("Duck") << endl;
        Magic* magic = hashTable->get("Void");
        cout << "Last function call returned " << ((magic==nullptr)?"nullptr":(magic->prefix+magic->suffix)) << endl;
    }
    else if(tableNumber == 7) //test DoubleHashingHashTable
    {
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Ball", 100, 40}) << endl;
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Cow", 200, 30}) << endl;
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Ant", 300, 20}) << endl;
        cout << "Add: " << hashTable->add(new Magic{"Fire", "Rock", 400, 10}) << endl;
        cout << "Remove: " << hashTable->remove("Void") << endl;
        cout << "Remove: " << hashTable->remove("Rock") << endl;
        Magic* magic = hashTable->get("Ant");
        cout << "Last function call returned " << ((magic==nullptr)?"nullptr":(magic->prefix+magic->suffix)) << endl;
    }
    else if(tableNumber == 8) //test rehashing multiple times
    {
        for(int i = 0; i < 10; i++)
        {
            string ballString = "Ball" + string(1, (char)(i+'a'));
            cout << "Add: " << hashTable->add(new Magic{"Fire", ballString, 100, 10}) << endl;
        }
    }

    hashTable->print();
    if(subCase == 1)
        printStats(hashTable, true, false, false, false, false);
    else if(subCase == 2)
        printStats(hashTable, false, true, false, false, false);
    else if(subCase == 3)
        printStats(hashTable, false, false, true, false, false);
    else if(subCase == 4)
        printStats(hashTable, false, false, false, true, false);
    else if(subCase == 5)
        printStats(hashTable, false, false, false, false, true);

    delete hashTable;
}

int main()
{
    cout << boolalpha; //to print true/false instead of 1/0

    cout << "Hi, computer wizard! Which test case do you want to run?" << endl;
    int testCase;
    cin >> testCase;
    
    // for(testCase=1;testCase<=67;testCase++)
    {
        cout << endl << "Test case " << testCase << ":" << endl;
        cout << "=============================================" << endl;

        if(testCase == 1) //example code used in "Hashing example" with possibly some additional output
        {
            HashTable* hashTable = new LinearProbingHashTable(3, stringLength);
            hashTable->print();
            printStats(hashTable, true, true, true, true, true);
            delete hashTable;
        }
        else if(testCase == 2) //example code used in "Hashing example" with possibly some additional output
        {
            HashTable* hashTable = new LinearProbingHashTable(3, stringLength);
            hashTable->togglePrintSteps();
            bool returnValue = hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            cout << "Last function call returned " << returnValue << endl;
            hashTable->print();
            printStats(hashTable, true, true, true, true, true);
            delete hashTable;
        }
        else if(testCase == 3) //example code used in "Hashing example" with possibly some additional output
        {
            HashTable* hashTable = new LinearProbingHashTable(3, stringLength);
            hashTable->togglePrintSteps();
            hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            bool returnValue = hashTable->add(new Magic{"Fire", "Wind", 200, 20});
            cout << "Last function call returned " << returnValue << endl;
            hashTable->print();
            printStats(hashTable, true, true, true, true, true);
            delete hashTable;
        }
        else if(testCase == 4) //example code used in "Hashing example" with possibly some additional output
        {
            HashTable* hashTable = new LinearProbingHashTable(3, stringLength);
            hashTable->togglePrintSteps();
            hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            hashTable->add(new Magic{"Fire", "Wind", 200, 20});
            bool returnValue = hashTable->add(new Magic{"Fire", "Storm", 300, 30});
            cout << "Last function call returned " << returnValue << endl;
            hashTable->print();
            printStats(hashTable, true, true, true, true, true);
            delete hashTable;
        }
        else if(testCase == 5) //example code used in "Hashing example" with possibly some additional output
        {
            HashTable* hashTable = new LinearProbingHashTable(3, stringLength);
            hashTable->togglePrintSteps();
            hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            hashTable->add(new Magic{"Fire", "Wind", 200, 20});
            hashTable->add(new Magic{"Fire", "Storm", 300, 30});
            bool returnValue = hashTable->add(new Magic{"Fire", "Ox", 400, 40});
            cout << "Last function call returned " << returnValue << endl;
            hashTable->print();
            printStats(hashTable, true, true, true, true, true);
            delete hashTable;
        }
        else if(testCase == 6) //example code used in "Hashing example" with possibly some additional output
        {
            HashTable* hashTable = new LinearProbingHashTable(3, stringLength);
            hashTable->togglePrintSteps();
            hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            hashTable->add(new Magic{"Fire", "Wind", 200, 20});
            hashTable->add(new Magic{"Fire", "Storm", 300, 30});
            hashTable->add(new Magic{"Fire", "Ox", 400, 40});
            bool returnValue = hashTable->remove("Void");
            cout << "Last function call returned " << returnValue << endl;
            hashTable->print();
            printStats(hashTable, true, true, true, true, true);
            delete hashTable;
        }
        else if(testCase == 7) //example code used in "Hashing example" with possibly some additional output
        {
            HashTable* hashTable = new LinearProbingHashTable(3, stringLength);
            hashTable->togglePrintSteps();
            hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            hashTable->add(new Magic{"Fire", "Wind", 200, 20});
            hashTable->add(new Magic{"Fire", "Storm", 300, 30});
            hashTable->add(new Magic{"Fire", "Ox", 400, 40});
            hashTable->remove("Void");
            bool returnValue = hashTable->remove("Ball");
            cout << "Last function call returned " << returnValue << endl;
            hashTable->print();
            printStats(hashTable, true, true, true, true, true);
            delete hashTable;
        }
        else if(testCase == 8) //example code used in "Hashing example" with possibly some additional output
        {
            HashTable* hashTable = new LinearProbingHashTable(3, stringLength);
            hashTable->togglePrintSteps();
            hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            hashTable->add(new Magic{"Fire", "Wind", 200, 20});
            hashTable->add(new Magic{"Fire", "Storm", 300, 30});
            hashTable->add(new Magic{"Fire", "Ox", 400, 40});
            hashTable->remove("Void");
            hashTable->remove("Ball");
            Magic* magic = hashTable->get("Void");
            cout << "Last function call returned " << ((magic==nullptr)?"nullptr":(magic->prefix+magic->suffix)) << endl;
            hashTable->print();
            printStats(hashTable, true, true, true, true, true);
            delete hashTable;
        }
        else if(testCase == 9) //example code used in "Hashing example" with possibly some additional output
        {
            HashTable* hashTable = new LinearProbingHashTable(3, stringLength);
            hashTable->togglePrintSteps();
            hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            hashTable->add(new Magic{"Fire", "Wind", 200, 20});
            hashTable->add(new Magic{"Fire", "Storm", 300, 30});
            hashTable->add(new Magic{"Fire", "Ox", 400, 40});
            hashTable->remove("Void");
            hashTable->remove("Ball");
            hashTable->get("Void");
            Magic* magic = hashTable->get("Wind");
            cout << "Last function call returned " << ((magic==nullptr)?"nullptr":(magic->prefix+magic->suffix)) << endl;
            hashTable->print();
            printStats(hashTable, true, true, true, true, true);
            delete hashTable;
        }

        else if(testCase == 10) //test stockUp (2 new items in the 2nd and last slot)
        {
            Shop* shop = new Shop(new LinearProbingHashTable(3, stringLength), new LinearProbingHashTable(3, stringLength), new LinearProbingHashTable(3, stringLength));
            cout << "Stock up: " << shop->stockUp("FireBall", 1, 100) << endl;
            cout << "Stock up: " << shop->stockUp("FireWind", 2, 200) << endl;
            shop->print();
            delete shop;
        }
        else if(testCase == 11) //test stockUp (add to an existing item)
        {
            Shop* shop = new Shop(new LinearProbingHashTable(3, stringLength), new LinearProbingHashTable(3, stringLength), new LinearProbingHashTable(3, stringLength));
            cout << "Stock up: " << shop->stockUp("FireBall", 1, 100) << endl;
            cout << "Stock up: " << shop->stockUp("FireWind", 2, 200) << endl;
            cout << "Stock up: " << shop->stockUp("FireWind", 3, 200) << endl;
            shop->print();
            delete shop;
        }
        else if(testCase == 12) //test stockUp (add to an existing item and change its price)
        {
            Shop* shop = new Shop(new LinearProbingHashTable(3, stringLength), new LinearProbingHashTable(3, stringLength), new LinearProbingHashTable(3, stringLength));
            cout << "Stock up: " << shop->stockUp("FireBall", 1, 100) << endl;
            cout << "Stock up: " << shop->stockUp("FireWind", 2, 200) << endl;
            cout << "Stock up: " << shop->stockUp("FireWind", 3, 200) << endl;
            cout << "Stock up: " << shop->stockUp("FireWind", 6, 999) << endl;
            shop->print();
            delete shop;
        }
        else if(testCase == 13) //test stockUp (for two tables)
        {
            Shop* shop = new Shop(new LinearProbingHashTable(3, stringLength), new LinearProbingHashTable(3, stringLength), new LinearProbingHashTable(3, stringLength));
            cout << "Stock up: " << shop->stockUp("FireBall", 1, 100) << endl;
            cout << "Stock up: " << shop->stockUp("FireWind", 2, 200) << endl;
            cout << "Stock up: " << shop->stockUp("FireWind", 3, 200) << endl;
            cout << "Stock up: " << shop->stockUp("FireWind", 6, 999) << endl;
            cout << "Stock up: " << shop->stockUp("IceBall", 1, 100) << endl;
            cout << "Stock up: " << shop->stockUp("IceWind", 2, 200) << endl;
            cout << "Stock up: " << shop->stockUp("IceWind", 3, 200) << endl;
            cout << "Stock up: " << shop->stockUp("IceWind", 6, 999) << endl;
            cout << "Stock up: " << shop->stockUp("IceStorm", 5, 500) << endl;
            shop->print();
            delete shop;
        }

        else if(testCase == 14) //test sell (more than enough stock)
        {
            Shop* shop = new Shop(new LinearProbingHashTable(3, stringLength), new LinearProbingHashTable(3, stringLength), new LinearProbingHashTable(3, stringLength));
            cout << "Stock up: " << shop->stockUp("IceWind", 5, 200) << endl;
            cout << "Stock up: " << shop->stockUp("IceStorm", 5, 500) << endl;
            cout << "Sell: " << shop->sell("IceWind", 2) << endl;
            shop->print();
            delete shop;
        }

        else if(testCase == 15) //test get
        {
            HashTable* hashTable = new LinearProbingHashTable(7, stringLength);
            hashTable->togglePrintSteps();
            hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            hashTable->add(new Magic{"Fire", "Wind", 200, 20});
            hashTable->add(new Magic{"Fire", "Storm", 300, 30});
            hashTable->add(new Magic{"Fire", "Ox", 400, 40});
            hashTable->remove("Ball");
            hashTable->print();
            Magic* magic = hashTable->get("Ball");
            cout << "Last function call returned " << ((magic==nullptr)?"nullptr":(magic->prefix+magic->suffix)) << endl;
            printStats(hashTable, false, true, false, false, false);
            delete hashTable;
        }
        else if(testCase == 16) //test get
        {
            HashTable* hashTable = new LinearProbingHashTable(7, stringLength);
            hashTable->togglePrintSteps();
            hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            hashTable->add(new Magic{"Fire", "Wind", 200, 20});
            hashTable->add(new Magic{"Fire", "Storm", 300, 30});
            hashTable->add(new Magic{"Fire", "Ox", 400, 40});
            hashTable->remove("Ball");
            hashTable->print();
            Magic* magic = hashTable->get("Wind");
            cout << "Last function call returned " << ((magic==nullptr)?"nullptr":(magic->prefix+magic->suffix)) << endl;
            printStats(hashTable, false, true, false, false, false);
            delete hashTable;
        }
        else if(testCase == 17) //test get
        {
            HashTable* hashTable = new LinearProbingHashTable(7, stringLength);
            hashTable->togglePrintSteps();
            hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            hashTable->add(new Magic{"Fire", "Wind", 200, 20});
            hashTable->add(new Magic{"Fire", "Storm", 300, 30});
            hashTable->add(new Magic{"Fire", "Ox", 400, 40});
            hashTable->remove("Ball");
            hashTable->print();
            Magic* magic = hashTable->get("Storm");
            cout << "Last function call returned " << ((magic==nullptr)?"nullptr":(magic->prefix+magic->suffix)) << endl;
            printStats(hashTable, false, true, false, false, false);
            delete hashTable;
        }
        else if(testCase == 18) //test get
        {
            HashTable* hashTable = new LinearProbingHashTable(7, stringLength);
            hashTable->togglePrintSteps();
            hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            hashTable->add(new Magic{"Fire", "Wind", 200, 20});
            hashTable->add(new Magic{"Fire", "Storm", 300, 30});
            hashTable->add(new Magic{"Fire", "Ox", 400, 40});
            hashTable->remove("Ball");
            hashTable->print();
            Magic* magic = hashTable->get("Ox");
            cout << "Last function call returned " << ((magic==nullptr)?"nullptr":(magic->prefix+magic->suffix)) << endl;
            printStats(hashTable, false, true, false, false, false);
            delete hashTable;
        }
        else if(testCase == 19) //test get
        {
            HashTable* hashTable = new LinearProbingHashTable(7, stringLength);
            hashTable->togglePrintSteps();
            hashTable->add(new Magic{"Fire", "Ball", 100, 10});
            hashTable->add(new Magic{"Fire", "Wind", 200, 20});
            hashTable->add(new Magic{"Fire", "Storm", 300, 30});
            hashTable->add(new Magic{"Fire", "Ox", 400, 40});
            hashTable->remove("Ball");
            hashTable->print();
            Magic* magic = hashTable->get("Rain");
            cout << "Last function call returned " << ((magic==nullptr)?"nullptr":(magic->prefix+magic->suffix)) << endl;
            printStats(hashTable, false, true, false, false, false);
            delete hashTable;
        }

        else //for the latter cases
        {
            testCaseForTable((testCase - 20) / 6 + 1, (testCase - 20) % 6);
        }
        

        cout << "=============================================" << endl;
    }

    return 0;
}