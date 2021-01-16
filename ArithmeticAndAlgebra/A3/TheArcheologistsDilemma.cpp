//
// Created by Oğuz Kerem Yıldız on 17.01.2021.
//
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

void reserve(vector<int> &numbers, int number) {
    while (number != 0){
        numbers.push_back(number % 10);
        number -= number % 10;
        number /= 10;
    }
}

bool isSuitable(int number, int temporary) {
    bool boolean = true;
    vector<int> numbers = vector<int>();
    vector<int> temporaries = vector<int>();
    reserve(numbers, number);
    reserve(temporaries, temporary);
    if (numbers.size() * 2 < temporaries.size()) {
        for (int i = 0; i < numbers.size(); i++) {
            if (numbers.at(numbers.size() - 1 - i) != temporaries.at(temporaries.size() - 1 - i)) {
                boolean = false;
                break;
            }
        }
    } else {
        boolean = false;
    }
    return boolean;
}

int main() {
    fstream file;
    file.open("Dilemma.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int number;
        int temporary;
        while (!file.eof()) {
            file >> number;
            int i = 1;
            while (pow(2, i) < 2147483647) {
                temporary = pow(2, i);
                if (isSuitable(number, temporary)) {
                    cout << i << endl;
                    break;
                } else {
                    i++;
                }
            }
        }
    }
}