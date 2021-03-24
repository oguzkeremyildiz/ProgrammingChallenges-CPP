//
// Created by Oğuz Kerem Yıldız on 25.12.2020.
//

#ifndef COOKIES_CPP_LENGTHINTERFACE_H
#define COOKIES_CPP_LENGTHINTERFACE_H

using namespace std;

template<class Length> class LengthInterface {
public:
    virtual ~LengthInterface() {}
    virtual int compare(Length length1, Length length2) = 0;
    virtual Length min() = 0;
    virtual Length max() = 0;
    virtual Length add(Length length1, Length length2) = 0;
    virtual Length remove(Length length1, Length length2) = 0;
    virtual Length min(Length length1, Length length2) = 0;
};

#endif //COOKIES_CPP_LENGTHINTERFACE_H
