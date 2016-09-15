#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>


using namespace std;
template<typename T>
class node
{
    public:
        node();
        node(const T&);
        ~node();
        node(const node<T> &);
        node<T> operator=(const node<T> &);
        T& theData();
        node<T>*& theLink();

        template<typename A>
        friend
        ostream& operator<<(ostream &, const node<A> &);


        template<typename A>
        friend
        istream& operator>>(istream &, node<A> &);

    private:
        T data;
        node<T> *next;

        void copy(const node<T> &);
        void nukem();
};

template<typename T>
node<T>::node()
{
    nukem();
}

template<typename T>
node<T>::node(const T &d)
{
    data = d;
    next = NULL;
}

template<typename T>
node<T>::~node()
{
    nukem();
}

template<typename T>
node<T>::node(const node<T> &other)
{
    copy(other);
}

template<typename T>
node<T> node<T>::operator=(const node<T> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
T& node<T>::theData()
{
    return data;
}

template<typename T>
node<T>*& node<T>::theLink()
{
    return next;
}


template<typename T>
void node<T>::copy(const node<T> &other)
{
    data = other.data;
    next = NULL;
}

template<typename T>
void node<T>::nukem()
{
    next = NULL;
    data = T();
}

template<typename A>
ostream& operator<<(ostream &out, const node<A> &item)
{
    out<<"("<<item.data<<") ";
    return out;
}

template<typename A>
istream& operator>>(istream &in, node<A> &item)
{
    A data;
    char junk;
    if(in == cin)
    {
        cout<<"Data: ";
        in>>data;
    }
    else
        in>junk>>data>>junk;
    item.theData() = data;
    item.theLink() = NULL;
    return in;
}

#endif // NODE_H
