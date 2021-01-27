//
// Created by Oğuz Kerem Yıldız on 27.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_ROAD_H
#define PROGRAMMINGCHALLENGES_CPP_ROAD_H
#include <iostream>

using namespace std;

class Road {
private:
    string name;
    int hour;
public:
    Road();
    Road(string name, int hour);
    string getName() const;
    int getHour() const;
    bool operator ==(const Road& r) const {
        return this->name == r.name && this->hour == r.hour;
    }
    bool operator !=(const Road& r) const {
        return !this->operator==(r);
    }
};


#endif //PROGRAMMINGCHALLENGES_CPP_ROAD_H
