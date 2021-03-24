//
// Created by Oğuz Kerem Yıldız on 17.03.2021.
//

#ifndef COOKIES_CPP_RESIDUALEDGE_H
#define COOKIES_CPP_RESIDUALEDGE_H
#include "Edge.h"

using namespace std;

template<class E> class ResidualEdge : public Edge<E> {
private:
    E flow;
    E residual;
    LengthInterface<E> *lengthInterface;
public:
    ResidualEdge() : Edge<E>() {
    }
    explicit ResidualEdge(E capacity, LengthInterface<E> *lengthInterface) : Edge<E>(capacity) {
        this->lengthInterface = lengthInterface;
        flow = lengthInterface->min();
        residual = capacity;
    }
    explicit ResidualEdge(E capacity, E residual, LengthInterface<E> *lengthInterface) : Edge<E>(capacity) {
        this->residual = residual;
        flow = lengthInterface->remove(capacity, residual);
        this->lengthInterface = lengthInterface;
    }
    E getFlow() {
        return flow;
    }
    E getResidual() {
        return residual;
    }
    void setFlow(E e) {
        this->flow = e;
        setResidual(lengthInterface->remove(this->getLength(), getFlow()));
    }
    void setResidual(E e) {
        this->residual = e;
    }
};

#endif //COOKIES_CPP_RESIDUALEDGE_H
