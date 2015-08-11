#ifndef __StackClassH__
#define __StackClassH__

#include <iostream>
using namespace std;

const int MAX_SIZE = 100;


class StackOverFlowException
{
public:
    StackOverFlowException()
    {
        cout << "Stack overflow..." << endl;
    }
};

class StackUnderFlowException
{
public:
    StackUnderFlowException()
    {
        cout << "Stack underflow..." << endl;
    }
};

template <class T>
class ArrayStack {
private:
    T data_[MAX_SIZE];
    int top_;
    
public:
    ArrayStack();
    void Push(const T& element);
    T& Pop();
    T& Top() const;
    int Size() const;
    bool IsEmpty() const;
    void Output(ostream& out) const;
};

template <class T>
ArrayStack<T>::ArrayStack() {
    top_ = -1;
}

template <class T>
void ArrayStack<T>::Push(const T& element) {
    if (top_ >= MAX_SIZE) {
        throw new StackOverFlowException();
    }
    data_[++top_] = element;
}

template <class T>
T& ArrayStack<T>::Pop() {
    if (top_ == -1) {
        throw new StackUnderFlowException();
    }
    return data_[top_--];
}

template <class T>
T& ArrayStack<T>::Top() const {
    return data_[top_];         // top == -1??
}

template <class T>
int ArrayStack<T>::Size() const {
    return top_ + 1;
}

template <class T>
bool ArrayStack<T>::IsEmpty() const {
    return (top_ == -1) ? true : false;
}

template <class T>
void ArrayStack<T>::Output(ostream& out) const {
    for (int i = 0; i <= top_; ++i) {
        out << data_[i] << " ";
    }
}

//overload <<
template<class T>
ostream& operator<<(ostream& out, const ArrayStack<T>& x) {
    x.Output(out);
    return out;
}

///////////////////////////////////////////////////////////////////////////////////
template <typename T>
class ChainStack;

template <class T>
class ChainNode {
    friend ChainStack<T>;
private:
    T data_;
    ChainNode<T>* next_;
};

template <class T>
class ChainStack {
    
private:
    ChainNode<T>* top_;
    int count_;

public:
    ChainStack();
    void Push(const T& element);
    T Pop();
    T& Top() const;
    int Size() const;
    bool IsEmpty() const;
    void Output(ostream& out) const;
};

template <class T>
ChainStack<T>::ChainStack() {
    top_ = 0;
    count_ = 0;
}

template <class T>
void ChainStack<T>::Push(const T& element) {
    ChainNode<T>* node = new ChainNode<T>();
    node->data_ = element;
    node->next_ = top_;
    
    top_ = node;
    count_++;
}

template <class T>
T ChainStack<T>::Pop() {
    if (top_ == 0) {
        throw new StackUnderFlowException();
    }
    
    T ret = top_->data_;
    ChainNode<T>* node = top_->next_;
    delete top_;
    top_ = node;
    count_--;
    
    return ret;
}

template <class T>
T& ChainStack<T>::Top() const {
    return top_->data_;
}

template <class T>
int ChainStack<T>::Size() const {
    return count_;
}

template <class T>
bool ChainStack<T>::IsEmpty() const {
    return (top_ == 0) ? true : false;
}

template <class T>
void ChainStack<T>::Output(ostream &out) const
{
    ChainNode<T>* node = top_;
    while (node != 0) {
        out << node->data_ << " ";
        node = node->next_;
    }
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const ChainStack<T>& x) {
    x.Output(out);
    return out;
}

////////////////////////////////////////////////////////////////////////////////

void test_array_stack() {
    ArrayStack<int> arraystack;
    try {
        if (arraystack.IsEmpty()) {
            cout << "Stack is empty..." << endl;
        }
        
        arraystack.Push(100);
        arraystack.Push(200);
        
        //cout << "Size of array stack is " << arraystack.Size() << endl;
        cout << arraystack << endl;
        
        cout << arraystack.Pop() << endl;
        cout << arraystack.Pop() << endl;
        cout << arraystack.Pop() << endl;
        
        
    } catch (...) {
        cout << "Exception Occurs!" << endl;
    }
}

void test_chain_stack() {
    ChainStack<int> chainstack;
    try {
        if (chainstack.IsEmpty()) {
            cout << "Stack is empty..." << endl;
        }
        chainstack.Push(100);
        chainstack.Push(200);
        
        cout << chainstack << endl;
        
        cout << chainstack.Pop() << endl;
        cout << chainstack.Pop() << endl;
        cout << chainstack.Pop() << endl;
        
    }
    catch (...) {
        cout << "Exception Occurs!" << endl;
    }
}




#endif /*__StackClassH__*/