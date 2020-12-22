//
// Created by Oğuz Kerem Yıldız on 20.12.2020.
//

#include <iostream>
#include <vector>

using namespace std;


void upSide(int area, string **region, int m) {
    if (m == 0) {
        for (int t = 0; t < area; t++) {
            region[0][t + 1] = "-";
        }
    } else {
        for (int t = 0; t < area; t++) {
            region[0][m * (area + 2) + t + 2] = "-";
        }
    }
}
void leftUpSide(int area, string **region, int m) {
    if (m == 0) {
        for (int k = 1; k < area + 1; k++) {
            region[k][0] = "|";
        }
    } else {
        for (int k = 1; k < area + 1; k++) {
            region[k][m * (area + 2) + 1] = "|";
        }
    }
}
void rightUpSide(int area, string **region, int m) {
    if (m == 0){
        for (int k = 1; k < area + 1; k++) {
            region[k][area + 1] = "|";
        }
    } else {
        for (int k = 1; k < area + 1; k++) {
            region[k][m * (area + 2) + 1 + (area + 1)] = "|";
        }
    }
}
void middleSide(int area, string **region, int m) {
    if (m == 0) {
        for (int i = 0; i < area; i++) {
            region[area + 1][i + 1] = "-";
        }
    } else {
        for (int i = 0; i < area; i++) {
            region[area + 1][m * (area + 2) + i + 2] = "-";
        }
    }
}
void leftUnderSide(int area, string **region, int m) {
    if (m == 0) {
        for (int d = area + 3; d < (2 * area) + 3; d++) {
            region[d - 1][0] = "|";
        }
    } else {
        for (int d = area + 3; d < (2 * area) + 3; d++) {
            region[d - 1][m * (area + 2) + 1] = "|";
        }
    }
}
void rightUnderSide(int area, string **region, int m) {
    if (m == 0) {
        for (int d = area + 3; d < (2 * area) + 3; d++) {
            region[d - 1][area + 1] = "|";
        }
    } else {
        for (int d = area + 3; d < (2 * area) + 3; d++) {
            region[d - 1][m * (area + 2) + 1 + (area + 1)] = "|";
        }
    }
}
void underSide(int area, string **region, int m) {
    if (m == 0) {
        for (int z = 0; z < area; z++) {
            region[(2 * area) + 2][z + 1] = "-";
        }
    } else {
        for (int z = 0; z < area; z++) {
            region[(2 * area) + 2][m * (area + 2) + z + 2] = "-";
        }
    }
}

void print(int area, string **region, vector<int> digitsReverse, int area1, int area2) {
    for (int m = 0; m < digitsReverse.size(); m++) {
        switch (digitsReverse.at(m)) {
            case 1:
                rightUpSide(area, region, m);
                rightUnderSide(area, region, m);
                break;
            case 2:
                upSide(area, region, m);
                rightUpSide(area, region, m);
                middleSide(area, region, m);
                leftUnderSide(area, region, m);
                underSide(area, region, m);
                break;
            case 3:
                upSide(area, region, m);
                rightUpSide(area, region, m);
                middleSide(area, region, m);
                rightUnderSide(area, region, m);
                underSide(area, region, m);
                break;
            case 4:
                leftUpSide(area, region, m);
                rightUpSide(area, region, m);
                middleSide(area, region, m);
                rightUnderSide(area, region, m);
                break;
            case 5:
                upSide(area, region, m);
                leftUpSide(area, region, m);
                middleSide(area, region, m);
                rightUnderSide(area, region, m);
                underSide(area, region, m);
                break;
            case 6:
                upSide(area, region, m);
                leftUpSide(area, region, m);
                middleSide(area, region, m);
                leftUnderSide(area, region, m);
                rightUnderSide(area, region, m);
                underSide(area, region, m);
                break;
            case 7:
                upSide(area, region, m);
                rightUpSide(area, region, m);
                rightUnderSide(area, region, m);
                break;
            case 8:
                upSide(area, region, m);
                leftUpSide(area, region, m);
                rightUpSide(area, region, m);
                middleSide(area, region, m);
                leftUnderSide(area, region, m);
                rightUnderSide(area, region, m);
                underSide(area, region, m);
                break;
            case 9:
                upSide(area, region, m);
                leftUpSide(area, region, m);
                rightUpSide(area, region, m);
                middleSide(area, region, m);
                rightUnderSide(area, region, m);
                underSide(area, region, m);
                break;
            case 0:
                upSide(area, region, m);
                leftUpSide(area, region, m);
                rightUpSide(area, region, m);
                leftUnderSide(area, region, m);
                rightUnderSide(area, region, m);
                underSide(area, region, m);
                break;
            default:
                break;
        }
    }
    for (int i = 0; i < area1; i++) {
        for (int j = 0; j < area2; j++) {
            printf("%s", region[i][j].c_str());
        }
        cout << "" << endl;
    }
}

int main() {
    int region = 1, number, temporary;
    while (region != 0) {
        cin >> region;
        cin >> number;
        vector<int> digits = vector<int>();
        vector<int> digitsReverse = vector<int>();
        while (number != 0) {
            temporary = number % 10;
            number = (number - temporary) / 10;
            digits.push_back(temporary);
        }
        for (int m = 0; m < digits.size(); m++) {
            digitsReverse.push_back(digits.at(digits.size() - m - 1));
        }
        int area1 = ((2 * region) + 4);
        int area2 = ((region + 2) * digits.size()) + (digits.size());
        string **area;
        area = (string **)malloc(area1 * sizeof(string *));
        for (int i = 0; i < area1; i++) {
            area[i] = (string *) malloc(area2 * sizeof(string));
        }
        if (region != 0) {
            for (int i = 0; i < ((2 * region) + 4); i++) {
                for (int j = 0; j < (((region + 2) * digits.size()) + (digits.size())); j++) {
                    area[i][j] = " ";
                }
            }
            if (region > 0) {
                print(region, area, digitsReverse, area1, area2);
            }
        }
    }
}
