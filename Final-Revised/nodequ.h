#ifndef NODE
#define NODE

#include <iostream>

using namespace std;
template<typename T, typename U>
class nodeq
{
    public:
        nodeq();
        nodeq(const T& d,const U& p);
        ~nodeq();
        nodeq(const nodeq<T,U>& other);
        nodeq<T,U> operator=(const nodeq<T,U>& other);

        U& returnPriority();
        T& returnData();
        nodeq<T,U>*& nextLink();
        nodeq<T,U>*& prevLink();

        template<typename A,typename B>
        friend
        ostream& operator<<(ostream &out, const nodeq<A,B> &item);

        template<typename A,typename B>
        friend
        istream& operator>>(istream &in, nodeq<A,B> &item);

        template<typename A,typename B>
        friend
        bool higherPriority( nodeq<A,B> &one,  nodeq<A,B> &two);

    private:
        T data;
        U priority;
        nodeq<T,U> *next, *prev;

        void copy(const nodeq<T,U> &other);
        void nukem();
};

template<typename T, typename U>
nodeq<T,U>::nodeq()
{
    nukem();
}

template<typename T, typename U>
nodeq<T,U>::nodeq(const T& d,const U& p)
{
    data = d;
    priority = p;
    next = prev = NULL;
}

template<typename T, typename U>
nodeq<T,U>::~nodeq()
{
    nukem();
}

template<typename T, typename U>
nodeq<T,U>::nodeq(const nodeq<T,U> &other)
{
    copy(other);
}

template<typename T, typename U>
nodeq<T,U> nodeq<T,U>::operator=(const nodeq<T,U> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T, typename U>
U& nodeq<T,U>::returnPriority()
{
    return priority;
}

template<typename T, typename U>
T& nodeq<T,U>::returnData()
{
    return data;
}

template<typename T, typename U>
nodeq<T,U>*& nodeq<T,U>::nextLink()
{
    return next;
}

template<typename T, typename U>
nodeq<T,U>*& nodeq<T,U>::prevLink()
{
    return prev;
}

template<typename T, typename U>
void nodeq<T,U>::copy(const nodeq<T,U> &other)
{
    priority = other.priority;
    data = other.data;
    next = prev = NULL;
}

template<typename T, typename U>
void nodeq<T,U>::nukem()
{
    next = prev = NULL;
    data = T();
    priority = U();
}

template<typename A,typename B>
ostream& operator<<(ostream &out, const nodeq<A,B> &item)
{
    out<<"("<<item.data<<", "<<item.priority<<") ";
    return out;
}

template<typename A,typename B>
istream& operator>>(istream &in, nodeq<A,B> &item)
{
    A data;
    B priority;
    char junk;
    if(in == cin)
    {
        cout<<"Data: ";
        in>>data;
        cout<<"Priority: ";
        in>>priority;
    }
    else
        in>>junk>>data>>junk>>priority>>junk;
    item.theData() = data;
    item.thePriority() = priority;
    item.nextLink() = item.prevLink() = NULL;
    return in;
}

template<typename A, typename B>
bool higherPriority( nodeq<A,B> &one,  nodeq<A,B> &two)
{
    return one.returnPriority() > two.returnPriority();
}

#endif // NODE

