//
// Created by Oğuz Kerem Yıldız on 7.01.2021.
//
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void commonCharacters(vector<char> &charactersList1, vector<char> &charactersList2) {
    int i = 0;
    int j = 0;
    while (i < charactersList1.size() && j < charactersList2.size()) {
        if (charactersList1.at(i) == charactersList2.at(j)) {
            cout << charactersList1.at(i);
            i++;
            j++;
        } else if (charactersList1.at(i) < charactersList2.at(j)) {
            i++;
        } else if (charactersList2.at(j) < charactersList1.at(i)) {
            j++;
        }
    }
}

void sort(vector<char> &list) {
    sort(list.begin(), list.end());
}

int main() {
    fstream file;
    file.open("Permutation.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        string firstWord;
        vector<char> charactersList1 = vector<char>();
        string secondWord;
        vector<char> charactersList2 = vector<char>();
        while (!file.eof()) {
            file >> firstWord;
            for (int i = 0; i < firstWord.length(); i++){
                charactersList1.push_back(firstWord.at(i));
            }
            file >> secondWord;
            for (int j = 0; j < secondWord.length(); j++){
                charactersList2.push_back(secondWord.at(j));
            }
            sort(charactersList1);
            sort(charactersList2);
            commonCharacters(charactersList1, charactersList2);
            cout << "" << endl;
            charactersList1.clear();
            charactersList2.clear();
        }
    }
}