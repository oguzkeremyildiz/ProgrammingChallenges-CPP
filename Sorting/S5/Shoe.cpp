//
// Created by Oğuz Kerem Yıldız on 10.01.2021.
//

#include "Shoe.h"

Shoe::Shoe() = default;

Shoe::Shoe(int time, int cent, int index) {
    this->time = time;
    this->cent = cent;
    this->index = index;
    this->ratio = (double)this->cent - (double)this->time;
}

int Shoe::getIndex() {
    return index;
}

int Shoe::getCent() {
    return cent;
}

int Shoe::getTime() {
    return time;
}

double Shoe::getRatio() {
    return ratio;
}
