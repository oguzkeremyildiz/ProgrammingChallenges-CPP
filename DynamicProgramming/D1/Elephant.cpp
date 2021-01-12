//
// Created by Oğuz Kerem Yıldız on 12.01.2021.
//

#include "Elephant.h"

Elephant::Elephant() = default;

int Elephant::getWeight() {
    return weight;
}

int Elephant::getIq() {
    return iq;
}

Elephant::Elephant(int weight, int iq, int no) {
    this->weight = weight;
    this->iq = iq;
    this->no = no;
}

int Elephant::getNo() {
    return no;
}

bool operator ==(Elephant e1, Elephant e2) {
    return e1.getIq() == e2.getIq() && e1.getNo() == e2.getNo() && e1.getWeight() == e2.getWeight();
}