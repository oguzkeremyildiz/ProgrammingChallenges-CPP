//
// Created by Oğuz Kerem Yıldız on 27.01.2021.
//

#include "Road.h"

#include <utility>

Road::Road() = default;

Road::Road(string name, int hour) {
    this->name = move(name);
    this->hour = hour;
}

string Road::getName() const {
    return name;
}

int Road::getHour() const {
    return hour;
}
