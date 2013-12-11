
template<class T>
class ChainNode {
    friend Chain<T>;
private:
    T data_;
    ChainNode<T>* next_;
};

template<class T>
class Chain {
public:
    Chain() { first_ = 0; }
    ~Chain();
    bool IsEmpty() const { return first_ == 0; }
    int Length() const;
    bool Find(int k, T& x) const;
    int Search(const T& x) const;
    Chain<T>& Delete(int k, T& x);
    Chain<T>& Insert(int k, const T& x);
    void Output(ostream& out) const;
private:
    ChainNode<T>* first_;
};

template<class T>
Chain::~Chain() {
    ChainNode<T>* next;
    while (first_) {
        next = first_->next_;
        delete first_;
        first_ = next;
    }
}

template<class T>
int Chain::Length() const {
    int count = 0;
    ChainNode<T>* current = first_;
    while (current) {
        count++;
        current = current->next_;
    }
    return count;
}

template<class T>
bool Chain::Find(int k, T& x) const {
    if (k < 1) return false;
    ChainNode<T>* current = first_;
    int index = 1;
    while (index < k && current) {
        index++;
        current = current->next_;
    }
    if (current) {
        x = current->data_;
        return true;
    }
    return false;
}

template<class T>
int Chain::Search(const T& x) const {
    ChainNode<T>* current = first_;
    int index = 1;
    while (current && current->data_ != x) {
        current = current->next_;
        index++;
    }
    if (current) return index;
    return 0;
}

template<class T>
void Chain<T>::Output(ostream& out) const {
    ChainNode<T>* current;
    for (current = first_; current; current = current->next_)
        out << current->data_; << " ";
}

//overload <<
template<class T>
ostream& operator<<(ostream& out, const Chain<T>& x) {
    x.Output(out);
    return out;
}