//
// Created by Oğuz Kerem Yıldız on 1.02.2021.
//

#ifndef COOKIES_CPP_EDGE_H
#define COOKIES_CPP_EDGE_H
#include "LengthInterface.h"

using namespace std;

template<class E> class Edge {
private:
    E capacity;
    E flow;
    E residual;
    LengthInterface<E> *lengthInterface;
public:
    Edge();
    Edge(E capacity, LengthInterface<E> *lengthInterface);
    Edge(E capacity, E residual, LengthInterface<E> *lengthInterface);
    E getCapacity();
    E getFlow();
    E getResidual();
    void setFlow(E e);
    void setResidual(E residual);
};

template<class E> Edge<E>::Edge() = default;

template<class E> Edge<E>::Edge(E capacity, LengthInterface<E> *lengthInterface) {
    this->capacity = capacity;
    this->lengthInterface = lengthInterface;
    flow = lengthInterface->min();
    residual = capacity;
}

template<class E> Edge<E>::Edge(E capacity, E residual, LengthInterface<E> *lengthInterface) {
    this->capacity = capacity;
    this->residual = residual;
    flow = lengthInterface->remove(capacity, residual);
    this->lengthInterface = lengthInterface;
}

template<class E> E Edge<E>::getCapacity() {
    return capacity;
}

template<class E> E Edge<E>::getFlow() {
    return flow;
}

template<class E> E Edge<E>::getResidual() {
    return residual;
}

template<class E> void Edge<E>::setFlow(E e) {
    this->flow = e;
    setResidual(lengthInterface->remove(getCapacity(), getFlow()));
}

template<class E> void Edge<E>::setResidual(E e) {
    this->residual = e;
}

#endif //COOKIES_CPP_EDGE_H
