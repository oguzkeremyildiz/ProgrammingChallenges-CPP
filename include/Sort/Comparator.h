//
// Created by Oğuz Kerem Yıldız on 3.01.2021.
//

#ifndef COOKIES_CPP_COMPARATOR_H
#define COOKIES_CPP_COMPARATOR_H

template<class Symbol> class Comparator {
public:
    virtual ~Comparator() {}
    virtual int compare(Symbol first, Symbol second) = 0;
};

#endif //COOKIES_CPP_COMPARATOR_H
