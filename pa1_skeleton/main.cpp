#include "polynomial.h"
#include <iostream>
using namespace std;

int main()
{    
    int testCase = 1;
    // cout << "Hello! Which test case do you want to run? ";
    // cin >> testCase;
    for(;testCase<=22;testCase++)
    {
        cout << endl << "Test case " << testCase << ":" << endl;
        cout << "===================================" << endl;

        if(testCase == 1) //test the print function with the pre-made polynomials
        {
            for(int i=1; i<=4; i++)
            {
                Polynomial p(i);
                cout << "Polynomial " << i << ": \"";
                p.print();
                cout << "\"";
                cout << endl;
            }
        }
        else if(testCase == 2) //test the print function with the pre-made polynomials
        {
            for(int i=5; i<=7; i++)
            {
                Polynomial p(i);
                cout << "Polynomial " << i << ": \"";
                p.print();
                cout << "\"";
                cout << endl;
            }
        }
        else if(testCase == 3) //test the print function with the pre-made polynomials
        {
            for(int i=8; i<=15; i++)
            {
                Polynomial p(i);
                cout << "Polynomial " << i << ": \"";
                p.print();
                cout << "\"";
                cout << endl;
            }
        }

        else if(testCase == 4) //test the default constructor
        {
            Polynomial p;
            cout << "\"";
            p.print();
            cout << "\"";
        }
        
        else if(testCase == 5) //test the deep copy constructor
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(*p1);
            delete p1;
            cout << "\ncopy of p1: \"";
            p2->print();
            cout << "\"";
            delete p2;
        }

        else if(testCase == 6) //test the array constructor
        {                   
            int arr[1] = {3};
            Polynomial* p1 = new Polynomial(arr, 1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            delete p1;
        }
        else if(testCase == 7) //test the array constructor
        {
            int arr[2] = {3, 4};
            Polynomial* p1 = new Polynomial(arr, 2);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            delete p1;
        }
        else if(testCase == 8) //test the array constructor
        {
            int arr[4] = {0, 0, 3, 0};
            Polynomial* p1 = new Polynomial(arr, 4);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            delete p1;
        }

        else if(testCase == 9) //test add
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(2);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->add(*p2);
            cout << "\np1+p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        else if(testCase == 10) //test add
        {
            Polynomial* p1 = new Polynomial(3);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(4);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->add(*p2);
            cout << "\np1+p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        else if(testCase == 11) //test add
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(5);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->add(*p2);
            cout << "\np1+p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        
        else if(testCase == 12) //test subtract
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(2);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->subtract(*p2);
            cout << "\np1-p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        else if(testCase == 13) //test subtract
        {
            Polynomial* p1 = new Polynomial(3);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(4);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->subtract(*p2);
            cout << "\np1-p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        else if(testCase == 14) //test subtract
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(5);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->subtract(*p2);
            cout << "\np1-p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }

        else if(testCase == 15) //test multiply
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(2);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->multiply(*p2);
            cout << "\np1*p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        else if(testCase == 16) //test multiply
        {
            Polynomial* p1 = new Polynomial(3);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(4);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->multiply(*p2);
            cout << "\np1*p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        else if(testCase == 17) //test multiply
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(5);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            Polynomial p3 = p1->multiply(*p2);
            cout << "\np1*p2: \"";
            p3.print();
            cout << "\"";
            delete p1;
            delete p2;
        }
        

        else if(testCase == 18) //test evaluate
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            cout << "\np1(2): ";
            cout << p1->evaluate(2);
            delete p1;
        }
        else if(testCase == 19) //test evaluate
        {
            Polynomial* p1 = new Polynomial(8);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            cout << "\np1(2): ";
            cout << p1->evaluate(2);
            delete p1;
        }

        else if(testCase == 20) //test compare
        {
            Polynomial* p1 = new Polynomial(1);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(2);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            cout << "\ncompare p1 and p2: ";
            cout << p1->compare(*p2);
            cout << "\ncompare p2 and p1: ";
            cout << p2->compare(*p1);
            delete p1;
            delete p2;
        }
        else if(testCase == 21) //test compare
        {
            Polynomial* p1 = new Polynomial(3);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(4);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            cout << "\ncompare p1 and p2: ";
            cout << p1->compare(*p2);
            cout << "\ncompare p2 and p1: ";
            cout << p2->compare(*p1);
            delete p1;
            delete p2;
        }
        else if(testCase == 22) //test compare
        {
            Polynomial* p1 = new Polynomial(5);
            cout << "p1: \"";
            p1->print();
            cout << "\"";
            Polynomial* p2 = new Polynomial(5);
            cout << "\np2: \"";
            p2->print();
            cout << "\"";
            cout << "\ncompare p1 and p2: ";
            cout << p1->compare(*p2);
            cout << "\ncompare p2 and p1: ";
            cout << p2->compare(*p1);
            delete p1;
            delete p2;
        }        

        cout << endl << "===================================" << endl;
    }

    return 0;
}