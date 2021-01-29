//
// Created by Oğuz Kerem Yıldız on 24.12.2020.
//

#ifndef COOKIES_CPP_TRIPLET_H
#define COOKIES_CPP_TRIPLET_H

template<class A, class B, class C> class Triplet {
private:
    A a;
    B b;
    C c;
public:
    Triplet();
    Triplet(A a, B b, C c);
    A getA() const;
    B getB() const;
    C getC() const;
};

template<class A, class B, class C> Triplet<A, B, C>::Triplet() = default;

template<class A, class B, class C> Triplet<A, B, C>::Triplet(A a, B b, C c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

template<class A, class B, class C> A Triplet<A, B, C>::getA() const {
    return this->a;
}

template<class A, class B, class C> B Triplet<A, B, C>::getB() const {
    return this->b;
}

template<class A, class B, class C> C Triplet<A, B, C>::getC() const {
    return this->c;
}

template <class A, class B, class C> bool operator ==(Triplet<A, B, C> triplet1, Triplet<A, B, C> triplet2) {
    return triplet1.getA() == triplet2.getA() && triplet1.getB() == triplet2.getB() && triplet1.getC() == triplet2.getC();
}

template <class A, class B, class C> bool operator !=(Triplet<A, B, C> triplet1, Triplet<A, B, C> triplet2) {
    return triplet1.getA() != triplet2.getA() || triplet1.getB() != triplet2.getB() || triplet1.getC() != triplet2.getC();
}

#endif //COOKIES_CPP_TRIPLET_H
