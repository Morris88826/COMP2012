#include <iostream>
#include <string>
#include "smartptr.h"
#include "graph.h"

#define __ALL_TESTS

using namespace std;

int main(int argc, char** argv) {
    cout << boolalpha;
    #ifdef __ALL_TESTS
    for ( int testCase = 1; testCase <= 27; ++testCase )
    #else
    int testCase;
    if ( argc > 1 )
        testCase = stoi(argv[1]);
    else {
        cout << "Select test case: ";
        cin >> testCase;
    }
    #endif
    {
        cout << "Test case " << testCase << ":\n===================================\n";
        if ( testCase == 1 ) {
            SmartPtr<int> sp {42};
            cout << "sp: " << sp << "\n";
        }
        else if ( testCase == 2 ) {
            SmartPtr<double> sp1 {3.14};
            cout << "sp1: " << sp1 << "\n\n";
            SmartPtr<double> sp2 {sp1};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
        }
        else if ( testCase == 3 ) {
            SmartPtr<double> sp1 {3.14};
            SmartPtr<double> sp2 {0.};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n\n";
            sp1 = sp2;
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n\n";
            sp1 = sp2 = SmartPtr<double>{};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
        }
        else if ( testCase == 4 ) {
            SmartPtr<int> sp1;
            SmartPtr<int> sp2 {42};
            SmartPtr<int> sp3 {sp2};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp3: " << sp3 << "\n\n";
            sp1.set(43);
            sp2.set(0);
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp3: " << sp3 << "\n";
        }
        else if ( testCase == 5 ) {
            SmartPtr<int> sp1 {42};
            SmartPtr<int> sp2 {sp1};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n\n";
            sp1.unset();
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
        }
        else if ( testCase == 6 ) {
            SmartPtr<double> sp1;
            cout << "sp1: " << sp1 << "\n";
            cout << "sp1.is_null(): " << sp1.is_null() << "\n\n";
            SmartPtr<double> sp2 {3.14};
            cout << "sp2: " << sp2 << "\n";
            cout << "sp2.is_null(): " << sp2.is_null() << "\n";
        }
        else if ( testCase == 7 ) {
            SmartPtr<string> sp1;
            SmartPtr<string> sp2;
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp1 == sp2: " << ( sp1 == sp2 ) << "\n";
            cout << "sp1 != sp2: " << ( sp1 != sp2 ) << "\n\n";
            sp1.set("Hello");
            sp2.set("Hello");
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp1 == sp2: " << ( sp1 == sp2 ) << "\n";
            cout << "sp1 != sp2: " << ( sp1 != sp2 ) << "\n\n";
            sp1 = sp2;
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp1 == sp2: " << ( sp1 == sp2 ) << "\n";
            cout << "sp1 != sp2: " << ( sp1 != sp2 ) << "\n\n";
            sp2.unset();
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp1 == sp2: " << ( sp1 == sp2 ) << "\n";
            cout << "sp1 != sp2: " << ( sp1 != sp2 ) << "\n";
        }
        else if ( testCase == 8 ) {
            SmartPtr<int> sp1 {42};
            SmartPtr<int> sp2 {sp1};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "*sp1: " << *sp1 << "\n\n";
            *sp1 = 0;
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
        }
        else if ( testCase == 9 ) {
            SmartPtr<string> sp;
            cout << "sp: " << sp << "\n";
            cout << "sp.operator->(): " << sp.operator->() << "\n\n";
            sp.set("Hello World");
            cout << "sp: " << sp << "\n";
            cout << "sp->size(): " << sp->size() << "\n";
        }
        else if ( testCase == 10 ) {
            SmartPtr<string> sp1 {string("Hello")};
            SmartPtr<double> sp2 {3.14};
            cout << "sp1: " << sp1;
            cout << "\nsp2: " << sp2;
            SmartPtr<string> sp3 {sp1};
            cout << "\n\nsp3: " << sp3;
            cout << "\n";
        }
        else if ( testCase == 11 ) {
            SmartPtr<SmartPtr<double>> sp1 {SmartPtr<double>{3.14}};
            SmartPtr<SmartPtr<double>> sp2 {sp1};
            SmartPtr<double> sp3 {*sp1};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp3: " << sp3 << "\n\n";
            **sp1 = 2.72;
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp3: " << sp3 << "\n\n";
            *sp1 = SmartPtr<double>{3.14};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp3: " << sp3 << "\n\n";
            sp2.set(SmartPtr<double>{0.});
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp3: " << sp3 << "\n\n";
        }
        else if ( testCase == 12 ) {
            Node<int> n {42};
            cout << "n: " << n << "\n";
        }
        else if ( testCase == 13 ) {
            Node<double> n1 {3.14};
            cout << "n1: " << n1 << "\n";
            Node<double> n2 {n1};
            cout << "n2: " << n2 << "\n";
        }
        else if ( testCase == 14 ) {
            Node<string> n1 {"Hello"};
            const Node<string> n2 {"World"};
            cout << "*n1: " << *n1 << "\n";
            cout << "*n2: " << *n2 << "\n\n";
            *n1 = *n2;
            cout << "*n1: " << *n1 << "\n";
            cout << "*n2: " << *n2 << "\n";
        }
        else if ( testCase == 15 ) {
            Node<int> n {0};
            SmartPtr<Node<int>> np1 {new_node(1)};
            SmartPtr<Node<int>> np2 {new_node(2)};
            SmartPtr<Node<int>> np3 {new_node(3)};
            n.add(np1);
            n.add(np2);
            n.add(np3);
            n.remove(np2);
            cout << "n: " << n << "\n";
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "np3: " << np3 << "\n\n";
            cout << "n.degree(): " << n.degree() << "\n";
            cout << "n.size(): " << n.size() << "\n";
        }
        else if ( testCase == 16 ) {
            Node<int> n {0};
            SmartPtr<Node<int>> np1 {new_node(1)};
            SmartPtr<Node<int>> np2 {new_node(2)};
            SmartPtr<Node<int>> np3 {new_node(3)};
            n.add(np1);
            n.add(np2);
            n.add(np3);
            n.remove(np2);
            cout << "n: " << n << "\n";
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "np3: " << np3 << "\n\n";
            cout << "n[0]: " << n[0] << "\n";
            cout << "n[1]: " << n[1] << "\n";
            cout << "n[2]: " << n[2] << "\n";
        }
        else if ( testCase == 17 ) {
            SmartPtr<Node<int>> np1 {new_node(1)};
            SmartPtr<Node<int>> np2 {new_node(2)};
            SmartPtr<Node<int>> np3 {new_node(3)};
            {
                Node<int> n {0};
                n.add(np1);
                n.add(np2);
                n.add(np3);
                cout << "n: " << n << "\n";
                cout << "np1: " << np1 << "\n";
                cout << "np2: " << np2 << "\n";
                cout << "np3: " << np3 << "\n\n";
            }
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "np3: " << np3 << "\n";
        }
        else if ( testCase == 18 ) {
            Node<int> n {0};
            SmartPtr<Node<int>> np1 {new_node(1)};
            SmartPtr<Node<int>> np2 {new_node(2)};
            SmartPtr<Node<int>> np3 {new_node(3)};
            n.add(np1);
            n.add(np2);
            n.add(np3);
            cout << "n: " << n << "\n";
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "np3: " << np3 << "\n\n";
            n.remove(np3);
            cout << "n: " << n << "\n";
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "np3: " << np3 << "\n\n";
            n.remove(np3);
            n.remove(SmartPtr<Node<int>>{});
            cout << "n: " << n << "\n";
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "np3: " << np3 << "\n";
        }
        else if ( testCase == 19 ) {
            Node<double> n {0.};
            SmartPtr<Node<double>> np1 {new_node(3.14)};
            SmartPtr<Node<double>> np2 {new_node(2.72)};
            n.add(np1);
            cout << "n: " << n << "\n";
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "n.exists(np1): " << n.exists(np1) << "\n";
            cout << "n.exists(np2): " << n.exists(np2) << "\n";
        }
        else if ( testCase == 20 ) {
            Node<string> n {string{"Hello"}};
            SmartPtr<Node<string>> np {new_node(string{"World"})};
            n.add(np);
            cout << "n: " << n << "\n";
            cout << "np: " << np << "\n";
            cout << "n.find(\"Hello\"): " << n.find("Hello") << "\n";
            cout << "n.find(\"World\"): " << n.find("World") << "\n";
        }
        else if ( testCase == 21 ) {
            SmartPtr<Node<double>> n {new_node(3.14)};
            cout << "n: " << n << "\n";
            cout << "*n: " << *n << "\n";
        }
        else if ( testCase == 22 ) {
            SmartPtr<Node<int>> n1 {new_node(1)};
            SmartPtr<Node<int>> n2 {new_node(2)};
            SmartPtr<Node<int>> n3 {new_node(3)};
            SmartPtr<Node<int>> n4 {new_node(4)};
            add_edge(n1, n2);
            add_edge(n2, n3);
            add_edge(n3, n4);
            add_edge(n4, n1);
            cout << "n1: " << n1 << "\n";
            cout << "n2: " << n2 << "\n";
            cout << "n3: " << n3 << "\n";
            cout << "n4: " << n4 << "\n\n";
            remove_node(n1);
            cout << "n1: " << n1 << "\n";
            cout << "n2: " << n2 << "\n";
            cout << "n3: " << n3 << "\n";
            cout << "n4: " << n4 << "\n\n";
            remove_node(n2);
            cout << "n1: " << n1 << "\n";
            cout << "n2: " << n2 << "\n";
            cout << "n3: " << n3 << "\n";
            cout << "n4: " << n4 << "\n\n";
            remove_node(n3);
            cout << "n1: " << n1 << "\n";
            cout << "n2: " << n2 << "\n";
            cout << "n3: " << n3 << "\n";
            cout << "n4: " << n4 << "\n\n";
            remove_node(n4);
            cout << "n1: " << n1 << "\n";
            cout << "n2: " << n2 << "\n";
            cout << "n3: " << n3 << "\n";
            cout << "n4: " << n4 << "\n";
        }
        else if ( testCase == 23 ) {
            SmartPtr<Node<int>> n {new_node(0)};
            for ( int i = 1; i <= 5; ++i )
                add_edge(n, new_node(i));
            for ( int i = 0; i < 5; ++i )
                for ( int j = i + 1; j < 5; ++j )
                    add_edge((*n)[i], (*n)[j]);
            cout << "n: " << n << "\n";
            for ( int i = 0; i < 5; ++i )
                cout << "(*n)[" << i << "]: " << (*n)[i] << "\n";
            for ( int i = 0; i < 4; ++i )
                remove_edge((*n)[i], (*n)[4]);
            remove_edge(n, (*n)[4]);
            remove_edge((*n)[3], (*n)[0]);
            cout << "\nn: " << n << "\n";
            for ( int i = 0; i < 4; ++i )
                cout << "(*n)[" << i << "]: " << (*n)[i] << "\n";
            for ( int i = 0; i < 4; ++i )
                remove_node((*n)[i]);
        }
        else if ( testCase == 24 ) {
            SmartPtr<Node<int>> n {new_node(0)};
            for ( int i = 1; i <= 5; ++i )
                add_edge(n, new_node(i));
            for ( int i = 0; i < 5; ++i )
                for ( int j = i + 1; j < 5; ++j )
                    add_edge((*n)[i], (*n)[j]);
            SmartPtr<Node<int>> n2 ((*n)[2]);
            cout << "n: " << n << "\n";
            for ( int i = 0; i < 5; ++i )
                cout << "(*n)[" << i << "]: " << (*n)[i] << "\n";
            remove_graph(n2);
            cout << "\nn: " << n << "\n";
            cout << "n2: " << n2 << "\n";
        }
        else if ( testCase == 25 ) {
            SmartPtr<Node<int>> n {new_node(0)};
            add_edge(n, new_node(1));
            add_edge(n, new_node(2));
            add_edge((*n)[0], new_node(3));
            add_edge((*n)[1], (*(*n)[0])[1]);
            cout << n << "\n";
            cout << (*n)[0] << "\n";
            cout << (*n)[1] << "\n";
            cout << (*(*n)[0])[1] << "\n\n";
            cout << "find(n, 0): " << find(n, 0) << "\n";
            cout << "find(n, 1): " << find(n, 1) << "\n";
            cout << "find(n, 3): " << find(n, 3) << "\n";
            cout << "find(n, 4): " << find(n, 4) << "\n";
            remove_graph(n);
        }
        else if ( testCase == 26 ) {
            SmartPtr<Node<int>> n {new_node(0)};
            SmartPtr<Node<int>> n1 {new_node(1)};
            SmartPtr<Node<int>> n2 {new_node(2)};
            add_edge(n, n1);
            add_edge(n1, n2);
            cout << "n: " << n << "\n";
            cout << "n1: " << n1 << "\n";
            cout << "n2: " << n2 << "\n\n";
            cout << "reachable(n, n1): " << reachable(n, n1) << "\n";
            cout << "reachable(n, n2): " << reachable(n, n2) << "\n\n";
            remove_edge(n1, n2);
            cout << "reachable(n, n2): " << reachable(n, n2) << "\n";
            remove_graph(n);
        }
        else if ( testCase == 27 ) {
            Node<int> n {42};
            Node<int> n1 {1};
            Node<int> n2 {2};
            Node<int> n3 {3};
            Node<int> n4 {4};
            cout << "n: " << n;
            n.add(n1);
            cout << "\n\nn: " << n;
            n.add(n2);
            n.add(n3);
            n.add(n4);
            cout << "\n\nn: " << n;
            cout << "\n";
        }
        cout << "\n";
    }
    return 0;
}
