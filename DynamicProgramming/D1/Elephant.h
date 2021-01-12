//
// Created by Oğuz Kerem Yıldız on 12.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_ELEPHANT_H
#define PROGRAMMINGCHALLENGES_CPP_ELEPHANT_H


class Elephant {
private:
    int weight;
    int iq;
    int no;
public:
    Elephant(int weight, int iq, int no);
    Elephant();
    int getWeight();
    int getIq();
    int getNo();
};

bool operator ==(Elephant e1, Elephant e2);


#endif //PROGRAMMINGCHALLENGES_CPP_ELEPHANT_H
