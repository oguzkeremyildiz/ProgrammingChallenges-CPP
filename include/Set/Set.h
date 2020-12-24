//
// Created by Oğuz Kerem Yıldız on 24.12.2020.
//

#ifndef COOKIES_CPP_SET_H
#define COOKIES_CPP_SET_H

template<class T> class Set {
public:
    T data;
    int parent;
    int depth;
    Set();
    Set(T data, int index);
};

template<class T> Set<T>::Set() = default;

template<class T> Set<T>::Set(T data, int index) {
    this->data = data;
    parent = index;
    depth = 1;
}
#endif //COOKIES_CPP_SET_H
