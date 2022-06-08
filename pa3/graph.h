#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <queue>
#include <set>
#include <ostream>
#include "smartptr.h"

using namespace std;

template <typename T>
class Node {
    private:
        static const unsigned int init_capacity = 10;
        T val;
        SmartPtr<Node<T>>* out;
        unsigned int capacity;
        unsigned int size_p;

    public:
        Node(const T& val);
        Node(const Node<T>& that);
        ~Node();
        T& operator*();
        const T& operator*() const;
        unsigned int degree() const;
        unsigned int size() const;
        SmartPtr<Node<T>> operator[](unsigned int i) const;
        void add(SmartPtr<Node<T>> n);
        void remove(SmartPtr<Node<T>> n);
        bool exists(SmartPtr<Node<T>> n) const;
        SmartPtr<Node<T>> find(T val) const;
};

template <typename T> ostream& operator<<(ostream& os, const Node<T>& n);

template <typename T> SmartPtr<Node<T>> new_node(const T& val);
template <typename T> void remove_node(SmartPtr<Node<T>> n);
template <typename T> void add_edge(SmartPtr<Node<T>> n1, SmartPtr<Node<T>> n2);
template <typename T> void remove_edge(SmartPtr<Node<T>> n1, SmartPtr<Node<T>> n2);
template <typename T> void remove_graph(SmartPtr<Node<T>> root);
template <typename T> SmartPtr<Node<T>> find(SmartPtr<Node<T>> root, T val);
template <typename T> bool reachable(SmartPtr<Node<T>> root, SmartPtr<Node<T>> dest);

#include "graph.tpp"
#include "graph-output.tpp"

#endif
