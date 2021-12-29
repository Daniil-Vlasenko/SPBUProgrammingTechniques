#include <iostream>
using namespace std;


class COMPLEX {
    double Re{};
    double In{};
public:
    explicit COMPLEX(double Re = 0, double In = 0) : Re{Re}, In{In} {}

    void set(double sRe = 0, double sIn = 0) {
        Re = sRe;
        In = sIn;
    }

    double getRe() const {return Re;}
    double getIn() const {return In;}

    void print() const {
        cout << Re << "+i(" << In << ")" << endl;
    }

    COMPLEX& add(COMPLEX const &c2) {
        Re += c2.Re;
        In += c2.In;
        return *this;
    }

    COMPLEX sum1(COMPLEX const &c2) const {
        COMPLEX c3(Re, In);
        return c3.add(c2);
    }
};

COMPLEX sum2(COMPLEX const &c1, COMPLEX const &c2) {
    COMPLEX c3;
    c3.set(c1.getRe(), c1.getIn());
    return c3.add(c2);
}






int main() {
    COMPLEX c1, c2, c3, c4;
    c1.set(2, 3);
    c1.print();
    c2.set(1, -3);
    c2.print();
    c3 = c1.sum1(c2);
    c3.print();
    c4 = sum2(c1, c2);
    c4.print();
    return 0;
}