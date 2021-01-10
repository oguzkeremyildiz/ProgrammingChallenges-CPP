//
// Created by Oğuz Kerem Yıldız on 10.01.2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "Comparator.h"
#include "Sort/QuickSort.h"

using namespace std;

class IntegerComparator : public Comparator<int> {
public:
    IntegerComparator() = default;
    virtual int compare(int first, int second) {
        if (first > second) {
            return 1;
        } else if (first < second) {
            return -1;
        } else {
            return 0;
        }
    }
};

void print(int napStart, int longestNap, int day) {
    string napStartString = to_string(napStart);
    int hour, minute;
    napStartString = napStartString.substr(0, 2) + ":" + napStartString.substr(2);
    if (longestNap < 60) {
        cout << "Day #" + to_string(day) + " the longest nap starts at " + napStartString + " and will last for " + to_string(longestNap) + " minutes." << endl;
    } else {
        hour = longestNap / 60;
        minute = longestNap % 60;
        cout << "Day #" + to_string(day) + " the longest nap starts at " + napStartString + " and will last for " + to_string(hour) + " hours and " + to_string(minute) + " minutes." << endl;
    }
}

void convert(string line, vector<int> &first, vector<int> &last) {
    string firstString = "";
    int firstInt;
    string lastString = "";
    int lastInt;
    for (int i = 0; i < line.length(); i++) {
        if (i < 5){
            switch (line.at(i)) {
                case '1':
                    firstString += '1';
                    break;
                case '2':
                    firstString += '2';
                    break;
                case '3':
                    firstString += '3';
                    break;
                case '4':
                    firstString += '4';
                    break;
                case '5':
                    firstString += '5';
                    break;
                case '6':
                    firstString += '6';
                    break;
                case '7':
                    firstString += '7';
                    break;
                case '8':
                    firstString += '8';
                    break;
                case '9':
                    firstString += '9';
                    break;
                case '0':
                    firstString += '0';
                    break;
                default:
                    break;
            }
        } else {
            switch (line.at(i)) {
                case '1':
                    lastString += '1';
                    break;
                case '2':
                    lastString += '2';
                    break;
                case '3':
                    lastString += '3';
                    break;
                case '4':
                    lastString += '4';
                    break;
                case '5':
                    lastString += '5';
                    break;
                case '6':
                    lastString += '6';
                    break;
                case '7':
                    lastString += '7';
                    break;
                case '8':
                    lastString += '8';
                    break;
                case '9':
                    lastString += '9';
                    break;
                case '0':
                    lastString += '0';
                    break;
                default:
                    break;
            }
        }
    }
    firstInt = stoi(firstString);
    lastInt = stoi(lastString);
    first.push_back(firstInt);
    last.push_back(lastInt);
}

void longestNap(vector<int> &first, vector<int> &last, int napStart, int day) {
    int longestNap = 0;
    int timeFirst = 1000;
    int timeLast = 1800;
    Comparator<int> *comparator = new IntegerComparator();
    QuickSort<int> quickSort = QuickSort<int>(comparator);
    quickSort.sort(first, 0, first.size() - 1);
    quickSort.sort(last, 0, last.size() - 1);
    for (int i = 0; i < last.size(); i++) {
        if (i + 1 < first.size()){
            if (i == 0){
                if (first.at(i + 1) - last.at(i) > 60){
                    longestNap = ((first.at(i + 1) / 100) * 60) - ((last.at(i) / 100) * 60) + (first.at(i + 1) % 100) - (last.at(i) % 100);
                    napStart = last.at(i);
                } else {
                    longestNap = first.at(i + 1) - last.at(i);
                    napStart = last.at(i);
                }
            } else {
                if (first.at(i + 1) - last.at(i) > 60){
                    if (((first.at(i + 1) / 100) * 60) - ((last.at(i) / 100) * 60) + (first.at(i + 1) % 100) - (last.at(i) % 100) > longestNap) {
                        longestNap = ((first.at(i + 1) / 100) * 60) - ((last.at(i) / 100) * 60) + (first.at(i + 1) % 100) - (last.at(i) % 100);
                        napStart = last.at(i);
                    }
                } else {
                    if (first.at(i + 1) - last.at(i) > longestNap) {
                        longestNap = first.at(i + 1) - last.at(i);
                        napStart = last.at(i);
                    }
                }
            }
        }
    }
    if (timeLast - last.at(last.size() - 1) > longestNap){
        if (timeLast - last.at(last.size() - 1) > 60){
            longestNap = ((timeLast / 100) * 60) - ((last.at(last.size() - 1) / 100) * 60) - last.at(last.size() - 1) % 100;
            napStart = last.at(last.size() - 1);
        }
    } else {
        if (1760 - last.at(last.size() - 1) > longestNap){
            longestNap = 1760 - last.at(last.size() - 1);
            napStart = last.at(last.size() - 1);
        }
    }
    if (first.at(0) - timeFirst > longestNap){
        if (first.at(0) - timeFirst > 60){
            if (((first.at(0) / 100) * 60) - ((timeFirst / 100) * 60) + first.at(0) % 100 > longestNap){
                longestNap = ((first.at(0) / 100) * 60) - ((timeFirst / 100) * 60) + first.at(0) % 100;
                napStart = timeFirst;
            }
        } else {
            if (first.at(0) - timeFirst > longestNap){
                longestNap = first.at(0) - timeFirst;
                napStart = timeFirst;
            }
        }
    }
    print(napStart, longestNap, day);
}

int main() {
    fstream file;
    file.open("Nap.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int day = 0;
        int times;
        int napStart;
        string line;
        vector<int> first = vector<int>();
        vector<int> last = vector<int>();
        while (!file.eof()) {
            day++;
            first.clear();
            last.clear();
            napStart = 0;
            getline(file, line);
            times = stoi(line);
            for (int i = 0; i < times; i++) {
                getline(file, line);
                convert(line, first, last);
            }
            longestNap(first, last, napStart, day);
        }
    }
}