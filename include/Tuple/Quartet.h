//
// Created by Oğuz Kerem Yıldız on 28.01.2021.
//

#ifndef COOKIES_CPP_QUARTET_H
#define COOKIES_CPP_QUARTET_H

template<class A, class B, class C, class D> class Quartet {
private:
    A a;
    B b;
    C c;
    D d;
public:
    Quartet();
    Quartet(A a, B b, C c, D d);
    A getA() const;
    B getB() const;
    C getC() const;
    D getD() const;
};

template<class A, class B, class C, class D> Quartet<A, B, C, D>::Quartet() = default;

template<class A, class B, class C, class D> Quartet<A, B, C, D>::Quartet(A a, B b, C c, D d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

template<class A, class B, class C, class D> A Quartet<A, B, C, D>::getA() const {
    return this->a;
}

template<class A, class B, class C, class D> B Quartet<A, B, C, D>::getB() const {
    return this->b;
}

template<class A, class B, class C, class D> C Quartet<A, B, C, D>::getC() const {
    return this->c;
}

template<class A, class B, class C, class D> D Quartet<A, B, C, D>::getD() const {
    return this->d;
}

template <class A, class B, class C, class D> bool operator ==(Quartet<A, B, C, D> quartet1, Quartet<A, B, C, D> quartet2) {
    return quartet1.getA() == quartet2.getA() && quartet1.getB() == quartet2.getB() && quartet1.getC() == quartet2.getC() && quartet1.getD() == quartet2.getD();
}

template <class A, class B, class C, class D> bool operator !=(Quartet<A, B, C, D> quartet1, Quartet<A, B, C, D> quartet2) {
    return !(quartet1 == quartet2);
}

#endif //COOKIES_CPP_QUARTET_H
