//
// Created by Oğuz Kerem Yıldız on 1.01.2021.
//

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void selected(int **vote, int secondSection) {
    double firstSection[secondSection];
    vector<double> smallest = vector<double>();
    int i = 0, t = 0;
    vector<double> current = vector<double>();
    while (current.size() < secondSection / 2) {
        for (int j = 0; j < secondSection; j++) {
            if (smallest.size() > 0) {
                if (vote[i][j] == smallest.at(0)) {
                    firstSection[j] = vote[i + t][j];
                } else {
                    firstSection[j] = vote[i][j];
                }
            } else {
                firstSection[j] = vote[i][j];
            }
        }
        for (int k = 0; k < secondSection; k++) {
            current.push_back(firstSection[k]);
            for (int z = 0; z < secondSection; z++) {
                if (k != z) {
                    if (firstSection[k] == firstSection[z]) {
                        current.push_back(firstSection[z]);
                    }
                }
                if (z == secondSection - 1) {
                    if (current.size() >= secondSection / 2.0) {
                        cout << to_string(current.at(0)) + " candidate won." << endl;
                        return;
                    } else {
                        if (k == 0) {
                            for (int j = 0; j < current.size(); j++) {
                                smallest.push_back(current.at(i));
                            }
                        } else {
                            if (current.size() < smallest.size()) {
                                smallest.clear();
                                for (double j : current) {
                                    smallest.push_back(j);
                                }
                            }
                        }
                        current.clear();
                    }
                }
            }
        }
        t++;
    }
}

int main() {
    fstream file;
    file.open("Voting.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        while (true) {
            int firstSection, secondSection;
            file >> firstSection;
            file >> secondSection;
            if (firstSection == 0 && secondSection == 0) {
                break;
            }
            int **vote;
            vote = (int **)malloc(firstSection * sizeof(int *));
            for (int i = 0; i < firstSection; ++i) {
                vote[i] = (int*) malloc(secondSection * sizeof(int));
            }
            for (int j = 0; j < secondSection; j++) {
                for (int i = 0; i < firstSection; i++) {
                    file >> vote[i][j];
                }
            }
            selected(vote, secondSection);
        }
    }
}