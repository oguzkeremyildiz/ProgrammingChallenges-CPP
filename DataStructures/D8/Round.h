//
// Created by Oğuz Kerem Yıldız on 6.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_ROUND_H
#define PROGRAMMINGCHALLENGES_CPP_ROUND_H
#include <vector>
#include <iostream>
#include <Sort/TimSort.h>
#include <sstream>

using namespace std;

class Round {
private:
    vector<int> dices;
    void sort();
    int sum();
    int basicCategories(int dice);
    int maxOfAKind();
    int fiveOfAKind();
    int fourOfAKind();
    int threeOfAKind();
    int longStraight();
    int shortStraight();
    int fullHouse();
public:
    Round(string readNext);
    Round();
    void print(string head);
    int calculate(int type);
};


#endif //PROGRAMMINGCHALLENGES_CPP_ROUND_H
