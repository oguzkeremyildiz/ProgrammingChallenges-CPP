//
// Created by Oğuz Kerem Yıldız on 6.01.2021.
//

#include "Car.h"

Car::Car() = default;

Car::Car(string name, string status, int time, int hour, int kilometres, int money) {
    this->name = name;
    this->status = status;
    this->time = time;
    this->hour = hour;
    this->kilometres = kilometres;
    this->money = money;
}

int Car::getMoney() {
    return money;
}

void Car::setMoney(int money) {
    this->money = money;
}

string Car::getName() {
    return name;
}

string Car::getStatus() {
    return status;
}

int Car::getHour() {
    return hour;
}

int Car::getKilometres() {
    return kilometres;
}
