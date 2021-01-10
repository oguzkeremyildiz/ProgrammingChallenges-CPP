//
// Created by Oğuz Kerem Yıldız on 10.01.2021.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "Shoe.h"
#include "Util/Permutation.h"

using namespace std;

void print(vector<int> v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        if (i > 0) {
            cout << ", " + to_string(v.at(i));
        } else {
            cout << to_string(v.at(i));
        }
    }
    cout << "]";
}

void tryAll(vector<Shoe> shoes, int size) {
    Permutation p = Permutation(size);
    vector<int> currentShoesIndex = vector<int>();
    vector<int> shoesIndex = vector<int>();
    int wholeTime;
    int wholeCent = 0;
    int currentWholeCent;
    do{
        int *list = p.get();
        currentShoesIndex.clear();
        wholeTime = 0;
        currentWholeCent = 0;
        for (int i = 0; i < size; i++) {
            int value = list[i];
            currentWholeCent += wholeTime * shoes.at(value).getCent();
            wholeTime += shoes.at(value).getTime();
            currentShoesIndex.push_back(shoes.at(value).getIndex());
        }
        if (wholeCent == 0) {
            wholeCent = currentWholeCent;
            shoesIndex.insert(shoesIndex.end(), currentShoesIndex.begin(), currentShoesIndex.end());
        } else if (currentWholeCent < wholeCent){
            wholeCent = currentWholeCent;
            shoesIndex.clear();
            shoesIndex.insert(shoesIndex.end(), currentShoesIndex.begin(), currentShoesIndex.end());
        }
    }while (p.next());
    print(shoesIndex);
}

int main() {
    fstream file;
    file.open("Shoes.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int scenario;
        int shoesTimes;
        int time;
        int cent;
        file >> scenario;
        vector<Shoe> shoes;
        for (int i = 0; i < scenario; i++){
            file >> shoesTimes;
            shoes = vector<Shoe>();
            for (int j = 0; j < shoesTimes; j++){
                file >> time;
                file >> cent;
                shoes.emplace_back(time, cent, j + 1);
            }
            tryAll(shoes, shoesTimes);
        }
    }
}