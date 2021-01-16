//
// Created by Oğuz Kerem Yıldız on 17.01.2021.
//
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int digit(int number) {
    int i = 0;
    while (number != 0) {
        i++;
        number -= number % 10;
        number /= 10;
    }
    return i;
}

int addDigit(int number, int iterator) {
    int temporary = number;
    if (iterator != 0) {
        temporary = number * 10;
        temporary++;
    }
    return temporary;
}

void addList(vector<int> &temporary) {
    temporary.push_back(1);
}

bool isDividable(vector<int> temporary, int number) {
    bool boolean = false;
    int willDivide = 1;
    int remaining = 0;
    int iterator = 0;
    int i = 0;
    if (temporary.size() > digit(number)) {
        vector<int> copy = vector<int>(temporary.begin(), temporary.end());
        while (digit(number) + 1 != iterator){
            willDivide = addDigit(willDivide, iterator);
            copy.erase(copy.begin() + 0);
            iterator++;
        }
        while (copy.size() != 0) {
            if (i == 0){
                remaining = (willDivide % number) * 10;
            } else {
                remaining = (remaining % number) * 10;
            }
            remaining++;
            copy.erase(copy.begin() + 0);
            i++;
            if (copy.size() == 0) {
                if (remaining % number == 0) {
                    boolean = true;
                    break;
                }
            }
        }
    }
    return boolean;
}

int divide(int number) {
    vector<int> temporary = vector<int>();
    while (true) {
        if (isDividable(temporary, number)) {
            break;
        } else {
            addList(temporary);
        }
    }
    return temporary.size();
}

int main() {
    fstream file;
    file.open("Ones.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int number;
        while (!file.eof()) {
            file >> number;
            cout << to_string(divide(number)) << endl;
        }
    }
}