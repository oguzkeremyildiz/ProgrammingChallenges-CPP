//
// Created by Oğuz Kerem Yıldız on 18.12.2020.
//
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void leftSide(int number1, int number2, int **mine) {
    if (number2 - 1 > -1) {
        mine[number1][number2 - 1]++;
    }
}

void upSide(int number1, int number2, int **mine) {
    if (number1 - 1 > -1) {
        mine[number1 - 1][number2]++;
    }
}

void leftUpSide(int number1, int number2, int **mine) {
    if (number1 - 1 > -1 && number2 - 1 > -1) {
        mine[number1 - 1][number2 - 1]++;
    }
}

void underSide(int number1, int number2, int **mine, int size) {
    if (number1 + 1 < size) {
        mine[number1 + 1][number2]++;
    }
}

void rightSide(int number1, int number2, int **mine, int size) {
    if (number2 + 1 < size) {
        mine[number1][number2 + 1]++;
    }
}

void rightUpSide(int number1, int number2, int **mine, int size) {
    if (number1 - 1 > -1 && number2 + 1 < size) {
        mine[number1 - 1][number2 + 1]++;
    }
}

void rightUnderSide(int number1, int number2, int **mine, int size1, int size2) {
    if (number1 + 1 < size1 && number2 + 1 < size2) {
        mine[number1 + 1][number2 + 1]++;
    }
}

void leftUnderSide(int number1, int number2, int **mine, int size) {
    if (number1 + 1 < size && number2 - 1 > -1) {
        mine[number1 + 1][number2 - 1]++;
    }
}

int main() {
    fstream file;
    file.open("Minesweeper.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int count = 0;
        while (true) {
            int area1;
            file >> area1;
            int area2;
            file >> area2;
            if (area1 == 0 && area2 == 0) {
                break;
            }
            int **area;
            area = (int **)malloc(area1 * sizeof(int *));
            for (int i = 0; i < sizeof(area); ++i) {
                area[i] = (int*) malloc(area2 * sizeof(int));
            }
            int **mine;
            mine = (int **)malloc(area1 * sizeof(int *));
            for (int i = 0; i < sizeof(mine); ++i) {
                mine[i] = (int*) malloc(area2 * sizeof(int));
            }
            for (int i = 0; i < area1; ++i) {
                for (int j = 0; j < area2; ++j) {
                    mine[i][j] = 0;
                    area[i][j] = 0;
                }
            }
            count += 1;
            cout << count << endl;
            string line;
            for (int t = 0; t < area1; t++) {
                file >> line;
                for (int j = 0; j < area2; j++) {
                    if (line.at(j) == '*') {
                        area[t][j] = 1;
                    }
                }
            }
            for (int z = 0; z < area1; z++) {
                for (int k = 0; k < area2; k++) {
                    if (area[z][k] == 1) {
                        leftSide(z, k, mine);
                        rightSide(z, k, mine, area2);
                        rightUpSide(z ,k, mine, area2);
                        leftUpSide(z, k, mine);
                        upSide(z, k, mine);
                        underSide(z, k, mine, area1);
                        rightUnderSide(z, k, mine, area1, area2);
                        leftUnderSide(z, k, mine, area1);
                    }
                }
            }
            for (int t = 0; t < area1; t++) {
                for (int j = 0; j < area2; j++) {
                    if (area[t][j] == 1) {
                        printf("x");
                    } else {
                        printf("%d", mine[t][j]);
                    }
                }
                printf("\n");
            }
        }
    }
    file.close();
    return 0;
}