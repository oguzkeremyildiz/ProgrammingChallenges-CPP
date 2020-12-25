//
// Created by Oğuz Kerem Yıldız on 24.12.2020.
//

#ifndef COOKIES_CPP_TRIPLET_H
#define COOKIES_CPP_TRIPLET_H

#include <string>

using namespace std;

template<class A, class B, class C> class Triplet {
private:
    A a;
    B b;
    C c;
public:
    Triplet();
    Triplet(A a, B b, C c);
    A getA();
    B getB();
    C getC();
    std::string toString();
};

template<class A, class B, class C> Triplet<A, B, C>::Triplet() = default;

template<class A, class B, class C> Triplet<A, B, C>::Triplet(A a, B b, C c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

template<class A, class B, class C> A Triplet<A, B, C>::getA() {
    return this->a;
}

template<class A, class B, class C> B Triplet<A, B, C>::getB() {
    return this->b;
}

template<class A, class B, class C> C Triplet<A, B, C>::getC() {
    return this->c;
}

template<class A, class B, class C> std::string Triplet<A, B, C>::toString() {
    return "[" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + "]";
}

template <class A, class B, class C> bool operator ==(Triplet<A, B, C> triplet1, Triplet<A, B, C> triplet2) {
    return triplet1.getA() == triplet2.getA() && triplet1.getB() == triplet2.getB() && triplet1.getC() == triplet2.getC();
}

template <class A, class B, class C> bool operator !=(Triplet<A, B, C> triplet1, Triplet<A, B, C> triplet2) {
    return triplet1.getA() != triplet2.getA() || triplet1.getB() != triplet2.getB() || triplet1.getC() != triplet2.getC();
}

#endif //COOKIES_CPP_TRIPLET_H