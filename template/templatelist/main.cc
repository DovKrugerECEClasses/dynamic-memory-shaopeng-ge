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
            data = new T[++capacity];
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
        data[used++] = v;
    }

    T removeEnd() {
        return data[--used];
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
    cout << "a:"<<a<<endl;
    cout << "b:"<<b<<endl;
    
    cout<< "remove the last item of a : " << a.removeEnd() << endl;
    
    cout<< "a[1]: " << a[1] << endl;
    a[1] = 100;
    cout<< "after change ele a[1] to 100"<< endl;
    cout<< "a[1]: "<<a[1] << endl;
    
    cout << "a:"<<a<<endl;
    cout << "b:"<<b<<endl;

    GrowArray<int> c(a);
    cout <<"a copy of a: " << c << endl;

    c = b;
    cout <<" after assigning b to c, c is :"<< c << endl;

    GrowArray<Elephant> e;
    e.addEnd(Elephant("Alice"));
    e.addEnd(Elephant("Betty"));
    cout << "e: "<<e << endl;
    cout<<  "remove " << e.removeEnd() << endl;
    cout << "after remove remove, e is: "<<e << endl;
}