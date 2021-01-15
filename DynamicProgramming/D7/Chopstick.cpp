//
// Created by Oğuz Kerem Yıldız on 15.01.2021.
//

#include "Chopstick.h"

Chopstick::Chopstick() = default;

Chopstick::Chopstick(int index, int chopstick) {
    this->index = index;
    this->chopstick = chopstick;
}

int Chopstick::getIndex() {
    return index;
}

int Chopstick::getChopstick() {
    return chopstick;
}
