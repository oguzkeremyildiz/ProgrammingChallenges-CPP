//
// Created by Oğuz Kerem Yıldız on 19.12.2020.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int biggest(int array[], int currentBishopNumber) {
    if (currentBishopNumber < 1) {
        return -1;
    }
    return array[currentBishopNumber - 1];
}

bool isMatchWithBishop(int array[], int currentBishopNumber, int i, int j, int boardLength) {
    for (int k = 0; k < currentBishopNumber; k++) {
        int x = array[k] / boardLength;
        int y = array[k] % boardLength;
        if (abs(x - i) == abs(y - j)) {
            return true;
        }
    }
    return false;
}

vector<int> constructCandidates(int array[], int currentBishopNumber, int boardLength, int arrayLength) {
    vector<int> subsets;
    int x, y;
    if (biggest(array, currentBishopNumber) + arrayLength - currentBishopNumber >= boardLength * boardLength) {
        return subsets;
    }
    for (int i = biggest(array, currentBishopNumber) + 1; i < boardLength * boardLength; i++) {
        x = i / boardLength;
        y = i % boardLength;
        if (!isMatchWithBishop(array, currentBishopNumber, x, y, boardLength)) {
            subsets.push_back(i);
        }
    }
    return subsets;
}

int backtrack(int array[], int currentBishopNumber, int size, int boardLength) {
    int times = 0;
    if (currentBishopNumber == size) {
        times++;
    } else {
        vector<int> subsets = constructCandidates(array, currentBishopNumber, boardLength, size);
        for (int subset : subsets) {
            array[currentBishopNumber] = subset;
            times += backtrack(array, currentBishopNumber + 1, size, boardLength);
        }
    }
    return times;
}

int main() {
    fstream file;
    file.open("Bishops.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int size;
        int bishopsNumber;
        while (!file.eof()) {
            file >> size;
            file >> bishopsNumber;
            int total;
            if (size != 0 && bishopsNumber != 0){
                int array[bishopsNumber];
                total = backtrack(array, 0, bishopsNumber, size);
                cout << total << endl;
            } else {
                break;
            }
        }
    }
    file.close();
}
