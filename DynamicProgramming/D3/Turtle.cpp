//
// Created by Oğuz Kerem Yıldız on 23.12.2020.
//

#include "Turtle.h"

Turtle::Turtle() {
}

Turtle::Turtle(int index, Pair<int, int> pair) {
    this->index = index;
    this->pair = pair;
}

int Turtle::getIndex() {
    return index;
}

Pair<int, int> Turtle::getPair() {
    return pair;
}

string Turtle::toString() {
    return  std::to_string(index) + ", " + std::to_string(pair.getKey()) + ", " + std::to_string(pair.getValue());
}