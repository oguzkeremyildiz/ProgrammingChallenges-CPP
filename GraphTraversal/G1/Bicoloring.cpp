//
// Created by Oğuz Kerem Yıldız on 24.12.2020.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <Graph/Graph.h>

using namespace std;

bool containsAllValues(unordered_map<bool, vector<int>> colorMap, unordered_set<int> vertexList) {
    bool check = false;
    for (auto& key : colorMap) {
        for (int i = 0; i < colorMap[key.first].size(); i++) {
            check = false;
            for (int vertex : vertexList) {
                if (colorMap[key.first].at(i) == vertex) {
                    check = true;
                }
            }
            if (!check) {
                break;
            }
        }
        if (!check) {
            break;
        }
    }
    return check;
}

unordered_map<bool, vector<int>> addColor(Graph<int> graph, unordered_set<int> vertexList) {
    unordered_map<bool, vector<int>> colorMap = unordered_map<bool, vector<int>>();
    bool color = false;
    colorMap[false];
    colorMap[true];
    for (int key : graph.getKeySet()) {
        for (int i = 0; i < graph.get(key).size(); i++) {
            colorMap[true].push_back(graph.get(key, i));
        }
        break;
    }
    while (!containsAllValues(colorMap, vertexList)) {
        if (!color) {
            for (int i = 0; i < colorMap[true].size(); i++) {
                for (int j = 0; j < graph.get(colorMap[true].at(i)).size(); j++) {
                    colorMap[false].push_back(graph.get(colorMap[true].at(i), j));
                }
            }
            color = true;
        } else {
            for (int i = 0; i < colorMap[false].size(); i++) {
                for (int j = 0; j < graph.get(colorMap[false].at(i)).size(); j++) {
                    colorMap[true].push_back(graph.get(colorMap[false].at(i), j));
                }
            }
            color = false;
        }
    }
    return colorMap;
}

bool isBicolorable(unordered_map<bool, vector<int>> colorMap) {
    bool boolean = true;
    unordered_set<int> set = unordered_set<int>();
    for (int i = 0; i < colorMap[false].size(); ++i) {
        set.insert(colorMap[false].at(i));
    }
    for (int i = 0; i < colorMap[true].size(); i++) {
        if (set.find(colorMap[true].at(i)) != set.end()) {
            boolean = false;
            break;
        }
    }
    return boolean;
}

int main() {
    fstream file;
    file.open("Bicoloring.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        Graph<int> graph = Graph<int>();
        unordered_map<bool, vector<int>> colorMap;
        unordered_set<int> vertexList = unordered_set<int>();
        int times, edgeSize, vertex, edge;
        while (true) {
            file >> edgeSize;
            if (edgeSize > 0) {
                file >> times;
                for (int i = 0; i < times; i++) {
                    file >> vertex;
                    file >> edge;
                    vertexList.insert(vertex);
                    vertexList.insert(edge);
                    graph.addUnDirectedEdge(edge, vertex);
                }
                colorMap = addColor(graph, vertexList);
                if (isBicolorable(colorMap)) {
                    cout << "BICOLORABLE." << endl;
                } else {
                    cout << "NOT BICOLORABLE." << endl;
                }
                graph.clear();
                colorMap.clear();
            } else {
                break;
            }
        }
    }
}