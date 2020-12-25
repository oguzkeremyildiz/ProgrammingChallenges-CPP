//
// Created by Oğuz Kerem Yıldız on 25.12.2020.
//

#ifndef COOKIES_CPP_INTEGERLENGTH_H
#define COOKIES_CPP_INTEGERLENGTH_H
#include <iostream>

using namespace std;

class IntegerLength : public LengthInterface<int> {
public:
    virtual int compare(int length1, int length2) {
        if (length1 > length2) {
            return 1;
        } else if (length1 < length2) {
            return -1;
        } else {
            return 0;
        }
    }
    virtual int min() {
        return 0;
    }
    virtual int max() {
        return INT_MAX;
    }
    virtual int add(int length1, int length2) {
        return length1 + length2;
    }
    virtual int remove(int length1, int length2) {
        return length1 - length2;
    }
};
#endif //COOKIES_CPP_INTEGERLENGTH_H
