//
// Created by Oğuz Kerem Yıldız on 18.01.2021.
//
#include <iostream>
#include <vector>

using namespace std;

int numberTotal(int number) {
    int total = 0;
    if (number == 0) {
        return 0;
    }else {
        for (int i = 1; i <= number; i++) {
            total += i;
        }
    }
    return total;
}

int main() {
    int numberOfEntries;
    cin >> numberOfEntries;
    for (int i = 1; i <= numberOfEntries; i++) {
        int number1, number2;
        cin >> number1;
        cin >> number2;
        int number = number2 - number1;
        int numberYD = 0;
        vector<int> shortCut = vector<int>();
        if (number2 > number1) {
            while (number != 0) {
                while (numberTotal(numberYD) < number) {
                    numberYD++;
                    if (numberTotal(numberYD) < number) {
                        if (numberYD != 0){
                            number -= numberYD;
                            shortCut.push_back(numberYD);
                        }
                    }
                } while (numberTotal(numberYD) == number) {
                    number -= numberYD;
                    if (numberYD != 0){
                        shortCut.push_back(numberYD);
                    }
                } while (numberTotal(numberYD) > number) {
                    numberYD--;
                    if (numberYD != 0){
                        number -= numberYD;
                        shortCut.push_back(numberYD);
                    }
                }
            }
        }
        cout << shortCut.size();
    }
}