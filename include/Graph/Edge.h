//
// Created by Oğuz Kerem Yıldız on 1.02.2021.
//

#ifndef COOKIES_CPP_EDGE_H
#define COOKIES_CPP_EDGE_H
#include "LengthInterface.h"

using namespace std;

template<class E> class Edge {
protected:
    E length;
public:
    Edge();
    Edge(E length);
    E getLength();
};

template<class E> Edge<E>::Edge() = default;

template<class E> Edge<E>::Edge(E length) {
    this->length = length;
}

template<class E> E Edge<E>::getLength() {
    return length;
}

#endif //COOKIES_CPP_EDGE_H
