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
    Edge<E> clone();
    Edge<E>* clonePointer();
};

template<class E> Edge<E>::Edge() = default;

template<class E> Edge<E>::Edge(E length) {
    this->length = length;
}

template<class E> E Edge<E>::getLength() {
    return length;
}

template<class E> Edge<E> Edge<E>::clone() {
    return Edge<E>(length);
}

template<class E> Edge<E>* Edge<E>::clonePointer() {
    return new Edge<E>(length);
}

template <class E> bool operator ==(Edge<E> edge1, Edge<E> edge2) {
    return edge1.length == edge2.length;
}

template <class E> bool operator !=(Edge<E> edge1, Edge<E> edge2) {
    return !(edge1 == edge2);
}

#endif //COOKIES_CPP_EDGE_H
