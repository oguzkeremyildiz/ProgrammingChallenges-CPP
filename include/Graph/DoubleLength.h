//
// Created by Oğuz Kerem Yıldız on 25.12.2020.
//

#ifndef COOKIES_CPP_DOUBLELENGTH_H
#define COOKIES_CPP_DOUBLELENGTH_H
#include <iostream>
#include <float.h>

using namespace std;

class DoubleLength : public LengthInterface<double> {
public:
    virtual int compare(double length1, double length2) {
        if (length1 > length2) {
            return 1;
        } else if (length1 < length2) {
            return -1;
        } else {
            return 0;
        }
    }
    virtual double min() {
        return 0.0;
    }
    virtual double max() {
        return DBL_MAX;
    }
    virtual double add(double length1, double length2) {
        return length1 + length2;
    }
    virtual double remove(double length1, double length2) {
        return length1 - length2;
    }
};
#endif //COOKIES_CPP_DOUBLELENGTH_H
