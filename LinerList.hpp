template<class T>
class LinerList
{
public:
    LinerList(int MaxListSize = 10);
    ~LinerList() { delete []element; }
    bool IsEmpty() { return length == 0; }
    int Length() { return length; }
    bool Find(int k, T& x) const;
    int Search(const T& x) const;
    LinerList<T>& Delete(int k, T& x);
    LinerList<T>& Insert(int k, const T& x);
    void Output(ostream& out) const;
private:
    int length;
    int MaxSize;
    T *element;
};

template<class T>
LinerList<T>::LinerList(int MaxListSize){
    MaxSize = MaxListSize;
    element = new T[MaxSize];
    length = 0;
}

template<class T>
bool LinerList<T>::Find(int k, T& x) const{
    if (k < 1 || k > length) return false;
    x = element[k - 1];
    return true;
}

template<class T>
int LinerList<T>::Search(const T& x) const{
    for (int i = 0; i < length; ++i)
        if (element[i] == x) return ++i;
    return 0;
}

template<class T>
LinerList<T>& LinerList<T>::Delete(int k, T& x) {
    if (Find(k, x)) {
        for (int i = k; i < length; i++)
            element[i - 1] = element[i];
        length--;
        return *this;
    }
    else throw OutOfBounds();
}