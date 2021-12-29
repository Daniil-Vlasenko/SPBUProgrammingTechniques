#include <iostream>
#include <cassert>


template <class T>
class Arr{
    T *a;
    size_t size;
public:
    T* getA() const {return a;}
    size_t getSize() const {return size;}

    explicit Arr(size_t size = 0, T el = 0): size{size}, a{nullptr} {
        if(size > 0) {
            this->a = new T[size];
            for (int i = 0; i < size; ++i)
                a[i] = el;
        }
    }
    Arr(Arr const &ar): size{ar.size}, a{nullptr} {
        if(size != 0) {
            a = new T[size];
            for (int i = 0; i < size; ++i)
                a[i] = ar.a[i];
        }
    }
    Arr& operator = (Arr const &ar) {
        if(this != &ar) {
            delete[] a;
            size = ar.size;
            if(size != 0) {
                a = new T[size];
                for (int i = 0; i < size; ++i)
                    a[i] = ar.a[i];
            }
            else
                a = nullptr;
        }
        return *this;
    }
    ~Arr() {delete[] a;}
    void print() const {
        for(int i = 0; i < size; ++i)
            std::cout << a[i] << ' ';
        std::cout << std::endl;
    }
    Arr& add(Arr const &ar) {
        assert(ar.size == size);
        for(size_t i = 0; i < size; ++i)
            a[i] += ar.a[i];
        return *this;
    }
};

template <class T>
Arr<T> sum(const Arr<T> &ar1, const Arr<T> &ar2) {
    return Arr(ar1).add(ar2);
}

int main() {
    Arr<double> a1 = Arr(5, -1.7);
    Arr<double> a2 = Arr(5, 2.2);
    Arr<double> a3;
    Arr<double> a4;

    a1.print();
    a1.add(a2);
    a1.print();
    a3 = sum(a1, a2);
    a3.print();

    return 0;
}
