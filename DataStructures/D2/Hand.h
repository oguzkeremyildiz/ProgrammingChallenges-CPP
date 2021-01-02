//
// Created by Oğuz Kerem Yıldız on 2.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_HAND_H
#define PROGRAMMINGCHALLENGES_CPP_HAND_H
#include "Card.h"
#include <vector>
#include <utility>

using namespace std;

class Hand {
private:
    int partition(int head, int end);
    void changePlace(int i, int j);
    vector<Card> cards = vector<Card>();
public:
    Hand();
    void quickSort(int head, int end);
    bool straightFlush();
    void addCard(Card card);
    int size();
    int compareTo(Hand second);
    bool fourOfAKind();
    bool fullHouse();
    bool flush();
    bool straight();
    int pair();
    int threeOfAKind();
    int twoPairs();
};

Hand::Hand() = default;

void Hand::addCard(Card card) {
    cards.push_back(card);
}

int Hand::size() {
    return cards.size();
}

void Hand::quickSort(int head, int end) {
    int pivot;
    if (head < end) {
        pivot = partition(head, end);
        quickSort(head, pivot - 1);
        quickSort(pivot + 1, end);
    }
}

int Hand::partition(int head, int end) {
    int x = cards.at(end).getValue();
    int i = head - 1, j;
    for (j = head; j < end; j++) {
        if (cards.at(j).getValue() < x) {
            i++;
            changePlace(i, j);
        }
    }
    changePlace(i + 1, end);
    return i + 1;
}

void Hand::changePlace(int i, int j) {
    Card temporary = cards.at(i);
    cards.at(i) = cards.at(j);
    cards.at(j) = temporary;
}

bool Hand::straightFlush() {
    for (int i = 0; i < cards.size() - 1; i++) {
        if (cards.at(i).getSuit() != cards.at(i + 1).getSuit() || cards.at(i).getValue() + 1 != cards.at(i + 1).getValue()) {
            return false;
        }
    }
    return true;
}

int Hand::compareTo(Hand second) {
    for (int i = cards.size() - 1; i >= 0; i--) {
        if (cards.at(i).compareTo(second.cards.at(i)) != 0) {
            return cards.at(i).compareTo(second.cards.at(i));
        }
    }
    return 0;
}

bool Hand::fourOfAKind() {
    int number = 0;
    int current = cards.at(0).getValue();
    for (int i = 0; i < cards.size(); i++) {
        if (i < cards.size() - 1) {
            if (cards.at(i + 1).getValue() == current) {
                number++;
            } else {
                current = cards.at(i + 1).getValue();
                number = 0;
            }
        }
    }
    return number == 3;
}

bool Hand::fullHouse() {
    vector<Card> copy = vector<Card>(cards);
    vector<int> cards1 = vector<int>();
    int number1 = 1;
    int number2 = 1;
    for (int i = 0; i < cards.size(); i++) {
        if (i < cards.size() - 1) {
            if (cards.at(i).getValue() == cards.at(i + 1).getValue()) {
                number1++;
                cards1.push_back(cards.at(i).getValue());
                cards1.push_back(cards.at(i).getValue());
            } else {
                break;
            }
        }
    }
    for (int j : cards1) {
        for (int k = 0; k < cards.size(); k++) {
            if (cards.at(k).getValue() == j) {
                cards.erase(cards.begin() + k);
            }
        }
    }
    for (int t = 0; t < cards.size(); t++) {
        if (t < cards.size() - 1) {
            if (cards.at(t).getValue() == cards.at(t + 1).getValue()) {
                number2++;
            } else {
                break;
            }
        }
    }
    cards = vector<Card>(copy);
    return number1 == 3 && number2 == 2 || number1 == 2 && number2 == 3;
}

bool Hand::flush() {
    for (int i = 0; i < cards.size(); i++) {
        if (i < cards.size() - 1) {
            if (cards.at(i).getSuit() != cards.at(i + 1).getSuit()) {
                return false;
            }
        }
    }
    return true;
}

bool Hand::straight() {
    for (auto & card : cards) {
        if (card.getValue() == 14) {
            card.setValue(1);
        }
    }
    for (int i = 0; i < cards.size(); i++) {
        if (i < cards.size() - 1) {
            for (auto & card : cards) {
                if (card.getValue() == 1) {
                    card.setValue(14);
                }
            }
            if (cards.at(i).getValue() + 1 != cards.at(i + 1).getValue()) {
                return false;
            }
        }
    }
    for (auto & card : cards) {
        if (card.getValue() == 1) {
            card.setValue(14);
        }
    }
    return true;
}

int Hand::pair() {
    int sum = 0;
    int number = 0;
    int current = cards.at(0).getValue();
    for (int i = 0; i < cards.size(); i++) {
        if (i < cards.size() - 1) {
            if (cards.at(i + 1).getValue() == current) {
                number++;
            } else {
                if (number == 1) {
                    sum = 1;
                }
                current = cards.at(i + 1).getValue();
                number = 0;
            }
        }
    }
    return sum;
}

int Hand::threeOfAKind() {
    int sum = 0;
    int number = 0;
    int current = cards.at(0).getValue();
    for (int i = 0; i < cards.size(); i++) {
        if (i < cards.size() - 1) {
            if (cards.at(i + 1).getValue() == current) {
                number++;
            } else {
                if (number == 2) {
                    sum = 1;
                }
                current = cards.at(i + 1).getValue();
                number = 0;
            }
        }
    }
    if (number == 2) {
        sum = 1;
    }
    return sum;
}

int Hand::twoPairs() {
    vector<int> cards1 = vector<int>();
    vector<Card> copy = vector<Card>(cards);
    int sum = 0;
    int number1 = 0;
    int number2 = 0;
    int current = cards.at(0).getValue();
    for (int i = 0; i < cards.size(); i++) {
        if (i < cards.size() - 1) {
            if (cards.at(i + 1).getValue() == current) {
                number1++;
                cards1.push_back(current);
                cards1.push_back(current);
            } else {
                if (number1 == 1) {
                    break;
                }
                current = cards.at(i + 1).getValue();
                number1 = 0;
            }
        }
    }
    for (int j = 0; j < cards1.size(); j++) {
        for (int k = 0; k < cards.size(); k++) {
            if (cards.at(k).getValue() == cards1.at(j)) {
                cards.erase(cards.begin() + k);
            }
        }
    }
    int current2 = cards.at(0).getValue();
    for (int i = 0; i < cards.size(); i++) {
        if (i < cards.size() - 1) {
            if (cards.at(i + 1).getValue() == current2) {
                number2++;
            } else {
                if (number1 == 1 && number2 == 1) {
                    sum = 1;
                }
                current2 = cards.at(i + 1).getValue();
                number2 = 0;
            }
        }
    }
    if (number1 == 1 && number2 == 1) {
        sum = 1;
    }
    cards = vector<Card>(copy);
    return sum;
}

#endif //PROGRAMMINGCHALLENGES_CPP_HAND_H
