//
// Created by Oğuz Kerem Yıldız on 4.01.2021.
//
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool isSmaller(vector<int> fibonacciNumber, vector<int> number) {
    if (fibonacciNumber.size() < number.size()) {
        return true;
    } else if (fibonacciNumber.size() > number.size()) {
        return false;
    } else {
        for (int i = 0; i < fibonacciNumber.size(); i++) {
            if (fibonacciNumber.at(i) > number.at(i)) {
                return false;
            } else if (fibonacciNumber.at(i) < number.at(i)) {
                return true;
            }
        }
    }
    return true;
}

bool isBigger(vector<int> fibonacciNumber, vector<int> number) {
    if (fibonacciNumber.size() > number.size()) {
        return true;
    } else if (fibonacciNumber.size() < number.size()) {
        return false;
    } else {
        for (int i = 0; i < fibonacciNumber.size(); i++) {
            if (fibonacciNumber.at(i) < number.at(i)) {
                return false;
            } else if (fibonacciNumber.at(i) > number.at(i)) {
                return true;
            }
        }
    }
    return true;
}

void addFibonacci(vector<vector<int>> &fibonacciNumbers) {
    int number = 0;
    int current = 0;
    fibonacciNumbers.emplace_back();
    for (int j = 0; j < fibonacciNumbers.at(fibonacciNumbers.size() - 3).size(); j++) {
        vector<int> listOne = fibonacciNumbers.at(fibonacciNumbers.size() - 2);
        vector<int> listTwo = fibonacciNumbers.at(fibonacciNumbers.size() - 3);
        number += current;
        number += listOne.at(listOne.size() - j - 1);
        number += listTwo.at(listTwo.size() - j - 1);
        current = 0;
        if (number < 10) {
            fibonacciNumbers.at(fibonacciNumbers.size() - 1).push_back(number);
        } else {
            current = 1;
            fibonacciNumbers.at(fibonacciNumbers.size() - 1).push_back(number % 10);
        }
        number = 0;
    }
    if (fibonacciNumbers.at(fibonacciNumbers.size() - 2).size() != fibonacciNumbers.at(fibonacciNumbers.size() - 3).size()) {
        number += current;
        vector<int> listOne = fibonacciNumbers.at(fibonacciNumbers.size() - 2);
        number += listOne.at(0);
        fibonacciNumbers.at(fibonacciNumbers.size() - 1).push_back(number);
    } else if (current == 1) {
        fibonacciNumbers.at(fibonacciNumbers.size() - 1).push_back(1);
    }
    reverse(fibonacciNumbers.at(fibonacciNumbers.size() - 1).begin(), fibonacciNumbers.at(fibonacciNumbers.size() - 1).end());
}

int sum(vector<vector<int>> &fibonacciNumbers, vector<int> &numberOneList, vector<int> &numberTwoList) {
    int sum = 0;
    while (isSmaller(fibonacciNumbers.at(fibonacciNumbers.size() - 1), numberTwoList)) {
        if (isBigger(fibonacciNumbers.at(fibonacciNumbers.size() - 1), numberOneList)) {
            sum++;
        }
        addFibonacci(fibonacciNumbers);
    }
    return sum;
}

int main() {
    fstream file;
    file.open("Fibs.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        while (true) {
            string numberOne, numberTwo;
            file >> numberOne;
            file >> numberTwo;
            vector<int> numberOneList = vector<int>();
            vector<int> numberTwoList = vector<int>();
            vector<vector<int>> fibonacciNumbers = vector<vector<int>>();
            fibonacciNumbers.emplace_back();
            fibonacciNumbers.at(0).push_back(1);
            fibonacciNumbers.emplace_back();
            fibonacciNumbers.at(1).push_back(1);
            fibonacciNumbers.emplace_back();
            fibonacciNumbers.at(2).push_back(2);
            if (numberOne == "0" && numberTwo =="0") {
                break;
            } else {
                for (char i : numberOne) {
                    string s;
                    s.append(1, i);
                    numberOneList.push_back(stoi(s));
                }
                for (char i : numberTwo) {
                    string s;
                    s.append(1, i);
                    numberTwoList.push_back(stoi(s));
                }
            }
            cout << sum(fibonacciNumbers, numberOneList, numberTwoList) << endl;
            numberOneList.clear();
            numberTwoList.clear();
            fibonacciNumbers.clear();
        }
    }
}