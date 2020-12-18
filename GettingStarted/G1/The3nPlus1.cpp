//
// Created by Oğuz Kerem Yıldız on 18.12.2020.
//
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int rule(int number1, int number2) {
    int biggest = 0;
    int count = 0;
    if (number2 > number1) {
        for (int i = number1; i <= number2; i++) {
            int temporary = i;
            count++;
            while (temporary != 1) {
                if (temporary % 2 == 0) {
                    temporary /= 2;
                    count++;
                } else {
                    temporary *= 3;
                    temporary += 1;
                    count++;
                }
            }
            if (count > biggest) {
                biggest = count;
            }
            count = 0;
        }
    }
    return biggest;
}

int main() {
    int i = 0;
    vector<int> number;
    fstream file;
    file.open("Numbers.txt", ios::in);
    int current;
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        while (!file.eof()) {
            i++;
            file >> current;
            number.push_back(current);
            if (i % 2 == 0) {
                cout << number.at(i - 2) << " " << number.at(i - 1) << " " << rule(number.at(i - 2), number.at(i - 1)) << endl;
            }
        }
    }
    file.close();
    return 0;
}
