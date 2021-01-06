//
// Created by Oğuz Kerem Yıldız on 6.01.2021.
//

#include "Round.h"

class IntegerComparator : public Comparator<int> {
public:
    IntegerComparator() = default;
    virtual int compare(int first, int second) {
        if (first > second) {
            return 1;
        } else if (first < second) {
            return -1;
        } else {
            return 0;
        }
    }
};

Round::Round(string readNext) {
    vector<string> split = vector<string>();
    stringstream check(readNext);
    string intermediate;
    while (getline(check, intermediate, ' ')) {
        split.push_back(intermediate);
    }
    dices = vector<int>();
    for (int t = 0; t < split.size(); t++) {
        int splitInt = stoi(split[t]);
        dices.push_back(splitInt);
    }
    sort();
}

Round::Round() = default;

void Round::sort() {
    Comparator<int> *comparator = new IntegerComparator();
    TimSort<int> timSort = TimSort<int>(comparator);
    timSort.sort(dices, dices.size());
}

int Round::sum() {
    int sum = 0;
    for (int dice : dices) {
        sum += dice;
    }
    return sum;
}

void Round::print(string head) {
    for (int dice : dices) {
        cout << to_string(dice) + " ";
    }
    cout << head << endl;
}

int Round::basicCategories(int dice) {
    int sum = 0;
    for (int i = 0; i < dices.size(); i++) {
        if (dices.at(i) == dice){
            sum += dice;
        }
    }
    return sum;
}

int Round::maxOfAKind() {
    int count = 1;
    int max = 0;
    int previous = dices.at(0);
    for (int i = 1; i < dices.size(); i++) {
        if (dices.at(i) == previous) {
            count++;
        } else {
            if (count > max) {
                max = count;
            }
            count = 1;
            previous = dices.at(i);
        }
    }
    if (count > max) {
        max = count;
    }
    return max;
}

int Round::fiveOfAKind() {
    if (maxOfAKind() == 5) {
        return 50;
    } else {
        return 0;
    }
}

int Round::fourOfAKind() {
    if (maxOfAKind() >= 4) {
        return sum();
    } else {
        return 0;
    }
}

int Round::calculate(int type) {
    switch (type) {
        case 0:
            return basicCategories(1);
        case 1:
            return basicCategories(2);
        case 2:
            return basicCategories(3);
        case 3:
            return basicCategories(4);
        case 4:
            return basicCategories(5);
        case 5:
            return basicCategories(6);
        case 6:
            return sum();
        case 7:
            return threeOfAKind();
        case 8:
            return fourOfAKind();
        case 9:
            return fiveOfAKind();
        case 10:
            return shortStraight();
        case 11:
            return longStraight();
        case 12:
            return fullHouse();
    }
    return 0;
}

int Round::threeOfAKind() {
    if (maxOfAKind() >= 3) {
        return sum();
    } else {
        return 0;
    }
}

int Round::longStraight() {
    for (int i = 0; i < dices.size() - 1; i++) {
        if (dices.at(i) + 1 != dices.at(i + 1)) {
            return 0;
        }
    }
    return 35;
}

int Round::shortStraight() {
    bool flag = true;
    for (int i = 0; i < dices.size() - 2; i++) {
        if (dices.at(i) + 1 != dices.at(i + 1)) {
            flag = false;
            break;
        }
    }
    if (flag) {
        return 25;
    }
    for (int i = 1; i < dices.size() - 1; i++) {
        if (dices.at(i) + 1 != dices.at(i + 1)) {
            return 0;
        }
    }
    return 25;
}

int Round::fullHouse() {
    if (dices.at(0) == dices.at(1) && dices.at(3) == dices.at(4)) {
        if (dices.at(1) == dices.at(2) && dices.at(2) != dices.at(3)) {
            return 40;
        }
        if (dices.at(1) != dices.at(2) && dices.at(2) == (dices.at(3))) {
            return 40;
        }
    }
    return 0;
}
