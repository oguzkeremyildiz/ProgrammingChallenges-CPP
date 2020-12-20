//
// Created by Oğuz Kerem Yıldız on 19.12.2020.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_NUMBER_H
#define PROGRAMMINGCHALLENGES_CPP_NUMBER_H


class Number {
public:
    Number();
    Number(int x, int y, int value);
    int x;
    int y;
    int value;
    bool operator==(const Number &anotherWord) const{
        return (x == anotherWord.x && y == anotherWord.y && value == anotherWord.value);
    }
};


#endif //PROGRAMMINGCHALLENGES_CPP_NUMBER_H
