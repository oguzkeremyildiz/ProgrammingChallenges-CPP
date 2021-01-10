//
// Created by Oğuz Kerem Yıldız on 10.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_SHOE_H
#define PROGRAMMINGCHALLENGES_CPP_SHOE_H


class Shoe {
private:
    int time;
    int cent;
    int index;
    double ratio;
public:
    Shoe();
    Shoe(int time, int cent, int index);
    int getIndex();
    int getCent();
    int getTime();
    double getRatio();
};


#endif //PROGRAMMINGCHALLENGES_CPP_SHOE_H
