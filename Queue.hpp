#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <iostream>
#include <cstdlib>

using namespace std;

namespace data_structure { namespace queue {
        
    
const int MAX_SIZE = 100;

class QueueOverFlowException {
public:
    QueueOverFlowException() {
        cout << "Queue overflow..." << endl;
    }
};

class QueueEmptyException {
public:
    QueueEmptyException() {
        cout << "Queue empty..." << endl;
    }
};

template <class T>
class ArrayQueue {
private:
    T data_[MAX_SIZE];
    int front_;
    int rear_;
public:
    ArrayQueue();
    int Size() const;
    bool IsEmpty() const;
    void Enqueue(const T& element);
    T Dequeue();
    T Front();
    void Output(ostream& out) const;
};

template <class T>
ArrayQueue<T>::ArrayQueue() {
    front_ = -1;
    rear_ = -1;
}

template <class T>
int ArrayQueue<T>::Size() const {
    return abs(rear_ - front_);
}

template <class T>
bool ArrayQueue<T>::IsEmpty() const {
    return (front_ == rear_) ? true: false;
}

template <class T>
void ArrayQueue<T>::Enqueue(const T& element) {
    if(Size() == MAX_SIZE - 1) {
        throw new QueueOverFlowException();
    }

    data_[rear_] = element;
    rear_ = ++rear_ % MAX_SIZE;
}

template <class T>
T ArrayQueue<T>::Dequeue() {
    if(IsEmpty()) {
        throw new QueueEmptyException();
    }

    T ret = data_[front_];
    front_ = ++front_ % MAX_SIZE;
    return ret;
}

template <class T>
T ArrayQueue<T>::Front() {
    if(IsEmpty()) {
        throw new QueueEmptyException();
    }
    return data_[front_];
}

template <class T>
void ArrayQueue<T>::Output(ostream& out) const {
    for (int i = front_; i < rear_ ; ++i) {
        out << data_[i] << " ";
    }
}

// overload <<
template <class T>
ostream& operator<< (ostream& out, ArrayQueue<T>& x) {
    x.Output(out);
    return out;
}

template <typename T>
class ChainQueue;

template <class T>
class ChainNode {
    friend ChainQueue<T>;
private:
    T data_;
    ChainNode<T>* next_;
};

template <class T>
class ChainQueue {
private:
    ChainNode<T>* front_;
    ChainNode<T>* rear_;
    int count_;
public:
    ChainQueue();
    int Size() const;
    bool IsEmpty() const;
    void Enqueue(const T& element);
    T Dequeue();
    T Front() const;
    void Output(ostream& out) const;
};

template <class T>
ChainQueue<T>::ChainQueue() {
    front_ = NULL;
    rear_ = NULL;
    count_ = 0;
}

template <class T>
int ChainQueue<T>::Size() const {
    return count_;
}

template <class T>
bool ChainQueue<T>::IsEmpty() const {
    return (count_ == 0) ? true: false;
}

template <class T>
void ChainQueue<T>::Enqueue(const T& element) {
    if (count_ == MAX_SIZE) {
        throw QueueOverFlowException();
    }

    ChainNode<T>* node = new ChainNode<T>();
    node->data_ = element;
    node->next_ = NULL;

    if (IsEmpty()) {
        front_ = rear_ = node;
    }
    else {
        rear_->next_ = node;
        rear_ = node;
    }

    count_++;
}

template <class T>
T ChainQueue<T>::Dequeue() {
    if (IsEmpty()) {
        throw new QueueEmptyException();
    }
    ChainNode<T>* node = front_;
    T ret = front_->data_;
    front_ = front_->next_;
    count_--;

    delete node;
    node = NULL;

    return ret;
}

template <class T>
T ChainQueue<T>::Front() const {
    if (IsEmpty()) {
        throw new QueueEmptyException();
    }
    return front_->data_;
}

template <class T>
void ChainQueue<T>::Output(ostream& out) const {
    if (front_ == rear_ && front_ != NULL) {
        out << front_->data_;
    }
    else {
        ChainNode<T>* node = front_;
        while (node != rear_) {
            out << node->data_ << " ";
            node = node->next_;
        }
        out << rear_->data_;
    }
}

//overload <<
template <class T>
ostream& operator<< (ostream& out, const ChainQueue<T>& x) {
    x.Output(out);
    return out;
}


void test_array_queue() {
    ArrayQueue<int> q;
    try {
        if (q.IsEmpty()) {
            cout << "Queue is empty." << endl;
        }
        q.Enqueue(100);
        q.Enqueue(200);
        q.Enqueue(300);

        cout << "Size of queue is: " << q.Size() << endl;
        cout << q << endl;

        cout << q.Front() << endl;

        cout << q.Dequeue() << endl;
        cout << q.Dequeue() << endl;
        cout << q.Dequeue() << endl;
        cout << q.Dequeue() << endl;
    }
    catch (...) {
        cout << "Some exception occurs!" << endl;
    }
}

void test_chain_queue() {
    ChainQueue<int> q;
    try {
        if (q.IsEmpty()) {
            cout << "Queue is empty." << endl;
        }
        q.Enqueue(100);
        q.Enqueue(200);
        q.Enqueue(300);

        cout << "Size of queue is: " << q.Size() << endl;
        cout << q << endl;

        cout << q.Front() << endl;

        cout << q.Dequeue() << endl;
        cout << q.Dequeue() << endl;
        cout << q.Dequeue() << endl;
        cout << q.Dequeue() << endl;
    }
    catch (...) {
        cout << "Some exception occurs!" << endl;
    }
}
}//namespace queue
}//namespace data_structure


#endif // __QUEUE_H__
