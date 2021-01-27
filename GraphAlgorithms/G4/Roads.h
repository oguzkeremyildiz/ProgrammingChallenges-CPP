//
// Created by Oğuz Kerem Yıldız on 27.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_ROADS_H
#define PROGRAMMINGCHALLENGES_CPP_ROADS_H
#include <vector>
#include "Road.h"

using namespace std;

class Roads {
private:
    vector<Road> roads;
public:
    Roads();
    void add(Road road);
    Road getFirst();
    Road getLast();
    Road get(int index);
    int size();
    void clear();
};


#endif //PROGRAMMINGCHALLENGES_CPP_ROADS_H
