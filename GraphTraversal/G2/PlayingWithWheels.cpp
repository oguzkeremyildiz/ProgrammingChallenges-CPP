//
// Created by Oğuz Kerem Yıldız on 27.12.2020.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include "Graph/Graph.h"
#include <utility>

using namespace std;

vector<string> changeDigit(int i, string current) {
    vector<string> list = vector<string>();
    string str(1, current.at(i));
    int currentDigit = stoi(str);
    if (currentDigit == 9) {
        list.push_back(current.substr(0, i) + "0" + current.substr(i + 1));
        list.push_back(current.substr(0, i) + "8" + current.substr(i + 1));
    } else if (currentDigit == 0) {
        list.push_back(current.substr(0, i) + "1" + current.substr(i + 1));
        list.push_back(current.substr(0, i) + "9" + current.substr(i + 1));
    } else {
        list.push_back(current.substr(0, i) + to_string(currentDigit + 1) + current.substr(i + 1));
        list.push_back(current.substr(0, i) + to_string(currentDigit - 1) + current.substr(i + 1));
    }
    return list;
}

vector<string> constructCandidates(string current) {
    vector<string> list = vector<string>();
    for (int i = 0; i < 4; i++) {
        vector<string> vector = changeDigit(i, current);
        for (int j = 0; j < vector.size(); j++) {
            list.push_back(vector.at(j));
        }
    }
    return list;
}

bool contains(vector<string> vector, string str) {
    for (auto & i : vector) {
        if (i == str) {
            return true;
        }
    }
    return false;
}

Graph<string> addEdges() {
    Graph<string> graph = Graph<string>();
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                for (int l = 0; l < 10; l++) {
                    string current = to_string(i) + to_string(j) + to_string(k) + to_string(l);
                    vector<string> subsets = constructCandidates(current);
                    for (int m = 0; m < subsets.size(); m++) {
                        if (!graph.containsKey(current)) {
                            graph.addUnDirectedEdge(current, subsets.at(m));
                        } else if (!contains(graph.get(current), subsets.at(m))) {
                            graph.addUnDirectedEdge(current, subsets.at(m));
                        }
                    }
                }
            }
        }
    }
    return graph;
}

bool breadthFirstSearch(Graph<string> graph, unordered_set<string> edgeList, string current, string target) {
    unordered_map<int, vector<string>> depth = unordered_map<int, vector<string>>();
    int iterate = 1;
    depth[iterate].push_back(current);
    bool find = false;
    do {
        for (int i = 0; i < depth[iterate].size(); i++) {
            string element = depth[iterate].at(i);
            for (int j = 0; j < graph.get(element).size(); j++) {
                if (edgeList.find(graph.get(element, j)) == edgeList.end()) {
                    edgeList.insert(graph.get(element, j));
                    depth[iterate + 1].push_back(graph.get(element, j));
                    if (graph.get(element, j) == target) {
                        cout << iterate << endl;
                        find = true;
                        break;
                    }
                }
            }
        }
        iterate++;
    } while (!depth[iterate].empty());
    return find;
}

int main() {
    fstream file;
    file.open("Wheels.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int times, edgeListSize;
        file >> times;
        string currentWheel, target, current;
        unordered_set<string> edgeList = unordered_set<string>();
        Graph<string> graph = addEdges();
        for (int i = 0; i < times; i++) {
            file >> currentWheel;
            file >> target;
            file >> edgeListSize;
            for (int j = 0; j < edgeListSize; j++) {
                file >> current;
                edgeList.insert(current);
            }
            if (!breadthFirstSearch(graph, edgeList, currentWheel, target)) {
                if (currentWheel == target) {
                    cout << 0 << endl;
                } else {
                    cout << -1 << endl;
                }
            }
            edgeList.clear();
        }
    }
}