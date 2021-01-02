//
// Created by Oğuz Kerem Yıldız on 2.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_CARD_H
#define PROGRAMMINGCHALLENGES_CPP_CARD_H
#include <string>

using namespace std;

class Card {
private:
    enum SuitType {CLUBS, DIAMONDS, HEARTS, SPADES} suit;
    int value;
public:
    SuitType getSuit();
    int getValue();
    void setValue(int value);
    Card();
    Card(string line);
    int compareTo(Card second);
};

Card::Card() = default;

Card::Card(string line) {
    if (line.at(0) == '2' || line.at(0) == '3' || line.at(0) == '4' || line.at(0) == '5' || line.at(0) == '6' || line.at(0) == '7' || line.at(0) == '8' || line.at(0) == '9') {
        value = line.at(0) - '0';
    } else if (line.at(0) == 'T') {
        value = 10;
    } else if (line.at(0) == 'J') {
        value = 11;
    } else if (line.at(0) == 'Q') {
        value = 12;
    } else if (line.at(0) == 'K') {
        value = 13;
    } else if (line.at(0) == 'A') {
        value = 14;
    }
    if (line.at(1) == 'C') {
        suit = CLUBS;
    } else if (line.at(1) == 'D') {
        suit = DIAMONDS;
    } else if (line.at(1) == 'H') {
        suit = HEARTS;
    } else if (line.at(1) == 'S') {
        suit = SPADES;
    }
}

Card::SuitType Card::getSuit() {
    return suit;
}

int Card::getValue() {
    return value;
}

void Card::setValue(int value) {
    this->value = value;
}

int Card::compareTo(Card second) {
    return value - second.value;
}

#endif //PROGRAMMINGCHALLENGES_CPP_CARD_H
