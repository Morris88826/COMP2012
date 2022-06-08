#ifndef __SMARTPTR_H__
#define __SMARTPTR_H__

#include <ostream>

using namespace std;

template <typename T> class SmartPtr;

template <typename T> ostream& operator<<(ostream& os, const SmartPtr<T>& sp);

template <typename T>
class SmartPtr {
    friend ostream& operator<<<T>(ostream&, const SmartPtr<T>&);

    private:
        T* ptr;
        unsigned int* count;

    public:
        SmartPtr();
        SmartPtr(const T& val);
        SmartPtr(const SmartPtr<T>& that);
        ~SmartPtr();
        SmartPtr<T>& operator=(const SmartPtr<T>& that);
        void set(const T& val);
        void unset();
        bool is_null() const;
        bool operator==(const SmartPtr<T>& that) const;
        bool operator!=(const SmartPtr<T>& that) const;
        T& operator*() const;
        T* operator->() const;
};

#include "smartptr.tpp"
#include "smartptr-output.tpp"

#endif
