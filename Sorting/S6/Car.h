//
// Created by Oğuz Kerem Yıldız on 6.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_CAR_H
#define PROGRAMMINGCHALLENGES_CPP_CAR_H
#include <iostream>

using namespace std;

class Car {
private:
    string name;
    int money;
    string status;
    int time;
    int hour;
    int kilometres;
public:
    int getMoney();
    void setMoney(int money);
    string getName();
    string getStatus();
    int getHour();
    int getKilometres();
    Car(string name, string status, int time, int hour, int kilometres, int money);
    Car();
};


#endif //PROGRAMMINGCHALLENGES_CPP_CAR_H
