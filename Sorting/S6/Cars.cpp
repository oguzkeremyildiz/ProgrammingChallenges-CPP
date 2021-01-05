//
// Created by Oğuz Kerem Yıldız on 6.01.2021.
//

#include "Cars.h"

Cars::Cars() {
}

void Cars::addCar(Car car) {
    cars.push_back(car);
}

Car Cars::getCar(int index) {
    return cars.at(index);
}

int Cars::size() {
    return cars.size();
}
