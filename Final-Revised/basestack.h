#ifndef BASESTACK
#define BASESTACK

#include <node.h>

enum ERRORS{FULL};

template<typename T>
class baseStack
{
    public:
        baseStack();
        ~baseStack();
        baseStack(const baseStack<T>& other);
        baseStack<T>& operator=(const baseStack<T>& other);
        void push(const T& d);
        T& top();
        T& pop();
        bool empty();
        void clear();
        int size();
        int capacity();

        baseStack<T>& operator<<(const T &data);
        baseStack<T>& operator>>(T &data);

        template<typename U>
        friend
        ostream& operator<<(ostream& out,  baseStack<U>&y);

        template<typename U>
        friend
        istream& operator>>(istream& out,  baseStack<U>&x);


    private:
        node<T>* root;
        int count;
        void nukem();
        void copy(const baseStack<T>& other);
};

template<typename T>
baseStack<T>::baseStack()
{
    root = NULL;
    count = 0;
}

template<typename T>
baseStack<T>::~baseStack()
{
    nukem();
}

template<typename T>
baseStack<T>::baseStack(const baseStack<T>& other)
{
    copy(other);
}

template<typename T>
baseStack<T>& baseStack<T>::operator=(const baseStack<T>& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
void baseStack<T>::nukem()
{
    for(node<T> *temp, *ptr = root;
                          ptr;
                          temp = ptr,
                          ptr = ptr->theLink(),
                          delete temp);
    count = 0;
}

template<typename T>
void baseStack<T>::copy(const baseStack<T>& other)
{
    node<T> newRoot, *end = &newRoot;
    for(node<T>*ptr = other.root; ptr; ptr = ptr->theLink())
    {
        end->theLink() = new node<T>(*ptr);
        end = end->theLink();
    }
    root = newRoot.theLink();
}

template<typename T>
void baseStack<T>::push(const T &d)
{
    node<T>*temp, *newNode = new node<T>(d);

    if(!root)
        root = newNode;

    else
    {
         temp = root;
         root = newNode;
         root->theLink() = temp;
    }
    count++;
}

template<typename T>
T& baseStack<T>::top()
{
    return root->theData();
}

template<typename T>
T& baseStack<T>::pop()
{
    T data = root->theData();
    root = root->theLink();
    count--;
    return data;
}

template<typename T>
bool baseStack<T>::empty()
{
    return !root;
}

template<typename T>
void baseStack<T>::clear()
{
    nukem();
}

template<typename T>
int baseStack<T>::size()
{
    return count;
}

template<typename T>
baseStack<T>& baseStack<T>::operator<<(const T &data)
{
    push(data);
    return *this;
}

template<typename T>
baseStack<T>& baseStack<T>::operator>>(T &data)
{
    data = pop();
    return *this;
}

template<typename U>
ostream& operator<<(ostream& out,  baseStack<U> &y)
{
    node<U>* temp = y.root;
    for(node<U>* ptr = temp; ptr; ptr = ptr->theLink())
    {
        out<<y.pop()<<" ";
    }
    return out;
}

template<typename U>
istream& operator>>(istream& in, baseStack<U>&x)
{
    U data;
    int size;
    if(in == cin)
    {
        cout<<"Size of Stack = ";
        cin>>size;
        x.total = size;
        cout<<"Fill the stack: ";
        while(in>>data)
        {
            x.push(data);
            if(x.count == x.total)
                break;
        }
    }
    return in;
}

#endif // BASESTACK
