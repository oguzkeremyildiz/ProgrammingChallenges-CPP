//
// Created by Oğuz Kerem Yıldız on 19.01.2021.
//
#include <iostream>
#include <fstream>
#include <unordered_set>
#include "Graph/Graph.h"
#include <vector>

using namespace std;

bool finish(int pegs, Graph<int> graph) {
    bool boolean = true;
    if (graph.size() > pegs) {
        int total = 0;
        for (int key : graph.getKeySet()) {
            if (graph.get(key).empty()) {
                total++;
            }
        }
        if (total == pegs) {
            boolean = false;
        }
    } else {
        return true;
    }
    return boolean;
}

Graph<int> addEdge(unordered_set<int> elements, int pegs) {
    Graph<int> graph = Graph<int>();
    bool boolean;
    int number = 0;
    do {
        number++;
        for (int key : graph.getKeySet()) {
            if (elements.find(key + number) != elements.end()) {
                graph.addDirectedEdge(key, number);
            }
        }
        boolean = finish(pegs, graph);
        if (boolean) {
            graph.put(number, vector<int>());
        }
    } while (boolean);
    return graph;
}

unordered_set<int> addSet() {
    unordered_set<int> set = unordered_set<int>();
    for (int i = 1; i <= 1300; i++) {
        set.insert(i * i);
    }
    return set;
}

int main() {
    fstream file;
    file.open("Hanoi.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        Graph<int> graph;
        unordered_set<int> elements;
        elements = addSet();
        int times, pegs;
        file >> times;
        for (int i = 0; i < times; i++) {
            file >> pegs;
            if (pegs != 1) {
                graph = addEdge(elements, pegs);
                cout << graph.size() << endl;
                graph.clear();
            } else {
                cout << "1" << endl;
            }
        }
    }
}