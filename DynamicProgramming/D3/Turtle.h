//
// Created by Oğuz Kerem Yıldız on 23.12.2020.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_TURTLE_H
#define PROGRAMMINGCHALLENGES_CPP_TURTLE_H
#include <Pair.h>
#include <iostream>

using namespace std;

class Turtle {
private:
    int index;
    Pair<int, int> pair;
public:
    Turtle();
    Turtle(int index, Pair<int, int> pair);
    int getIndex();
    Pair<int, int> getPair();
    string toString();
};


#endif //PROGRAMMINGCHALLENGES_CPP_TURTLE_H
