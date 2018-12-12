#include <iostream>
#include "string"
using namespace std;

template<typename T>
class GrowArray {
private:
    int used;
    int capacity;
    T* data;
    void checkGrow() {
        if (capacity == 0){
            capacity++;
            data = new T[1];
            return;
        }

        if (used < capacity)
            return;

        T* old = data;
        capacity *= 2;
        data = new T[capacity];
        for (int i = 0; i < used; i++)
            data[i] = old[i];
        delete [] old ;
    }
public:
    GrowArray() : used(0), capacity(0), data(nullptr) {}

    GrowArray(int  initialCapacity) : used(0), capacity(initialCapacity), data(new T[initialCapacity]){}

    ~ GrowArray(){
        delete [] data;
    }

    GrowArray(const GrowArray<T>& orig):used(orig.used),capacity(orig.capacity),data(new T[capacity]){
        for (int i = 0; i < orig.used; i++){
            data[i] = orig.data[i];
        }
    }

    GrowArray& operator =(const GrowArray<T>& orig){
        GrowArray copy(orig);
        used = orig.used;
        capacity = orig.capacity;
        swap(data,copy.data);
        return *this;
    }

    void addEnd(const T& v) {
        checkGrow();
        data[used] = v;
        used++;
    }

    T removeEnd() {
        used--;
    }



    T operator [](int i) const {
        return data[i];
    }

    T& operator [](int i) {
        return data[i];
    }

    friend ostream& operator <<(ostream& s, const GrowArray<T>& list) {
        for (int i = 0; i < list.used; i++)
            s << list[i] << ' ';
        return s;
    }
};



class Elephant {
private:
    string name;
public:
    Elephant(const string& name) : name(name) {}
    Elephant()  {}
    friend ostream& operator <<(ostream& s, const Elephant& e) {
        return s << e.name;
    }
};

int main() {
    GrowArray<int> a;
    GrowArray<int> b(1000);

    for (int i = 0; i < 10; i++)
        a.addEnd(i);
    for (int i = 0; i < 10; i++)
        b.addEnd(i);
    a.removeEnd();
    cout<< a[1] << endl;
    a[1] = 100;
    cout<< a[1] << endl;
    cout << a << endl;
    cout << b << endl;

    GrowArray<int> c(a);
    cout << c << endl;

    c = b;
    cout << c << endl;

    GrowArray<Elephant> e;
    e.addEnd(Elephant("Alice"));
    e.addEnd(Elephant("Betty"));
    cout << e;
}