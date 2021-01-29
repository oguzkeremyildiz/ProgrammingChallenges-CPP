//
// Created by Oğuz Kerem Yıldız on 27.01.2021.
//
#include <iostream>
#include <fstream>
#include <utility>
#include "Tuple/Triplet.h"
#include "Tuple/Quartet.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

static int minimum;

struct triplet_hash
{
    template <class T1, class T2, class T3>
    std::size_t operator() (const Triplet<T1, T2, T3> &triplet) const
    {
        return std::hash<T1>()(triplet.getA()) ^ std::hash<T2>()(triplet.getB()) ^ std::hash<T3>()(triplet.getC());
    }
};

bool drinkForTransportation(int timeOne, int timeTwo) {
    if (timeOne > timeTwo) {
        return timeOne >= 12 && 12 <= timeTwo;
    } else if (timeTwo > timeOne) {
        for (int i = timeOne; i <= timeTwo; i++) {
            if (i == 12) {
                return true;
            }
        }
    } else {
        return false;
    }
    return false;
}

int setTime(int currentTime, int addedOne) {
    int total = currentTime + addedOne;
    if (total > 24) {
        total = (currentTime + addedOne) - 24;
    }
    return total;
}

bool drink(int currentTime, int addedOne) {
    if (addedOne < 24) {
        int last = setTime(currentTime, addedOne);
        return last >= 12 && 12 >= currentTime;
    }
    return true;
}

bool checkTime(int time) {
    if (time > 17) {
        return true;
    } else return time < 7;
}

int breadthFirstSearch(unordered_map<string, vector<Triplet<string, int, int>>> map, const Triplet<string, int, int>& current, const pair<string, string>& directions) {
    int iterate = 1;
    int returning = 0;
    unordered_map<int, vector<Quartet<int, string, int, int>>> bfs = unordered_map<int, vector<Quartet<int, string, int, int>>>();
    unordered_set<Triplet<string, int, int>, triplet_hash> visited = unordered_set<Triplet<string, int, int>, triplet_hash>();
    vector<Quartet<int, string, int, int>> destinationList = vector<Quartet<int, string, int, int>>();
    visited.insert(current);
    bfs[iterate] = vector<Quartet<int, string, int, int>>();
    if (drink(current.getB(), current.getC())) {
        bfs[iterate].push_back(Quartet<int, string, int, int>(1, current.getA(), current.getB(), current.getC()));
    } else {
        bfs[iterate].push_back(Quartet<int, string, int, int>(0, current.getA(), current.getB(), current.getC()));
    }
    do {
        iterate++;
        bfs[iterate] = vector<Quartet<int, string, int, int>>();
        for (int i = 0; i < bfs[iterate - 1].size(); i++) {
            Quartet<int, string, int, int> from = bfs[iterate - 1].at(i);
            if (map.find(from.getB()) != map.end()) {
                for (int j = 0; j < map[from.getB()].size(); j++) {
                    Triplet<string, int, int> to = map[from.getB()].at(j);
                    if (visited.find(to) == visited.end()) {
                        if (checkTime(to.getB()) && checkTime(setTime(to.getB(), to.getC()))) {
                            int time = from.getA();
                            if (drinkForTransportation(setTime(from.getC(), from.getD()), to.getB())) {
                                time++;
                            }
                            if (drink(to.getB(), to.getC())) {
                                time++;
                            }
                            bfs[iterate].push_back(Quartet<int, string, int, int>(time, to.getA(), to.getB(), to.getC()));
                            if (to.getA() == directions.second) {
                                destinationList.push_back(bfs[iterate].at(bfs[iterate].size() - 1));
                            }
                            visited.insert(to);
                        }
                    }
                }
            }
        }
    } while (!bfs[iterate].empty());
    for (const Quartet<int, string, int, int>& element : destinationList) {
        if (returning == 0 || element.getA() < returning) {
            returning = element.getA();
        }
    }
    return returning;
}

int find(unordered_map<string, vector<Triplet<string, int, int>>> map, const pair<string, string>& directions) {
    for (int i = 0; i < map[directions.first].size(); i++) {
        Triplet<string, int, int> current = map[directions.first].at(i);
        if (checkTime(current.getB()) && checkTime(setTime(current.getB(), current.getC()))) {
            int count = breadthFirstSearch(map, current, directions);
            if (count > 0 && minimum == 0) {
                minimum = count;
            } else {
                if (count != 0) {
                    if (count < minimum) {
                        minimum = count;
                    }
                }
            }
        }
    }
    return minimum;
}

int main() {
    fstream file;
    file.open("Vladimir.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        unordered_map<string, vector<Triplet<string, int, int>>> map = unordered_map<string, vector<Triplet<string, int, int>>>();
        int times, numberOfPath;
        file >> times;
        int testCases = 0;
        for (int i = 0; i < times; i++) {
            file >> numberOfPath;
            minimum = 0;
            testCases++;
            for (int j = 0; j < numberOfPath; j++) {
                string placeOne, placeTwo, one, two;
                file >> placeOne;
                file >> placeTwo;
                file >> one;
                file >> two;
                if (map.find(placeOne) == map.end()) {
                    map[placeOne] = vector<Triplet<string, int, int>>();
                }
                map[placeOne].push_back(Triplet<string, int, int>(placeTwo, stoi(one), stoi(two)));
            }
            string from, to;
            file >> from;
            file >> to;
            pair<string, string> directions = pair<string, string>(from, to);
            int count = find(map, directions);
            cout << "Test Case " + to_string(testCases) + "." << endl;
            if (minimum == 0) {
                cout << "There is no route Vladimir can take." << endl;
            } else {
                cout << "Vladimir needs " + to_string(count) + " litre(s) of blood." << endl;
            }
            map.clear();
        }
    }
}