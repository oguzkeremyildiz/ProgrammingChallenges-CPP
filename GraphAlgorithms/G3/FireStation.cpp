//
// Created by Oğuz Kerem Yıldız on 26.12.2020.
//

#include <fstream>
#include "Graph/WeightedGraph.h"
#include "Graph/IntegerLength.h"
#include <iostream>
#include <vector>
#include "utility"
#include <unordered_set>
#include <unordered_map>

using namespace std;

unordered_map<int, int> reverse(unordered_map<int, int> map) {
    unordered_map<int, int> reversed = unordered_map<int, int>();
    for (auto &key : map) {
        reversed[key.second] = key.first;
    }
    return reversed;
}

int findSmallest(WeightedGraph<int, int> graph, int *stations, unordered_set<int> set, int size) {
    unordered_map<int, int> values = unordered_map<int, int>();
    pair<unordered_map<int, int>, vector<vector<int>>> pair = graph.floydWarshallWithKeys();
    unordered_map<int, int> reversed = reverse(pair.first);
    for (auto &key : pair.first) {
        int current = 0;
        if (set.find(key.second) == set.end()) {
            for (int j = 0; j < graph.size(); j++) {
                vector<vector<int>> second = pair.second;
                int now = second.at(key.first).at(j);
                for (int i = 0; i < size; i++) {
                    if (pair.second.at(reversed[stations[i]]).at(j) < now) {
                        now = pair.second.at(reversed[stations[i]]).at(j);
                    }
                }
                if (now > current) {
                    current = now;
                }
            }
            values[key.second] = current;
        }
    }
    if (values.size() == 0) {
        return 1;
    }
    int returning = 0;
    int best = INT_MAX;
    for (auto &key : values) {
        if (best > key.second) {
            best = key.second;
            returning = key.first;
        }
    }
    return returning;
}

int main() {
    fstream file;
    file.open("Station.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        unordered_set<int> set = unordered_set<int>();
        LengthInterface<int> *lengthInterface = new IntegerLength();
        WeightedGraph<int, int> graph = WeightedGraph<int, int>(lengthInterface);
        int *stations;
        int times, stationNumber, buildNumber;
        file >> times;
        for (int i = 0; i < times; i++) {
            file >> stationNumber;
            stations = new int[stationNumber];
            file >> buildNumber;
            for (int j = 0; j < stationNumber; j++) {
                file >> stations[j];
                set.insert(stations[j]);
            }
            int first, second, third;
            for (int j = 0; j < buildNumber; j++) {
                file >> first;
                file >> second;
                file >> third;
                graph.addUndirectedEdge(first, second, third);
            }
            cout << findSmallest(graph, stations, set, stationNumber) << endl;
            graph.clear();
            set.clear();
        }
    }
}