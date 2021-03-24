//
// Created by Oğuz Kerem Yıldız on 27.01.2021.
//
#include <iostream>
#include "Roads.h"
#include <fstream>
#include "Graph/WeightedGraph.h"
#include "Graph/IntegerLength.h"
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct road_hash {
    size_t operator() (const Road& road) const {
        return road.getHour() ^ hash<string>{}(road.getName());
    }
};

void addEdge(WeightedGraph<Road, int, road_hash> &graph, Roads list) {
    if (graph.size() > 0) {
        graph.put(list.getFirst(), vector<pair<Road, Edge<int>*>>());
        for (int i = 1; i < list.size(); i++) {
            graph.addDirectedEdge(list.getFirst(), list.get(i), abs(list.get(i).getHour() - list.getFirst().getHour()));
        }
        for (int i = 0; i < list.size(); i++) {
            unordered_set<Road, road_hash> keys = graph.getVertexList();
            for (const Road& key : keys) {
                if (key.getName() == list.get(i).getName() && key != list.get(i)) {
                    if (key.getHour() < list.get(i).getHour()) {
                        graph.addDirectedEdge(key, list.get(i), abs(list.get(i).getHour() - key.getHour()));
                    } else {
                        graph.addDirectedEdge(list.get(i), key, abs(list.get(i).getHour() - key.getHour()));
                    }
                }
            }
        }
    } else {
        graph.put(list.getFirst(), vector<pair<Road, Edge<int>*>>());
        for (int i = 1; i < list.size(); i++) {
            graph.addDirectedEdge(list.getFirst(), list.get(i), abs(list.get(i).getHour() - list.getFirst().getHour()));
        }
    }
}

void findPath(WeightedGraph<Road, int, road_hash> graph, int open, string start, string finish) {
    vector<pair<Road, Road>> list = vector<pair<Road, Road>>();
    for (const Road& key : graph.getKeySet()) {
        if (key.getName() == start && key.getHour() > open) {
            unordered_map<Road, pair<int, Road>, road_hash> map = graph.bellmanFord(key);
            for (auto &element : map) {
                if (element.first.getName() == finish && element.second.first != INT_MAX) {
                    list.emplace_back(key, element.first);
                }
            }
        }
    }
    if (!list.empty()) {
        int best = INT_MAX;
        pair<Road, Road> p = {Road("", INT_MAX), Road("", INT_MAX)};
        for (const pair<Road, Road>& roadPair : list) {
            if (roadPair.second.getHour() < best) {
                p = pair<Road, Road>(roadPair.first, roadPair.second);
                best = roadPair.second.getHour();
            } else if (roadPair.second.getHour() == best) {
                if (p.first.getHour() != INT_MAX) {
                    if (roadPair.first.getHour() > p.first.getHour()) {
                        p = pair<Road, Road>(roadPair.first, roadPair.second);
                    }
                }
            }
        }
        if (p.first.getHour() != INT_MAX) {
            cout << "Departure " + to_string(p.first.getHour()) + " " + p.first.getName() << endl;
            cout << "Arrival " + to_string(p.second.getHour()) + " " + p.second.getName() << endl;
        }
    } else {
        cout << "No connection" << endl;
    }
}

int main() {
    fstream file;
    file.open("Road.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        Roads list = Roads();
        LengthInterface<int> *lengthInterface = new IntegerLength();
        WeightedGraph<Road, int, road_hash> graph = WeightedGraph<Road, int, road_hash>(lengthInterface);
        string times, edges, stations, size;
        file >> times;
        for (int i = 0; i < stoi(times); i++) {
            file >> edges;
            for (int j = 0; j < stoi(edges); j++) {
                string s;
                file >> s;
            }
            file >> stations;
            for (int j = 0; j < stoi(stations); j++) {
                file >> size;
                for (int k = 0; k < stoi(size); k++) {
                    string hour, name;
                    file >> hour;
                    file >> name;
                    list.add(Road(name, stoi(hour)));
                }
                addEdge(graph, list);
                list.clear();
            }
            string open, start, finish;
            file >> open;
            file >> start;
            file >> finish;
            cout << "Scenario " + to_string(i + 1) << endl;
            findPath(graph, stoi(open), start, finish);
            graph.clear();
            list.clear();
        }
    }
}