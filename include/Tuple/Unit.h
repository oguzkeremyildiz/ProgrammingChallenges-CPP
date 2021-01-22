//
// Created by Oğuz Kerem Yıldız on 23.12.2020.
//

#ifndef COOKIES_CPP_UNIT_H
#define COOKIES_CPP_UNIT_H

using namespace std;

template<class A> class Unit {
private:
    A a;
public:
    Unit();
    Unit(A a);
    A getA();
};

template<class A> Unit<A>::Unit() = default;

template<class A> Unit<A>::Unit(A a) {
    this->a = a;
}

template<class A> A Unit<A>::getA() {
    return this->a;
}

template<class A> bool operator ==(Unit<A> unit1, Unit<A> unit2) {
    return unit1.getA() == unit2.getA();
}

template <class A> bool operator !=(Unit<A> unit1, Unit<A> unit2) {
    return unit1.getA() != unit2.getA();
}

#endif //COOKIES_CPP_UNIT_H
