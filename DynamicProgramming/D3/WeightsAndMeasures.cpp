//
// Created by Oğuz Kerem Yıldız on 23.12.2020.
//

#include <Tuple/Pair.h>
#include <vector>
#include <fstream>
#include <iostream>
#include "Turtle.h"

using namespace std;

void sort(vector<Turtle> &list) {
    for (int i = 0; i < list.size(); i++) {
        for (int j = 0; j < list.size(); j++) {
            if (list.at(i).getPair().getKey() < list.at(j).getPair().getKey()) {
                Turtle temporary = list.at(i);
                list.at(i) = list.at(j);
                list.at(j) = temporary;
            }
        }
    }
}

int find(vector<Turtle> list) {
    int best = 0;
    int total[list.size()];
    for (int i = 0; i < list.size(); i++) {
        total[i] = list.at(i).getPair().getKey();
    }
    int array[list.size()];
    for (int i = 0; i < list.size(); ++i) {
        array[i] = 1;
    }
    for (int i = 1; i < list.size(); i++) {
        int index = -1;
        int totalWeight = INT_MAX;
        for (int j = 0; j < i; j++) {
            if (index > -1) {
                if (array[j] >= array[index] && list.at(i).getPair().getValue() >= total[j] + list.at(index).getPair().getKey()) {
                    if (array[j] == array[index]) {
                        if (totalWeight >= total[j] + list.at(index).getPair().getKey()) {
                            totalWeight = total[j];
                            index = j;
                        }
                    } else {
                        totalWeight = total[j];
                        index = j;
                    }
                }
            } else {
                if (array[j] >= array[i] && list.at(i).getPair().getValue() >= total[j] + list.at(i).getPair().getKey()) {
                    totalWeight = total[j];
                    index = j;
                }
            }
        }
        if (index > -1) {
            array[i] = array[index] + 1;
            total[i] += totalWeight;
        }
    }
    for (int value : array) {
        if (value > best) {
            best = value;
        }
    }
    return best;
}

int main() {
    fstream file;
    file.open("Weights.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        vector<Turtle> list = vector<Turtle>();
        int index = -1;
        while (!file.eof()) {
            index++;
            int key, value;
            file >> key;
            file >> value;
            Pair<int, int> pair = Pair<int, int>(key, value);
            list.emplace_back(index, pair);
        }
        sort(list);
        cout << find(list) << endl;
    }
}
