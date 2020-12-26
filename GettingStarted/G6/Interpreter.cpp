//
// Created by Oğuz Kerem Yıldız on 26.12.2020.
//

#include <fstream>
#include <iostream>
#include <vector>
#include "utility"

using namespace std;

static int t = 0;

pair<int*, int*> ramMethod(int digit1, int digit2, int digit3, int *array, int *ram) {
    pair<int*, int*> returning = pair<int*, int*>();
    switch (digit1) {
        case 2:
            array[digit2] = digit3;
            t++;
            break;
        case 3:
            array[digit2] = (array[digit2] + digit3) % 1000;
            t++;
            break;
        case 4:
            array[digit2] = (array[digit2] * digit3) % 1000;
            t++;
            break;
        case 5:
            array[digit2] = array[digit3];
            t++;
            break;
        case 6:
            array[digit2] = (array[digit2] + array[digit3]) % 1000;
            t++;
            break;
        case 7:
            array[digit2] = (array[digit2] * array[digit3]) % 1000;
            t++;
            break;
        case 8:
            array[digit2] = ram[array[digit3]];
            t++;
            break;
        case 9:
            ram[array[digit3]] = array[digit2];
            t++;
            break;
        case 0:
            if (array[digit3] != 0) {
                t = array[digit2];
            } else {
                t++;
            }
            break;
        default:
            break;
    }
    returning.first = array;
    returning.second = ram;
    return returning;
}

int main() {
    fstream file;
    file.open("Interpreter.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int *array = new int[10];
        int count = 1, firstLine, number, j = 0;
        file >> firstLine;
        string line;
        getline(file, line);
        getline(file, line);
        for (int i = 0; i < firstLine; i++) {
            int *ram = new int[1000];
            while (!file.eof()) {
                getline(file, line);
                if (line.length() == 0) {
                    break;
                }
                number = stoi(line);
                ram[j] = number;
                j++;
            }
            t = 0;
            while (ram[t] != 100) {
                int temporary;
                vector<int> digit = vector<int>();
                temporary = ram[t] / 100;
                digit.push_back(temporary);
                temporary = (ram[t] / 10) % 10;
                digit.push_back(temporary);
                temporary = ram[t] % 10;
                digit.push_back(temporary);
                pair<int*, int*> pair = ramMethod(digit.at(digit.size() - 3), digit.at(digit.size() - 2), digit.at(digit.size() - 1), array, ram);
                array = pair.first;
                ram = pair.second;
                count++;
            }
            cout << count << endl;
            array = new int[10];
            j = 0;
            count = 1;
        }
    }
}