//
// Created by Oğuz Kerem Yıldız on 29.12.2020.
//

#include "Graph/Graph.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static int size;

unordered_map<int, vector<int>> constructCandidates(Graph<int> graph, unordered_map<int, vector<int>> sequence) {
    unordered_map<int, vector<int>> subsets = unordered_map<int, vector<int>>();
    for (int key : graph.getKeySet()) {
        if (sequence.find(key) == sequence.end()) {
            subsets[key] = graph.get(key);
        }
    }
    return subsets;
}

bool containsAll(vector<int> vector, unordered_set<int> set) {
    for (int i = 0; i < vector.size(); ++i) {
        if (set.find(vector.at(i)) == set.end()) {
            return false;
        }
    }
    return true;
}

bool isASolution(Graph<int> graph, unordered_map<int, vector<int>> sequence) {
    unordered_set<int> subsetsValues = unordered_set<int>();
    for (auto &key : sequence) {
        for (int i = 0; i < sequence[key.first].size(); i++) {
            subsetsValues.insert(sequence[key.first].at(i));
        }
    }
    return containsAll(graph.getKeySet(), subsetsValues);
}

void backtrack(Graph<int> graph, unordered_map<int, vector<int>> sequence) {
    if (size < sequence.size()) {
        return;
    }
    unordered_map<int, vector<int>> subsets;
    if (isASolution(graph, sequence)){
        size = sequence.size();
    } else {
        subsets = constructCandidates(graph, sequence);
        for (auto &key : subsets) {
            sequence[key.first] = subsets[key.first];
            backtrack(graph, sequence);
            sequence.erase(key.first);
        }
    }
}

int main() {
    fstream file;
    file.open("Service.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        Graph<int> graph = Graph<int>();
        vector<Graph<int>> graphs;
        size = 10000;
        int key, value, graphSize, times;
        while (!file.eof()) {
            file >> graphSize;
            file >> times;
            for (int i = 0; i < times; i++) {
                file >> key;
                key--;
                file >> value;
                value--;
                graph.addUnDirectedEdge(key, value);
            }
            graphs = graph.connectedComponents();
            for (int i = 0; i < graphs.size(); i++) {
                backtrack(graphs.at(i), unordered_map<int, vector<int>>());
                cout << size << endl;
                graph.clear();
                size = 10000;
            }
        }
    }
}