//
// Created by Oğuz Kerem Yıldız on 16.01.2021.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void reserve(vector<int> &numbers1, vector<int> &numbers2, int number1, int number2) {
    while (number1 != 0) {
        numbers1.push_back(number1 % 10);
        number1 -= number1 % 10;
        number1 /= 10;
    }
    while (number2 != 0) {
        numbers2.push_back(number2 % 10);
        number2 -= number2 % 10;
        number2 /= 10;
    }
}

int carry(int number1, int number2) {
    int carry = 0;
    int t = 0;
    vector<int> numbers1 = vector<int>();
    vector<int> numbers2 = vector<int>();
    reserve(numbers1, numbers2, number1, number2);
    if (numbers1.size() > numbers2.size()) {
        for (int i = 0; i < numbers1.size(); i++) {
            if (i < numbers2.size()) {
                if (numbers1.at(i) + numbers2.at(i) + t > 9) {
                    carry++;
                    t = 1;
                } else {
                    t = 0;
                }
            } else {
                if (numbers1.at(i) + t > 9) {
                    carry++;
                    t = 1;
                } else {
                    t = 0;
                }
            }
        }
    } else if (numbers2.size() > numbers1.size()) {
        for (int i = 0; i < numbers2.size(); i++) {
            if (i < numbers1.size()) {
                if (numbers2.at(i) + numbers1.at(i) + t > 9) {
                    carry++;
                    t = 1;
                } else {
                    t = 0;
                }
            } else {
                if (numbers2.at(i) + t > 9) {
                    carry++;
                    t = 1;
                } else {
                    t = 0;
                }
            }
        }
    } else {
        for (int i = 0; i < numbers1.size(); i++) {
            if (numbers1.at(i) + numbers2.at(i) + t > 9) {
                carry++;
                t = 1;
            } else {
                t = 0;
            }
        }
    }
    return carry;
}

void print(int number1, int number2) {
    if (carry(number1, number2) >  1) {
        cout << to_string(carry(number1, number2)) + " carry operations." << endl;
    } else if (carry(number1, number2) == 1) {
        cout << "1 carry operation." << endl;
    } else {
        cout << "No carry." << endl;
    }
}

int main() {
    fstream file;
    file.open("Arithmetic.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int number1, number2;
        while (true) {
            file >> number1;
            file >> number2;
            if (number1 != 0 || number2 != 0) {
                print(number1, number2);
            } else {
                break;
            }
        }
    }
}