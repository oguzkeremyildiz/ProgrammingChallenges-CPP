//
// Created by Oğuz Kerem Yıldız on 6.01.2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "Util/Permutation.h"
#include "Round.h"

using namespace std;

static string items[] = {"ones", "twos", "threes", "fours", "fives", "sixes",
                         "chance", "threeOfAKind", "fourOfAKind", "fiveOfAKind", "shortStraight", "longStraight", "fullHouse"};

int main() {
    fstream file;
    file.open("Yahtzee.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int i = 0;
        vector<Round> rounds = vector<Round>();
        string readNext;
        int *points = new int[13];
        while (!file.eof()) {
            i++;
            getline(file, readNext);
            rounds.emplace_back(readNext);
            if (i % 13 == 0){
                Permutation permutation = Permutation(13);
                int bestPoint = 0;
                do{
                    int *assignments = permutation.get();
                    int point = 0;
                    for (int k = 0; k < 13; k++) {
                        Round currentRound = rounds.at(k);
                        points[assignments[k]] = currentRound.calculate(assignments[k]);
                        point += points[assignments[k]];
                    }
                    int bonusPoint = 0;
                    for (int k = 0; k < 6; k++){
                        bonusPoint += points[k];
                    }
                    if (bonusPoint > 62){
                        point += 35;
                    }
                    if (point > bestPoint){
                        for (int k = 0; k < 13; k++){
                            rounds.at(k).print(items[assignments[k]]);
                        }
                        bestPoint = point;
                        for (int k = 0; k < 13; k++) {
                            cout << to_string(points[k]) + " ";
                        }
                        if (bonusPoint > 62) {
                            cout << "35 " + to_string(bestPoint) << endl;
                        } else {
                            cout << "0 " + to_string(bestPoint) << endl;
                        }
                    }
                } while (permutation.next());
                rounds.clear();
                i = 0;
            }
        }
    }
}