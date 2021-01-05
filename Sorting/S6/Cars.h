//
// Created by Oğuz Kerem Yıldız on 6.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_CARS_H
#define PROGRAMMINGCHALLENGES_CPP_CARS_H
#include <vector>
#include "Car.h"

using namespace std;

class Cars {
private:
    vector<Car> cars = vector<Car>();
public:
    Cars();
    void addCar(Car car);
    Car getCar(int index);
    int size();
};


#endif //PROGRAMMINGCHALLENGES_CPP_CARS_H
