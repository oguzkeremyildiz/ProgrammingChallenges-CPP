//
// Created by Oğuz Kerem Yıldız on 6.01.2021.
//
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Cars.h"
#include <istream>
#include <sstream>
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

void sort(unordered_map<int, int> &map, Car car, vector<int> &numbers, vector<int> &hours) {
    car.setMoney(car.getMoney() + (map.size() / 2) * 100);
    vector<int> keys = vector<int>();
    for (auto &key : map) {
        keys.push_back(key.first);
    }
    Comparator<int> *comparator = new IntegerComparator();
    QuickSort<int> quickSort = QuickSort<int>(comparator);
    quickSort.sort(keys, 0, keys.size() - 1);
    quickSort.sort(hours, 0, hours.size() - 1);
    int t = -1;
    for (int i = 0; i < map.size(); i++) {
        if (i % 2 == 0){
            t++;
            int total = map[keys.at(i + 1)] - map[keys.at(i)];
            car.setMoney(car.getMoney() + numbers.at(hours.at(t)) * total);
        }
    }
    cout << car.getName() + " " + to_string(car.getMoney()) << endl;
}

void print(Cars cars, vector<int> &numbers) {
    vector<int> hours = vector<int>();
    unordered_map<int, int> map = unordered_map<int, int>();
    unordered_set<string> names = unordered_set<string>();
    for (int i = 0; i < cars.size(); i++) {
        if (names.find(cars.getCar(i).getName()) == names.end()) {
            map[cars.getCar(i).getHour()] = cars.getCar(i).getKilometres();
            if (cars.getCar(i).getStatus() == "enter") {
                hours.push_back(cars.getCar(i).getHour());
            }
            for (int j = 0; j < cars.size(); j++) {
                if (i != j){
                    if (cars.getCar(i).getName()== cars.getCar(j).getName()) {
                        map[cars.getCar(j).getHour()] = cars.getCar(j).getKilometres();
                        if (cars.getCar(j).getStatus() == "enter") {
                            hours.push_back(cars.getCar(j).getHour());
                        }
                    }
                }
            }
        }
        if (names.find(cars.getCar(i).getName()) == names.end()){
            names.insert(cars.getCar(i).getName());
            sort(map, cars.getCar(i), numbers, hours);
            hours.clear();
            map.clear();
        }
    }
}

void addCar(Cars &cars, vector<string> &features) {
    int time;
    string timeString = "";
    vector<string> split = vector<string>();
    stringstream check(features.at(1));
    string intermediate;
    while (getline(check, intermediate, ':')) {
        split.push_back(intermediate);
    }
    for (const string& s : split) {
        timeString += s;
    }
    int hour = stoi(split[2]);
    time = stoi(timeString);
    cars.addCar(Car(features.at(0), features.at(2), time, hour, stoi(features.at(3)), 200));
}

int main() {
    fstream file;
    file.open("CDVII.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        string line;
        int convert;
        vector<string> split1 = vector<string>();
        vector<string> split2 = vector<string>();
        Cars cars = Cars();
        vector<int> numbers = vector<int>();
        vector<string> features = vector<string>();
        file >> convert;
        for (int i = 0; i < convert; i++) {
            getline(file, line);
            getline(file, line);
            stringstream check(line);
            string intermediate;
            while (getline(check, intermediate, ' ')) {
                split1.push_back(intermediate);
            }
            for (const string& s : split1) {
                numbers.push_back(stoi(s));
            }
            while (!file.eof()) {
                getline(file, line);
                stringstream check(line);
                string intermediate;
                while (getline(check, intermediate, ' ')) {
                    split2.push_back(intermediate);
                }
                for (const auto & j : split2) {
                    features.push_back(j);
                }
                addCar(cars, features);
                features.clear();
                split2.clear();
            }
            print(cars, numbers);
        }
    }
}